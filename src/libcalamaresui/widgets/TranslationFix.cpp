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
#include <QMessageBox>

namespace Calamares
{

void
fixButtonLabels( QMessageBox* box )
{
    if ( !box )
    {
        return;
    }

    static std::pair< decltype( QMessageBox::Ok ), const char* > maps[]
        = { { QMessageBox::Ok, QT_TRANSLATE_NOOP( "StandardButtons", "&OK" ) } };

    for ( auto [ sb, label ] : maps )
    {
        auto* button = box->button( sb );
        if ( button )
        {
            button->setText( QCoreApplication::translate( "StandardButtons", label ) );
        }
    }
}

}  // namespace Calamares
