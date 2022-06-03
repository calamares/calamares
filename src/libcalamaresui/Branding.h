/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2018 Raul Rodrigo Segura (raurodse)
 *   SPDX-FileCopyrightText: 2019 Camilo Higuita <milo.h@aol.com>
 *   SPDX-FileCopyrightText: 2021 Anubhav Choudhary <ac.10edu@gmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef BRANDING_H
#define BRANDING_H

#include "CalamaresConfig.h"
#include "DllMacro.h"
#include "utils/NamedSuffix.h"

#include <QMap>
#include <QObject>
#include <QPixmap>
#include <QSize>
#include <QStringList>
#include <QUrl>

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

    enum StringEntry
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
        ReleaseNotesUrl,
        DonateUrl
    };
    Q_ENUM( StringEntry )

    enum ImageEntry : short
    {
        ProductBanner,
        ProductIcon,
        ProductLogo,
        ProductWallpaper,
        ProductWelcome
    };
    Q_ENUM( ImageEntry )

    /** @brief Names of style entries, for use in code
     *
     * These names are mapped to names in the branding.desc file through
     * an internal table s_styleEntryStrings, which defines which names
     * in `branding.desc` key *style* are used for which entry.
     */
    enum StyleEntry : short
    {
        SidebarBackground,
        SidebarText,
        SidebarTextCurrent,
        SidebarBackgroundCurrent,
    };
    Q_ENUM( StyleEntry )

    /** @brief Supported log-upload servers.
     *
     * 'None' is here as a fallback.
     */
    enum UploadServerType : short
    {
        None,
        Fiche
    };
    Q_ENUM( UploadServerType )

    /** @brief Setting for how much the main window may expand. */
    enum class WindowExpansion
    {
        Normal,
        Fullscreen,
        Fixed
    };
    Q_ENUM( WindowExpansion )
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
    Q_ENUM( WindowDimensionUnit )
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
    /** @brief Placement of main window.
     */
    enum class WindowPlacement
    {
        Center,
        Free
    };
    Q_ENUM( WindowPlacement )
    ///@brief What kind of panel (sidebar, navigation) to use in the main window
    enum class PanelFlavor
    {
        None,
        Widget
#ifdef WITH_QML
        ,
        Qml
#endif
    };
    Q_ENUM( PanelFlavor )
    ///@brief Where to place a panel (sidebar, navigation)
    enum class PanelSide
    {
        None,
        Left,
        Right,
        Top,
        Bottom
    };
    Q_ENUM( PanelSide )

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

    /** @brief Path to the slideshow QML file, if any. (API == 1 or 2)*/
    QString slideshowPath() const { return m_slideshowPath; }
    /// @brief List of pathnames of slideshow images, if any. (API == -1)
    QStringList slideshowImages() const { return m_slideshowFilenames; }
    /** @brief Which slideshow API to use for the slideshow?
     *
     *  -  2    For QML-based slideshows loaded asynchronously (current)
     *  -  1    For QML-based slideshows, loaded when shown (legacy)
     *  - -1    For oldschool image-slideshows.
     */
    int slideshowAPI() const { return m_slideshowAPI; }

    QPixmap image( Branding::ImageEntry imageEntry, const QSize& size ) const;

    /** @brief Look up an image in the branding directory or as an icon
     *
     * The @p name is checked in the branding directory: if it is an image
     * file, return the pixmap from that file, at the requested size.
     * If it isn't a file, look it up as an icon name in the current theme.
     * May return a null pixmap if nothing is found.
     */
    QPixmap image( const QString& name, const QSize& size ) const;

    /** @brief Look up image with alternate names
     *
     * Calls image() for each name in the @p list and returns the first
     * one that is non-null. May return a null pixmap if nothing is found.
     */
    QPixmap image( const QStringList& list, const QSize& size ) const;

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
    bool windowPlacementCentered() const { return m_windowPlacement == WindowPlacement::Center; }

    ///@brief Which sidebar flavor is configured
    PanelFlavor sidebarFlavor() const { return m_sidebarFlavor; }
    ///@brief Which navigation flavor is configured
    PanelFlavor navigationFlavor() const { return m_navigationFlavor; }

    /** @brief Upload server configuration
     *
     * This object has 3 items : the type (which may be none, in which case the URL
     * is irrelevant and usually empty), the URL for the upload and the size limit of upload
     * in bytes (for configuration value < 0, it serves -1, which stands for having no limit).
     */
    struct UploadServerInfo
    {
        UploadServerType type;
        QUrl url;
        qint64 size;

        operator bool() const { return type != Calamares::Branding::UploadServerType::None && size != 0; }
    };
    UploadServerInfo uploadServer() const { return m_uploadServer; }

    /**
     * Creates a map called "branding" in the global storage, and inserts an
     * entry for each of the branding strings. This makes the branding
     * information accessible to the Python modules.
     */
    void setGlobals( GlobalStorage* globalStorage ) const;

public slots:
    QString string( StringEntry stringEntry ) const;
    QString versionedName() const { return string( VersionedName ); }
    QString productName() const { return string( ProductName ); }
    QString shortProductName() const { return string( ShortProductName ); }
    QString shortVersionedName() const { return string( ShortVersionedName ); }

    /** @brief Map an enum-value to the entry from the *style* key.
     *
     * e.g. StyleEntry::SidebarTextCurrent maps to the corresponding
     * *style* entry, which is (confusingly) named "sidebarTextSelect"
     * in the branding file.
     */
    QString styleString( StyleEntry styleEntry ) const;
    QString imagePath( ImageEntry imageEntry ) const;

    PanelSide sidebarSide() const { return m_sidebarSide; }
    PanelSide navigationSide() const { return m_navigationSide; }

private:
    static Branding* s_instance;

    static const QStringList s_stringEntryStrings;
    static const QStringList s_imageEntryStrings;
    static const QStringList s_uploadServerStrings;

    QString m_descriptorPath;  // Path to descriptor (e.g. "/etc/calamares/default/branding.desc")
    QString m_componentName;  // Matches last part of full path to containing directory
    QMap< QString, QString > m_strings;
    QMap< QString, QString > m_images;
    QMap< QString, QString > m_style;
    UploadServerInfo m_uploadServer;

    /* The slideshow can be done in one of two ways:
     *  - as a sequence of images
     *  - as a QML file
     * The slideshow: setting selects which one is used. If it is
     * a list (of filenames) then it is a sequence of images, and otherwise
     * it is a QML file which is run. (For QML, the slideshow API is
     * important).
     */
    QStringList m_slideshowFilenames;
    QString m_slideshowPath;
    int m_slideshowAPI;
    QString m_translationsPathPrefix;

    /** @brief Initialize the simple settings below */
    void initSimpleSettings( const YAML::Node& doc );
    ///@brief Initialize the slideshow settings, above
    void initSlideshowSettings( const YAML::Node& doc );

    bool m_welcomeStyleCalamares;
    bool m_welcomeExpandingLogo;

    WindowExpansion m_windowExpansion;
    WindowDimension m_windowHeight, m_windowWidth;
    WindowPlacement m_windowPlacement;

    PanelFlavor m_sidebarFlavor = PanelFlavor::Widget;
    PanelFlavor m_navigationFlavor = PanelFlavor::Widget;
    PanelSide m_sidebarSide = PanelSide::Left;
    PanelSide m_navigationSide = PanelSide::Bottom;
};

}  // namespace Calamares

#endif  // BRANDING_H
