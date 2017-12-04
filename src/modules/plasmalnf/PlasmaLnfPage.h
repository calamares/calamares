/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

#ifndef PLASMALNFPAGE_H
#define PLASMALNFPAGE_H

#include <QList>
#include <QString>
#include <QStringList>
#include <QWidget>

namespace Ui
{
class PlasmaLnfPage;
}

struct PlasmaLnfDescriptor
{
    QString id;
    QString name;
} ;

using PlasmaLnfList = QList<PlasmaLnfDescriptor>;

class PlasmaLnfPage : public QWidget
{
    Q_OBJECT
public:
    explicit PlasmaLnfPage( QWidget* parent = nullptr );

    void setLnfPath( const QString& path );
    void setEnabledThemes( const QStringList& themes );

public slots:
    void activated( int index );

signals:
    void plasmaThemeSelected( const QString& id );

private:
    void winnowThemes();

    Ui::PlasmaLnfPage* ui;
    QString m_lnfPath;
    QStringList m_enabledThemes;
    PlasmaLnfList m_availableLnf;
};

#endif //PLASMALNFPAGE_H
