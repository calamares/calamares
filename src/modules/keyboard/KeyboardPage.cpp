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
    , m_config( config )
{
    ui->setupUi( this );

    // Keyboard Preview
    ui->KBPreviewLayout->addWidget( m_keyboardPreview );

    {
        auto* model = config->keyboardModels();
        model->setCurrentIndex();  // To default PC105
        ui->physicalModelSelector->setModel( model );
        ui->physicalModelSelector->setCurrentIndex( model->currentIndex() );
    }
    {
        auto* model = config->keyboardLayouts();
        ui->layoutSelector->setModel( model );
        ui->layoutSelector->setCurrentIndex( model->index( model->currentIndex() ) );
    }
    {
        auto* model = config->keyboardVariants();
        ui->variantSelector->setModel( model );
        ui->variantSelector->setCurrentIndex( model->index( model->currentIndex() ) );
        cDebug() << "Variants now total=" << model->rowCount() << "selected=" << model->currentIndex();
    }

    connect( ui->buttonRestore,
             &QPushButton::clicked,
             [ config = config ] { config->keyboardModels()->setCurrentIndex(); } );

    connect( ui->physicalModelSelector,
             QOverload< int >::of( &QComboBox::currentIndexChanged ),
             config->keyboardModels(),
             QOverload< int >::of( &XKBListModel::setCurrentIndex ) );
    connect( config->keyboardModels(),
             &KeyboardModelsModel::currentIndexChanged,
             ui->physicalModelSelector,
             &QComboBox::setCurrentIndex );

    connect( ui->layoutSelector->selectionModel(),
             &QItemSelectionModel::currentChanged,
             [ this ]( const QModelIndex& current )
             { m_config->keyboardLayouts()->setCurrentIndex( current.row() ); } );
    connect( config->keyboardLayouts(),
             &KeyboardLayoutModel::currentIndexChanged,
             [ this ]( int index )
             {
                 ui->layoutSelector->setCurrentIndex( m_config->keyboardLayouts()->index( index ) );
                 m_keyboardPreview->setLayout( m_config->keyboardLayouts()->key( index ) );
                 m_keyboardPreview->setVariant(
                     m_config->keyboardVariants()->key( m_config->keyboardVariants()->currentIndex() ) );
             } );

    connect( ui->variantSelector->selectionModel(),
             &QItemSelectionModel::currentChanged,
             [ this ]( const QModelIndex& current )
             { m_config->keyboardVariants()->setCurrentIndex( current.row() ); } );
    connect( config->keyboardVariants(),
             &KeyboardVariantsModel::currentIndexChanged,
             [ this ]( int index )
             {
                 ui->variantSelector->setCurrentIndex( m_config->keyboardVariants()->index( index ) );
                 m_keyboardPreview->setVariant( m_config->keyboardVariants()->key( index ) );
             } );
    CALAMARES_RETRANSLATE_SLOT( &KeyboardPage::retranslate );
}

KeyboardPage::~KeyboardPage()
{
    delete ui;
}

void
KeyboardPage::retranslate()
{
    ui->retranslateUi( this );
    m_config->retranslate();
}
