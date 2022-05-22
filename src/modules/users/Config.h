/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef USERS_CONFIG_H
#define USERS_CONFIG_H

#include "CheckPWQuality.h"

#include "Job.h"
#include "modulesystem/Config.h"
#include "utils/NamedEnum.h"

#include <QList>
#include <QObject>
#include <QVariantMap>

enum class HostNameAction
{
    None,
    EtcHostname,  // Write to /etc/hostname directly
    SystemdHostname,  // Set via hostnamed(1)
    Transient,  // Force target system transient, remove /etc/hostname
};

const NamedEnumTable< HostNameAction >& hostnameActionNames();

/** @brief Settings for a single group
 *
 * The list of defaultgroups from the configuration can be
 * set up in a fine-grained way, with both user- and system-
 * level groups; this class stores a configuration for each.
 */
class GroupDescription
{
public:
    // TODO: still too-weakly typed, add a macro to define strongly-typed bools
    class MustExist : public std::true_type
    {
    };
    class CreateIfNeeded : public std::false_type
    {
    };
    class SystemGroup : public std::true_type
    {
    };
    class UserGroup : public std::false_type
    {
    };

    ///@brief An invalid, empty group
    GroupDescription() {}

    ///@brief A group with full details
    GroupDescription( const QString& name, bool mustExistAlready = CreateIfNeeded {}, bool isSystem = UserGroup {} )
        : m_name( name )
        , m_isValid( !name.isEmpty() )
        , m_mustAlreadyExist( mustExistAlready )
        , m_isSystem( isSystem )
    {
    }

    bool isValid() const { return m_isValid; }
    bool isSystemGroup() const { return m_isSystem; }
    bool mustAlreadyExist() const { return m_mustAlreadyExist; }
    QString name() const { return m_name; }

    ///@brief Equality of groups depends only on name and kind
    bool operator==( const GroupDescription& rhs ) const
    {
        return rhs.name() == name() && rhs.isSystemGroup() == isSystemGroup();
    }

private:
    QString m_name;
    bool m_isValid = false;
    bool m_mustAlreadyExist = false;
    bool m_isSystem = false;
};


class PLUGINDLLEXPORT Config : public Calamares::ModuleSystem::Config
{
    Q_OBJECT

    Q_PROPERTY( QString userShell READ userShell WRITE setUserShell NOTIFY userShellChanged )

    Q_PROPERTY( QString autoLoginGroup READ autoLoginGroup WRITE setAutoLoginGroup NOTIFY autoLoginGroupChanged )
    Q_PROPERTY( QString sudoersGroup READ sudoersGroup WRITE setSudoersGroup NOTIFY sudoersGroupChanged )

    Q_PROPERTY( bool doAutoLogin READ doAutoLogin WRITE setAutoLogin NOTIFY autoLoginChanged )

    Q_PROPERTY( QString fullName READ fullName WRITE setFullName NOTIFY fullNameChanged )
    Q_PROPERTY( QString loginName READ loginName WRITE setLoginName NOTIFY loginNameChanged )
    Q_PROPERTY( QString loginNameStatus READ loginNameStatus NOTIFY loginNameStatusChanged )

    Q_PROPERTY( QString hostname READ hostname WRITE setHostName NOTIFY hostnameChanged )
    Q_PROPERTY( QString hostnameStatus READ hostnameStatus NOTIFY hostnameStatusChanged )
    Q_PROPERTY( HostNameAction hostnameAction READ hostnameAction CONSTANT )

    Q_PROPERTY( QString userPassword READ userPassword WRITE setUserPassword NOTIFY userPasswordChanged )
    Q_PROPERTY( QString userPasswordSecondary READ userPasswordSecondary WRITE setUserPasswordSecondary NOTIFY
                    userPasswordSecondaryChanged )
    Q_PROPERTY( int userPasswordValidity READ userPasswordValidity NOTIFY userPasswordStatusChanged STORED false )
    Q_PROPERTY( QString userPasswordMessage READ userPasswordMessage NOTIFY userPasswordStatusChanged STORED false )

    Q_PROPERTY( QString rootPassword READ rootPassword WRITE setRootPassword NOTIFY rootPasswordChanged )
    Q_PROPERTY( QString rootPasswordSecondary READ rootPasswordSecondary WRITE setRootPasswordSecondary NOTIFY
                    rootPasswordSecondaryChanged )
    Q_PROPERTY( int rootPasswordValidity READ rootPasswordValidity NOTIFY rootPasswordStatusChanged STORED false )
    Q_PROPERTY( QString rootPasswordMessage READ rootPasswordMessage NOTIFY rootPasswordStatusChanged STORED false )

    Q_PROPERTY( bool writeRootPassword READ writeRootPassword CONSTANT )
    Q_PROPERTY( bool reuseUserPasswordForRoot READ reuseUserPasswordForRoot WRITE setReuseUserPasswordForRoot NOTIFY
                    reuseUserPasswordForRootChanged )

    Q_PROPERTY( bool permitWeakPasswords READ permitWeakPasswords CONSTANT )
    Q_PROPERTY( bool requireStrongPasswords READ requireStrongPasswords WRITE setRequireStrongPasswords NOTIFY
                    requireStrongPasswordsChanged )

    Q_PROPERTY( bool ready READ isReady NOTIFY readyChanged STORED false )

public:
    /** @brief Validity (status) of a password
     *
     * Valid passwords are:
     *  - primary and secondary are equal **and**
     *  - all the password-strength checks pass
     * Weak passwords:
     *  - primary and secondary are equal **and**
     *  - not all the checks pass **and**
     *  - permitWeakPasswords is @c true **and**
     *  - requireStrongPasswords is @c false
     * Invalid passwords (all other cases):
     *  - the primary and secondary values are not equal **or**
     *  - not all the checks pass and weak passwords are not permitted
     */
    enum PasswordValidity
    {
        Valid = 0,
        Weak = 1,
        Invalid = 2
    };

    /** @brief Full password status
     *
     * A password's status is in two parts:
     *  - a validity (valid, weak or invalid)
     *  - a message describing that validity
     * The message is empty when the password is valid, but
     * weak and invalid passwords have an explanatory message.
     */
    using PasswordStatus = QPair< PasswordValidity, QString >;

    Config( QObject* parent = nullptr );
    ~Config() override;

    void setConfigurationMap( const QVariantMap& ) override;

    /** @brief Fill Global Storage with some settings
     *
     * This should be called when moving on from the view step,
     * and copies some things to GS that otherwise would not.
     */
    void finalizeGlobalStorage() const;

    /** @brief Jobs for creating user, setting passwords
     *
     * If the Config object isn't ready yet, returns an empty list.
     */
    Calamares::JobList createJobs() const;

    /** @brief Full path to the user's shell executable
     *
     * Typically this will be /bin/bash, but it can be set from
     * the config file with the *userShell* setting.
     */
    QString userShell() const { return m_userShell; }

    /// The group of which auto-login users must be a member
    QString autoLoginGroup() const { return m_autoLoginGroup; }

    enum class SudoStyle
    {
        UserOnly,
        UserAndGroup
    };
    /// The group of which users who can "sudo" must be a member
    QString sudoersGroup() const { return m_sudoersGroup; }
    SudoStyle sudoStyle() const { return m_sudoStyle; }

    /// The full (GECOS) name of the user
    QString fullName() const { return m_fullName; }
    /// The login name of the user
    QString loginName() const { return m_loginName; }
    /// Status message about login -- empty for "ok"
    QString loginNameStatus() const;

    /// The host name (name for the system)
    QString hostname() const
    {
        return ( ( hostnameAction() == HostNameAction::EtcHostname )
                 || ( hostnameAction() == HostNameAction::SystemdHostname ) )
            ? m_hostname
            : QString();
    }
    /// Status message about hostname -- empty for "ok"
    QString hostnameStatus() const;
    /// How to write the hostname
    HostNameAction hostnameAction() const { return m_hostnameAction; }
    /// Write /etc/hosts ?
    bool writeEtcHosts() const { return m_writeEtcHosts; }

    /// Should the user be automatically logged-in?
    bool doAutoLogin() const { return m_doAutoLogin; }
    /// Should the root password be written (if false, no password is set and the root account is disabled for login)
    bool writeRootPassword() const { return m_writeRootPassword; }
    /// Should the user's password be used for root, too? (if root is written at all)
    bool reuseUserPasswordForRoot() const { return m_reuseUserPasswordForRoot; }
    /// Show UI to change the "require strong password" setting?
    bool permitWeakPasswords() const { return m_permitWeakPasswords; }
    /// Current setting for "require strong password"?
    bool requireStrongPasswords() const { return m_requireStrongPasswords; }

    const QList< GroupDescription >& defaultGroups() const { return m_defaultGroups; }
    /** @brief the names of all the groups for the current user
     *
     * Takes into account defaultGroups and autoLogin behavior.
     */
    QStringList groupsForThisUser() const;

    // The user enters a password (and again in a separate UI element)
    QString userPassword() const { return m_userPassword; }
    QString userPasswordSecondary() const { return m_userPasswordSecondary; }
    int userPasswordValidity() const;
    QString userPasswordMessage() const;
    PasswordStatus userPasswordStatus() const;

    // The root password **may** be entered in the UI, or may be suppressed
    //   entirely when writeRootPassword is off, or may be equal to
    //   the user password when reuseUserPasswordForRoot is on.
    QString rootPassword() const;
    QString rootPasswordSecondary() const;
    int rootPasswordValidity() const;
    QString rootPasswordMessage() const;
    PasswordStatus rootPasswordStatus() const;

    bool isReady() const;

    const QStringList& forbiddenLoginNames() const;
    const QStringList& forbiddenHostNames() const;

public Q_SLOTS:
    /** @brief Sets the user's shell if possible
     *
     * If the path is empty, that's ok: no shell will be explicitly set,
     * so the user will get whatever shell is set to default in the target.
     *
     * The given non-empty @p path must be an absolute path (for use inside
     * the target system!); if it is not, the shell is not changed.
     */
    void setUserShell( const QString& path );

    /// Sets the autoLogin group; empty is ignored
    void setAutoLoginGroup( const QString& group );
    /// Sets the sudoer group; empty is ignored
    void setSudoersGroup( const QString& group );

    /// Sets the full name, may guess a loginName
    void setFullName( const QString& name );
    /// Sets the login name (flags it as "custom")
    void setLoginName( const QString& login );

    /// Sets the host name (flags it as "custom")
    void setHostName( const QString& host );

    /// Sets the autoLogin flag
    void setAutoLogin( bool b );

    /// Set to true to use the user password, unchanged, for root too
    void setReuseUserPasswordForRoot( bool reuse );
    /// Change setting for "require strong password"
    void setRequireStrongPasswords( bool strong );

    void setUserPassword( const QString& );
    void setUserPasswordSecondary( const QString& );
    void setRootPassword( const QString& );
    void setRootPasswordSecondary( const QString& );

signals:
    void userShellChanged( const QString& );
    void autoLoginGroupChanged( const QString& );
    void sudoersGroupChanged( const QString& );
    void fullNameChanged( const QString& );
    void loginNameChanged( const QString& );
    void loginNameStatusChanged( const QString& );
    void hostnameChanged( const QString& );
    void hostnameStatusChanged( const QString& );
    void autoLoginChanged( bool );
    void reuseUserPasswordForRootChanged( bool );
    void requireStrongPasswordsChanged( bool );
    void userPasswordChanged( const QString& );
    void userPasswordSecondaryChanged( const QString& );
    void userPasswordStatusChanged( int, const QString& );
    void rootPasswordChanged( const QString& );
    void rootPasswordSecondaryChanged( const QString& );
    void rootPasswordStatusChanged( int, const QString& );
    void readyChanged( bool ) const;

private:
    PasswordStatus passwordStatus( const QString&, const QString& ) const;
    void checkReady();

    QList< GroupDescription > m_defaultGroups;
    QString m_userShell;
    QString m_autoLoginGroup;
    QString m_sudoersGroup;
    SudoStyle m_sudoStyle = SudoStyle::UserOnly;
    QString m_fullName;
    QString m_loginName;
    QString m_hostname;

    QString m_userPassword;
    QString m_userPasswordSecondary;  // enter again to be sure
    QString m_rootPassword;
    QString m_rootPasswordSecondary;

    bool m_doAutoLogin = false;

    bool m_writeRootPassword = true;
    bool m_reuseUserPasswordForRoot = false;

    bool m_permitWeakPasswords = false;
    bool m_requireStrongPasswords = true;

    bool m_customLoginName = false;
    bool m_customHostName = false;

    bool m_isReady = false;  ///< Used to reduce readyChanged signals

    HostNameAction m_hostnameAction = HostNameAction::EtcHostname;
    bool m_writeEtcHosts = false;
    QString m_hostnameTemplate;

    QStringList m_forbiddenHostNames;
    QStringList m_forbiddenLoginNames;

    PasswordCheckList m_passwordChecks;
};

#endif
