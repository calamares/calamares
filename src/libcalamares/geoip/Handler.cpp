/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Handler.h"

#include "GeoIPFixed.h"
#include "GeoIPJSON.h"
#if defined( QT_XML_LIB )
#include "GeoIPXML.h"
#endif

#include "Settings.h"
#include "network/Manager.h"
#include "utils/Logger.h"
#include "utils/NamedEnum.h"
#include "utils/Variant.h"

#include <memory>

static const NamedEnumTable< CalamaresUtils::GeoIP::Handler::Type >&
handlerTypes()
{
    using Type = CalamaresUtils::GeoIP::Handler::Type;

    // *INDENT-OFF*
    // clang-format off
    static const NamedEnumTable<Type> names{
        { QStringLiteral( "none" ), Type::None },
        { QStringLiteral( "json" ), Type::JSON },
        { QStringLiteral( "xml" ), Type::XML },
        { QStringLiteral( "fixed" ), Type::Fixed }
    };
    // *INDENT-ON*
    // clang-format on

    return names;
}

namespace CalamaresUtils
{
namespace GeoIP
{

Handler::Handler()
    : m_type( Type::None )
{
}

Handler::Handler( const QString& implementation, const QString& url, const QString& selector )
    : m_type( Type::None )
    , m_url( url )
    , m_selector( selector )
{
    bool ok = false;
    m_type = handlerTypes().find( implementation, ok );
    if ( !ok )
    {
        cWarning() << "GeoIP style" << implementation << "is not recognized.";
    }
    else if ( m_type == Type::None )
    {
        cWarning() << "GeoIP style *none* does not do anything.";
    }
    else if ( m_type == Type::Fixed && Calamares::Settings::instance()
              && !Calamares::Settings::instance()->debugMode() )
    {
        cWarning() << "GeoIP style *fixed* is not recommended for production.";
    }
#if !defined( QT_XML_LIB )
    else if ( m_type == Type::XML )
    {
        m_type = Type::None;
        cWarning() << "GeoIP style *xml* is not supported in this version of Calamares.";
    }
#endif
}

Handler::~Handler() {}

static std::unique_ptr< Interface >
create_interface( Handler::Type t, const QString& selector )
{
    switch ( t )
    {
    case Handler::Type::None:
        return nullptr;
    case Handler::Type::JSON:
        return std::make_unique< GeoIPJSON >( selector );
    case Handler::Type::XML:
#if defined( QT_XML_LIB )
        return std::make_unique< GeoIPXML >( selector );
#else
        return nullptr;
#endif
    case Handler::Type::Fixed:
        return std::make_unique< GeoIPFixed >( selector );
    }
    __builtin_unreachable();
}

static RegionZonePair
do_query( Handler::Type type, const QString& url, const QString& selector )
{
    const auto interface = create_interface( type, selector );
    if ( !interface )
    {
        return RegionZonePair();
    }

    using namespace CalamaresUtils::Network;
    return interface->processReply(
        CalamaresUtils::Network::Manager::instance().synchronousGet( url, { RequestOptions::FakeUserAgent } ) );
}

static QString
do_raw_query( Handler::Type type, const QString& url, const QString& selector )
{
    const auto interface = create_interface( type, selector );
    if ( !interface )
    {
        return QString();
    }

    using namespace CalamaresUtils::Network;
    return interface->rawReply(
        CalamaresUtils::Network::Manager::instance().synchronousGet( url, { RequestOptions::FakeUserAgent } ) );
}

RegionZonePair
Handler::get() const
{
    if ( !isValid() )
    {
        return RegionZonePair();
    }
    return do_query( m_type, m_url, m_selector );
}


QFuture< RegionZonePair >
Handler::query() const
{
    Handler::Type type = m_type;
    QString url = m_url;
    QString selector = m_selector;

    return QtConcurrent::run( [ = ] { return do_query( type, url, selector ); } );
}

QString
Handler::getRaw() const
{
    if ( !isValid() )
    {
        return QString();
    }
    return do_raw_query( m_type, m_url, m_selector );
}


QFuture< QString >
Handler::queryRaw() const
{
    Handler::Type type = m_type;
    QString url = m_url;
    QString selector = m_selector;

    return QtConcurrent::run( [ = ] { return do_raw_query( type, url, selector ); } );
}

}  // namespace GeoIP
}  // namespace CalamaresUtils
