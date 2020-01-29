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

#include "Entropy.h"

#include <QFile>

#include <random>

CalamaresUtils::EntropySource
CalamaresUtils::getEntropy( int size, QByteArray& b )
{
    b.clear();
    b.resize( size );
    char* buffer = b.data();
    std::fill( buffer, buffer + size, 0xcb );

    int readSize = 0;
    QFile urandom( "/dev/urandom" );
    if ( urandom.exists() && urandom.open( QIODevice::ReadOnly ) )
    {
        readSize = urandom.read( buffer, size );
        urandom.close();
    }

    if ( readSize >= size )
    {
        return EntropySource::URandom;
    }

    // If it wasn't available, or did not return enough bytes,
    // complete it with twister (and tell the client).
    std::random_device r;
    std::seed_seq seed { r(), r(), r(), r(), r(), r(), r(), r() };
    std::mt19937_64 twister( seed );

    std::uint64_t next = 0;

    do
    {
        next = twister();
        // Eight times, for a 64-bit next
#define GET_ONE_BYTE \
    if ( readSize < size ) \
    { \
        buffer[ readSize++ ] = next & 0xff; \
        next = next >> 8; \
    }
        GET_ONE_BYTE
        GET_ONE_BYTE
        GET_ONE_BYTE
        GET_ONE_BYTE
        GET_ONE_BYTE
        GET_ONE_BYTE
        GET_ONE_BYTE
        GET_ONE_BYTE
    } while ( readSize < size );

    return EntropySource::Twister;
}
