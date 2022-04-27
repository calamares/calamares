/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2022 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef TRANSLATION_BINDING_H
#define TRANSLATION_BINDING_H

#include "DllMacro.h"

#include <QObject>
#include <QString>
#include <QStringList>
#include <QWidget>

#include <functional>
#include <optional>

namespace Calamares
{
namespace Translation
{

/** @brief An object that can re-translate a whole collection of widgets.
 *
 * A translation binding should be created for a top-level widget (e.g. a
 * view page). Child widgets of that top-level can be added to the  binding.
 * This removes the need for CALAMARES_RETRANSLATE macro calls.
 *
 * For text widgets with fixed strings, use add().
 * For text widgets with strings with parameters, use add() with a string-list
 * parameter. The elements of the list will be substituted into the translated
 * string (as usual with QString, using the %1 .. substitution syntax).
 * For pages that use a .ui file and generate UI code via uic, use addUi().
 *
 */
class UIDLLEXPORT Binding : public QObject
{
    Q_OBJECT
public:
    Binding( QWidget* parent );
    virtual ~Binding() override;

    void update();

    /** @brief Adds (or updates) the string applied to a widget
     *
     * Sets the text on @p widget to be the (translated) @p string. If
     * @p widget already has a translation set via the Labeler, the
     * translation is updated with the new string.
     */
    template < typename T >
    void add( T* widget, const char* string )
    {
        auto* p = add_internal( widget, string );
        p->update( m_parent );
    }

    /** @brief Adds (or updates) the string applied to a widget
     *
     * As add() without the list parameter @p s . The items of
     * the list @p s are copied and used as substitutions in the
     * (translation of) @p string .
     */
    template < typename T >
    void add( T* widget, const char* string, const QStringList& s )
    {
        auto* p = add_internal( widget, string );
        p->setArgs( s );
        p->update( m_parent );
    }

    /** @brief Update the substitutions for a widget
     *
     * When the string doesn't change, but the substitutions to put into
     * it do, use updateArguments();
     */
    template < typename T >
    void updateArguments( T* widget, const QStringList& s )
    {
        auto* p = find_internal< T >( widget );
        if ( p )
        {
            p->setArgs( s );
            p->update( m_parent );
        }
    }

    /** @brief Add a UI-based class to translations */
    template < typename T >
    void addUi( T* ui )
    {
        auto it = std::find_if( m_labels.begin(), m_labels.end(), [ = ]( BaseUpdater* p ) { return p->widget == ui; } );
        if ( it == m_labels.end() )
        {
            auto* p = new UiUpdater< T > { ui };
            m_labels.append( p );
            p->update( m_parent );
        }
    }

private:
    struct UIDLLEXPORT BaseUpdater
    {
        void* widget = nullptr;
        const char* untranslated_string = nullptr;
        std::optional< QStringList > args;

        BaseUpdater( QWidget* w, const char* s )
            : widget( w )
            , untranslated_string( s )
        {
        }
        virtual ~BaseUpdater();

        virtual void update( QWidget* parent ) = 0;

        QString tr( QWidget* parent ) const;
        void setArgs( const QStringList& s ) { args = s; }
    };

    template < typename T >
    struct Updater : public BaseUpdater
    {
        using BaseUpdater::BaseUpdater;
        void update( QWidget* parent ) override
        {
            static_cast< T* >( widget )->setText( tr( parent ) );  // tr() is from BaseUpdater
        }
    };

    template < typename T >
    struct UiUpdater : public BaseUpdater
    {
        UiUpdater( T* ui )
            : BaseUpdater( nullptr, nullptr )
        {
            widget = ui;
        }
        void update( QWidget* parent ) override { static_cast< T* >( widget )->retranslateUi( parent ); }
    };

    QWidget* m_parent = nullptr;
    QList< BaseUpdater* > m_labels;

    template < typename T >
    BaseUpdater* add_internal( T* widget, const char* string )
    {
        auto* p = find_internal< T >( widget );
        if ( p )
        {
            p->untranslated_string = string;
            return p;
        }
        else
        {
            p = new Updater< T > { widget, string };
            m_labels.append( p );
            return p;
        }
    }

    template < typename T >
    BaseUpdater* find_internal( T* widget )
    {
        auto it
            = std::find_if( m_labels.begin(), m_labels.end(), [ = ]( BaseUpdater* p ) { return p->widget == widget; } );
        return ( it != m_labels.end() ) ? ( *it ) : nullptr;
    }
};

}  // namespace Translation
}  // namespace Calamares

#endif
