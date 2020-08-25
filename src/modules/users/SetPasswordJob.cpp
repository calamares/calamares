/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2017 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "SetPasswordJob.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Entropy.h"
#include "utils/Logger.h"

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
SetPasswordJob::make_salt( int length )
{
    Q_ASSERT( length >= 8 );
    Q_ASSERT( length <= 128 );

    QString salt_string;
    CalamaresUtils::EntropySource source = CalamaresUtils::getPrintableEntropy( length, salt_string );
    if ( salt_string.length() != length )
    {
        cWarning() << "getPrintableEntropy returned string of length" << salt_string.length() << "expected" << length;
        salt_string.truncate( length );
    }
    if ( source != CalamaresUtils::EntropySource::URandom )
    {
        cWarning() << "Entropy data for salt is low-quality.";
    }

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

    if ( m_userName == "root" && m_newPassword.isEmpty() )  //special case for disabling root account
    {
        int ec = CalamaresUtils::System::instance()->targetEnvCall( { "passwd", "-dl", m_userName } );
        if ( ec )
            return Calamares::JobResult::error( tr( "Cannot disable root account." ),
                                                tr( "passwd terminated with error code %1." ).arg( ec ) );
        return Calamares::JobResult::ok();
    }

    QString encrypted = QString::fromLatin1( crypt( m_newPassword.toUtf8(), make_salt( 16 ).toUtf8() ) );

    int ec = CalamaresUtils::System::instance()->targetEnvCall( { "usermod", "-p", encrypted, m_userName } );
    if ( ec )
        return Calamares::JobResult::error( tr( "Cannot set password for user %1." ).arg( m_userName ),
                                            tr( "usermod terminated with error code %1." ).arg( ec ) );

    return Calamares::JobResult::ok();
}
