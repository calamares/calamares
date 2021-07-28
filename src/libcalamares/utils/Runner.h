/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#ifndef UTILS_RUNNER_H
#define UTILS_RUNNER_H

#include "CalamaresUtilsSystem.h"

#include <QObject>
#include <QStringList>

#include <chrono>
#include <memory>
#include <optional>

namespace Calamares
{
namespace Utils
{

using RunLocation = CalamaresUtils::System::RunLocation;

class Runner : public QObject
{
    Q_OBJECT

public:
    Runner();
    Runner( const QStringList& command );
    virtual ~Runner() override;

    Runner& setCommand( const QStringList& command );
    Runner& setLocation( RunLocation r );
    Runner& setWorkingDirectory( const QString& directory );
    // TODO: maybe with QDir as well?
    Runner& setTimeout( std::chrono::seconds timeout );
    Runner& setInput( const QString& stdin );

private:
    struct Private;
    std::unique_ptr< Private > d;
};

}  // namespace Utils
}  // namespace Calamares

#endif
