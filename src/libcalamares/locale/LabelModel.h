/* === This file is part of Calamares - <https://github.com/calamares> ===
 * 
 *   SPDX-FileCopyrightText: 2019 Camilo Higuita <milo.h@aol.com>
 *   SPDX-FileCopyrightText: 2019-2020 Adriaan de Groot <groot@kde.org>
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
 *
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
 *
 */

#ifndef LOCALE_LABELMODEL_H
#define LOCALE_LABELMODEL_H

#include "DllMacro.h"
#include "Label.h"

#include <QAbstractListModel>
#include <QVector>


namespace CalamaresUtils
{
namespace Locale
{

class DLLEXPORT LabelModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum
    {
        LabelRole = Qt::DisplayRole,
        EnglishLabelRole = Qt::UserRole + 1
    };

    LabelModel( const QStringList& locales, QObject* parent = nullptr );
    virtual ~LabelModel() override;

    int rowCount( const QModelIndex& parent ) const override;

    QVariant data( const QModelIndex& index, int role ) const override;
    QHash< int, QByteArray > roleNames() const override;

    /** @brief Gets locale information for entry #n
     *
     * This is the backing data for the model; if @p row is out-of-range,
     * returns a reference to en_US.
     */
    const Label& locale( int row ) const;

    /// @brief Returns all of the locale Ids (e.g. en_US) put into this model.
    const QStringList& localeIds() const { return m_localeIds; }

    /** @brief Searches for an item that matches @p predicate
     *
     * Returns the row number of the first match, or -1 if there isn't one.
     */
    int find( std::function< bool( const QLocale& ) > predicate ) const;
    int find( std::function< bool( const Label& ) > predicate ) const;
    /// @brief Looks for an item using the same locale, -1 if there isn't one
    int find( const QLocale& ) const;
    /// @brief Looks for an item that best matches the 2-letter country code
    int find( const QString& countryCode ) const;

private:
    QVector< Label* > m_locales;
    QStringList m_localeIds;
};

/** @brief Returns a model with all available translations.
 *
 * The translations are set when Calamares is compiled; the list
 * is provided by CMake via the CALAMARES_TRANSLATION_LANGUAGES
 * #define.
 *
 * This model is a singleton and can be shared.
 *
 * NOTE: While the model is not typed const, it should be. Do not modify.
 */
DLLEXPORT LabelModel* availableTranslations();
}  // namespace Locale
}  // namespace CalamaresUtils
#endif
