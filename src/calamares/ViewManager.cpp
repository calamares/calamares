/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#include "ViewManager.h"

#include "viewpages/ViewStep.h"

#include <QApplication>
#include <QLabel>
#include <QBoxLayout>

namespace Calamares
{

ViewManager* ViewManager::s_instance = nullptr;

ViewManager*
ViewManager::instance()
{
    return s_instance;
}

ViewManager::ViewManager( QObject* parent )
    : QObject( parent )
    , m_widget( new QWidget() )
    , m_currentStep( 0 )
{
    s_instance = this;
    QBoxLayout* mainLayout = new QVBoxLayout;
    m_widget->setLayout( mainLayout );

    m_stack = new QStackedWidget( m_widget );
    m_stack->setContentsMargins( 0, 0, 0, 0 );
    mainLayout->addWidget( m_stack );

    m_back = new QPushButton( tr( "&Back" ), m_widget );
    m_next = new QPushButton( tr( "&Next" ), m_widget );
    m_quit = new QPushButton( tr( "&Quit" ), m_widget );

    QBoxLayout* bottomLayout = new QHBoxLayout;
    mainLayout->addLayout( bottomLayout );
    bottomLayout->addStretch();
    bottomLayout->addWidget( m_back );
    bottomLayout->addWidget( m_next );
    bottomLayout->addSpacing( 12 );
    bottomLayout->addWidget( m_quit );

    connect( m_quit, &QPushButton::clicked, qApp, &QApplication::quit );
    connect( m_next, &QPushButton::clicked, this, &ViewManager::next );
    connect( m_back, &QPushButton::clicked, this, &ViewManager::back );
    m_back->setEnabled( false );
}


ViewManager::~ViewManager()
{
    m_widget->deleteLater();
}


QWidget*
ViewManager::centralWidget()
{
    return m_widget;
}


void
ViewManager::addViewStep( ViewStep* step )
{
    step->setParent( this );
    m_steps.append( step );
    m_stack->addWidget( step->widget() );

    connect( step, &ViewStep::nextStatusChanged,
             m_next, &QPushButton::setEnabled );
}


void
ViewManager::next()
{
    ViewStep* step = m_steps.at( m_currentStep );
    if ( step->isAtEnd() && m_currentStep < m_steps.length() -1 )
    {
        m_currentStep++;
        m_stack->setCurrentIndex( m_currentStep );
    }
    else if ( !step->isAtEnd() )
    {
        step->next();
    }
    else return;

    m_next->setEnabled( m_steps.at( m_currentStep )->isNextEnabled() );
    m_back->setEnabled( true );
}


void
ViewManager::back()
{
    ViewStep* step = m_steps.at( m_currentStep );
    if ( step->isAtBeginning() && m_currentStep > 0 )
    {
        m_currentStep--;
        m_stack->setCurrentIndex( m_currentStep );
    }
    else if ( !step->isAtBeginning() )
    {
        step->back();
    }
    else return;

    m_next->setEnabled( m_steps.at( m_currentStep )->isNextEnabled() );
    if ( m_currentStep == 0 && m_steps.first()->isAtBeginning() )
        m_back->setEnabled( false );
}

}
