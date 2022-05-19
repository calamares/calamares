/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Contains strings from libpwquality under the terms of the
 *   GPL-3.0-or-later (libpwquality is BSD-3-clause or GPL-2.0-or-later,
 *   so we pick GPL-3.0-or-later).
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "CheckPWQuality.h"

#include "utils/Logger.h"

#include <QCoreApplication>
#include <QString>

#ifdef HAVE_LIBPWQUALITY
#include <pwquality.h>
#endif

#include <memory>

PasswordCheck::PasswordCheck()
    : m_weight( 0 )
    , m_message()
    , m_accept( []( const QString& ) { return true; } )
{
}

PasswordCheck::PasswordCheck( MessageFunc m, AcceptFunc a, Weight weight )
    : m_weight( weight )
    , m_message( m )
    , m_accept( a )
{
}

DEFINE_CHECK_FUNC( minLength )
{
    int minLength = -1;
    if ( value.canConvert( QVariant::Int ) )
    {
        minLength = value.toInt();
    }
    if ( minLength > 0 )
    {
        cDebug() << Logger::SubEntry << "minLength set to" << minLength;
        checks.push_back( PasswordCheck( []() { return QCoreApplication::translate( "PWQ", "Password is too short" ); },
                                         [ minLength ]( const QString& s ) { return s.length() >= minLength; },
                                         PasswordCheck::Weight( 10 ) ) );
    }
}

DEFINE_CHECK_FUNC( maxLength )
{
    int maxLength = -1;
    if ( value.canConvert( QVariant::Int ) )
    {
        maxLength = value.toInt();
    }
    if ( maxLength > 0 )
    {
        cDebug() << Logger::SubEntry << "maxLength set to" << maxLength;
        checks.push_back( PasswordCheck( []() { return QCoreApplication::translate( "PWQ", "Password is too long" ); },
                                         [ maxLength ]( const QString& s ) { return s.length() <= maxLength; },
                                         PasswordCheck::Weight( 10 ) ) );
    }
}

#ifdef HAVE_LIBPWQUALITY
/* NOTE:
 *
 * The munge*() functions are here because libpwquality uses void* to
 * represent user-data in callbacks and as a general "pass some parameter"
 * type. These need to be munged to the right C++ type.
 */

/// @brief Handle libpwquality using void* to represent a long
static inline long
mungeLong( void* p )
{
    return static_cast< long >( reinterpret_cast< intptr_t >( p ) );
}

/// @brief Handle libpwquality using void* to represent a char*
static inline const char*
mungeString( void* p )
{
    return reinterpret_cast< const char* >( p );
}

/**
 * Class that acts as a RAII placeholder for pwquality_settings_t pointers.
 * Gets a new pointer and ensures it is deleted only once; provides
 * convenience functions for setting options and checking passwords.
 */
class PWSettingsHolder
{
public:
    static constexpr int arbitrary_minimum_strength = 40;

    PWSettingsHolder()
        : m_settings( pwquality_default_settings() )
    {
    }

    ~PWSettingsHolder() { pwquality_free_settings( m_settings ); }

    /// Sets an option via the configuration string @p v, <key>=<value> style.
    int set( const QString& v ) { return pwquality_set_option( m_settings, v.toUtf8().constData() ); }

    /** @brief Checks the given password @p pwd against the current configuration
     *
     * Resets m_errorString and m_errorCount and then sets them appropriately
     * so that explanation() can be called afterwards. Sets m_rv as well.
     */

    int check( const QString& pwd )
    {
        void* auxerror = nullptr;
        m_rv = pwquality_check( m_settings, pwd.toUtf8().constData(), nullptr, nullptr, &auxerror );

        // Positive return values could be ignored; some negative ones
        // place extra information in auxerror, which is a void* and
        // which needs interpretation to long- or string-values.
        m_errorCount = 0;
        m_errorString = QString();

        switch ( m_rv )
        {
        case PWQ_ERROR_CRACKLIB_CHECK:
            if ( auxerror )
            {
                /* Here the string comes from cracklib, don't free? */
                m_errorString = mungeString( auxerror );
            }
            break;
        case PWQ_ERROR_MEM_ALLOC:
        case PWQ_ERROR_UNKNOWN_SETTING:
        case PWQ_ERROR_INTEGER:
        case PWQ_ERROR_NON_INT_SETTING:
        case PWQ_ERROR_NON_STR_SETTING:
            if ( auxerror )
            {
                m_errorString = mungeString( auxerror );
                free( auxerror );
            }
            break;
        case PWQ_ERROR_MIN_DIGITS:
        case PWQ_ERROR_MIN_UPPERS:
        case PWQ_ERROR_MIN_LOWERS:
        case PWQ_ERROR_MIN_OTHERS:
        case PWQ_ERROR_MIN_LENGTH:
        case PWQ_ERROR_MIN_CLASSES:
        case PWQ_ERROR_MAX_CONSECUTIVE:
        case PWQ_ERROR_MAX_CLASS_REPEAT:
        case PWQ_ERROR_MAX_SEQUENCE:
            if ( auxerror )
            {
                m_errorCount = mungeLong( auxerror );
            }
            break;
        default:
            break;
        }

        return m_rv;
    }

    /** @brief Explain the results of the last call to check()
     *
     * This is roughly the same as the function pwquality_strerror,
     * only with QStrings instead, and using the Qt translation scheme.
     * It is used under the terms of the GNU GPL v3 or later, as
     * allowed by the libpwquality license (LICENSES/GPLv2+-libpwquality)
     */
    QString explanation()
    {
        if ( m_rv >= arbitrary_minimum_strength )
        {
            return QString();
        }
        if ( m_rv >= 0 )
        {
            return QCoreApplication::translate( "PWQ", "Password is too weak" );
        }

        switch ( m_rv )
        {
        case PWQ_ERROR_MEM_ALLOC:
            if ( !m_errorString.isEmpty() )
            {
                return QCoreApplication::translate( "PWQ", "Memory allocation error when setting '%1'" )
                    .arg( m_errorString );
            }
            return QCoreApplication::translate( "PWQ", "Memory allocation error" );
        case PWQ_ERROR_SAME_PASSWORD:
            return QCoreApplication::translate( "PWQ", "The password is the same as the old one" );
        case PWQ_ERROR_PALINDROME:
            return QCoreApplication::translate( "PWQ", "The password is a palindrome" );
        case PWQ_ERROR_CASE_CHANGES_ONLY:
            return QCoreApplication::translate( "PWQ", "The password differs with case changes only" );
        case PWQ_ERROR_TOO_SIMILAR:
            return QCoreApplication::translate( "PWQ", "The password is too similar to the old one" );
        case PWQ_ERROR_USER_CHECK:
            return QCoreApplication::translate( "PWQ", "The password contains the user name in some form" );
        case PWQ_ERROR_GECOS_CHECK:
            return QCoreApplication::translate(
                "PWQ", "The password contains words from the real name of the user in some form" );
        case PWQ_ERROR_BAD_WORDS:
            return QCoreApplication::translate( "PWQ", "The password contains forbidden words in some form" );
        case PWQ_ERROR_MIN_DIGITS:
            if ( m_errorCount )
            {
                return QCoreApplication::translate(
                    "PWQ", "The password contains fewer than %n digits", nullptr, m_errorCount );
            }
            return QCoreApplication::translate( "PWQ", "The password contains too few digits" );
        case PWQ_ERROR_MIN_UPPERS:
            if ( m_errorCount )
            {
                return QCoreApplication::translate(
                    "PWQ", "The password contains fewer than %n uppercase letters", nullptr, m_errorCount );
            }
            return QCoreApplication::translate( "PWQ", "The password contains too few uppercase letters" );
        case PWQ_ERROR_MIN_LOWERS:
            if ( m_errorCount )
            {
                return QCoreApplication::translate(
                    "PWQ", "The password contains fewer than %n lowercase letters", nullptr, m_errorCount );
            }
            return QCoreApplication::translate( "PWQ", "The password contains too few lowercase letters" );
        case PWQ_ERROR_MIN_OTHERS:
            if ( m_errorCount )
            {
                return QCoreApplication::translate(
                    "PWQ", "The password contains fewer than %n non-alphanumeric characters", nullptr, m_errorCount );
            }
            return QCoreApplication::translate( "PWQ", "The password contains too few non-alphanumeric characters" );
        case PWQ_ERROR_MIN_LENGTH:
            if ( m_errorCount )
            {
                return QCoreApplication::translate(
                    "PWQ", "The password is shorter than %n characters", nullptr, m_errorCount );
            }
            return QCoreApplication::translate( "PWQ", "The password is too short" );
        case PWQ_ERROR_ROTATED:
            return QCoreApplication::translate( "PWQ", "The password is a rotated version of the previous one" );
        case PWQ_ERROR_MIN_CLASSES:
            if ( m_errorCount )
            {
                return QCoreApplication::translate(
                    "PWQ", "The password contains fewer than %n character classes", nullptr, m_errorCount );
            }
            return QCoreApplication::translate( "PWQ", "The password does not contain enough character classes" );
        case PWQ_ERROR_MAX_CONSECUTIVE:
            if ( m_errorCount )
            {
                return QCoreApplication::translate(
                    "PWQ", "The password contains more than %n same characters consecutively", nullptr, m_errorCount );
            }
            return QCoreApplication::translate( "PWQ", "The password contains too many same characters consecutively" );
        case PWQ_ERROR_MAX_CLASS_REPEAT:
            if ( m_errorCount )
            {
                return QCoreApplication::translate(
                    "PWQ",
                    "The password contains more than %n characters of the same class consecutively",
                    nullptr,
                    m_errorCount );
            }
            return QCoreApplication::translate(
                "PWQ", "The password contains too many characters of the same class consecutively" );
        case PWQ_ERROR_MAX_SEQUENCE:
            if ( m_errorCount )
            {
                return QCoreApplication::translate(
                    "PWQ",
                    "The password contains monotonic sequence longer than %n characters",
                    nullptr,
                    m_errorCount );
            }
            return QCoreApplication::translate( "PWQ",
                                                "The password contains too long of a monotonic character sequence" );
        case PWQ_ERROR_EMPTY_PASSWORD:
            return QCoreApplication::translate( "PWQ", "No password supplied" );
        case PWQ_ERROR_RNG:
            return QCoreApplication::translate( "PWQ", "Cannot obtain random numbers from the RNG device" );
        case PWQ_ERROR_GENERATION_FAILED:
            return QCoreApplication::translate( "PWQ",
                                                "Password generation failed - required entropy too low for settings" );
        case PWQ_ERROR_CRACKLIB_CHECK:
            if ( !m_errorString.isEmpty() )
            {
                return QCoreApplication::translate( "PWQ", "The password fails the dictionary check - %1" )
                    .arg( m_errorString );
            }
            return QCoreApplication::translate( "PWQ", "The password fails the dictionary check" );
        case PWQ_ERROR_UNKNOWN_SETTING:
            if ( !m_errorString.isEmpty() )
            {
                return QCoreApplication::translate( "PWQ", "Unknown setting - %1" ).arg( m_errorString );
            }
            return QCoreApplication::translate( "PWQ", "Unknown setting" );
        case PWQ_ERROR_INTEGER:
            if ( !m_errorString.isEmpty() )
            {
                return QCoreApplication::translate( "PWQ", "Bad integer value of setting - %1" ).arg( m_errorString );
            }
            return QCoreApplication::translate( "PWQ", "Bad integer value" );
        case PWQ_ERROR_NON_INT_SETTING:
            if ( !m_errorString.isEmpty() )
            {
                return QCoreApplication::translate( "PWQ", "Setting %1 is not of integer type" ).arg( m_errorString );
            }
            return QCoreApplication::translate( "PWQ", "Setting is not of integer type" );
        case PWQ_ERROR_NON_STR_SETTING:
            if ( !m_errorString.isEmpty() )
            {
                return QCoreApplication::translate( "PWQ", "Setting %1 is not of string type" ).arg( m_errorString );
            }
            return QCoreApplication::translate( "PWQ", "Setting is not of string type" );
        case PWQ_ERROR_CFGFILE_OPEN:
            return QCoreApplication::translate( "PWQ", "Opening the configuration file failed" );
        case PWQ_ERROR_CFGFILE_MALFORMED:
            return QCoreApplication::translate( "PWQ", "The configuration file is malformed" );
        case PWQ_ERROR_FATAL_FAILURE:
            return QCoreApplication::translate( "PWQ", "Fatal failure" );
        default:
            return QCoreApplication::translate( "PWQ", "Unknown error" );
        }
    }

private:
    QString m_errorString;  ///< Textual error from last call to check()
    int m_errorCount = 0;  ///< Count (used in %n) error from last call to check()
    int m_rv = 0;  ///< Return value from libpwquality

    pwquality_settings_t* m_settings = nullptr;
};

DEFINE_CHECK_FUNC( libpwquality )
{
    if ( !value.canConvert( QVariant::List ) )
    {
        cWarning() << "libpwquality settings is not a list";
        return;
    }

    QVariantList l = value.toList();
    unsigned int requirement_count = 0;
    auto settings = std::make_shared< PWSettingsHolder >();
    for ( const auto& v : l )
    {
        if ( v.type() == QVariant::String )
        {
            QString option = v.toString();
            int r = settings->set( option );
            if ( r )
            {
                cWarning() << "unrecognized libpwquality setting" << option;
            }
            else
            {
                cDebug() << Logger::SubEntry << "libpwquality setting" << option;
                ++requirement_count;
            }
        }
        else
        {
            cWarning() << "unrecognized libpwquality setting" << v;
        }
    }

    /* Something actually added? */
    if ( requirement_count )
    {
        checks.push_back( PasswordCheck( [ settings ]() { return settings->explanation(); },
                                         [ settings ]( const QString& s )
                                         {
                                             int r = settings->check( s );
                                             if ( r < 0 )
                                             {
                                                 cWarning() << "libpwquality error" << r
                                                            << pwquality_strerror( nullptr, 256, r, nullptr );
                                             }
                                             else if ( r < settings->arbitrary_minimum_strength )
                                             {
                                                 cDebug() << "Password strength" << r << "too low";
                                             }
                                             return r >= settings->arbitrary_minimum_strength;
                                         },
                                         PasswordCheck::Weight( 100 ) ) );
    }
}
#endif
