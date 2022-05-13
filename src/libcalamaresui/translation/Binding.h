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
 * A labeler should be attached to a top-level widget. Child widgets
 * of that top-level can be translated via the Labeler. This removes
 * the need for CALAMARES_RETRANSLATE macro calls.
 *
 */
class DLLEXPORT Binding : public QObject
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
        (void)add_internal( widget, string );
    }

    template < typename T >
    void add( T* widget, const char* string, const QStringList& s )
    {
        auto* p = add_internal( widget, string );
        p->setArgs( s );
    }

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
    struct BaseUpdater
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
        void update( QWidget* parent ) override { static_cast< T* >( widget )->setText( tr( parent ) ); }
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
        auto it
            = std::find_if( m_labels.begin(), m_labels.end(), [ = ]( BaseUpdater* p ) { return p->widget == widget; } );
        if ( it != m_labels.end() )
        {
            ( *it )->untranslated_string = string;
            ( *it )->update( m_parent );
            return *it;
        }
        else
        {
            auto* p = new Updater< T > { widget, string };
            m_labels.append( p );
            p->update( m_parent );
            return p;
        }
    }
};

}  // namespace Translation
}  // namespace Calamares

#endif
