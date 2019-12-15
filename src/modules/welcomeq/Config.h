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

#ifndef WELCOME_CONFIG_H
#define WELCOME_CONFIG_H

#include <QObject>
#include <QUrl>
#include "modulesystem/Requirement.h"

#include "locale/LabelModel.h"

class RequirementsModel : public QAbstractListModel
{
    Q_OBJECT
    using QAbstractListModel::QAbstractListModel;

public:
    enum Roles : short
    {
        Name,
        Satisfied,
        Mandatory,
        Details,
        NegatedText,
        HasDetails
    };

    void setRequirementsList( const Calamares::RequirementsList& requirements );
    int rowCount(const QModelIndex&) const override;
	QVariant data(const QModelIndex& index, int role) const override;

protected:
	QHash<int, QByteArray> roleNames() const override;

private:
    Calamares::RequirementsList m_requierements;

};


class Config : public QObject
{
    Q_OBJECT
    Q_PROPERTY( CalamaresUtils::Locale::LabelModel* languagesModel READ languagesModel CONSTANT FINAL)
    Q_PROPERTY( QUrl supportUrl READ supportUrl CONSTANT FINAL )
    Q_PROPERTY( QUrl knownIssuesUrl READ knownIssuesUrl CONSTANT FINAL )
    Q_PROPERTY( QUrl releaseNotesUrl READ releaseNotesUrl CONSTANT FINAL )
    Q_PROPERTY( QUrl donateUrl READ donateUrl CONSTANT FINAL )

    Q_PROPERTY( QString languageIcon READ languageIcon CONSTANT FINAL )

    Q_PROPERTY( QString countryCode MEMBER m_countryCode NOTIFY countryCodeChanged FINAL )
    Q_PROPERTY (int localeIndex MEMBER m_localeIndex NOTIFY localeIndexChanged)

    Q_PROPERTY( QString genericWelcomeMessage MEMBER m_genericWelcomeMessage CONSTANT FINAL )
    Q_PROPERTY( QString warningMessage MEMBER m_genericWelcomeMessage CONSTANT FINAL )
    Q_PROPERTY( RequirementsModel* requirementsModel MEMBER m_requirementsModel CONSTANT FINAL )

    Q_PROPERTY( bool isNextEnabled MEMBER m_isNextEnabled NOTIFY isNextEnabledChanged FINAL )

    Q_PROPERTY( bool isBackEnabled MEMBER m_isBackEnabled NOTIFY isBackEnabledChanged FINAL )


public:
     enum Alert : short
    {
        WarningAlert,
        ErrorAlert,
        SucessAlert

    }; Q_ENUM( Alert )

    Config( QObject* parent = nullptr );
    virtual ~Config();
    void setConfigurationMap( const QVariantMap& configurationMap );
    void setCountryCode( const QString &countryCode );
    void setLanguageIcon( const QString languageIcon );
    RequirementsModel& requirementsModel () const;

    void setIsNextEnabled( const bool& isNextEnabled );
    void setIsBackEnabled( const bool& isBackEnabled );

public slots:
    CalamaresUtils::Locale::LabelModel* languagesModel() const;

    QUrl supportUrl() const;
    QUrl knownIssuesUrl() const;
    QUrl releaseNotesUrl() const;
    QUrl donateUrl() const;

    QString languageIcon() const;

private:
    QVariantMap m_configurationMap;
    RequirementsModel* m_requirementsModel;
    QString m_languageIcon;
    QString m_countryCode;
    int m_localeIndex = 0;
    bool m_isNextEnabled = false;
    bool m_isBackEnabled = false;

    const QString m_genericWelcomeMessage = "This program will ask you some questions and set up your installation";

    const QString m_warningMessage = "This program does not satisfy the minimum requirements for installing.\nInstallation can not continue";

signals:
    void countryCodeChanged( QString countryCode );
    void localeIndexChanged( int localeIndex );
    void isNextEnabledChanged( bool isNextEnabled );
    void isBackEnabledChanged( bool isBackEnabled );
};

#endif
