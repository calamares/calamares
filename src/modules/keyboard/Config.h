/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019-2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2020 Camilo Higuita <milo.h@aol.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef KEYBOARD_CONFIG_H
#define KEYBOARD_CONFIG_H

#include "Job.h"
#include "KeyboardLayoutModel.h"

#include <QAbstractListModel>
#include <QMap>
#include <QObject>
#include <QTimer>
#include <QUrl>

class Config : public QObject
{
    Q_OBJECT
    Q_PROPERTY( KeyboardModelsModel* keyboardModelsModel READ keyboardModels CONSTANT FINAL )
    Q_PROPERTY( KeyboardLayoutModel* keyboardLayoutsModel READ keyboardLayouts CONSTANT FINAL )
    Q_PROPERTY( KeyboardVariantsModel* keyboardVariantsModel READ keyboardVariants CONSTANT FINAL )
    Q_PROPERTY( QString prettyStatus READ prettyStatus NOTIFY prettyStatusChanged FINAL )

public:
    Config( QObject* parent = nullptr );

    void init();

    Calamares::JobList createJobs();
    QString prettyStatus() const;

    void onActivate();
    void finalize();

    void setConfigurationMap( const QVariantMap& configurationMap );

private:
    void guessLayout( const QStringList& langParts );
    void updateVariants( const QPersistentModelIndex& currentItem, QString currentVariant = QString() );

    KeyboardModelsModel* m_keyboardModelsModel;
    KeyboardLayoutModel* m_keyboardLayoutsModel;
    KeyboardVariantsModel* m_keyboardVariantsModel;

    QString m_selectedLayout;
    QString m_selectedModel;
    QString m_selectedVariant;
    QTimer m_setxkbmapTimer;

    // From configuration
    QString m_xOrgConfFileName;
    QString m_convertedKeymapPath;
    bool m_writeEtcDefaultKeyboard = true;


protected:
    KeyboardModelsModel* keyboardModels() const;
    KeyboardLayoutModel* keyboardLayouts() const;
    KeyboardVariantsModel* keyboardVariants() const;


signals:
    void prettyStatusChanged();
};


#endif
