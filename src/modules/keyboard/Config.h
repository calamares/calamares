/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019-2020, Adriaan de Groot <groot@kde.org>
 *   Copyright 2020, Camilo Higuita <milo.h@aol.com>
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

#ifndef KEYBOARD_CONFIG_H
#define KEYBOARD_CONFIG_H

#include "Job.h"
#include "KeyboardLayoutModel.h"

#include <QAbstractListModel>
#include <QMap>
#include <QObject>
#include <QTimer>
#include <QUrl>

class KeyboardModelsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY( int currentIndex WRITE setCurrentIndex READ currentIndex NOTIFY currentIndexChanged )

public:
    explicit KeyboardModelsModel( QObject* parent = nullptr );
    int rowCount( const QModelIndex& = QModelIndex() ) const override;
    QVariant data( const QModelIndex& index, int role ) const override;

    void setCurrentIndex( const int& index );
    int currentIndex() const;
    const QMap< QString, QString > item( const int& index ) const;

public slots:
    void refresh();

protected:
    QHash< int, QByteArray > roleNames() const override;

private:
    int m_currentIndex = -1;
    QVector< QMap< QString, QString > > m_list;
    void detectModels();

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

class Config : public QObject
{
    Q_OBJECT
    Q_PROPERTY( KeyboardModelsModel* keyboardModelsModel READ keyboardModels CONSTANT FINAL )
    Q_PROPERTY( KeyboardLayoutModel* keyboardLayoutsModel READ keyboardLayouts CONSTANT FINAL )
    Q_PROPERTY( KeyboardVariantsModel* keyboardVariantsModel READ keyboardVariants CONSTANT FINAL )
    Q_PROPERTY( QString prettyStatus READ prettyStatus NOTIFY prettyStatusChanged FINAL )

public:
    Config( QObject* parent = nullptr );

    void init();

    Calamares::JobList
    createJobs( const QString& xOrgConfFileName, const QString& convertedKeymapPath, bool writeEtcDefaultKeyboard );
    QString prettyStatus() const;

    void onActivate();
    void finalize();

private:
    void guessLayout( const QStringList& langParts );
    void updateVariants( const QPersistentModelIndex& currentItem, QString currentVariant = QString() );

    KeyboardModelsModel* m_keyboardModelsModel;
    KeyboardLayoutModel* m_keyboardLayoutsModel;
    KeyboardVariantsModel* m_keyboardVariantsModel;

    QString m_selectedLayout;
    QString m_selectedModel;
    QString m_selectedVariant;
    QTimer m_setxkbmapTimer;

protected:
    KeyboardModelsModel* keyboardModels() const;
    KeyboardLayoutModel* keyboardLayouts() const;
    KeyboardVariantsModel* keyboardVariants() const;


signals:
    void prettyStatusChanged();
};


#endif
