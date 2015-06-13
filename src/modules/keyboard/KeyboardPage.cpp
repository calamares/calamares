/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"

#include <QComboBox>
#include <QProcess>
#include <QPushButton>


KeyboardPage::KeyboardPage( QWidget* parent )
    : QWidget()
    , ui( new Ui::Page_Keyboard )
    , m_keyboardPreview( new KeyBoardPreview( this ) )
    , m_defaultIndex( 0 )
{
    ui->setupUi( this );

    // Keyboard Preview
    ui->KBPreviewLayout->addWidget( m_keyboardPreview );

    // Connect signals and slots
    connect( ui->listLayout, &QListWidget::currentItemChanged,
             this, &KeyboardPage::onListLayoutCurrentItemChanged );
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
        QProcess::execute( QString( "setxkbmap -model \"%1\"" )
                           .arg( model ).toUtf8() );
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
        QStringList list = QString( process.readAll() )
                           .split( "\n", QString::SkipEmptyParts );

        foreach( QString line, list )
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

    // Block signals
    ui->listLayout->blockSignals( true );

    QMap< QString, KeyboardGlobal::KeyboardInfo > layouts =
            KeyboardGlobal::getKeyboardLayouts();
    QMapIterator< QString, KeyboardGlobal::KeyboardInfo > li( layouts );
    LayoutItem* currentLayoutItem = nullptr;

    while ( li.hasNext() )
    {
        li.next();

        LayoutItem* item = new LayoutItem();
        KeyboardGlobal::KeyboardInfo info = li.value();

        item->setText( info.description );
        item->data = li.key();
        item->info = info;
        ui->listLayout->addItem( item );

        // Find current layout index
        if ( li.key() == currentLayout )
            currentLayoutItem = item;
    }

    ui->listLayout->sortItems();

    // Set current layout and variant
    if ( currentLayoutItem )
    {
        ui->listLayout->setCurrentItem( currentLayoutItem );
        updateVariants( currentLayoutItem, currentVariant );
    }

    // Unblock signals
    ui->listLayout->blockSignals( false );

    // Default to the first available layout if none was set
    // Do this after unblocking signals so we get the default variant handling.
    if ( !currentLayoutItem && ui->listLayout->count() > 0 )
        ui->listLayout->setCurrentRow( 0 );
}


QString
KeyboardPage::prettyStatus() const
{
    QString status;
    status += tr( "Set keyboard model to %1.<br/>" )
              .arg( ui->comboBoxModel->currentText() );
    status += tr( "Set keyboard layout to %1/%2." )
              .arg( ui->listLayout->currentItem()->text() )
              .arg( ui->listVariant->currentItem()->text() );

    return status;
}


QList< Calamares::job_ptr >
KeyboardPage::createJobs( const QString& xOrgConfFileName,
                          const QString& convertedKeymapPath )
{
    QList< Calamares::job_ptr > list;
    QString selectedModel = m_models.value( ui->comboBoxModel->currentText(),
                                            "pc105" );

    Calamares::Job* j = new SetKeyboardLayoutJob( selectedModel,
                                                  m_selectedLayout,
                                                  m_selectedVariant,
                                                  xOrgConfFileName,
                                                  convertedKeymapPath );
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
KeyboardPage::updateVariants( LayoutItem* currentItem, QString currentVariant )
{
    // Block signals
    ui->listVariant->blockSignals( true );

    QMap< QString, QString > variants = currentItem->info.variants;
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
KeyboardPage::onListLayoutCurrentItemChanged( QListWidgetItem* current, QListWidgetItem* previous )
{
    LayoutItem* item = dynamic_cast< LayoutItem* >( current );
    if ( !item )
       return;

    updateVariants( item );
}


void
KeyboardPage::onListVariantCurrentItemChanged( QListWidgetItem* current, QListWidgetItem* previous )
{
    LayoutItem* layoutItem = dynamic_cast< LayoutItem* >( ui->listLayout->currentItem() );
    LayoutItem* variantItem = dynamic_cast< LayoutItem* >( current );

    if ( !layoutItem || !variantItem )
        return;

    QString layout = layoutItem->data;
    QString variant = variantItem->data;

    m_keyboardPreview->setLayout( layout );
    m_keyboardPreview->setVariant( variant );

    //emit checkReady();

    // Set Xorg keyboard layout
    QProcess::execute( QString( "setxkbmap -layout \"%1\" -variant \"%2\"" )
                       .arg( layout, variant ).toUtf8() );

    m_selectedLayout = layout;
    m_selectedVariant = variant;
    cDebug() << "xkbmap selection changed to: " << layout << "-" << variant;
}

