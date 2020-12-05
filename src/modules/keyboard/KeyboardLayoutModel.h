/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef KEYBOARDLAYOUTMODEL_H
#define KEYBOARDLAYOUTMODEL_H

#include "keyboardwidget/keyboardglobal.h"

#include <QAbstractListModel>
#include <QMap>
#include <QMetaType>
#include <QObject>

/** @brief A list model with an xkb key and a human-readable string
 *
 * This model acts like it has a single selection, as well.
 */
class XKBListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY( int currentIndex WRITE setCurrentIndex READ currentIndex NOTIFY currentIndexChanged )

public:
    enum
    {
        LabelRole = Qt::DisplayRole,  ///< Human-readable
        KeyRole = Qt::UserRole  ///< xkb identifier
    };

    explicit XKBListModel( QObject* parent = nullptr );

    int rowCount( const QModelIndex& = QModelIndex() ) const override;
    QVariant data( const QModelIndex& index, int role ) const override;
    /** @brief xkb key for a given index (row)
     *
     * This is like calling data( QModelIndex( index ), KeyRole ).toString(),
     * but shorter and faster. Can return an empty string if index is invalid.
     */
    QString key( int index ) const;

    /** @brief human-readable label for a given index (row)
     *
     * This is like calling data( QModelIndex( index ), LabelRole ).toString(),
     * but shorter and faster. Can return an empty string if index is invalid.
     */
    QString label( int index ) const;

    QHash< int, QByteArray > roleNames() const override;

    void setCurrentIndex( int index );
    int currentIndex() const { return m_currentIndex; }

signals:
    void currentIndexChanged( int index );

protected:
    struct ModelInfo
    {
        /// XKB identifier
        QString key;
        /// Human-readable
        QString label;
    };
    QVector< ModelInfo > m_list;
    int m_currentIndex = -1;
    const char* m_contextname = nullptr;
};


/** @brief A list model of the physical keyboard formats ("models" in xkb)
 *
 * This model acts like it has a single selection, as well.
 */
class KeyboardModelsModel : public XKBListModel
{
    Q_OBJECT

public:
    explicit KeyboardModelsModel( QObject* parent = nullptr );

    /// @brief Set the index back to PC105 (the default physical model)
    void setCurrentIndex() { XKBListModel::setCurrentIndex( m_defaultPC105 ); }

private:
    int m_defaultPC105 = -1;  ///< The index of pc105, if there is one
};

/** @brief A list of keyboard layouts (arrangements of keycaps)
 *
 * Layouts can have a list of associated Variants, so this
 * is slightly more complicated than the "regular" XKBListModel.
 */
class KeyboardLayoutModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY( int currentIndex WRITE setCurrentIndex READ currentIndex NOTIFY currentIndexChanged )

public:
    enum Roles : int
    {
        KeyboardVariantsRole = Qt::UserRole,
        KeyboardLayoutKeyRole
    };

    KeyboardLayoutModel( QObject* parent = nullptr );

    int rowCount( const QModelIndex& parent = QModelIndex() ) const override;

    QVariant data( const QModelIndex& index, int role ) const override;

    void setCurrentIndex( int index );
    int currentIndex() const;
    const QPair< QString, KeyboardGlobal::KeyboardInfo > item( const int& index ) const;

    /** @brief xkb key for a given index (row)
     *
     * This is like calling data( QModelIndex( index ), KeyboardLayoutKeyRole ).toString(),
     * but shorter and faster. Can return an empty string if index is invalid.
     */
    QString key( int index ) const;

protected:
    QHash< int, QByteArray > roleNames() const override;

private:
    void init();
    int m_currentIndex = -1;
    QList< QPair< QString, KeyboardGlobal::KeyboardInfo > > m_layouts;

signals:
    void currentIndexChanged( int index );
};

/** @brief A list of variants (xkb id and human-readable)
 *
 * The variants that are available depend on the Layout that is used,
 * so the `setVariants()` function can be used to update the variants
 * when the two models are related.
 */
class KeyboardVariantsModel : public XKBListModel
{
    Q_OBJECT

public:
    explicit KeyboardVariantsModel( QObject* parent = nullptr );

    void setVariants( QMap< QString, QString > variants );
};

/** @brief Adjust to changes in application language.
 */
void retranslateKeyboardModels();

#endif  // KEYBOARDLAYOUTMODEL_H
