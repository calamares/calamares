/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2017 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2017 Gabriel Craciunescu <crazy@frugalware.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

/* Based on code extracted from RequirementsChecker.cpp */

#include "CheckerContainer.h"

#include "ResultsListWidget.h"

#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "widgets/WaitingWidget.h"

#include <QHBoxLayout>

CheckerContainer::CheckerContainer( Config* config, QWidget* parent )
    : QWidget( parent )
    , m_waitingWidget( new WaitingWidget( QString(), this ) )
    , m_checkerWidget( nullptr )
    , m_verdict( false )
    , m_config( config )
{
    QBoxLayout* mainLayout = new QHBoxLayout;
    setLayout( mainLayout );
    CalamaresUtils::unmarginLayout( mainLayout );

    mainLayout->addWidget( m_waitingWidget );
    CALAMARES_RETRANSLATE( if ( m_waitingWidget )
                               m_waitingWidget->setText( tr( "Gathering system information..." ) ); );
}

CheckerContainer::~CheckerContainer()
{
    delete m_waitingWidget;
    delete m_checkerWidget;
}

void
CheckerContainer::requirementsComplete( bool ok )
{
    if ( !ok )
    {
        auto& model = *( m_config->requirementsModel() );
        cDebug() << "Requirements not satisfied" << model.count() << "entries:";
        for ( int i = 0; i < model.count(); ++i )
        {
            auto index = model.index( i );
            const bool satisfied = model.data( index, Calamares::RequirementsModel::Satisfied ).toBool();
            const bool mandatory = model.data( index, Calamares::RequirementsModel::Mandatory ).toBool();
            if ( !satisfied )
            {
                cDebug() << Logger::SubEntry << i << model.data( index, Calamares::RequirementsModel::Name ).toString()
                         << "not-satisfied"
                         << "mandatory?" << mandatory;
            }
        }
    }

    if ( m_waitingWidget )
    {
        layout()->removeWidget( m_waitingWidget );
        m_waitingWidget->deleteLater();
        m_waitingWidget = nullptr;  // Don't delete in destructor
    }
    if ( !m_checkerWidget )
    {
        m_checkerWidget = new ResultsListWidget( m_config, this );
        m_checkerWidget->setObjectName( "requirementsChecker" );
        layout()->addWidget( m_checkerWidget );
    }
    m_checkerWidget->requirementsComplete();

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
