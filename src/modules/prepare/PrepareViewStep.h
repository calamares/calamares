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

#ifndef PREPAREPAGEPLUGIN_H
#define PREPAREPAGEPLUGIN_H

#include <QObject>

#include "viewpages/ViewStep.h"
#include "PluginDllMacro.h"

class PreparePage;

class PLUGINDLLEXPORT PrepareViewStep : public Calamares::ViewStep
{
    Q_OBJECT
    Q_PLUGIN_METADATA( IID "calamares.ViewModule/1.0" )

    Q_INTERFACES( Calamares::ViewStep )

public:
    explicit PrepareViewStep( QObject* parent = nullptr );
    virtual ~PrepareViewStep();

    QString prettyName() const override;

    QWidget* widget() override;

    void next() override;
    void back() override;

    bool isNextEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    QList< Calamares::job_ptr > jobs() const override;

    void onLeave() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

private:
    bool checkEnoughStorage( qint64 requiredSpace );
    bool checkEnoughRam( qint64 requiredRam );
    bool checkHasPower();
    bool checkHasInternet();

    QWidget* m_widget;
    qreal m_requiredStorageGB;
    qreal m_requiredRamGB;

    PreparePage* m_actualWidget;
    bool m_nextEnabled;
};

#endif // PREPAREPAGEPLUGIN_H
