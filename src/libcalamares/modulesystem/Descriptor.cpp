/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include "Descriptor.h"

#include "utils/Logger.h"

namespace Calamares
{
namespace ModuleSystem
{

const NamedEnumTable< Type >&
typeNames()
{
    // *INDENT-OFF*
    // clang-format off
    static const NamedEnumTable< Type > table{
        { QStringLiteral( "job" ), Type::Job },
        { QStringLiteral( "view" ), Type::View },
        { QStringLiteral( "viewmodule" ), Type::View },
        { QStringLiteral( "jobmodule" ), Type::Job }
    };
    // *INDENT-ON*
    // clang-format on
    return table;
}

const NamedEnumTable< Interface >&
interfaceNames()
{
    // *INDENT-OFF*
    // clang-format off
    static const NamedEnumTable< Interface > table {
        { QStringLiteral("process"), Interface::Process },
        { QStringLiteral("qtplugin"), Interface::QtPlugin },
        { QStringLiteral("python"), Interface::Python },
        { QStringLiteral("pythonqt"), Interface::PythonQt }
    };
    // *INDENT-ON*
    // clang-format on
    return table;
}

Descriptor::Descriptor() {}

Descriptor
Descriptor::fromDescriptorData( const QVariantMap& moduleDesc )
{
    Descriptor d;

    cDebug() << moduleDesc;

    {
        bool typeOk = false;
        Type t = typeNames().find( moduleDesc.value( "type" ).toString(), typeOk );
        bool interfaceOk = false;
        Interface i = interfaceNames().find( moduleDesc.value( "interface" ).toString(), interfaceOk );
        d.m_name = moduleDesc.value( "name" ).toString();
        if ( typeOk && interfaceOk && !d.m_name.isEmpty() )
        {
            d.m_type = t;
            d.m_interface = i;
            d.m_isValid = true;
        }
    }
    if ( !d.m_isValid )
    {
        return d;
    }

    return d;
}

}  // namespace ModuleSystem
}  // namespace Calamares
