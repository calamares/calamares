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

/** @brief A list model of the physical keyboard formats ("models" in xkb)
 *
 * This model acts like it has a single selection, as well.
 */
class KeyboardModelsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY( int currentIndex WRITE setCurrentIndex READ currentIndex NOTIFY currentIndexChanged )

public:
    enum
    {
        LabelRole = Qt::DisplayRole,  ///< Human-readable
        KeyRole = Qt::UserRole  ///< xkb identifier
    };

    explicit KeyboardModelsModel( QObject* parent = nullptr );

    int rowCount( const QModelIndex& ) const override;
    QVariant data( const QModelIndex& index, int role ) const override;
    /** @brief xkb key for a given index (row)
     *
     * This is like calling data( QModelIndex( index ), KeyRole ).toString(),
     * but shorter and faster. Can return an empty string if index is invalid.
     */
    QString modelKey( int index ) const;

    /** @brief human-readable label for a given index (row)
     *
     * This is like calling data( QModelIndex( index ), LabelRole ).toString(),
     * but shorter and faster. Can return an empty string if index is invalid.
     */
    QString modelLabel( int index ) const;

    QHash< int, QByteArray > roleNames() const override;

    void setCurrentIndex( int index );
    /// @brief Set the index back to PC105 (the default physical model)
    void setCurrentIndex() { setCurrentIndex( m_defaultPC105 ); }
    int currentIndex() const { return m_currentIndex; }

signals:
    void currentIndexChanged( int index );

private:
    struct ModelInfo
    {
        /// XKB identifier
        QString key;
        /// Human-readable
        QString label;
    };
    QVector< ModelInfo > m_list;
    int m_currentIndex = -1;
    int m_defaultPC105 = -1;  ///< The index of pc105, if there is one
};

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

    void setCurrentIndex( const int& index );
    int currentIndex() const;
    const QPair< QString, KeyboardGlobal::KeyboardInfo > item( const int& index ) const;

protected:
    QHash< int, QByteArray > roleNames() const override;

private:
    void init();
    int m_currentIndex = -1;
    QList< QPair< QString, KeyboardGlobal::KeyboardInfo > > m_layouts;

signals:
    void currentIndexChanged( int index );
};

class KeyboardVariantsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY( int currentIndex WRITE setCurrentIndex READ currentIndex NOTIFY currentIndexChanged )

public:
    explicit KeyboardVariantsModel( QObject* parent = nullptr );
    void setVariants( QMap< QString, QString > variants );

    int rowCount( const QModelIndex& = QModelIndex() ) const override;
    QVariant data( const QModelIndex& index, int role ) const override;

    void setCurrentIndex( const int& index );
    int currentIndex() const;

    const QMap< QString, QString > item( const int& index ) const;

protected:
    QHash< int, QByteArray > roleNames() const override;

private:
    int m_currentIndex = -1;
    QVector< QMap< QString, QString > > m_list;

signals:
    void currentIndexChanged( int index );
};

#endif  // KEYBOARDLAYOUTMODEL_H
