/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019-2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef WELCOME_CONFIG_H
#define WELCOME_CONFIG_H

#include "checker/GeneralRequirements.h"
#include "locale/TranslationsModel.h"
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
    Q_PROPERTY( CalamaresUtils::Locale::TranslationsModel* languagesModel READ languagesModel CONSTANT FINAL )
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

    Q_PROPERTY( QString aboutMessage READ aboutMessage CONSTANT FINAL )
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

    QString aboutMessage() const;
    QString genericWelcomeMessage() const;
    QString warningMessage() const;

public slots:
    CalamaresUtils::Locale::TranslationsModel* languagesModel() const;
    void retranslate();

    ///@brief The **global** requirements model, from ModuleManager
    Calamares::RequirementsModel* requirementsModel() const;

    QAbstractItemModel* unsatisfiedRequirements() const;

    /// @brief Check the general requirements
    Calamares::RequirementsList checkRequirements() const { return m_requirementsChecker->checkRequirements(); }

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

    CalamaresUtils::Locale::TranslationsModel* m_languages = nullptr;
    std::unique_ptr< QSortFilterProxyModel > m_filtermodel;
    std::unique_ptr< GeneralRequirements > m_requirementsChecker;

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
