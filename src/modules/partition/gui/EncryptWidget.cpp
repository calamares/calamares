/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */


#include "EncryptWidget.h"

#include "ui_EncryptWidget.h"

#include "Branding.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Retranslator.h"

/** @brief Does this system support whole-disk encryption?
 *
 * Returns @c true if the system is likely to support encryption
 * with sufficient performance to be usable. A machine that can't
 * doe hardware-assisted AES is **probably** too slow, so we could
 * warn the user that ticking the "encrypt system" box is a bad
 * idea.
 *
 * Since we don't have an oracle that can answer that question,
 * just pretend every system can do it.
 */
static inline bool
systemSupportsEncryptionAcceptably()
{
    return true;
}

EncryptWidget::EncryptWidget( QWidget* parent )
    : QWidget( parent )
    , m_ui( new Ui::EncryptWidget )
    , m_state( Encryption::Disabled )
{
    m_ui->setupUi( this );

    m_ui->m_iconLabel->setFixedWidth( m_ui->m_iconLabel->height() );
    m_ui->m_passphraseLineEdit->hide();
    m_ui->m_confirmLineEdit->hide();
    m_ui->m_iconLabel->hide();
    // TODO: this deserves better rendering, an icon or something, but that will
    //       depend on having a non-bogus implementation of systemSupportsEncryptionAcceptably
    if ( systemSupportsEncryptionAcceptably() )
    {
        m_ui->m_encryptionUnsupportedLabel->hide();
    }
    else
    {
        // This is really ugly, but the character is unicode "unlocked"
        m_ui->m_encryptionUnsupportedLabel->setText( QStringLiteral( "🔓" ) );
        m_ui->m_encryptionUnsupportedLabel->show();
    }

    connect( m_ui->m_encryptCheckBox, &QCheckBox::stateChanged, this, &EncryptWidget::onCheckBoxStateChanged );
    connect( m_ui->m_passphraseLineEdit, &QLineEdit::textEdited, this, &EncryptWidget::onPassphraseEdited );
    connect( m_ui->m_confirmLineEdit, &QLineEdit::textEdited, this, &EncryptWidget::onPassphraseEdited );

    setFixedHeight( m_ui->m_passphraseLineEdit->height() );  // Avoid jumping up and down
    updateState();

    CALAMARES_RETRANSLATE_SLOT( &EncryptWidget::retranslate );
}


void
EncryptWidget::reset( bool checkVisible )
{
    m_ui->m_passphraseLineEdit->clear();
    m_ui->m_confirmLineEdit->clear();

    m_ui->m_encryptCheckBox->setChecked( false );

    m_ui->m_encryptCheckBox->setVisible( checkVisible );
    m_ui->m_passphraseLineEdit->setVisible( !checkVisible );
    m_ui->m_confirmLineEdit->setVisible( !checkVisible );
}

EncryptWidget::Encryption
EncryptWidget::state() const
{
    Encryption newState = Encryption::Unconfirmed;

    if ( m_ui->m_encryptCheckBox->isChecked() || !m_ui->m_encryptCheckBox->isVisible() )
    {
        if ( !m_ui->m_passphraseLineEdit->text().isEmpty()
             && m_ui->m_passphraseLineEdit->text() == m_ui->m_confirmLineEdit->text() )
        {
            newState = Encryption::Confirmed;
        }
        else
        {
            newState = Encryption::Unconfirmed;
        }
    }
    else
    {
        newState = Encryption::Disabled;
    }

    return newState;
}


void
EncryptWidget::setText( const QString& text )
{
    m_ui->m_encryptCheckBox->setText( text );
}


QString
EncryptWidget::passphrase() const
{
    if ( m_state == Encryption::Confirmed )
    {
        return m_ui->m_passphraseLineEdit->text();
    }
    return QString();
}


void
EncryptWidget::retranslate()
{
    m_ui->retranslateUi( this );
    onPassphraseEdited();  // For the tooltip
}


///@brief Give @p label the @p pixmap from the standard-pixmaps
static void
applyPixmap( QLabel* label, CalamaresUtils::ImageType pixmap )
{
    label->setFixedWidth( label->height() );
    label->setPixmap( CalamaresUtils::defaultPixmap( pixmap, CalamaresUtils::Original, label->size() ) );
}

void
EncryptWidget::updateState()
{
    if ( m_ui->m_passphraseLineEdit->isVisible() )
    {
        QString p1 = m_ui->m_passphraseLineEdit->text();
        QString p2 = m_ui->m_confirmLineEdit->text();

        if ( p1.isEmpty() && p2.isEmpty() )
        {
            applyPixmap( m_ui->m_iconLabel, CalamaresUtils::StatusWarning );
            m_ui->m_iconLabel->setToolTip( tr( "Please enter the same passphrase in both boxes." ) );
        }
        else if ( p1 == p2 )
        {
            applyPixmap( m_ui->m_iconLabel, CalamaresUtils::StatusOk );
            m_ui->m_iconLabel->setToolTip( QString() );
        }
        else
        {
            applyPixmap( m_ui->m_iconLabel, CalamaresUtils::StatusError );
            m_ui->m_iconLabel->setToolTip( tr( "Please enter the same passphrase in both boxes." ) );
        }
    }

    Encryption newState = state();

    if ( newState != m_state )
    {
        m_state = newState;
        Q_EMIT stateChanged( m_state );
    }
}

void
EncryptWidget::onPassphraseEdited()
{
    if ( !m_ui->m_iconLabel->isVisible() )
    {
        m_ui->m_iconLabel->show();
    }

    updateState();
}


void
EncryptWidget::onCheckBoxStateChanged( int checked )
{
    // @p checked is a Qt::CheckState, 0 is "unchecked" and 2 is "checked"
    m_ui->m_passphraseLineEdit->setVisible( checked );
    m_ui->m_confirmLineEdit->setVisible( checked );
    m_ui->m_iconLabel->setVisible( checked );
    m_ui->m_passphraseLineEdit->clear();
    m_ui->m_confirmLineEdit->clear();
    m_ui->m_iconLabel->clear();

    updateState();
}
