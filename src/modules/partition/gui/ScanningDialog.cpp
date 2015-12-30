/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
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

#include "ScanningDialog.h"

#include "widgets/QtWaitingSpinner.h"

#include <QBoxLayout>
#include <QLabel>


ScanningDialog::ScanningDialog(const QString& text, QWidget* parent)
    : QDialog( parent )
{
    setModal( true );

    QHBoxLayout* dialogLayout = new QHBoxLayout;
    setLayout( dialogLayout );

    QtWaitingSpinner* spinner = new QtWaitingSpinner;
    dialogLayout->addWidget( spinner );
    spinner->start();

    QLabel* rescanningLabel = new QLabel( text,
                                          this );
    dialogLayout->addWidget( rescanningLabel );
}

void ScanningDialog::setVisible(bool visible)
{
    QDialog::setVisible( visible );
    emit visibilityChanged();
}
