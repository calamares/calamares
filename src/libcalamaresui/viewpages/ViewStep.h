/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#ifndef VIEWSTEP_H
#define VIEWSTEP_H

#include <QObject>

#include "../UiDllMacro.h"
#include "Typedefs.h"

namespace Calamares
{

/**
 * @brief The ViewStep class is the base class for all view modules.
 * A view module is a Calamares module which has at least one UI page (exposed as
 * ViewStep::widget), and can optionally create Calamares jobs at runtime.
 * As of early 2017, a view module can be implemented by deriving from ViewStep
 * in C++ (as a Qt Plugin) or in Python with the PythonQt interface (which also
 * mimics the ViewStep class).
 */
class UIDLLEXPORT ViewStep : public QObject
{
    Q_OBJECT
public:
    explicit ViewStep( QObject* parent = nullptr );
    virtual ~ViewStep();

    virtual QString prettyName() const = 0;
    virtual QString prettyStatus() const;

    /**
     * Optional. Should return a widget which will be inserted in the summary
     * page. The caller takes ownership of the widget.
     */
    virtual QWidget* createSummaryWidget() const;

    //TODO: we might want to make this a QSharedPointer
    virtual QWidget* widget() = 0;

    virtual void next() = 0;
    virtual void back() = 0;

    virtual bool isNextEnabled() const = 0;
    virtual bool isBackEnabled() const = 0;

    virtual bool isAtBeginning() const = 0;
    virtual bool isAtEnd() const = 0;

    /**
     * @brief onActivate called every time a ViewStep is shown, either by going forward
     * or backward.
     * The default implementation does nothing.
     */
    virtual void onActivate();

    /**
     * @brief onLeave called every time a ViewStep is hidden and control passes to
     * another ViewStep, either by going forward or backward.
     * The default implementation does nothing.
     */
    virtual void onLeave();

    virtual QList< job_ptr > jobs() const = 0;

    void setModuleInstanceKey( const QString& instanceKey );
    QString moduleInstanceKey() const { return m_instanceKey; }

    virtual void setConfigurationMap( const QVariantMap& configurationMap );

signals:
    void nextStatusChanged( bool status );
    void done();

protected:
    QString m_instanceKey;
};

}

#endif // VIEWSTEP_H
