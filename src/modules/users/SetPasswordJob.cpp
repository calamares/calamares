/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2017, Teo Mrnjavac <teo@kde.org>
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

#include <SetPasswordJob.h>

#include "JobQueue.h"
#include "GlobalStorage.h"
#include "utils/Logger.h"
#include "utils/CalamaresUtilsSystem.h"

#include <QDir>

#include <random>

#ifndef NO_CRYPT_H
#include <crypt.h>
#endif
#include <unistd.h>


SetPasswordJob::SetPasswordJob( const QString& userName, const QString& newPassword )
    : Calamares::Job()
    , m_userName( userName )
    , m_newPassword( newPassword )
{
}


QString
SetPasswordJob::prettyName() const
{
    return tr( "Set password for user %1" ).arg( m_userName );
}


QString
SetPasswordJob::prettyStatusMessage() const
{
    return tr( "Setting password for user %1." ).arg( m_userName );
}


/// Returns a modular hashing salt for method 6 (SHA512) with a 16 character random salt.
QString
SetPasswordJob::make_salt(int length)
{
    Q_ASSERT(length >= 8);
    Q_ASSERT(length <= 128);

    static const char salt_chars[] = {
        '.', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B',
        'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
        'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
        's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

    static_assert( sizeof(salt_chars) == 64, "Missing salt_chars");

    std::random_device r;
    std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    std::mt19937_64 twister(seed);

    std::uint64_t next;
    int current_length = 0;

    QString salt_string;
    salt_string.reserve(length + 10);

    while ( current_length < length )
    {
        next = twister();
        // In 64 bits, we have 10 blocks of 6 bits; map each block of 6 bits
        // to a single salt character.
        for ( unsigned int char_count = 0; char_count < 10; ++char_count )
        {
            char c = salt_chars[next & 0b0111111];
            next >>= 6;
            salt_string.append( c );
            if (++current_length >= length)
                break;
        }
    }

    salt_string.truncate( length );
    salt_string.insert( 0, "$6$" );
    salt_string.append( '$' );
    return salt_string;
}

Calamares::JobResult
SetPasswordJob::exec()
{
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    QDir destDir( gs->value( "rootMountPoint" ).toString() );
    if ( !destDir.exists() )
        return Calamares::JobResult::error( tr( "Bad destination system path." ),
                                            tr( "rootMountPoint is %1" ).arg( destDir.absolutePath() ) );

    if ( m_userName == "root" &&
         m_newPassword.isEmpty() ) //special case for disabling root account
    {
        int ec = CalamaresUtils::System::instance()->
                 targetEnvCall( { "passwd",
                                  "-dl",
                                  m_userName } );
        if ( ec )
            return Calamares::JobResult::error( tr( "Cannot disable root account." ),
                                                tr( "passwd terminated with error code %1." )
                                                    .arg( ec ) );
        return Calamares::JobResult::ok();
    }

    QString encrypted = QString::fromLatin1(
                            crypt( m_newPassword.toUtf8(),
                                   make_salt( 16 ).toUtf8() ) );

    int ec = CalamaresUtils::System::instance()->
                          targetEnvCall( { "usermod",
                                           "-p",
                                           encrypted,
                                           m_userName } );
    if ( ec )
        return Calamares::JobResult::error( tr( "Cannot set password for user %1." )
                                                .arg( m_userName ),
                                            tr( "usermod terminated with error code %1." )
                                                .arg( ec ) );

    return Calamares::JobResult::ok();
}
