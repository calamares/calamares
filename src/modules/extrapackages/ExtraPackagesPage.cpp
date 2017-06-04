/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright (c) 2016-2017, Kyle Robbertze, AIMS, South Africa
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

#include "ExtraPackagesPage.h"

#include "Branding.h"
#include "GlobalStorage.h"
#include "InstallPackageJob.h"
#include "JobQueue.h"
#include "SetSourcesJob.h"
#include "ui_ExtraPackagesPage.h"
#include "utils/Logger.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Retranslator.h"

#include <QDesktopServices>
#include <QFocusEvent>
#include <QHeaderView>
#include <QNetworkAccessManager>
#include <QString>
#include <QVariant>

ExtraPackagesPage::ExtraPackagesPage( QWidget* parent ) :
    QWidget( parent ),
    ui( new Ui::ExtraPackagesPage )
{
    ui->setupUi( this );
    CALAMARES_RETRANSLATE (
    ui->maintext->setText( tr( "<p>Select the non-free packages you would like to install "
                               "(if any). This requires an Internet connection</p>"
                               "<p>By installing these packages you are accepting their respective "
                               "licenses.</p>" ) ); )
    ui->helpCentreButton->setIcon( CalamaresUtils::defaultPixmap(
                                       CalamaresUtils::Information,
                                       CalamaresUtils::Original,
                                       2*QSize( CalamaresUtils::defaultFontHeight(),
                                               CalamaresUtils::defaultFontHeight() ) ) );
    ui->helpCentreButton->setText( tr( "More help information" ) );
    connect( ui->selectAllBox, &QCheckBox::stateChanged, [=]
    {
        if ( ui->selectAllBox->checkState() == Qt::PartiallyChecked )
            return;
        stateChanging = true;
        int row = 0;
        for ( int i = 0; i < ui->packageTable->rowCount(); i++ )
            ui->packageTable->item( i, 0 )->
            setCheckState( ui->selectAllBox->checkState() );
        stateChanging = false;
    } );
    ui->selectAllBox->setText( tr( "Select all" ) );
    ui->packageTable->setHorizontalHeaderLabels( {tr( "Package Name" ), tr( "Description" )} );
}

void
ExtraPackagesPage::setUpLink( bool showHelpCentre, QString url )
{
    using namespace Calamares;
    if ( showHelpCentre && url != nullptr )
    {
        ui->helpCentreButton->setIcon( CalamaresUtils::defaultPixmap(
                                           CalamaresUtils::Information,
                                           CalamaresUtils::Original,
                                           2*QSize( CalamaresUtils::defaultFontHeight(),
                                                   CalamaresUtils::defaultFontHeight() ) ) );
        connect( ui->helpCentreButton, &QPushButton::clicked, [=]
        {
            QDesktopServices::openUrl( url );
        } );
    }
    else if ( showHelpCentre && url == nullptr )
    {
        cDebug() << "WARNING: Restricted Extras help URL is invalid. Disabling help button";
        ui->helpCentreButton->hide();
    }
    else
        ui->helpCentreButton->hide();
}

void
ExtraPackagesPage::setUpPackages( const QVariantList& packages )
{
    for ( int i = 0; i < ui->packageTable->horizontalHeader()->count(); i++ )
        ui->packageTable->horizontalHeader()->setSectionResizeMode( i,
                QHeaderView::Stretch );
    ui->packageTable->setRowCount( packages.size() );
    int row = 0;
    for ( auto i = packages.begin(); i != packages.end(); i++ )
    {
        QVariantMap packageMap = ( *i ).toMap();
        QTableWidgetItem* name =
            new QTableWidgetItem( packageMap.value( "name" ).toString() );
        name->setData( Qt::UserRole, packageMap.value( "pre-install" ) );
        name->setData( Qt::UserRole+1, packageMap.value( "post-install" ) );
        name->setCheckState( Qt::Unchecked );
        QTableWidgetItem* description =
            new QTableWidgetItem( packageMap.value( "description" ).toString() );
        ui->packageTable->setItem( row, 0, name );
        ui->packageTable->setItem( row, 1, description );
        row++;
    }
    connect( ui->packageTable, &QTableWidget::itemChanged, [=]
    {
        if ( stateChanging )
            return;
        int checked = 0;
        for ( int i = 0; i < ui->packageTable->rowCount(); i++ )
            if ( ui->packageTable->item( i, 0 )->checkState() == Qt::Checked )
                checked++;
        if ( checked && checked < ui->packageTable->rowCount() )
            ui->selectAllBox->setCheckState( Qt::PartiallyChecked );
        else if ( checked )
            ui->selectAllBox->setCheckState( Qt::Checked );
        else
            ui->selectAllBox->setCheckState( Qt::Unchecked );
    } );
}

QString 
ExtraPackagesPage::prettyStatus()
{
    QString status;
    const QList<Calamares::job_ptr> list = createJobs( QVariantList() );
    if ( !list.size() )
        return status;
    for ( auto i = list.begin(); i < list.end(); i++ )
        status += ( **i ).prettyName() + "\n";
    return status;
}

QList<Calamares::job_ptr> 
ExtraPackagesPage::createJobs( const QVariantList& sources )
{
    bool empty = true;
    for ( int i = 0; i < ui->packageTable->rowCount(); i++ )
    {
        if ( ui->packageTable->item( i, 0 )->checkState() == Qt::Checked )
        {
            empty = false;
            break;
        }
    }
    QList<Calamares::job_ptr> list;
    if ( !empty )
        for ( auto i = sources.begin(); i != sources.end(); i++ )
            list.prepend( Calamares::job_ptr( new SetSourcesJob( ( *i ).toString() ) ) );
    return list;
}

void
ExtraPackagesPage::addPackagesToStorage()
{
    QStringList packages;
    for ( int i = 0; i < ui->packageTable->rowCount(); i++ )
    {
        if ( ui->packageTable->item( i, 0 )->checkState() == Qt::Checked )
        {
            QString name =
                ui->packageTable->item( i, 0 )->data( Qt::DisplayRole ).toString();
            QString preScript =
                ui->packageTable->item( i, 0 )->data( Qt::UserRole ).toString();
            QString postScript =
                ui->packageTable->item( i, 0 )->data( Qt::UserRole+1 ).toString();
            packages += name; //TODO: Add pre/post script
        }
    }
    if ( packages.count() )
    {
        QMap<QString, QVariant> installList;
        installList.insert("try_install", packages);
        Calamares::JobQueue::instance()->globalStorage()->insert(
                "packageOperations", QVariant(installList));
    }
}

void
ExtraPackagesPage::checkInternet()
{
    if ( !Calamares::JobQueue::instance()->globalStorage()->value( "hasInternet" ).toBool() )
        cDebug() << "WARNING: No Internet connection detected. Unable to "
                 "install extra packages";

    ui->packageTable->setEnabled(
            Calamares::JobQueue::instance()->globalStorage()->value( "hasInternet" ).toBool() );
    ui->selectAllBox->setEnabled(
            Calamares::JobQueue::instance()->globalStorage()->value( "hasInternet" ).toBool() );
}

void 
ExtraPackagesPage::focusInEvent( QFocusEvent* e )
{
    if ( ui->packageTable )
        ui->packageTable->setFocus();
    e->accept();
}
