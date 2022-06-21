/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */
#ifndef UTILS_UMASK_H
#define UTILS_UMASK_H

#include "DllMacro.h"

#include <sys/types.h>

namespace CalamaresUtils
{
/** @brief Wrapper for umask(2)
 *
 * Like umask(2), sets the umask and returns the previous value of the mask.
 */
DLLEXPORT mode_t setUMask( mode_t u );

/** @brief RAII for setting and re-setting umask.
 *
 * Create an object of this class to set the umask,
 * and the umask is reset to its original value when
 * the object goes out of scope.
 */
class DLLEXPORT UMask
{
public:
    UMask( mode_t u );
    ~UMask();

    /** @brief a "safe" umask
     *
     * This umask will switch off group- and other- permissions for
     * files, so that the file cannot be read, written, or executed
     * except by the owner.
     */
    static constexpr mode_t Safe = 077;  // octal!
private:
    mode_t m_mode;
};
}  // namespace CalamaresUtils

#endif
