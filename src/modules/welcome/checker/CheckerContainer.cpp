/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2017, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, 2019-2020, Adriaan de Groot <groot@kde.org>
 *   Copyright 2017, Gabriel Craciunescu <crazy@frugalware.org>
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

/* Based on code extracted from RequirementsChecker.cpp */

#include "CheckerContainer.h"

#include "ResultsListWidget.h"

#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "widgets/WaitingWidget.h"

#include <QHBoxLayout>

CheckerContainer::CheckerContainer( const Calamares::RequirementsModel &model, QWidget* parent )
    : QWidget( parent )
    , m_waitingWidget( new WaitingWidget( QString(), this ) )
    , m_checkerWidget( nullptr )
    , m_verdict( false )
    , m_model( model )
{
    QBoxLayout* mainLayout = new QHBoxLayout;
    setLayout( mainLayout );
    CalamaresUtils::unmarginLayout( mainLayout );

    mainLayout->addWidget( m_waitingWidget );
    CALAMARES_RETRANSLATE( if ( m_waitingWidget ) m_waitingWidget->setText( tr( "Gathering system information..." ) ); )
}

CheckerContainer::~CheckerContainer()
{
    delete m_waitingWidget;
    delete m_checkerWidget;
}

void
CheckerContainer::requirementsComplete( bool ok )
{

    layout()->removeWidget( m_waitingWidget );
    m_waitingWidget->deleteLater();
    m_waitingWidget = nullptr;  // Don't delete in destructor

    m_checkerWidget = new ResultsListWidget( m_model, this);
    layout()->addWidget( m_checkerWidget );

    m_verdict = ok;
}

void
CheckerContainer::requirementsProgress( const QString& message )
{
    if ( m_waitingWidget )
    {
        m_waitingWidget->setText( message );
    }
}

bool
CheckerContainer::verdict() const
{
    return m_verdict;
}
