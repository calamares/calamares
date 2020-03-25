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

#include "modulesystem/Requirement.h"
#include "locale/LabelModel.h"

#include <QObject>
#include <QUrl>

// TODO: move this (and modulesystem/Requirement) to libcalamares
class RequirementsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY( bool satisfiedRequirements READ satisfiedRequirements NOTIFY satisfiedRequirementsChanged FINAL )
    Q_PROPERTY( bool satisfiedMandatory READ satisfiedMandatory NOTIFY satisfiedMandatoryChanged FINAL )
    Q_PROPERTY( QString warningMessage READ warningMessage NOTIFY warningMessageChanged FINAL )

public:
    using QAbstractListModel::QAbstractListModel;

    enum Roles : short
    {
        Name,
        Satisfied,
        Mandatory,
        Details,
        NegatedText,
        HasDetails
    };

    bool satisfiedRequirements() const { return m_satisfiedRequirements; }

    bool satisfiedMandatory() const { return m_satisfiedMandatory; }

    const Calamares::RequirementEntry& getEntry( const int& index ) const
    {
        if ( index > count() || index < 0 )
        {
            return *( new Calamares::RequirementEntry() );
        }

        return m_requirements.at( index );
    }

    void setRequirementsList( const Calamares::RequirementsList& requirements );
    int rowCount( const QModelIndex& ) const override;
    int count() const { return m_requirements.count(); }

    QString warningMessage() const { return m_warningMessage; }

    void retranslate();

    QVariant data( const QModelIndex& index, int role ) const override;

protected:
    QHash< int, QByteArray > roleNames() const override;

private:
    Calamares::RequirementsList m_requirements;
    bool m_satisfiedRequirements = false;
    bool m_satisfiedMandatory = false;

    QString m_warningMessage;

signals:
    void satisfiedRequirementsChanged( bool value );
    void satisfiedMandatoryChanged();
    void warningMessageChanged();
};


class Config : public QObject
{
    Q_OBJECT
    Q_PROPERTY( CalamaresUtils::Locale::LabelModel* languagesModel READ languagesModel CONSTANT FINAL )
    Q_PROPERTY( RequirementsModel* requirementsModel MEMBER m_requirementsModel CONSTANT FINAL )

    Q_PROPERTY( QString languageIcon READ languageIcon CONSTANT FINAL )

    Q_PROPERTY( QString countryCode MEMBER m_countryCode NOTIFY countryCodeChanged FINAL )
    Q_PROPERTY( int localeIndex READ localeIndex WRITE setLocaleIndex NOTIFY localeIndexChanged )

    Q_PROPERTY( QString genericWelcomeMessage MEMBER m_genericWelcomeMessage NOTIFY genericWelcomeMessageChanged FINAL )

    Q_PROPERTY( QString supportUrl MEMBER m_supportUrl NOTIFY supportUrlChanged FINAL )
    Q_PROPERTY( QString knownIssuesUrl MEMBER m_knownIssuesUrl NOTIFY knownIssuesUrlChanged FINAL )
    Q_PROPERTY( QString releaseNotesUrl MEMBER m_releaseNotesUrl NOTIFY releaseNotesUrlChanged FINAL )
    Q_PROPERTY( QString donateUrl MEMBER m_donateUrl NOTIFY donateUrlChanged FINAL )

    Q_PROPERTY( bool isNextEnabled MEMBER m_isNextEnabled NOTIFY isNextEnabledChanged FINAL )

public:
    Config( QObject* parent = nullptr );
    void setCountryCode( const QString& countryCode );
    void setLanguageIcon( const QString& languageIcon );
    RequirementsModel& requirementsModel() const;

    void setIsNextEnabled( const bool& isNextEnabled );

    void setLocaleIndex( const int& index );
    int localeIndex() const { return m_localeIndex; }

    QString supportUrl() const;
    void setSupportUrl( const QString& url );

    QString knownIssuesUrl() const;
    void setKnownIssuesUrl( const QString& url );

    QString releaseNotesUrl() const;
    void setReleaseNotesUrl( const QString& url );

    QString donateUrl() const;
    void setDonateUrl( const QString& url );

    QString genericWelcomeMessage();


public slots:
    CalamaresUtils::Locale::LabelModel* languagesModel() const;
    void retranslate();
    QString languageIcon() const;

private:
    void initLanguages();
    QVariantMap m_configurationMap;
    RequirementsModel* m_requirementsModel;
    QString m_languageIcon;
    QString m_countryCode;
    int m_localeIndex = 0;
    bool m_isNextEnabled = false;
    CalamaresUtils::Locale::LabelModel* m_languages;

    QString m_genericWelcomeMessage;

    QString m_supportUrl;
    QString m_knownIssuesUrl;
    QString m_releaseNotesUrl;
    QString m_donateUrl;

signals:
    void countryCodeChanged( QString countryCode );
    void localeIndexChanged( int localeIndex );
    void isNextEnabledChanged( bool isNextEnabled );
    void genericWelcomeMessageChanged();
    void supportUrlChanged();
    void knownIssuesUrlChanged();
    void releaseNotesUrlChanged();
    void donateUrlChanged();
};

#endif
