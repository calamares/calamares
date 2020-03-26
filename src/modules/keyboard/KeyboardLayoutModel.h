/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2016, Teo Mrnjavac <teo@kde.org>
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
