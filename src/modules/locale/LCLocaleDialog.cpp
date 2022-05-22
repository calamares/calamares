/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "LCLocaleDialog.h"

#include <QBoxLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>

LCLocaleDialog::LCLocaleDialog( const QString& guessedLCLocale, const QStringList& localeGenLines, QWidget* parent )
    : QDialog( parent )
{
    setModal( true );
    setWindowTitle( tr( "System locale setting" ) );

    QBoxLayout* mainLayout = new QVBoxLayout;
    setLayout( mainLayout );

    QLabel* upperText = new QLabel( this );
    upperText->setWordWrap( true );
    upperText->setText( tr( "The system locale setting affects the language and character "
                            "set for some command line user interface elements.<br/>"
                            "The current setting is <strong>%1</strong>." )
                            .arg( guessedLCLocale ) );
    mainLayout->addWidget( upperText );
    setMinimumWidth( upperText->fontMetrics().height() * 24 );

    m_localesWidget = new QListWidget( this );
    m_localesWidget->addItems( localeGenLines );
    m_localesWidget->setSelectionMode( QAbstractItemView::SingleSelection );
    mainLayout->addWidget( m_localesWidget );

    int selected = -1;
    for ( int i = 0; i < localeGenLines.count(); ++i )
    {
        if ( localeGenLines[ i ].contains( guessedLCLocale ) )
        {
            selected = i;
            break;
        }
    }

    QDialogButtonBox* dbb
        = new QDialogButtonBox( QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this );
    dbb->button( QDialogButtonBox::Cancel )->setText( tr( "&Cancel" ) );
    dbb->button( QDialogButtonBox::Ok )->setText( tr( "&OK" ) );

    mainLayout->addWidget( dbb );

    connect( dbb->button( QDialogButtonBox::Ok ), &QPushButton::clicked, this, &QDialog::accept );
    connect( dbb->button( QDialogButtonBox::Cancel ), &QPushButton::clicked, this, &QDialog::reject );

    connect( m_localesWidget, &QListWidget::itemDoubleClicked, this, &QDialog::accept );
    connect( m_localesWidget,
             &QListWidget::itemSelectionChanged,
             [ this, dbb ]()
             {
                 if ( m_localesWidget->selectedItems().isEmpty() )
                 {
                     dbb->button( QDialogButtonBox::Ok )->setEnabled( false );
                 }
                 else
                 {
                     dbb->button( QDialogButtonBox::Ok )->setEnabled( true );
                 }
             } );

    if ( selected > -1 )
    {
        m_localesWidget->setCurrentRow( selected );
    }
}


QString
LCLocaleDialog::selectedLCLocale()
{
    return m_localesWidget->selectedItems().first()->text();
}
