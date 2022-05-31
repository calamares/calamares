/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

/*
 * KPMCore header file inclusion.
 *
 * Includes the system KPMCore headers without warnings (by switching off
 * the expected warnings).
 */
#ifndef PARTITION_KPMHELPER_H
#define PARTITION_KPMHELPER_H

// The kpmcore headers are not C++17 warning-proof, especially
// with picky compilers like Clang 10. Since we use Clang for the
// find-all-the-warnings case, switch those warnings off for
// the we-can't-change-them system headers.
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#pragma clang diagnostic ignored "-Wsuggest-destructor-override"
#pragma clang diagnostic ignored "-Winconsistent-missing-destructor-override"
// Because of __lastType
#pragma clang diagnostic ignored "-Wreserved-identifier"
#endif

#include <backend/corebackend.h>
#include <core/device.h>
#include <core/lvmdevice.h>
#include <core/partition.h>
#include <core/partitionrole.h>
#include <core/partitiontable.h>
#include <fs/filesystem.h>
#include <fs/filesystemfactory.h>

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#endif
