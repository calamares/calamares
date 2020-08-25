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

#endif  // KEYBOARDLAYOUTMODEL_H
