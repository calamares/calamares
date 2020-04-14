/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2020, Adriaan de Groot <groot@kde.org>
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


#include "EncryptWidget.h"

#include "ui_EncryptWidget.h"

#include "utils/CalamaresUtilsGui.h"
#include "utils/Retranslator.h"

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

    connect( m_ui->m_encryptCheckBox, &QCheckBox::stateChanged, this, &EncryptWidget::onCheckBoxStateChanged );
    connect( m_ui->m_passphraseLineEdit, &QLineEdit::textEdited, this, &EncryptWidget::onPassphraseEdited );
    connect( m_ui->m_confirmLineEdit, &QLineEdit::textEdited, this, &EncryptWidget::onPassphraseEdited );

    setFixedHeight( m_ui->m_passphraseLineEdit->height() );  // Avoid jumping up and down
    updateState();

    CALAMARES_RETRANSLATE_SLOT( &EncryptWidget::retranslate )
}


void
EncryptWidget::reset()
{
    m_ui->m_passphraseLineEdit->clear();
    m_ui->m_confirmLineEdit->clear();

    m_ui->m_encryptCheckBox->setChecked( false );
}


EncryptWidget::Encryption
EncryptWidget::state() const
{
    return m_state;
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


void
EncryptWidget::updateState()
{
    Encryption newState;
    if ( m_ui->m_encryptCheckBox->isChecked() )
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

    if ( newState != m_state )
    {
        m_state = newState;
        emit stateChanged( m_state );
    }
}

///@brief Give @p label the @p pixmap from the standard-pixmaps
static void
applyPixmap( QLabel* label, CalamaresUtils::ImageType pixmap )
{
    label->setFixedWidth( label->height() );
    label->setPixmap( CalamaresUtils::defaultPixmap( pixmap, CalamaresUtils::Original, label->size() ) );
}

void
EncryptWidget::onPassphraseEdited()
{
    if ( !m_ui->m_iconLabel->isVisible() )
    {
        m_ui->m_iconLabel->show();
    }

    QString p1 = m_ui->m_passphraseLineEdit->text();
    QString p2 = m_ui->m_confirmLineEdit->text();

    m_ui->m_iconLabel->setToolTip( QString() );
    if ( p1.isEmpty() && p2.isEmpty() )
    {
        m_ui->m_iconLabel->clear();
    }
    else if ( p1 == p2 )
    {
        applyPixmap( m_ui->m_iconLabel, CalamaresUtils::Yes );
    }
    else
    {
        applyPixmap( m_ui->m_iconLabel, CalamaresUtils::No );
        m_ui->m_iconLabel->setToolTip( tr( "Please enter the same passphrase in both boxes." ) );
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
