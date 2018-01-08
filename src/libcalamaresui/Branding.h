/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

#ifndef BRANDING_H
#define BRANDING_H

#include "UiDllMacro.h"
#include "Typedefs.h"

#include <QObject>
#include <QStringList>
#include <QMap>


namespace Calamares
{

class GlobalStorage;

class UIDLLEXPORT Branding : public QObject
{
    Q_OBJECT
public:
    /**
     * Descriptive strings in the configuration file. use
     * e.g. *Branding::ProductName to get the string value for
     * the product name.
     */
    enum StringEntry : short
    {
        ProductName,
        Version,
        ShortVersion,
        VersionedName,
        ShortVersionedName,
        ShortProductName,
        BootloaderEntryName,
        ProductUrl,
        SupportUrl,
        KnownIssuesUrl,
        ReleaseNotesUrl
    };

    enum ImageEntry : short
    {
        ProductLogo,
        ProductIcon,
        ProductWelcome
    };
    
    enum StyleEntry : short
    {
        SidebarBackground,
        SidebarText,
        SidebarTextSelect,
        SidebarTextHighlight
    };

    static Branding* instance();

    explicit Branding( const QString& brandingFilePath,
                       QObject* parent = nullptr );

    QString descriptorPath() const;
    QString componentName() const;
    QString componentDirectory() const;
    QString translationsPathPrefix() const;

    QString string( Branding::StringEntry stringEntry ) const;
    QString styleString( Branding::StyleEntry styleEntry ) const;
    QString imagePath( Branding::ImageEntry imageEntry ) const;
    QPixmap image( Branding::ImageEntry imageEntry, const QSize& size ) const;
    QString slideshowPath() const;

    bool welcomeStyleCalamares() const { return m_welcomeStyleCalamares; }
    bool welcomeExpandingLogo() const { return m_welcomeExpandingLogo; }

    /**
     * Creates a map called "branding" in the global storage, and inserts an
     * entry for each of the branding strings. This makes the branding
     * information accessible to the Python modules.
     */
    void setGlobals( GlobalStorage* globalStorage ) const;

private:
    static Branding* s_instance;

    static const QStringList s_stringEntryStrings;
    static const QStringList s_imageEntryStrings;
    static const QStringList s_styleEntryStrings;

    void bail( const QString& message );

    QString m_descriptorPath;
    QString m_componentName;
    QMap< QString, QString > m_strings;
    QMap< QString, QString > m_images;
    QMap< QString, QString > m_style;
    QString m_slideshowPath;
    QString m_translationsPathPrefix;

    bool m_welcomeStyleCalamares;
    bool m_welcomeExpandingLogo;
};

template<typename U> inline QString operator*(U e) { return Branding::instance()->string( e ); }

}

#endif // BRANDING_H
