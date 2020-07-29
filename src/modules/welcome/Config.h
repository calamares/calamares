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
#include "modulesystem/RequirementsModel.h"

#include <QObject>
#include <QSortFilterProxyModel>
#include <QUrl>

#include <memory>

class Config : public QObject
{
    Q_OBJECT
    /** @brief The languages available in Calamares.
     *
     * This is a list-model, with names and descriptions for the translations
     * available to Calamares.
     */
    Q_PROPERTY( CalamaresUtils::Locale::LabelModel* languagesModel READ languagesModel CONSTANT FINAL )
    /** @brief The requirements (from modules) and their checked-status
     *
     * The model grows rows over time as each module is checked and its
     * requirements are taken into account. The model **as a whole**
     * has properties *satisfiedRequirements* and *satisfiedMandatory*
     * to say if all of the requirements held in the model have been
     * satisfied. See the model documentation for details.
     */
    Q_PROPERTY( Calamares::RequirementsModel* requirementsModel READ requirementsModel CONSTANT FINAL )
    /** @brief The requirements (from modules) that are **unsatisfied**
     *
     * This is the same as requirementsModel(), except filtered so
     * that only those requirements that are not satisfied are exposed.
     * Note that the type is different, so you should still use the
     * requirementsModel() for overall status like *satisfiedMandatory*.
     */
    Q_PROPERTY( QAbstractItemModel* unsatisfiedRequirements READ unsatisfiedRequirements CONSTANT FINAL )

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

    void setConfigurationMap( const QVariantMap& );

    void setCountryCode( const QString& countryCode );

    QString languageIcon() const;
    void setLanguageIcon( const QString& languageIcon );

    void setIsNextEnabled( bool isNextEnabled );

    int localeIndex() const { return m_localeIndex; }
    void setLocaleIndex( int index );

    QString supportUrl() const { return m_supportUrl; }
    void setSupportUrl( const QString& url );

    QString knownIssuesUrl() const { return m_knownIssuesUrl; }
    void setKnownIssuesUrl( const QString& url );

    QString releaseNotesUrl() const { return m_releaseNotesUrl; }
    void setReleaseNotesUrl( const QString& url );

    QString donateUrl() const { return m_donateUrl; }
    void setDonateUrl( const QString& url );

    QString genericWelcomeMessage() const;
    QString warningMessage() const;

public slots:
    CalamaresUtils::Locale::LabelModel* languagesModel() const;
    void retranslate();

    ///@brief The **global** requirements model, from ModuleManager
    Calamares::RequirementsModel* requirementsModel() const;

    QAbstractItemModel* unsatisfiedRequirements() const;

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

    CalamaresUtils::Locale::LabelModel* m_languages = nullptr;
    std::unique_ptr< QSortFilterProxyModel > m_filtermodel;

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
