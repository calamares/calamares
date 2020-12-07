/*
 *   SPDX-FileCopyrightText: 2016 Luca Giambonini <almack@chakraos.org>
 *   SPDX-FileCopyrightText: 2016 Lisa Vitolo     <shainer@chakraos.org>
 *   SPDX-FileCopyrightText: 2017 Kyle Robbertze  <krobbertze@gmail.com>
 *   SPDX-FileCopyrightText: 2017-2018 2020, Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2017 Gabriel Craciunescu <crazy@frugalware.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "NetInstallPage.h"

#include "PackageModel.h"
#include "ui_page_netinst.h"

#include "JobQueue.h"

#include "network/Manager.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "utils/Yaml.h"

#include <QHeaderView>
#include <QNetworkReply>

NetInstallPage::NetInstallPage( Config* c, QWidget* parent )
    : QWidget( parent )
    , m_config( c )
    , ui( new Ui::Page_NetInst )
{
    ui->setupUi( this );
    ui->groupswidget->header()->setSectionResizeMode( QHeaderView::ResizeToContents );
    ui->groupswidget->setModel( c->model() );
    connect( c, &Config::statusChanged, this, &NetInstallPage::setStatus );
    connect( c, &Config::statusReady, this, &NetInstallPage::expandGroups );

    setPageTitle( nullptr );
    CALAMARES_RETRANSLATE_SLOT( &NetInstallPage::retranslate )
}

NetInstallPage::~NetInstallPage() {}

void
NetInstallPage::setPageTitle( CalamaresUtils::Locale::TranslatedString* t )
{
    m_title.reset( t );
    if ( !m_title )
    {
        ui->label->hide();
    }
    else
    {
        ui->label->show();
    }
    retranslate();
}

void
NetInstallPage::retranslate()
{
    if ( m_title )
    {
        ui->label->setText( m_title->get() );  // That's get() on the TranslatedString
    }
    ui->netinst_status->setText( m_config->status() );
}

void
NetInstallPage::expandGroups()
{
    auto* model = m_config->model();
    // Go backwards because expanding a group may cause rows to appear below it
    for ( int i = model->rowCount() - 1; i >= 0; --i )
    {
        auto index = model->index( i, 0 );
        if ( model->data( index, PackageModel::MetaExpandRole ).toBool() )
        {
            ui->groupswidget->setExpanded( index, true );
        }
    }
}

void
NetInstallPage::setStatus( QString s )
{
    ui->netinst_status->setText( s );
}

void
NetInstallPage::onActivate()
{
    ui->groupswidget->setFocus();
}
