/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

#ifndef PACKAGECHOOSERVIEWSTEP_H
#define PACKAGECHOOSERVIEWSTEP_H

#include "DllMacro.h"
#include "locale/TranslatableConfiguration.h"
#include "utils/PluginFactory.h"
#include "viewpages/ViewStep.h"

#include "PackageModel.h"

#include <QObject>
#include <QUrl>
#include <QVariantMap>

class PackageChooserPage;

class PLUGINDLLEXPORT PackageChooserViewStep : public Calamares::ViewStep
{
    Q_OBJECT

public:
    explicit PackageChooserViewStep( QObject* parent = nullptr );
    virtual ~PackageChooserViewStep() override;

    QString prettyName() const override;

    QWidget* widget() override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    void onActivate() override;
    void onLeave() override;

    Calamares::JobList jobs() const override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

private:
    void fillModel( const QVariantList& items );
    void hookupModel();

    PackageChooserPage* m_widget;
    PackageListModel* m_model;

    // Configuration
    PackageChooserMode m_mode;
    QString m_id;
    CalamaresUtils::Locale::TranslatedString* m_stepName;  // As it appears in the sidebar
    QModelIndex m_defaultIdx;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( PackageChooserViewStepFactory )

#endif  // PACKAGECHOOSERVIEWSTEP_H
