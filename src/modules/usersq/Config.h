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

#ifndef USERS_CONFIG_H
#define USERS_CONFIG_H

#include <QObject>
#include "CheckPWQuality.h"
#include "Job.h"

struct Status
{
    Q_GADGET
    Q_PROPERTY(QString message MEMBER message CONSTANT FINAL)
    Q_PROPERTY(QString icon MEMBER icon CONSTANT FINAL)

public:
    /** @brief How bad is the error for labelError() ? */
    enum StatusCode
    {
        Ok,
        Fatal,
        Warning

    } Q_ENUMS(StatusCode);

    StatusCode status;
    QString message;
    QString icon;

}; Q_DECLARE_METATYPE(Status)


class Config : public QObject
{
    Q_OBJECT
//     Q_PROPERTY(bool passwordVisible READ setPasswordVisible WRITE setPasswordVisible NOTIFY passwordVisibleChanged)
    Q_PROPERTY(Status status READ getStatus NOTIFY statusChanged FINAL)
    Q_PROPERTY(QString userName MEMBER m_userName NOTIFY userNameChanged FINAL)
    Q_PROPERTY(bool userNameReady MEMBER m_readyUsername NOTIFY userNameReadyChanged FINAL)
    Q_PROPERTY(QString hostName MEMBER m_hostName NOTIFY hostNameChanged FINAL)
    Q_PROPERTY(bool hostNameReady MEMBER m_readyHostname NOTIFY hostNameReadyChanged FINAL)
    Q_PROPERTY(QString fullName MEMBER m_fullName NOTIFY fullNameChanged FINAL)
    Q_PROPERTY(bool fullNameReady MEMBER m_readyFullName NOTIFY fullNameReadyChanged FINAL)

    Q_PROPERTY(bool passwordReady MEMBER m_readyPassword NOTIFY passwordReadyChanged FINAL )
    Q_PROPERTY(bool rootPasswordReady MEMBER m_readyRootPassword NOTIFY rootPasswordReadyChanged FINAL )

    Q_PROPERTY(bool autologin READ autologinDefault WRITE setAutologinDefault NOTIFY autologinChanged)

    Q_PROPERTY(bool validatePasswords READ validatePasswords WRITE setValidatePasswordDefault NOTIFY validatePasswordsChanged)

    Q_PROPERTY(bool validatePasswordsVisible MEMBER m_validatePasswordsVisible NOTIFY validatePasswordsVisibleChanged FINAL)

    Q_PROPERTY(bool resusePassword READ reusePassword WRITE setReusePasswordDefault NOTIFY reusePasswordChanged)

    Q_PROPERTY(bool resusePasswordVisible MEMBER m_reusePasswordVisible NOTIFY reusePasswordVisibleChanged FINAL)


public:

    Config( QObject* parent = nullptr );

    bool isReady();

    Calamares::JobList createJobs(  const QStringList& defaultGroupsList );
    QString prettyStatus() const;

    void onActivate();

    void setWriteRootPassword( bool show );
    void setPasswordCheckboxVisible( bool visible );

    void setValidatePasswordDefault( bool checked );
    bool validatePasswords () const { return m_validatePasswords; }

    void setAutologinDefault( bool checked );
    bool autologinDefault () const {return m_autologin;};

    void setReusePasswordDefault( bool checked );
    bool reusePassword() const { return m_reusePassword; }

    Status getStatus() const { return m_status; }

    /** @brief Process entries in the passwordRequirements config entry
     *
     * Called once for each item in the config entry, which should
     * be a key-value pair. What makes sense as a value depends on
     * the key. Supported keys are documented in users.conf.
     */
    void addPasswordCheck( const QString& key, const QVariant& value );

public slots:
    void onFullNameTextEdited( const QString& );
    void fillSuggestions();
    void onUsernameTextEdited( const QString& );
    void validateUsernameText( const QString& );
    void onHostnameTextEdited( const QString& );
    void validateHostnameText( const QString& );
    void onPasswordTextChanged( const QString&, const QString&  );
    void onRootPasswordTextChanged( const QString&, const QString&  );

signals:
    void prettyStatusChanged();
    void checkReady(bool);

    void passwordVisibleChanged();

    void statusChanged();
    void warningMessageChanged();

    void fullNameChanged();
    void userNameChanged();
    void hostNameChanged();

    void fullNameReadyChanged();
    void userNameReadyChanged();
    void hostNameReadyChanged();
    void passwordReadyChanged();
    void rootPasswordReadyChanged();

    void autologinChanged();
    void reusePasswordChanged();
    void reusePasswordVisibleChanged();

    void validatePasswordsChanged();
    void validatePasswordsVisibleChanged();

private:
    /** @brief Is the password acceptable?
     *
     * Checks the two copies of the password and places error messages in the
     * given QLabels. Returns true (and clears the error messages) if the
     * password is acceptable.
     */
    bool checkPasswordAcceptance( const QString& pw1, const QString& pw2);

    void retranslate();
    void labelError(const QString& message, const Status::StatusCode &status = Status::StatusCode::Fatal );
    void labelOk(const Status::StatusCode &status = Status::StatusCode::Ok );

    PasswordCheckList m_passwordChecks;
    bool m_passwordChecksChanged = false;

    bool m_readyFullName;
    bool m_readyUsername;
    bool m_customUsername;
    bool m_readyHostname;
    bool m_customHostname;
    bool m_readyPassword;
    bool m_readyRootPassword;

    bool m_writeRootPassword;

    bool m_reusePassword;
    bool m_reusePasswordVisible;

    QString m_userName;
    QString m_hostName;
    QString m_fullName;
    QString m_userPassword;
    QString m_userVerifiedPassword;
    QString m_rootPassword;
    QString m_rootVerifiedPassword;

    Status m_status;

    bool m_autologin;
    bool m_validatePasswords;
    bool m_validatePasswordsVisible;
};


#endif
