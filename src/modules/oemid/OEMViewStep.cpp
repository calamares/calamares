/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "OEMViewStep.h"

#include "ui_OEMPage.h"

#include "IDJob.h"

#include "utils/Retranslator.h"
#include "utils/Variant.h"

#include <QDate>
#include <QLabel>
#include <QWidget>

class OEMPage : public QWidget
{
public:
    OEMPage()
        : QWidget( nullptr )
        , m_ui( new Ui_OEMPage() )
    {
        m_ui->setupUi( this );

        CALAMARES_RETRANSLATE( m_ui->retranslateUi( this ); );
    }

    ~OEMPage() override;

    Ui_OEMPage* m_ui;
};

OEMPage::~OEMPage() {}


OEMViewStep::OEMViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_widget( nullptr )
    , m_visited( false )
{
}

OEMViewStep::~OEMViewStep()
{
    if ( m_widget && m_widget->parent() == nullptr )
    {
        m_widget->deleteLater();
    }
}

bool
OEMViewStep::isBackEnabled() const
{
    return true;
}

bool
OEMViewStep::isNextEnabled() const
{
    return true;
}

bool
OEMViewStep::isAtBeginning() const
{
    return true;
}

bool
OEMViewStep::isAtEnd() const
{
    return true;
}

static QString
substitute( QString s )
{
    QString t_date = QStringLiteral( "@@DATE@@" );
    if ( s.contains( t_date ) )
    {
        auto date = QDate::currentDate();
        s = s.replace( t_date, date.toString( Qt::ISODate ) );
    }

    return s;
}

void
OEMViewStep::onActivate()
{
    if ( !m_widget )
    {
        (void)widget();
    }
    if ( !m_visited && m_widget )
    {
        m_widget->m_ui->batchIdentifier->setText( m_user_batchIdentifier );
    }
    m_visited = true;

    ViewStep::onActivate();
}

void
OEMViewStep::onLeave()
{
    m_user_batchIdentifier = m_widget->m_ui->batchIdentifier->text();

    ViewStep::onLeave();
}

QString
OEMViewStep::prettyName() const
{
    return tr( "OEM Configuration" );
}

QString
OEMViewStep::prettyStatus() const
{
    return tr( "Set the OEM Batch Identifier to <code>%1</code>." ).arg( m_user_batchIdentifier );
}


QWidget*
OEMViewStep::widget()
{
    if ( !m_widget )
    {
        m_widget = new OEMPage;
    }
    return m_widget;
}

Calamares::JobList
OEMViewStep::jobs() const
{
    return Calamares::JobList() << Calamares::job_ptr( new IDJob( m_user_batchIdentifier ) );
}

void
OEMViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    m_conf_batchIdentifier = CalamaresUtils::getString( configurationMap, "batch-identifier" );
    m_user_batchIdentifier = substitute( m_conf_batchIdentifier );
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( OEMViewStepFactory, registerPlugin< OEMViewStep >(); )
