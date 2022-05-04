/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Camilo Higuita <milo.h@aol.com>
 *   SPDX-FileCopyrightText: 2019-2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#ifndef LOCALE_TRANSLATIONSMODEL_H
#define LOCALE_TRANSLATIONSMODEL_H

#include "DllMacro.h"
#include "Translation.h"

#include <QAbstractListModel>
#include <QVector>


namespace CalamaresUtils
{
namespace Locale
{

class DLLEXPORT TranslationsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum
    {
        LabelRole = Qt::DisplayRole,
        EnglishLabelRole = Qt::UserRole + 1
    };

    TranslationsModel( const QStringList& locales, QObject* parent = nullptr );
    ~TranslationsModel() override;

    int rowCount( const QModelIndex& parent ) const override;

    QVariant data( const QModelIndex& index, int role ) const override;
    QHash< int, QByteArray > roleNames() const override;

    /** @brief Gets locale information for entry #n
     *
     * This is the backing data for the model; if @p row is out-of-range,
     * returns a reference to en_US.
     */
    const Translation& locale( int row ) const;

    /// @brief Returns all of the locale Ids (e.g. en_US) put into this model.
    const QStringList& localeIds() const { return m_localeIds; }

    /** @brief Searches for an item that matches @p predicate
     *
     * Returns the row number of the first match, or -1 if there isn't one.
     */
    int find( std::function< bool( const QLocale& ) > predicate ) const;
    int find( std::function< bool( const Translation& ) > predicate ) const;
    /// @brief Looks for an item using the same locale, -1 if there isn't one
    int find( const QLocale& ) const;
    /// @brief Looks for an item that best matches the 2-letter country code
    int find( const QString& countryCode ) const;
    /// @brief Looks up a translation Id
    int find( const Translation::Id& id ) const;

private:
    QVector< Translation* > m_locales;
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
DLLEXPORT TranslationsModel* availableTranslations();
}  // namespace Locale
}  // namespace CalamaresUtils
#endif
