/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PYTHONQTVIEWSTEP_H
#define PYTHONQTVIEWSTEP_H

#include "ViewStep.h"

#include <PythonQt.h>

namespace Calamares
{

class PythonQtViewStep : public Calamares::ViewStep
{
    Q_OBJECT
public:
    PythonQtViewStep( PythonQtObjectPtr cxt, QObject* parent = nullptr );

    QString prettyName() const override;

    QWidget* widget() override;

    void next() override;
    void back() override;
    void onLeave() override;
    void onActivate() override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    JobList jobs() const override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

    QWidget* createScriptingConsole();

protected:
    QWidget* m_widget;

private:
    PythonQtObjectPtr m_cxt;
    PythonQtObjectPtr m_obj;
};

}  // namespace Calamares

#endif  // PYTHONQTVIEWSTEP_H
