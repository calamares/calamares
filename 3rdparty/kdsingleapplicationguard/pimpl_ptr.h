/*
 *   SPDX-License-Identifier: LGPL-2.0-only
 *   License-Filename: LICENSES/LGPLv2-KDAB
 *
 *   The KD Tools Library is Copyright (C) 2001-2010 Klaralvdalens Datakonsult AB.
 */
#ifndef KDTOOLSCORE_PIMPL_PTR_H
#define KDTOOLSCORE_PIMPL_PTR_H

#include "kdtoolsglobal.h"

#ifndef DOXYGEN_RUN
namespace kdtools {
#endif

    template <typename T>
    class pimpl_ptr {
        KDAB_DISABLE_COPY( pimpl_ptr );
        T * d;
    public:
        pimpl_ptr() : d( new T ) {}
        explicit pimpl_ptr( T * t ) : d( t ) {}
        ~pimpl_ptr() { delete d; d = nullptr; }

        T * get() { return d; }
        const T * get() const { return d; }

        T * operator->() { return get(); }
        const T * operator->() const { return get(); }

        T & operator*() { return *get(); }
        const T & operator*() const { return *get(); }

        KDAB_IMPLEMENT_SAFE_BOOL_OPERATOR( get() )
    };

    // these are not implemented, so's we can catch their use at
    // link-time. Leaving them undeclared would open up a comparison
    // via operator unspecified-bool-type().
    template <typename T, typename S>
    void operator==( const pimpl_ptr<T> &, const pimpl_ptr<S> & );
    template <typename T, typename S>
    void operator!=( const pimpl_ptr<T> &, const pimpl_ptr<S> & );

#ifndef DOXYGEN_RUN
} // namespace kdtools
#endif

#endif /* KDTOOLSCORE_PIMPL_PTR_H */

