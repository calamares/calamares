/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2007 Free Software Foundation, Inc.
 *   SPDX-FileCopyrightText: 2014-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Portions from the Manjaro Installation Framework
 *   by Roland Singer <roland@manjaro.org>
 *   Copyright (C) 2007 Free Software Foundation, Inc.
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "KeyboardPage.h"

#include "Config.h"
#include "KeyboardLayoutModel.h"
#include "SetKeyboardLayoutJob.h"
#include "keyboardwidget/keyboardpreview.h"
#include "ui_KeyboardPage.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "utils/String.h"

#include <QComboBox>
#include <QProcess>
#include <QPushButton>

class LayoutItem : public QListWidgetItem
{
public:
    QString data;

    ~LayoutItem() override;
};

LayoutItem::~LayoutItem() {}

KeyboardPage::KeyboardPage( Config* config, QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::Page_Keyboard )
    , m_keyboardPreview( new KeyBoardPreview( this ) )
{
    ui->setupUi( this );

    // Keyboard Preview
    ui->KBPreviewLayout->addWidget( m_keyboardPreview );

    ui->comboBoxModel->setModel( config->keyboardModels() );
    // Connect signals and slots
    connect( ui->listVariant, &QListWidget::currentItemChanged, this, &KeyboardPage::onListVariantCurrentItemChanged );

    connect(
        ui->buttonRestore, &QPushButton::clicked, [this] {
            cDebug() << "Restore clicked";
            // ui->comboBoxModel->setCurrentIndex( m_defaultIndex );
        } );

    connect( ui->comboBoxModel, &QComboBox::currentTextChanged, [this]( const QString& text ) {
        cDebug() << "ComboBox changed to" << text;
        // QString model = m_models.value( text, "pc105" );

        // Set Xorg keyboard model
        // QProcess::execute( "setxkbmap", QStringList { "-model", model } );
    } );

    CALAMARES_RETRANSLATE( ui->retranslateUi( this ); )
}


KeyboardPage::~KeyboardPage()
{
    delete ui;
}

void
KeyboardPage::updateVariants( const QPersistentModelIndex& currentItem, QString currentVariant )
{
    // Block signals
    ui->listVariant->blockSignals( true );

    QMap< QString, QString > variants
        = currentItem.data( KeyboardLayoutModel::KeyboardVariantsRole ).value< QMap< QString, QString > >();
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
        {
            defaultItem = item;
        }
    }

    // Unblock signals
    ui->listVariant->blockSignals( false );

    // Set to default value
    if ( defaultItem )
    {
        ui->listVariant->setCurrentItem( defaultItem );
    }
}


void
KeyboardPage::onListLayoutCurrentItemChanged( const QModelIndex& current, const QModelIndex& previous )
{
    Q_UNUSED( previous )
    if ( !current.isValid() )
    {
        return;
    }

    updateVariants( QPersistentModelIndex( current ) );
}

void
KeyboardPage::onListVariantCurrentItemChanged( QListWidgetItem* current, QListWidgetItem* previous )
{
    Q_UNUSED( previous )

    cDebug() << "item" << Logger::Pointer( current );

    QPersistentModelIndex layoutIndex = ui->listLayout->currentIndex();
    LayoutItem* variantItem = dynamic_cast< LayoutItem* >( current );

    if ( !layoutIndex.isValid() || !variantItem )
    {
        return;
    }

    QString layout = layoutIndex.data( KeyboardLayoutModel::KeyboardLayoutKeyRole ).toString();
    QString variant = variantItem->data;

    cDebug() << Logger::SubEntry << layout << variant;

    m_keyboardPreview->setLayout( layout );
    m_keyboardPreview->setVariant( variant );
}
