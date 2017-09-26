/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2016, Teo Mrnjavac <teo@kde.org>
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

#include <utils/CalamaresUtilsGui.h>

EncryptWidget::EncryptWidget( QWidget* parent )
    : QWidget( parent )
    , m_state( EncryptionDisabled )
{
    setupUi( this );

    m_iconLabel->setFixedWidth( m_iconLabel->height() );
    m_passphraseLineEdit->hide();
    m_confirmLineEdit->hide();
    m_iconLabel->hide();

    connect( m_encryptCheckBox, &QCheckBox::stateChanged,
             this, &EncryptWidget::onCheckBoxStateChanged );
    connect( m_passphraseLineEdit, &QLineEdit::textEdited,
             this, &EncryptWidget::onPassphraseEdited );
    connect( m_confirmLineEdit, &QLineEdit::textEdited,
             this, &EncryptWidget::onPassphraseEdited );

    setFixedHeight( m_passphraseLineEdit->height() ); // Avoid jumping up and down
    updateState();
}


void
EncryptWidget::reset()
{
    m_passphraseLineEdit->clear();
    m_confirmLineEdit->clear();

    m_encryptCheckBox->setChecked( false );
}


EncryptWidget::State
EncryptWidget::state() const
{
    return m_state;
}


void
EncryptWidget::setText( const QString& text )
{
    m_encryptCheckBox->setText( text );
}


QString
EncryptWidget::passphrase() const
{
    if ( m_state == EncryptionConfirmed )
        return m_passphraseLineEdit->text();
    return QString();
}


void
EncryptWidget::changeEvent( QEvent* e )
{
    QWidget::changeEvent( e );
    switch ( e->type() )
    {
    case QEvent::LanguageChange:
        retranslateUi( this );
        break;
    default:
        break;
    }
}


void
EncryptWidget::updateState()
{
    State newState;
    if ( m_encryptCheckBox->isChecked() )
    {
        if ( !m_passphraseLineEdit->text().isEmpty() &&
             m_passphraseLineEdit->text() == m_confirmLineEdit->text() )
        {
            newState = EncryptionConfirmed;
        }
        else
        {
            newState = EncryptionUnconfirmed;
        }
    }
    else
    {
        newState = EncryptionDisabled;
    }

    if ( newState != m_state )
    {
        m_state = newState;
        emit stateChanged( m_state );
    }
}


void
EncryptWidget::onPassphraseEdited()
{
    if ( !m_iconLabel->isVisible() )
        m_iconLabel->show();

    QString p1 = m_passphraseLineEdit->text();
    QString p2 = m_confirmLineEdit->text();

    m_iconLabel->setToolTip( QString() );
    if ( p1.isEmpty() && p2.isEmpty() )
    {
        m_iconLabel->clear();
    }
    else if ( p1 == p2 )
    {
        m_iconLabel->setFixedWidth( m_iconLabel->height() );
        m_iconLabel->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::Yes,
                                                               CalamaresUtils::Original,
                                                               m_iconLabel->size() ) );
    }
    else
    {
        m_iconLabel->setFixedWidth( m_iconLabel->height() );
        m_iconLabel->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::No,
                                                               CalamaresUtils::Original,
                                                               m_iconLabel->size() ) );
        m_iconLabel->setToolTip( tr( "Please enter the same passphrase in both boxes." ) );
    }

    updateState();
}


void
EncryptWidget::onCheckBoxStateChanged( int state )
{
    m_passphraseLineEdit->setVisible( state );
    m_confirmLineEdit->setVisible( state );
    m_iconLabel->setVisible( state );
    m_passphraseLineEdit->clear();
    m_confirmLineEdit->clear();
    m_iconLabel->clear();

    updateState();
}
