/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019-2020, Adriaan de Groot <groot@kde.org>
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

#ifndef WELCOME_CONFIG_H
#define WELCOME_CONFIG_H

#include "locale/LabelModel.h"
#include "modulesystem/Requirement.h"
#include "modulesystem/RequirementsModel.h"

#include <QObject>
#include <QUrl>

class Config : public QObject
{
    Q_OBJECT
    Q_PROPERTY( CalamaresUtils::Locale::LabelModel* languagesModel READ languagesModel CONSTANT FINAL )
    Q_PROPERTY( Calamares::RequirementsModel* requirementsModel MEMBER m_requirementsModel CONSTANT FINAL )

    Q_PROPERTY( QString languageIcon READ languageIcon CONSTANT FINAL )

    Q_PROPERTY( QString countryCode MEMBER m_countryCode NOTIFY countryCodeChanged FINAL )
    Q_PROPERTY( int localeIndex READ localeIndex WRITE setLocaleIndex NOTIFY localeIndexChanged )

    Q_PROPERTY( QString genericWelcomeMessage MEMBER m_genericWelcomeMessage NOTIFY genericWelcomeMessageChanged FINAL )
    Q_PROPERTY( QString warningMessage READ warningMessage NOTIFY warningMessageChanged FINAL )

    Q_PROPERTY( QString supportUrl MEMBER m_supportUrl NOTIFY supportUrlChanged FINAL )
    Q_PROPERTY( QString knownIssuesUrl MEMBER m_knownIssuesUrl NOTIFY knownIssuesUrlChanged FINAL )
    Q_PROPERTY( QString releaseNotesUrl MEMBER m_releaseNotesUrl NOTIFY releaseNotesUrlChanged FINAL )
    Q_PROPERTY( QString donateUrl MEMBER m_donateUrl NOTIFY donateUrlChanged FINAL )

    Q_PROPERTY( bool isNextEnabled MEMBER m_isNextEnabled NOTIFY isNextEnabledChanged FINAL )

public:
    Config( QObject* parent = nullptr );

    Calamares::RequirementsModel& requirementsModel() const;

    void setCountryCode( const QString& countryCode );

    QString languageIcon() const;
    void setLanguageIcon( const QString& languageIcon );

    void setIsNextEnabled( bool isNextEnabled );

    void setLocaleIndex( int index );
    int localeIndex() const { return m_localeIndex; }

    QString supportUrl() const;
    void setSupportUrl( const QString& url );

    QString knownIssuesUrl() const;
    void setKnownIssuesUrl( const QString& url );

    QString releaseNotesUrl() const;
    void setReleaseNotesUrl( const QString& url );

    QString donateUrl() const;
    void setDonateUrl( const QString& url );

    QString genericWelcomeMessage() const;
    QString warningMessage() const;

public slots:
    CalamaresUtils::Locale::LabelModel* languagesModel() const;
    void retranslate();

signals:
    void countryCodeChanged( QString countryCode );
    void localeIndexChanged( int localeIndex );
    void isNextEnabledChanged( bool isNextEnabled );

    void genericWelcomeMessageChanged( QString message );
    void warningMessageChanged( QString message );

    void supportUrlChanged();
    void knownIssuesUrlChanged();
    void releaseNotesUrlChanged();
    void donateUrlChanged();

private:
    void initLanguages();

    Calamares::RequirementsModel* m_requirementsModel;
    CalamaresUtils::Locale::LabelModel* m_languages;

    QString m_languageIcon;
    QString m_countryCode;
    int m_localeIndex = 0;
    bool m_isNextEnabled = false;

    QString m_genericWelcomeMessage;
    QString m_warningMessage;

    QString m_supportUrl;
    QString m_knownIssuesUrl;
    QString m_releaseNotesUrl;
    QString m_donateUrl;
};

#endif
