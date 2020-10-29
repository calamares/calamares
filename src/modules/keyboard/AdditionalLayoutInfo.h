/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Artem Grinev <agrinev@manjaro.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef KEYBOARD_ADDITIONAL_LAYOUT_INFO_H
#define KEYBOARD_ADDITIONAL_LAYOUT_INFO_H

#include <QString>

struct AdditionalLayoutInfo
{
    QString additionalLayout;
    QString additionalVariant;

    QString groupSwitcher;

    QString vconsoleKeymap;
};

#endif
