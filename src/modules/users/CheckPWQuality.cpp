/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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

#include "CheckPWQuality.h"

#include "utils/Logger.h"

#include <QCoreApplication>
#include <QString>
#include <QWidget>

#ifdef HAVE_LIBPWQUALITY
#include <pwquality.h>
#endif

#include <memory>

PasswordCheck::PasswordCheck()
    : m_message()
    , m_accept( []( const QString& ){ return true; } )
{
}

PasswordCheck::PasswordCheck( const QString& m, AcceptFunc a )
    : m_message( [m](){ return m; } )
    , m_accept( a )
{
}

PasswordCheck::PasswordCheck( MessageFunc m, AcceptFunc a )
    : m_message( m )
    , m_accept( a )
{
}

DEFINE_CHECK_FUNC( minLength )
{
    int minLength = -1;
    if ( value.canConvert( QVariant::Int ) )
        minLength = value.toInt();
    if ( minLength > 0 )
    {
        cDebug() << " .. minLength set to" << minLength;
        checks.push_back(
            PasswordCheck(
                []()
                {
                    return QCoreApplication::translate( "PWQ", "Password is too short" );
                },
                [minLength]( const QString& s )
                {
                    return s.length() >= minLength;
                }
            ) );
    }
}

DEFINE_CHECK_FUNC( maxLength )
{
    int maxLength = -1;
    if ( value.canConvert( QVariant::Int ) )
        maxLength = value.toInt();
    if ( maxLength > 0 )
    {
        cDebug() << " .. maxLength set to" << maxLength;
        checks.push_back(
            PasswordCheck(
                []()
                {
                    return QCoreApplication::translate("PWQ", "Password is too long" );
                },
                [maxLength]( const QString& s )
                {
                    return s.length() <= maxLength;
                }
            ) );
    }
}

#ifdef HAVE_LIBPWQUALITY
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
        , m_auxerror( nullptr )
    {
    }

    ~PWSettingsHolder()
    {
        cDebug() << "Freeing PWQ@" << ( void* )m_settings;
        pwquality_free_settings( m_settings );
    }

    /// Sets an option via the configuration string @p v, <key>=<value> style.
    int set( const QString& v )
    {
        return pwquality_set_option( m_settings, v.toUtf8().constData() );
    }

    /// Checks the given password @p pwd against the current configuration
    int check( const QString& pwd )
    {
        void* auxerror = nullptr;
        int r = pwquality_check( m_settings, pwd.toUtf8().constData(), nullptr, nullptr, &auxerror );
        m_rv = r;
        return r;
    }

    bool hasExplanation() const
    {
        return m_rv < 0;
    }

    /* This is roughly the same as the function pwquality_strerror,
     * only with QStrings instead, and using the Qt translation scheme.
     * It is used under the terms of the GNU GPL v3 or later, as
     * allowed by the libpwquality license (LICENSES/GPLv2+-libpwquality)
     */
    QString explanation()
    {
        void* auxerror = m_auxerror;
        m_auxerror = nullptr;

        if ( m_rv >= arbitrary_minimum_strength )
            return QString();
        if ( m_rv >= 0 )
            return QCoreApplication::translate( "PWQ",  "Password is too weak" );

        switch ( m_rv )
        {
        case PWQ_ERROR_MEM_ALLOC:
            if ( auxerror )
            {
                QString s = QCoreApplication::translate( "PWQ", "Memory allocation error when setting '%1'" ).arg( ( const char* )auxerror );
                free( auxerror );
                return s;
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
            return QCoreApplication::translate( "PWQ", "The password contains words from the real name of the user in some form" );
        case PWQ_ERROR_BAD_WORDS:
            return QCoreApplication::translate( "PWQ", "The password contains forbidden words in some form" );
        case PWQ_ERROR_MIN_DIGITS:
            if ( auxerror )
                return QCoreApplication::translate( "PWQ", "The password contains less than %1 digits" ).arg( ( long )auxerror );
            return QCoreApplication::translate( "PWQ", "The password contains too few digits" );
        case PWQ_ERROR_MIN_UPPERS:
            if ( auxerror )
                return QCoreApplication::translate( "PWQ", "The password contains less than %1 uppercase letters" ).arg( ( long )auxerror );
            return QCoreApplication::translate( "PWQ", "The password contains too few uppercase letters" );
        case PWQ_ERROR_MIN_LOWERS:
            if ( auxerror )
                return QCoreApplication::translate( "PWQ", "The password contains less than %1 lowercase letters" ).arg( ( long )auxerror );
            return QCoreApplication::translate( "PWQ", "The password contains too few lowercase letters" );
        case PWQ_ERROR_MIN_OTHERS:
            if ( auxerror )
                return QCoreApplication::translate( "PWQ", "The password contains less than %1 non-alphanumeric characters" ).arg( ( long )auxerror );
            return QCoreApplication::translate( "PWQ", "The password contains too few non-alphanumeric characters" );
        case PWQ_ERROR_MIN_LENGTH:
            if ( auxerror )
                return QCoreApplication::translate( "PWQ", "The password is shorter than %1 characters" ).arg( ( long )auxerror );
            return QCoreApplication::translate( "PWQ", "The password is too short" );
        case PWQ_ERROR_ROTATED:
            return QCoreApplication::translate( "PWQ", "The password is just rotated old one" );
        case PWQ_ERROR_MIN_CLASSES:
            if ( auxerror )
                return QCoreApplication::translate( "PWQ", "The password contains less than %1 character classes" ).arg( ( long )auxerror );
            return QCoreApplication::translate( "PWQ", "The password does not contain enough character classes" );
        case PWQ_ERROR_MAX_CONSECUTIVE:
            if ( auxerror )
                return QCoreApplication::translate( "PWQ", "The password contains more than %1 same characters consecutively" ).arg( ( long )auxerror );
            return QCoreApplication::translate( "PWQ", "The password contains too many same characters consecutively" );
        case PWQ_ERROR_MAX_CLASS_REPEAT:
            if ( auxerror )
                return QCoreApplication::translate( "PWQ", "The password contains more than %1 characters of the same class consecutively" ).arg( ( long )auxerror );
            return QCoreApplication::translate( "PWQ", "The password contains too many characters of the same class consecutively" );
        case PWQ_ERROR_MAX_SEQUENCE:
            if ( auxerror )
                return QCoreApplication::translate( "PWQ", "The password contains monotonic sequence longer than %1 characters" ).arg( ( long )auxerror );
            return QCoreApplication::translate( "PWQ", "The password contains too long of a monotonic character sequence" );
        case PWQ_ERROR_EMPTY_PASSWORD:
            return QCoreApplication::translate( "PWQ", "No password supplied" );
        case PWQ_ERROR_RNG:
            return QCoreApplication::translate( "PWQ", "Cannot obtain random numbers from the RNG device" );
        case PWQ_ERROR_GENERATION_FAILED:
            return QCoreApplication::translate( "PWQ", "Password generation failed - required entropy too low for settings" );
        case PWQ_ERROR_CRACKLIB_CHECK:
            if ( auxerror )
            {
                /* Here the string comes from cracklib, don't free? */
                return QCoreApplication::translate( "PWQ", "The password fails the dictionary check - %1" ).arg( ( const char* )auxerror );
            }
            return QCoreApplication::translate( "PWQ", "The password fails the dictionary check" );
        case PWQ_ERROR_UNKNOWN_SETTING:
            if ( auxerror )
            {
                QString s = QCoreApplication::translate( "PWQ", "Unknown setting - %1" ).arg( ( const char* )auxerror );
                free( auxerror );
                return s;
            }
            return QCoreApplication::translate( "PWQ", "Unknown setting" );
        case PWQ_ERROR_INTEGER:
            if ( auxerror )
            {
                QString s = QCoreApplication::translate( "PWQ", "Bad integer value of setting - %1" ).arg( ( const char* )auxerror );
                free( auxerror );
                return s;
            }
            return QCoreApplication::translate( "PWQ", "Bad integer value" );
        case PWQ_ERROR_NON_INT_SETTING:
            if ( auxerror )
            {
                QString s = QCoreApplication::translate( "PWQ", "Setting %1 is not of integer type" ).arg( ( const char* )auxerror );
                free( auxerror );
                return s;
            }
            return QCoreApplication::translate( "PWQ", "Setting is not of integer type" );
        case PWQ_ERROR_NON_STR_SETTING:
            if ( auxerror )
            {
                QString s = QCoreApplication::translate( "PWQ", "Setting %1 is not of string type" ).arg( ( const char* )auxerror );
                free( auxerror );
                return s;
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
    pwquality_settings_t* m_settings;
    int m_rv;
    void* m_auxerror;
} ;

DEFINE_CHECK_FUNC( libpwquality )
{
    if ( !value.canConvert( QVariant::List ) )
    {
        cWarning() << "libpwquality settings is not a list";
        return;
    }

    QVariantList l = value.toList();
    unsigned int requirement_count = 0;
    auto settings = std::make_shared<PWSettingsHolder>();
    for ( const auto& v : l )
    {
        if ( v.type() == QVariant::String )
        {
            QString option = v.toString();
            int r = settings->set( option );
            if ( r )
                cWarning() << "unrecognized libpwquality setting" << option;
            else
            {
                cDebug() << " .. libpwquality setting" << option;
                ++requirement_count;
            }
        }
        else
            cWarning() << "unrecognized libpwquality setting" << v;
    }

    /* Something actually added? */
    if ( requirement_count )
    {
        checks.push_back(
            PasswordCheck(
                [settings]()
                {
                    return settings->explanation();
                },
                [settings]( const QString& s )
                {
                    int r = settings->check( s );
                    if ( r < 0 )
                        cWarning() << "libpwquality error" << r;
                    else if ( r < settings->arbitrary_minimum_strength )
                        cDebug() << "Password strength" << r << "too low";
                    return r >= settings->arbitrary_minimum_strength;
                }
            ) );
    }
}
#endif
