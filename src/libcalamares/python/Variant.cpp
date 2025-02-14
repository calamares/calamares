/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018-2020, 2024 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Variant.h"

#include "PythonTypes.h"
#include "compat/Variant.h"

namespace
{

Calamares::Python::List
variantListToPyList( const QVariantList& variantList )
{
    Calamares::Python::List pyList;
    for ( const QVariant& variant : variantList )
    {
        pyList.append( Calamares::Python::variantToPyObject( variant ) );
    }
    return pyList;
}

Calamares::Python::Dictionary
variantHashToPyDict( const QVariantHash& variantHash )
{
    Calamares::Python::Dictionary pyDict;
    for ( auto it = variantHash.constBegin(); it != variantHash.constEnd(); ++it )
    {
        pyDict[ Calamares::Python::String( it.key().toStdString() ) ] = Calamares::Python::variantToPyObject( it.value() );
    }
    return pyDict;
}

}

namespace Calamares
{
namespace Python
{

Dictionary
variantMapToPyDict( const QVariantMap& variantMap )
{
    Calamares::Python::Dictionary pyDict;
    for ( auto it = variantMap.constBegin(); it != variantMap.constEnd(); ++it )
    {
        pyDict[ Calamares::Python::String( it.key().toStdString() ) ] = Calamares::Python::variantToPyObject( it.value() );
    }
    return pyDict;
}

Object
variantToPyObject( const QVariant& variant )
{
    QT_WARNING_PUSH
    QT_WARNING_DISABLE_CLANG( "-Wswitch-enum" )

    // 49 enumeration values not handled
    switch ( Calamares::typeOf( variant ) )
    {
    case Calamares::MapVariantType:
        return variantMapToPyDict( variant.toMap() );

    case Calamares::HashVariantType:
        return variantHashToPyDict( variant.toHash() );

    case Calamares::ListVariantType:
    case Calamares::StringListVariantType:
        return variantListToPyList( variant.toList() );

    case Calamares::IntVariantType:
        return Python::Integer( variant.toInt() );
    case Calamares::UIntVariantType:
        return Python::Integer( variant.toUInt() );

    case Calamares::LongLongVariantType:
        return Python::Integer( variant.toLongLong() );
    case Calamares::ULongLongVariantType:
        return Python::Integer( variant.toULongLong() );

    case Calamares::DoubleVariantType:
        return Python::Float( variant.toDouble() );

    case Calamares::CharVariantType:
#if QT_VERSION < QT_VERSION_CHECK( 6, 0, 0 )
#else
    // In Qt6, QChar is also available and different from CharVariantType
    case QMetaType::Type::QChar:
#endif
    case Calamares::StringVariantType:
        return Calamares::Python::String( variant.toString().toStdString() );

    case Calamares::BoolVariantType:
        return Python::Boolean( variant.toBool() );

#if QT_VERSION < QT_VERSION_CHECK( 6, 0, 0 )
    case QVariant::Invalid:
#endif
    default:
        return Python::None();
    }
    QT_WARNING_POP
}


    }
}
