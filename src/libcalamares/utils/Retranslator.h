/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#ifndef CALAMARESUTILS_RETRANSLATOR_H
#define CALAMARESUTILS_RETRANSLATOR_H

#include <QList>
#include <QObject>

#include <functional>

class QEvent;

namespace CalamaresUtils
{

class Retranslator : public QObject
{
    Q_OBJECT
public:
    static void attachRetranslator( QObject* parent,
                                    std::function< void( void ) > retranslateFunc );

    void addRetranslateFunc( std::function< void( void ) > retranslateFunc );

protected:
    bool eventFilter( QObject* obj, QEvent* e ) override;

private:
    explicit Retranslator( QObject* parent );

    QList< std::function< void( void ) > > m_retranslateFuncList;
};


} // namespace CalamaresUtils

#define CALAMARES_RETRANSLATE(body) \
    CalamaresUtils::Retranslator::attachRetranslator( this, [=] { body } );
#define CALAMARES_RETRANSLATE_WIDGET(widget,body) \
    CalamaresUtils::Retranslator::attachRetranslator( widget, [=] { body } );

#endif // CALAMARESUTILS_RETRANSLATOR_H
