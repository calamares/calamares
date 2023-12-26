/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020, Camilo Higuita <milo.h@aol.com>
 *   SPDX-FileCopyrightText: 2021 Anke Boersma <demm@kaosx.us>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "SummaryModel.h"

#include <QWidget>

SummaryModel::SummaryModel( QObject* parent )
    : QAbstractListModel( parent )
{
}

QHash< int, QByteArray >
SummaryModel::roleNames() const
{
    // Not including WidgetRole here because that wouldn't make sense
    // in a QML context which is where the roleNames are important.
    return { { TitleRole, "title" }, { MessageRole, "message" } };
}

QVariant
SummaryModel::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() )
    {
        return QVariant();
    }
    auto& item = m_summary.at( index.row() );
    switch ( role )
    {
    case TitleRole:
        return item.title;
    case MessageRole:
        return item.message;
    case WidgetRole:
        return item.widget ? QVariant::fromValue( item.widget ) : QVariant();
    default:
        return QVariant();
    }
}

int
SummaryModel::rowCount( const QModelIndex& ) const
{
    return m_summary.count();
}

void
SummaryModel::setSummaryList( const Calamares::ViewStepList& steps, bool withWidgets )
{
    beginResetModel();
    m_summary.clear();

    for ( Calamares::ViewStep* step : steps )
    {
        QString text = step->prettyStatus();
        QWidget* widget = withWidgets ? step->createSummaryWidget() : nullptr;

        if ( text.isEmpty() && !widget )
        {
            continue;
        }

        m_summary << StepSummary { step->prettyName(), text, widget };
    }
    endResetModel();
}
