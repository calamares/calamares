/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#include "SummaryPage.h"

#include "ViewManager.h"
#include "viewpages/ViewStep.h"

#include <QBoxLayout>
#include <QLabel>


SummaryPage::SummaryPage( QWidget* parent )
    : QWidget()
{
    QBoxLayout *mainLayout = new QVBoxLayout;
    setLayout( mainLayout );

    mainLayout->addStretch();

    m_label = new QLabel( this );
    mainLayout->addWidget( m_label );
    m_label->setWordWrap( true );

    mainLayout->addStretch();
}


void
SummaryPage::onActivate()
{
    QString text;
    foreach ( Calamares::ViewStep* step,
              Calamares::ViewManager::instance()->prepareSteps() )
    {
        //TODO: make it nice!
        if ( !step->prettyStatus().isEmpty() )
        {
            if ( !text.isEmpty() )
                text += "<br/><br/>";

            text += "<h3>" + step->prettyName() +
                    "</h3><br/>" + step->prettyStatus();
        }
    }

    m_label->setText( text );
}
