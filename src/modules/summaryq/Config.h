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

#include <QObject>
#include <QAbstractListModel>
#include <QQmlParserStatus>
#include "viewpages/ViewStep.h"

class SummaryQmlViewStep;

struct StepSummary
{
    QString title;
    QString message;
};

class SummaryModel : public QAbstractListModel
{
  Q_OBJECT
public:
    explicit SummaryModel(QObject *parent = nullptr);
    int rowCount( const QModelIndex& = QModelIndex() ) const override;
    QVariant data( const QModelIndex& index, int role ) const override;

    void setSummary(const Calamares::ViewStepList &steps);

protected:
    QHash< int, QByteArray > roleNames() const override;
private:
    QVector<StepSummary*> m_summary;
};

class Config : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_PROPERTY(QString message MEMBER m_message NOTIFY messageChanged CONSTANT)
    Q_PROPERTY(QString title MEMBER m_title NOTIFY titleChanged CONSTANT)
    Q_PROPERTY(SummaryModel * summaryModel READ summaryModel CONSTANT FINAL)

public:
    explicit Config(QObject *parent = nullptr);
    virtual void componentComplete() override;
    virtual void classBegin() override {}

    void refresh();
    void init();

    SummaryModel * summaryModel() const
    {
        return m_summary;
    }

private:
    Calamares::ViewStepList stepsForSummary( const Calamares::ViewStepList& allSteps ) const;
    const SummaryQmlViewStep* m_thisViewStep;
    SummaryModel *m_summary;

    QString m_message;
    QString m_title;

signals:
    void messageChanged();
    void titleChanged();
};
#endif
