/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019-2020, Adriaan de Groot <groot@kde.org>
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

#include "Config.h"

#include "Config.h"

#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "Branding.h"
#include "Settings.h"

#include <KPackage/Package>
#include <KPackage/PackageLoader>

#include <QFileInfo>
#include <QDir>

ThemeInfo::ThemeInfo( const KPluginMetaData& data )
: id( data.pluginId() )
, name( data.name() )
, description( data.description() )
{
    QDir dir(data.fileName());
    dir.cdUp();
    previewImage = QUrl::fromLocalFile(dir.absolutePath() + "/contents/previews/preview.png").toString();
}

static ThemeInfoList plasma_themes()
{
    ThemeInfoList packages;

    QList<KPluginMetaData> pkgs = KPackage::PackageLoader::self()->listPackages( "Plasma/LookAndFeel" );

    for ( const KPluginMetaData& data : pkgs )
    {
        if ( data.isValid() && !data.isHidden() && !data.name().isEmpty() )
        {
            packages << ThemeInfo{ data };
        }
    }

    return packages;
}

static QString _munge_imagepath( const QString& path )
{

    if ( path.isEmpty() )
        return ":/view-preview.png";

    if ( path.startsWith( '/' ) )
        return path;

    if ( QFileInfo::exists( path ) )
        return path;

    QFileInfo fi( QDir( Calamares::Branding::instance()->componentDirectory() ), path );
       cDebug() << "Checking imagepath " << path <<  fi.absoluteFilePath() << fi.exists();
    if ( fi.exists() )
        return fi.absoluteFilePath();

    return QString();
}

void ThemesModel::setThemes(const ThemeInfoList& themes)
{
    emit beginResetModel();

    for(const auto &theme :  themes)
    {
        m_list << QMap<QString, QString> {{"id", theme.id}, {"description", theme.description}, {"image", _munge_imagepath(theme.imagePath)}, {"name", theme.name}};
    }

    emit endResetModel();
}

Config::Config(QObject *parent) : QObject(parent)
, m_themesModel( new ThemesModel(this) )
{

    connect( m_themesModel, &ThemesModel::themeSelected, this, &Config::plasmaThemeSelected);

    CALAMARES_RETRANSLATE(
        {

            if ( Calamares::Settings::instance()->isSetupMode() )
                m_prettyStatus = tr(
                    "Please choose a look-and-feel for the KDE Plasma Desktop. "
                    "You can also skip this step and configure the look-and-feel "
                    "once the system is set up. Clicking on a look-and-feel "
                    "selection will give you a live preview of that look-and-feel.");
                else
                    m_prettyStatus = tr(
                        "Please choose a look-and-feel for the KDE Plasma Desktop. "
                        "You can also skip this step and configure the look-and-feel "
                        "once the system is set up. Clicking on a look-and-feel "
                        "selection will give you a live preview of that look-and-feel.");

                emit prettyStatusChanged();
                updateThemeNames();
                m_themesModel->setThemes(m_enabledThemes);
        }
    )
}

void
Config::setLnfPath( const QString& path )
{
    m_lnfPath = path;
}

void
Config::setEnabledThemes(const ThemeInfoList& themes, bool showAll )
{
    m_enabledThemes = themes; //TODO for now only use the installed themes

    if ( showAll )
    {
        auto plasmaThemes = plasma_themes();
        for ( auto& installed_theme : plasmaThemes )
            if ( !m_enabledThemes.findById( installed_theme.id ) )
                m_enabledThemes.append( installed_theme );
    }

    updateThemeNames();
    winnowThemes();
    m_themesModel->setThemes(m_enabledThemes);
}

void
Config::setEnabledThemesAll()
{
    // Don't need to set showAll=true, because we're already passing in
    // the complete list of installed themes.
    setEnabledThemes( plasma_themes(), false );
}

void
Config::setPreselect( const QString& id )
{
    m_preselect = id;

    if ( !m_enabledThemes.isEmpty() )
    {
//          m_themesModel->setThemes(m_enabledThemes);
//          m_themesModel->setCurrentIndex(m_enabledThemes->findById(m_preselect));
    }
}

void Config::updateThemeNames()
{
    auto plasmaThemes = plasma_themes();
    for ( auto& enabled_theme : m_enabledThemes )
    {
        ThemeInfo* t = plasmaThemes.findById( enabled_theme.id );
        if ( t != nullptr )
        {
            enabled_theme.name = t->name;
            enabled_theme.description = t->description;
        }
    }
}

void Config::winnowThemes()
{
    auto plasmaThemes = plasma_themes();
    bool winnowed = true;
    int winnow_index = 0;
    while ( winnowed )
    {
        winnowed = false;
        winnow_index = 0;

        for ( auto& enabled_theme : m_enabledThemes )
        {
            ThemeInfo* t = plasmaThemes.findById( enabled_theme.id );
            if ( t == nullptr )
            {
                cDebug() << "Removing" << enabled_theme.id;
                winnowed = true;
                break;
            }
            ++winnow_index;
        }

        if ( winnowed )
        {
            m_enabledThemes.removeAt( winnow_index );
        }
    }
}



