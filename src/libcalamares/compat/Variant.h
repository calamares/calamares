/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2023 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */
#ifndef CALAMARES_COMPAT_VARIANT_H
#define CALAMARES_COMPAT_VARIANT_H

#include <QVariant>

namespace Calamares
{
/* Compatibility of QVariant between Qt5 and Qt6 */
#if QT_VERSION < QT_VERSION_CHECK( 6, 0, 0 )
const auto typeOf = []( const QVariant& v ) { return v.type(); };
const auto ListVariantType = QVariant::List;
const auto MapVariantType = QVariant::Map;
const auto HashVariantType = QVariant::Hash;
const auto StringVariantType = QVariant::String;
const auto CharVariantType = QVariant::Char;
const auto StringListVariantType = QVariant::StringList;
const auto BoolVariantType = QVariant::Bool;
const auto IntVariantType = QVariant::Int;
const auto UIntVariantType = QVariant::UInt;
const auto LongLongVariantType = QVariant::LongLong;
const auto ULongLongVariantType = QVariant::ULongLong;
const auto DoubleVariantType = QVariant::Double;
#else
const auto typeOf = []( const QVariant& v ) { return v.typeId(); };
const auto ListVariantType = QMetaType::Type::QVariantList;
const auto MapVariantType = QMetaType::Type::QVariantMap;
const auto HashVariantType = QMetaType::Type::QVariantHash;
const auto StringVariantType = QMetaType::Type::QString;
const auto CharVariantType = QMetaType::Type::Char;
const auto StringListVariantType = QMetaType::Type::QStringList;
const auto BoolVariantType = QMetaType::Type::Bool;
const auto IntVariantType = QMetaType::Type::Int;
const auto UIntVariantType = QMetaType::Type::UInt;
const auto LongLongVariantType = QMetaType::Type::LongLong;
const auto ULongLongVariantType = QMetaType::Type::ULongLong;
const auto DoubleVariantType = QMetaType::Type::Double;
#endif

inline bool
isIntegerVariantType( const QVariant& v )
{
    const auto t = typeOf( v );
    return t == IntVariantType || t == UIntVariantType || t == LongLongVariantType || t == ULongLongVariantType;
}

}  // namespace Calamares

#endif
