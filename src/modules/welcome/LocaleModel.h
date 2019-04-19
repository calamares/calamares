/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

#ifndef WELCOME_LOCALEMODEL_H
#define WELCOME_LOCALEMODEL_H

#include <QAbstractListModel>
#include <QStyledItemDelegate>
#include <QVector>

#include "utils/LocaleLabel.h"

class LocaleModel : public QAbstractListModel
{
public:
    using LocaleLabel = CalamaresUtils::LocaleLabel;

    enum
    {
        LabelRole = Qt::DisplayRole,
        EnglishLabelRole = Qt::UserRole + 1
    };

    LocaleModel( const QStringList& locales, QObject* parent = nullptr );
    virtual ~LocaleModel() override;

    int rowCount( const QModelIndex& parent ) const override;

    QVariant data( const QModelIndex& index, int role ) const override;

    /** @brief Gets locale information for entry #n
     *
     * This is the backing data for the model; if @p row is out-of-range,
     * returns a reference to en_US.
     */
    const LocaleLabel& locale( int row );

    /** @brief Searches for an item that matches @p predicate
     *
     * Returns the row number of the first match, or -1 if there isn't one.
     */
    int find( std::function<bool( const QLocale& )> predicate ) const;
    int find( std::function<bool( const LocaleLabel& )> predicate ) const;
    int find( const QLocale& ) const;

private:
    QVector< LocaleLabel > m_locales;
} ;

class LocaleTwoColumnDelegate : public QStyledItemDelegate
{
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    void paint( QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index ) const override;
} ;

#endif
