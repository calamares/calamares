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
 */
class QmlViewStep : public Calamares::ViewStep
{
    Q_OBJECT

public:
    enum class QmlSearch
    {
        QrcOnly,
        BrandingOnly,
        Both
    };

    /** @brief Creates a QML view step
     *
     * The name should not have an extension or schema or anything;
     * just the plain name, which will be searched as "/<name>.qml" in
     * QRC files, or "<name>.qml" in suitable branding paths.
     * The search behavior depends on a QmlSearch value.
     */
    QmlViewStep( const QString& name, QObject* parent = nullptr );
    virtual ~QmlViewStep() override;

    virtual QString prettyName() const override;

    virtual QWidget* widget() override;

    virtual bool isNextEnabled() const override;
    virtual bool isBackEnabled() const override;

    virtual bool isAtBeginning() const override;
    virtual bool isAtEnd() const override;

    virtual void onActivate() override;
    virtual void onLeave() override;

    /// @brief QML widgets don't produce jobs by default
    virtual JobList jobs() const override;

    /// @brief Configure search paths; subclasses should call this as well
    virtual void setConfigurationMap( const QVariantMap& configurationMap ) override;

private Q_SLOTS:
    void loadComplete();

private:
    /// @brief Swap out the spinner for the QQuickWidget
    void showQml();
    /// @brief Show error message in spinner.
    void showFailedQml();

    /// @brief Controls where m_name is searched
    QmlSearch m_searchMethod;

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
