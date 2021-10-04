/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019-2020, Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2020, Camilo Higuita <milo.h@aol.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef SUMMARY_CONFIG_H
#define SUMMARY_CONFIG_H

#include "viewpages/ViewStep.h"

#include <QAbstractListModel>
#include <QObject>
#include <QQmlParserStatus>

class Config;

/** @brief Data for one step
 *
 * A step generally has a text description, but **may** have a
 * QWidget. There is no ownership of the QWidget, that is assumed
 * to be handed off to some owning parent-widget.
 */
struct StepSummary
{
    QString title;
    QString message;
    QWidget* widget = nullptr;
};

class SummaryModel : public QAbstractListModel
{
    Q_OBJECT
    friend class Config;

public:
    enum Roles : int
    {
        TitleRole = Qt::DisplayRole,  // Name of the step
        MessageRole = Qt::UserRole,  // String saying what it will do
        WidgetRole,  // Pointer to widget
    };

    explicit SummaryModel( QObject* parent = nullptr );
    int rowCount( const QModelIndex& = QModelIndex() ) const override;
    QVariant data( const QModelIndex& index, int role ) const override;

protected:
    QHash< int, QByteArray > roleNames() const override;

private:
    /** @brief Sets the model data from @p steps
     *
     * Replaces the list of summaries with summaries given by
     * the jobs and ViewSteps objects in @p steps. If @p withWidgets
     * is @c true, then also queries for widget summaries alongside
     * the text summaries for each step.
     */
    void setSummaryList( const Calamares::ViewStepList& steps, bool withWidgets = false );

    QVector< StepSummary > m_summary;
};

class Config : public QObject
{
    Q_OBJECT

    ///@brief Name of this summary (generally, "Summary")
    Q_PROPERTY( QString title READ title NOTIFY titleChanged )
    ///@brief Description of what the summary means
    Q_PROPERTY( QString message READ message NOTIFY messageChanged )

    Q_PROPERTY( QAbstractListModel* summaryModel READ summaryModel CONSTANT FINAL )

public:
    explicit Config( QObject* parent = nullptr );

    ///@brief Include widgets in the model?
    enum class Widgets
    {
        Disabled,
        Enabled
    };

    static Calamares::ViewStepList stepsForSummary( const Calamares::ViewStep* upToHere );

    ///@brief Called later, to load the model once all viewsteps are there
    void collectSummaries( const Calamares::ViewStep* upToHere, Widgets withWidgets );
    ///@brief Clear the model of steps (to avoid dangling widgets)
    void clearSummaries();

    QAbstractListModel* summaryModel() const { return m_summary; }

    QString title() const { return m_title; }
    QString message() const { return m_message; }

private:
    void retranslate();

    SummaryModel* m_summary;

    QString m_title;
    QString m_message;

Q_SIGNALS:
    void titleChanged( QString title );
    void messageChanged( QString message );
};
#endif
