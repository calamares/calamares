/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2020, Adriaan de Groot <groot@kde.org>
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

#ifndef QMLVIEWSTEP_H
#define QMLVIEWSTEP_H

#include "utils/Qml.h"
#include "viewpages/ViewStep.h"

class QQmlComponent;
class QQuickItem;
class QQuickWidget;
class WaitingWidget;

namespace Calamares
{

/** @brief A viewstep that uses QML for the UI
 *
 * This is generally a **base** class for other view steps, but
 * it can be used stand-alone for viewsteps that don't really have
 * any functionality.
 *
 * Most subclasses will override the following methods:
 * - prettyName() to provide a meaningful human-readable name
 * - jobs() if there is real work to be done during installation
 * - getConfig() to return a meaningful configuration object
 *
 * For details on the interaction between the config object and
 * the QML in the module, see the module documentation:
 *      src/modules/README.md
 */
class QmlViewStep : public Calamares::ViewStep
{
    Q_OBJECT
public:
    /** @brief Creates a QML view step
     *
     * The search behavior for the actial QML depends on a QmlSearch value.
     * This is set through common configuration key *qmlSearch*.
     * The filename used comes from the module identifier, or can be
     * set in the configuration file through *qmlFilename*.
     *
     * @see Qml.h for available Calamares internals.
     */
    QmlViewStep( QObject* parent = nullptr );
    virtual ~QmlViewStep() override;

    virtual QString prettyName() const override;

    virtual QWidget* widget() override;
    virtual QSize widgetMargins( Qt::Orientations panelSides ) override;

    virtual bool isNextEnabled() const override;
    virtual bool isBackEnabled() const override;

    virtual bool isAtBeginning() const override;
    virtual bool isAtEnd() const override;

    virtual void onActivate() override;
    virtual void onLeave() override;

    /// @brief QML widgets don't produce jobs by default
    virtual JobList jobs() const override;

    /// @brief Configure search paths; subclasses should call this at the **end** of their own implementation
    virtual void setConfigurationMap( const QVariantMap& configurationMap ) override;

protected:
    /** @brief Gets a pointer to the Config of this view step
     *
     * Parts of the configuration of the viewstep can be passed to QML
     * by placing them in a QObject (as properties). The default
     * implementation returns nullptr, for no-config.
     *
     * Ownership of the config object remains with the ViewStep; it is possible
     * to return a pointer to a member variable.
     *
     * This object is made available as a context-property *config* in QML.
     */
    virtual QObject* getConfig();

    /** @brief Adds a context property for this QML file
     *
     * Does not take ownership.
     */
    void setContextProperty( const char* name, QObject* property );

private Q_SLOTS:
    void loadComplete();

private:
    /// @brief Swap out the spinner for the QQuickWidget
    void showQml();
    /// @brief Show error message in spinner.
    void showFailedQml();

    /// @brief Controls where m_name is searched
    CalamaresUtils::QmlSearch m_searchMethod;

    QString m_name;
    QString m_qmlFileName;

    QWidget* m_widget = nullptr;
    WaitingWidget* m_spinner = nullptr;
    QQuickWidget* m_qmlWidget = nullptr;
    QQmlComponent* m_qmlComponent = nullptr;
    QQuickItem* m_qmlObject = nullptr;
};

}  // namespace Calamares
#endif
