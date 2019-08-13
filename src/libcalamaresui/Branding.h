/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
 *   Copyright 2018, Raul Rodrigo Segura (raurodse)
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

#include "utils/NamedSuffix.h"

#include <QMap>
#include <QObject>
#include <QStringList>

namespace YAML
{
class Node;
}

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

    /** @brief Setting for how much the main window may expand. */
    enum class WindowExpansion
    {
        Normal,
        Fullscreen,
        Fixed
    };
    /** @brief Setting for the main window size.
     *
     * The units are pixels (Pixies) or something-based-on-fontsize (Fonties), which
     * we suffix as "em", e.g. "600px" or "32em".
     */
    enum class WindowDimensionUnit
    {
        None,
        Pixies,
        Fonties
    };
    class WindowDimension : public NamedSuffix< WindowDimensionUnit, WindowDimensionUnit::None >
    {
    public:
        static const NamedEnumTable< WindowDimensionUnit >& suffixes();
        bool isValid() const;

        using NamedSuffix::NamedSuffix;
        WindowDimension( const QString& s )
            : NamedSuffix( suffixes(), s )
        {
        }
    };

    static Branding* instance();

    explicit Branding( const QString& brandingFilePath, QObject* parent = nullptr );

    /** @brief Complete path of the branding descriptor file. */
    QString descriptorPath() const { return m_descriptorPath; }
    /** @brief The component name found in the descriptor file.
     *
     * The component name always matches the last directory name in the path.
     */
    QString componentName() const { return m_componentName; }
    /** @brief The directory holding all of the branding assets. */
    QString componentDirectory() const;
    /** @brief The directory where branding translations live.
     *
     * This is componentDir + "/lang".
     */
    QString translationsDirectory() const { return m_translationsPathPrefix; }

    /** @brief Path to the slideshow QML file, if any. */
    QString slideshowPath() const { return m_slideshowPath; }
    int slideshowAPI() const { return m_slideshowAPI; }

    QString string( Branding::StringEntry stringEntry ) const;
    QString styleString( Branding::StyleEntry styleEntry ) const;
    QString imagePath( Branding::ImageEntry imageEntry ) const;
    QPixmap image( Branding::ImageEntry imageEntry, const QSize& size ) const;

    /** @brief Look up an image in the branding directory or as an icon
     *
     * The @p name is checked in the branding directory: if it is an image
     * file, return the pixmap from that file, at the requested size.
     * If it isn't a file, look it up as an icon name in the current theme.
     * May return a null pixmap if nothing is found.
     */
    QPixmap image( const QString& name, const QSize& size ) const;

    /** @brief Stylesheet to apply for this branding. May be empty.
     *
     * The file is loaded every time this function is called, so
     * it may be quite expensive -- although normally it will be
     * called only once, on startup. (Or from the debug window)
     */
    QString stylesheet() const;

    bool welcomeStyleCalamares() const { return m_welcomeStyleCalamares; }
    bool welcomeExpandingLogo() const { return m_welcomeExpandingLogo; }
    bool windowMaximize() const { return m_windowExpansion == WindowExpansion::Fullscreen; }
    bool windowExpands() const { return m_windowExpansion != WindowExpansion::Fixed; }
    QPair< WindowDimension, WindowDimension > windowSize() const
    {
        return QPair< WindowDimension, WindowDimension >( m_windowWidth, m_windowHeight );
    }

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

    [[noreturn]] void bail( const QString& message );

    QString m_descriptorPath;  // Path to descriptor (e.g. "/etc/calamares/default/branding.desc")
    QString m_componentName;  // Matches last part of full path to containing directory
    QMap< QString, QString > m_strings;
    QMap< QString, QString > m_images;
    QMap< QString, QString > m_style;
    QString m_slideshowPath;
    int m_slideshowAPI;
    QString m_translationsPathPrefix;

    /** @brief Initialize the simple settings below */
    void initSimpleSettings( const YAML::Node& doc );

    bool m_welcomeStyleCalamares;
    bool m_welcomeExpandingLogo;
    WindowExpansion m_windowExpansion;

    WindowDimension m_windowHeight, m_windowWidth;
};

template < typename U >
inline QString operator*( U e )
{
    return Branding::instance()->string( e );
}

}  // namespace Calamares

#endif  // BRANDING_H
