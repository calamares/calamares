/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
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

#ifndef CALAMARESUTILSGUI_H
#define CALAMARESUTILSGUI_H

#include "utils/CalamaresUtils.h"
#include "UiDllMacro.h"

#include <QObject>
#include <QPixmap>
#include <QSize>

class QLayout;

namespace CalamaresUtils
{

/**
 * @brief The ImageType enum lists all common Calamares icons.
 * Icons are loaded from SVGs and cached. Each icon has an enum value, through which
 * it can be accessed.
 * You can forward-declare this as:
 * enum ImageType : int;
 */
enum ImageType : int
{
    Yes,
    No,
    Information,
    Fail,
    Bugs,
    Help,
    Release,
    PartitionDisk,
    PartitionPartition,
    PartitionAlongside,
    PartitionEraseAuto,
    PartitionManual,
    PartitionReplaceOs,
    PartitionTable,
    BootEnvironment,
    Squid,
    StatusOk,         // Icons for the requirements checker
    StatusWarning,
    StatusError
};

/**
 * @brief The ImageMode enum contains different transformations that can be applied.
 * Most of these are currently unused.
 */
enum ImageMode
{
    Original,
    CoverInCase,
    Grid,
    DropShadow,
    RoundedCorners
};

/**
 * @brief defaultPixmap returns a resized and/or transformed pixmap for a given
 * ImageType.
 * @param type the ImageType i.e. the enum value for an SVG.
 * @param mode the transformation to apply (default: no transformation).
 * @param size the target pixmap size (default: original SVG size).
 * @return the new pixmap.
 */
UIDLLEXPORT QPixmap defaultPixmap( ImageType type,
                                   ImageMode mode = CalamaresUtils::Original,
                                   const QSize& size = QSize( 0, 0 ) );

/**
 * @brief createRoundedImage returns a rounded version of a pixmap.
 * @param avatar the input pixmap.
 * @param size the new size.
 * @param frameWidthPct the frame size, as percentage of width.
 * @return the transformed pixmap.
 * This one is currently unused.
 */
UIDLLEXPORT QPixmap createRoundedImage( const QPixmap& avatar,
                                        const QSize& size,
                                        float frameWidthPct = 0.20f );

/**
 * @brief unmarginLayout recursively walks the QLayout tree and removes all margins.
 * @param layout the layout to unmargin.
 */
UIDLLEXPORT void unmarginLayout( QLayout* layout );

/**
 * @brief clearLayout recursively walks the QLayout tree and deletes all the child
 * widgets and layouts.
 * @param layout the layout to clear.
 */
UIDLLEXPORT void clearLayout( QLayout* layout );

UIDLLEXPORT void setDefaultFontSize( int points );
UIDLLEXPORT int defaultFontSize();      // in points
UIDLLEXPORT int defaultFontHeight();    // in pixels, DPI-specific
UIDLLEXPORT QFont defaultFont();
UIDLLEXPORT QFont largeFont();
UIDLLEXPORT QSize defaultIconSize();

/**
 * @brief Size constants for the main Calamares window.
 */
constexpr int windowMinimumWidth = 800;
constexpr int windowMinimumHeight = 520;
constexpr int windowPreferredWidth = 1024;
constexpr int windowPreferredHeight = 520;

/**
 * @brief Consistent locale (language + country) naming.
 *
 * Support class to turn locale names (as used by Calamares's
 * translation system) into QLocales, and also into consistent
 * human-readable text labels.
 */
class LocaleLabel
{
public:
    /** @brief Formatting option for label -- add (country) to label. */
    enum class LabelFormat { AlwaysWithCountry, IfNeededWithCountry } ;

    /** @brief Construct from a locale name.
     *
     * The @p localeName should be one that Qt recognizes, e.g. en_US or ar_EY.
     * The @p format determines whether the country name is always present
     * in the label (human-readable form) or only if needed for disambiguation.
     */
    LocaleLabel( const QString& localeName, LabelFormat format = LabelFormat::IfNeededWithCountry );

    /** @brief Define a sorting order.
     *
     * English (@see isEnglish() -- it means en_US) is sorted at the top.
     */
    bool operator <( const LocaleLabel& other ) const
    {
        if ( isEnglish() )
            return !other.isEnglish();
        if ( other.isEnglish() )
            return false;
        return m_sortKey < other.m_sortKey;
    }

    /** @brief Is this locale English?
     *
     * en_US and en (American English) is defined as English. The Queen's
     * English -- proper English -- is relegated to non-English status.
     */
    bool isEnglish() const
    {
        return m_localeId == QLatin1Literal( "en_US" ) || m_localeId == QLatin1Literal( "en" );
    }

    /** @brief Get the human-readable name for this locale. */
    QString label() const
    {
        return m_label;
    }
    /** @brief Get the Qt locale. */
    QLocale locale() const
    {
        return m_locale;
    }

    /** @brief Get a Qt locale for the given @p localeName
     *
     * This special-cases `sr@latin`, which is used as a translation
     * name in Calamares, while Qt recognizes `sr@latn`.
     */
    static QLocale getLocale( const QString& localeName );

protected:
    QLocale m_locale;
    QString m_localeId;  // the locale identifier, e.g. "en_GB"
    QString m_sortKey;  // the English name of the locale
    QString m_label;  // the native name of the locale
} ;


}  // namespace CalamaresUtils

#endif // CALAMARESUTILSGUI_H
