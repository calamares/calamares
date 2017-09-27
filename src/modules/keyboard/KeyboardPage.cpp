/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
 *
 *   Portions from the Manjaro Installation Framework
 *   by Roland Singer <roland@manjaro.org>
 *   Copyright (C) 2007 Free Software Foundation, Inc.
 *
 *   Calamares is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Calamares is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
 */

#include "KeyboardPage.h"

#include "ui_KeyboardPage.h"
#include "keyboardwidget/keyboardpreview.h"
#include "SetKeyboardLayoutJob.h"
#include "KeyboardLayoutModel.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"

#include <QComboBox>
#include <QProcess>
#include <QPushButton>

class LayoutItem : public QListWidgetItem
{
public:
    QString data;

    virtual ~LayoutItem();
};

LayoutItem::~LayoutItem()
{
}

static QPersistentModelIndex
findLayout( const KeyboardLayoutModel* klm, const QString& currentLayout )
{
    QPersistentModelIndex currentLayoutItem;

    for ( int i = 0; i < klm->rowCount(); ++i )
    {
        QModelIndex idx = klm->index( i );
        if ( idx.isValid() &&
             idx.data( KeyboardLayoutModel::KeyboardLayoutKeyRole ).toString() == currentLayout )
            currentLayoutItem = idx;
    }

    return currentLayoutItem;
}

KeyboardPage::KeyboardPage( QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::Page_Keyboard )
    , m_keyboardPreview( new KeyBoardPreview( this ) )
    , m_defaultIndex( 0 )
{
    ui->setupUi( this );

    // Keyboard Preview
    ui->KBPreviewLayout->addWidget( m_keyboardPreview );

    m_setxkbmapTimer.setSingleShot( true );

    // Connect signals and slots
    connect( ui->listVariant, &QListWidget::currentItemChanged,
             this, &KeyboardPage::onListVariantCurrentItemChanged );

    connect( ui->buttonRestore, &QPushButton::clicked,
             [this]
    {
        ui->comboBoxModel->setCurrentIndex( m_defaultIndex );
    });

    connect( ui->comboBoxModel,
             static_cast< void ( QComboBox::* )( const QString& ) >( &QComboBox::currentIndexChanged ),
             [this]( const QString& text )
    {
        QString model = m_models.value( text, "pc105" );

        // Set Xorg keyboard model
        QProcess::execute( QLatin1Literal( "setxkbmap" ),
                           QStringList() << "-model" << model );
    });

    CALAMARES_RETRANSLATE( ui->retranslateUi( this ); )
}


KeyboardPage::~KeyboardPage()
{
    delete ui;
}


void
KeyboardPage::init()
{
    //### Detect current keyboard layout and variant
    QString currentLayout;
    QString currentVariant;
    QProcess process;
    process.start( "setxkbmap", QStringList() << "-print" );

    if ( process.waitForFinished() )
    {
        const QStringList list = QString( process.readAll() )
                           .split( "\n", QString::SkipEmptyParts );

        for ( QString line : list )
        {
            line = line.trimmed();
            if ( !line.startsWith( "xkb_symbols" ) )
                continue;

            line = line.remove( "}" )
                       .remove( "{" )
                       .remove( ";" );
            line = line.mid( line.indexOf( "\"" ) + 1 );

            QStringList split = line.split( "+", QString::SkipEmptyParts );
            if ( split.size() >= 2 )
            {
                currentLayout = split.at( 1 );

                if ( currentLayout.contains( "(" ) )
                {
                    int parenthesisIndex = currentLayout.indexOf( "(" );
                    currentVariant = currentLayout.mid( parenthesisIndex + 1 )
                                                  .trimmed();
                    currentVariant.chop( 1 );
                    currentLayout = currentLayout
                                    .mid( 0, parenthesisIndex )
                                    .trimmed();
                }

                break;
            }
        }
    }

    //### Models
    m_models = KeyboardGlobal::getKeyboardModels();
    QMapIterator< QString, QString > mi( m_models );

    ui->comboBoxModel->blockSignals( true );

    while ( mi.hasNext() )
    {
        mi.next();

        if ( mi.value() == "pc105" )
            m_defaultIndex = ui->comboBoxModel->count();

        ui->comboBoxModel->addItem( mi.key() );
    }

    ui->comboBoxModel->blockSignals( false );

    // Set to default value pc105
    ui->comboBoxModel->setCurrentIndex( m_defaultIndex );


    //### Layouts and Variants

    KeyboardLayoutModel* klm = new KeyboardLayoutModel( this );
    ui->listLayout->setModel( klm );
    connect( ui->listLayout->selectionModel(), &QItemSelectionModel::currentChanged,
             this, &KeyboardPage::onListLayoutCurrentItemChanged );

    // Block signals
    ui->listLayout->blockSignals( true );

    QPersistentModelIndex currentLayoutItem = findLayout( klm, currentLayout );
    if ( !currentLayoutItem.isValid() && (
           ( currentLayout == "latin" )
        || ( currentLayout == "pc" ) ) )
    {
        currentLayout = "us";
        currentLayoutItem = findLayout( klm, currentLayout );
    }

    // Set current layout and variant
    if ( currentLayoutItem.isValid() )
    {
        ui->listLayout->setCurrentIndex( currentLayoutItem );
        updateVariants( currentLayoutItem, currentVariant );
    }

    // Unblock signals
    ui->listLayout->blockSignals( false );

    // Default to the first available layout if none was set
    // Do this after unblocking signals so we get the default variant handling.
    if ( !currentLayoutItem.isValid() && klm->rowCount() > 0 )
        ui->listLayout->setCurrentIndex( klm->index( 0 ) );
}


QString
KeyboardPage::prettyStatus() const
{
    QString status;
    status += tr( "Set keyboard model to %1.<br/>" )
              .arg( ui->comboBoxModel->currentText() );
    status += tr( "Set keyboard layout to %1/%2." )
              .arg( ui->listLayout->currentIndex().data().toString() )
              .arg( ui->listVariant->currentItem()->text() );

    return status;
}


QList< Calamares::job_ptr >
KeyboardPage::createJobs( const QString& xOrgConfFileName,
                          const QString& convertedKeymapPath,
                          bool writeEtcDefaultKeyboard )
{
    QList< Calamares::job_ptr > list;
    QString selectedModel = m_models.value( ui->comboBoxModel->currentText(),
                                            "pc105" );

    Calamares::Job* j = new SetKeyboardLayoutJob( selectedModel,
                                                  m_selectedLayout,
                                                  m_selectedVariant,
                                                  xOrgConfFileName,
                                                  convertedKeymapPath,
                                                  writeEtcDefaultKeyboard );
    list.append( Calamares::job_ptr( j ) );

    return list;
}


void
KeyboardPage::onActivate()
{
    ui->listLayout->setFocus();
}


void
KeyboardPage::finalize()
{
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    if ( !m_selectedLayout.isEmpty() )
    {
        gs->insert( "keyboardLayout", m_selectedLayout );
        gs->insert( "keyboardVariant", m_selectedVariant ); //empty means default variant
    }

    //FIXME: also store keyboard model for something?
}


void
KeyboardPage::updateVariants( const QPersistentModelIndex& currentItem,
                              QString currentVariant )
{
    // Block signals
    ui->listVariant->blockSignals( true );

    QMap< QString, QString > variants =
            currentItem.data( KeyboardLayoutModel::KeyboardVariantsRole )
                       .value< QMap< QString, QString > >();
    QMapIterator< QString, QString > li( variants );
    LayoutItem* defaultItem = nullptr;

    ui->listVariant->clear();

    while ( li.hasNext() )
    {
       li.next();

       LayoutItem* item = new LayoutItem();
       item->setText( li.key() );
       item->data = li.value();
       ui->listVariant->addItem( item );

       // currentVariant defaults to QString(). It is only non-empty during the
       // initial setup.
       if ( li.value() == currentVariant )
           defaultItem = item;
    }

    // Unblock signals
    ui->listVariant->blockSignals( false );

    // Set to default value
    if ( defaultItem )
       ui->listVariant->setCurrentItem( defaultItem );
}


void
KeyboardPage::onListLayoutCurrentItemChanged( const QModelIndex& current,
                                              const QModelIndex& previous )
{
    Q_UNUSED( previous );
    if ( !current.isValid() )
        return;

    updateVariants( QPersistentModelIndex( current ) );
}

/* Returns stringlist with suitable setxkbmap command-line arguments
 * to set the given @p layout and @p variant.
 */
static inline QStringList xkbmap_args( QStringList&& r, const QString& layout, const QString& variant)
{
    r << "-layout" << layout;
    if ( !variant.isEmpty() )
        r << "-variant" << variant;
    return r;
}

void
KeyboardPage::onListVariantCurrentItemChanged( QListWidgetItem* current, QListWidgetItem* previous )
{
    Q_UNUSED( previous );

    QPersistentModelIndex layoutIndex = ui->listLayout->currentIndex();
    LayoutItem* variantItem = dynamic_cast< LayoutItem* >( current );

    if ( !layoutIndex.isValid() || !variantItem )
        return;

    QString layout = layoutIndex.data( KeyboardLayoutModel::KeyboardLayoutKeyRole ).toString();
    QString variant = variantItem->data;

    m_keyboardPreview->setLayout( layout );
    m_keyboardPreview->setVariant( variant );

    //emit checkReady();

    // Set Xorg keyboard layout
    if ( m_setxkbmapTimer.isActive() )
    {
        m_setxkbmapTimer.stop();
        m_setxkbmapTimer.disconnect( this );
    }

    connect( &m_setxkbmapTimer, &QTimer::timeout,
             this, [=]
    {
        QProcess::execute( QLatin1Literal( "setxkbmap" ),
                           xkbmap_args( QStringList(), layout, variant ) );
        cDebug() << "xkbmap selection changed to: " << layout << "-" << variant;
        m_setxkbmapTimer.disconnect( this );
    } );
    m_setxkbmapTimer.start( QApplication::keyboardInputInterval() );

    m_selectedLayout = layout;
    m_selectedVariant = variant;
}
