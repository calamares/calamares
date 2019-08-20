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

#ifndef LIBCALAMARES_NETWORK_MANAGER_H
#define LIBCALAMARES_NETWORK_MANAGER_H

#include "DllMacro.h"

#include <QObject>
#include <QUrl>

#include <memory>

namespace CalamaresUtils
{
namespace Network
{
class DLLEXPORT Manager : QObject
{
    Q_OBJECT

    Manager();

public:
    static Manager& instance();
    virtual ~Manager();

    bool synchronousPing( const QUrl& url );

    void setCheckHasInternetUrl( const QUrl& url );
    bool checkHasInternet();
    bool hasInternet();

private:
    struct Private;
    std::unique_ptr< Private > d;
};
}  // namespace Network
}  // namespace CalamaresUtils
#endif  // LIBCALAMARES_NETWORK_MANAGER_H
