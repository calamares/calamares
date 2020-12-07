/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */
#ifndef CALAMARES_REQUIREMENTSCHECKER_H
#define CALAMARES_REQUIREMENTSCHECKER_H

#include "modulesystem/Requirement.h"

#include <QFutureWatcher>
#include <QObject>
#include <QTimer>
#include <QVector>

namespace Calamares
{

class Module;
class RequirementsModel;

/** @brief A manager-class that checks all the module requirements
 *
 * Asynchronously checks the requirements for each module, and
 * emits progress signals as appropriate.
 */
class RequirementsChecker : public QObject
{
    Q_OBJECT

public:
    RequirementsChecker( QVector< Module* > modules, RequirementsModel* model, QObject* parent = nullptr );
    ~RequirementsChecker() override;

public Q_SLOTS:
    /// @brief Start checking all the requirements
    void run();

    /// @brief Called when requirements are reported by a module
    void addCheckedRequirements( Module* );

    /// @brief Called when all requirements have been checked
    void finished();

    /// @brief Called periodically while requirements are being checked
    void reportProgress();

signals:
    /// @brief Human-readable progress message
    void requirementsProgress( const QString& );
    /// @brief Emitted after requirementsComplete
    void done();

private:
    QVector< Module* > m_modules;

    using Watcher = QFutureWatcher< void >;
    QVector< Watcher* > m_watchers;

    RequirementsModel* m_model;

    QTimer* m_progressTimer;
    unsigned m_progressTimeouts;
};

}  // namespace Calamares

#endif
