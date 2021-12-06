/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2015 Anke Boersma <demm@kaosx.us>
 *   SPDX-FileCopyrightText: 2015 Alexandre Arnt <qtgzmanager@gmail.com>
 *   SPDX-FileCopyrightText: 2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef LICENSE_LICENSEWIDGET_H
#define LICENSE_LICENSEWIDGET_H

#include "LicensePage.h"

#include <QLabel>
#include <QWidget>

class QPushButton;

class LicenseWidget : public QWidget
{
    Q_OBJECT
public:
    LicenseWidget( LicenseEntry e, QWidget* parent = nullptr );
    ~LicenseWidget() override;

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
