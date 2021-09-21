/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019-2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#include "Entropy.h"

#include <QFile>

#include <random>

CalamaresUtils::EntropySource
CalamaresUtils::getEntropy( int size, QByteArray& b )
{
    constexpr const char filler = char( 0xcb );

    b.fill( filler );
    b.clear();
    if ( size < 1 )
    {
        return EntropySource::None;
    }

    b.fill( filler, size );
    char* buffer = b.data();

    qint64 readSize = 0;
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
        buffer[ readSize++ ] = char( next & 0xffU ); \
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

CalamaresUtils::EntropySource
CalamaresUtils::getPrintableEntropy( int size, QString& s )
{
    s.clear();
    if ( size < 1 )
    {
        return EntropySource::None;
    }

    static const char salt_chars[] = { '.', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D',
                                       'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                                       'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                                       'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
    static_assert( sizeof( salt_chars ) == 64, "Missing salt_chars" );

    // Number of bytes we're going to need
    int byteSize = ( ( size * 6 ) / 8 ) + 1;
    QByteArray b;
    EntropySource r = getEntropy( byteSize, b );

    int bitsLeft = 0;
    int byteOffset = 0;
    qint64 next = 0;
    do
    {
        if ( bitsLeft < 6 )
        {
            next = ( next << 8 ) | b.at( byteOffset++ );
            bitsLeft += 8;
        }
        char c = salt_chars[ next & 0b0111111 ];
        next >>= 6;
        bitsLeft -= 6;
        s.append( c );
    } while ( ( s.length() < size ) && ( byteOffset < b.size() ) );

    if ( s.length() < size )
    {
        // It's incomplete, not really no-entropy
        return EntropySource::None;
    }

    return r;
}
