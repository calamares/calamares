/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2015, Anke Boersma <demm@kaosx.us>
 *   Copyright 2015, Alexandre Arnt <qtgzmanager@gmail.com>
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

#ifndef LICENSEPAGE_H
#define LICENSEPAGE_H

#include <QWidget>
#include <QUrl>

namespace Ui
{
class LicensePage;
}

class LicensePage : public QWidget
{
    Q_OBJECT
public:
    explicit LicensePage( QWidget* parent = nullptr );
    
    void showLicense1Url( bool enabled );
    void showLicense2Url( bool enabled );
    void showLicense3Url( bool enabled );
    void showLicense4Url( bool enabled );
    void setLicense1Url( const QString& url );
    void setLicense2Url( const QString& url );
    void setLicense3Url( const QString& url );
    void setLicense4Url( const QString& url );
    void setLicense1Button( const QString& text );

private:
    Ui::LicensePage* ui;
    QString m_license1Url;
    QString m_license2Url;
    QString m_license3Url;
    QString m_license4Url;
    QString m_license1Button;
};

#endif //LICENSEPAGE_H
