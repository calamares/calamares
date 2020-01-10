/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2015, Anke Boersma <demm@kaosx.us>
 *   Copyright 2015, Alexandre Arnt <qtgzmanager@gmail.com>
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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

#ifndef LICENSE_LICENSEWIDGET_H
#define LICENSE_LICENSEWIDGET_H

#include "LicensePage.h"

#include <QLabel>
#include <QWidget>

class QPushButton;

class LicenseWidget : public QWidget
{
public:
    LicenseWidget( LicenseEntry e, QWidget* parent = nullptr );
    virtual ~LicenseWidget() override;

    void retranslateUi();

private:
    void showLocalLicenseText();  // Display (or hide) the local license text
    void expandClicked();  // "slot" to toggle show/hide of local license text
    void viewClicked();  // "slot" to open link
    void updateExpandToolTip();

    LicenseEntry m_entry;
    QLabel* m_label;
    QPushButton* m_viewLicenseButton;
    QLabel* m_licenceTextLabel;
    QString m_fullTextContents;
    bool m_isExpanded;
};
#endif
