#include "NetInstallPage.h"

#include "./widgets/groupselectionwidget.h"
#include "ui_page_netinst.h"
#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/Logger.h"

#include <QFile>
#include <QMap>
#include <QTextStream>

#include <KIO/Job>
#include <KIO/StoredTransferJob>

#include <QtDebug>
#include <QtGlobal>
#include <QWidget>

#include <yaml-cpp/yaml.h>


NetInstallPage::NetInstallPage( QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::Page_NetInst )
{
    ui->setupUi( this );
}

bool
NetInstallPage::isReady()
{
    // nothing to wait for, the data are immediately ready
    // if the user does not select any group nothing is installed
    return true;
}

void NetInstallPage::ReadGroups( const QByteArray& yamlData )
{
    YAML::Node groups = YAML::Load( yamlData.constData() );
    Q_ASSERT( groups.IsSequence() );

    for ( YAML::const_iterator it = groups.begin(); it != groups.end(); ++it )
    {
        YAML::Node groupDefinition = it->as<YAML::Node>();

        QString name( tr( groupDefinition["name"].as<std::string>().c_str() ) );
        QString description( tr( groupDefinition["description"].as<std::string>().c_str() ) );
        QStringList packages;

        for ( YAML::const_iterator it = groupDefinition["packages"].begin();
                it != groupDefinition["packages"].end(); ++it )
            packages.append( ( *it ).as<std::string>().c_str() );

        m_groups[name].name = name;
        m_groups[name].description = description;
        m_groups[name].packages = packages;

        if ( groupDefinition["selected"] )
            m_groups[name].selected = groupDefinition["selected"].as<bool>();

        if ( groupDefinition["hidden"] )
            m_groups[name].hidden = groupDefinition["hidden"].as<bool>();

        m_groupOrder.append( name );
    }
}

void
NetInstallPage::dataIsHere( KJob* job )
{
    if ( job->error() )
    {
        qDebug() << job->errorString();
        ui->netinst_status->setText( tr( "Network Installation. (Disabled: Unable to fetch package lists, check your network connection)" ) );
        return;
    }

    auto transferJob = dynamic_cast<KIO::StoredTransferJob*>( job );
    Q_ASSERT( transferJob != nullptr );
    ReadGroups( transferJob->data() );

    QSignalMapper* mapper = new QSignalMapper( this );
    foreach ( const QString& groupKey, m_groupOrder )
    {
        Group group = m_groups[groupKey];
        if ( group.hidden )
        {
            // Do not present on view.
            continue;
        }

        GroupSelectionWidget* groupWidget = new GroupSelectionWidget( group.name, group.description, group.packages, this );
        m_groupWidgets.insert( groupKey, groupWidget );
        ui->groupswidget->layout()->addWidget( groupWidget );

        mapper->setMapping( groupWidget, groupKey );
        connect( groupWidget, SIGNAL( toggled( bool ) ), mapper, SLOT( map() ) );
    }

    // TODO
    emit checkReady( isReady() );
}

QStringList NetInstallPage::selectedPackages() const
{
    QStringList selectedPackages;

    // Add all the packages for groups that are toggled in the view.
    for ( auto it = m_groupWidgets.constBegin(); it != m_groupWidgets.constEnd(); it++ )
    {
        if ( it.value()->isToggled() )
            selectedPackages += m_groups[it.key()].packages;
    }

    // Add all the packages for groups that are hidden but selected.
    for ( const Group& group : m_groups.values() )
    {
        if ( group.hidden && group.selected )
            selectedPackages += group.packages;
    }

    return selectedPackages;
}

void NetInstallPage::loadGroupList()
{
    QString confUrl(
        Calamares::JobQueue::instance()->globalStorage()->value(
            "groupsUrl" ).toString() );

    KIO::Job* getJob = KIO::storedGet( confUrl, KIO::Reload, KIO::Overwrite | KIO::HideProgressInfo );
    connect ( getJob, SIGNAL(  result( KJob* ) ), this, SLOT( dataIsHere( KJob* ) ) );
}

void NetInstallPage::onActivate()
{
    ui->groupswidget->setFocus();
}
