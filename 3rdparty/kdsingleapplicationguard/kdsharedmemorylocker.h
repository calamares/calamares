/*
 *   SPDX-FileCopyrightText: 2001-2010 Klaralvdalens Datakonsult AB.
 *   SPDX-License-Identifier: LGPL-2.0-only
 *
 *   The KD Tools Library is Copyright (C) 2001-2010 Klaralvdalens Datakonsult AB.
 */
#ifndef __KDTOOLS__CORE__KDSHAREDMEMORYLOCKER_H
#define __KDTOOLS__CORE__KDSHAREDMEMORYLOCKER_H

#include "kdtoolsglobal.h"

#if QT_VERSION < 0x040400 && !defined( DOXYGEN_RUN )
#ifdef Q_CC_GNU
#warning "Can't use KDTools KDSharedMemoryLocker with Qt versions prior to 4.4"
#endif
#else

class QSharedMemory;

#ifndef DOXYGEN_RUN
namespace kdtools
{
#endif

class KDTOOLSCORE_EXPORT KDSharedMemoryLocker
{
    Q_DISABLE_COPY( KDSharedMemoryLocker )
public:
    KDSharedMemoryLocker( QSharedMemory* mem );
    ~KDSharedMemoryLocker();

private:
    QSharedMemory* const mem;
};

#ifndef DOXYGEN_RUN
}
#endif

#endif

#endif
