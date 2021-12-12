/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "TranslationFix.h"

#include <QAbstractButton>
#include <QCoreApplication>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QPushButton>

namespace Calamares
{

//Using QMessageBox's StandardButton enum here but according to headers they should be kept in-sync between multiple classes.
static std::pair< decltype( QMessageBox::Ok ), const char* > maps[] = {
    { QMessageBox::Ok, QT_TRANSLATE_NOOP( "StandardButtons", "&OK" ) },
    { QMessageBox::Yes, QT_TRANSLATE_NOOP( "StandardButtons", "&Yes" ) },
    { QMessageBox::No, QT_TRANSLATE_NOOP( "StandardButtons", "&No" ) },
    { QMessageBox::Cancel, QT_TRANSLATE_NOOP( "StandardButtons", "&Cancel" ) },
    { QMessageBox::Close, QT_TRANSLATE_NOOP( "StandardButtons", "&Close" ) },
};

template < typename TButtonBox >
void
fixButtonLabels( TButtonBox* box )
{
    if ( !box )
    {
        return;
    }

    for ( auto [ sb, label ] : maps )
    {
        auto* button = box->button( static_cast< typename TButtonBox::StandardButton >( int( sb ) ) );
        if ( button )
        {
            button->setText( QCoreApplication::translate( "StandardButtons", label ) );
        }
    }
}

void
fixButtonLabels( QMessageBox* box )
{
    fixButtonLabels< QMessageBox >( box );
}

void
fixButtonLabels( QDialogButtonBox* box )
{
    fixButtonLabels< QDialogButtonBox >( box );
}

}  // namespace Calamares
