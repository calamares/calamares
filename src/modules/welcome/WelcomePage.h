/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include <QWidget>

namespace Ui
{
class WelcomePage;
}

class RequirementsChecker;

class WelcomePage : public QWidget
{
    Q_OBJECT
public:
    explicit WelcomePage( RequirementsChecker* requirementsChecker,
                          QWidget* parent = nullptr );

    void setUpLinks( bool showSupportUrl,
                     bool showKnownIssuesUrl,
                     bool showReleaseNotesUrl );

protected:
    void focusInEvent( QFocusEvent* e ) override; //choose the child widget to focus

private:
    void initLanguages();
    Ui::WelcomePage* ui;
    RequirementsChecker* m_requirementsChecker;
};

#endif // WELCOMEPAGE_H
