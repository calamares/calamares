/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef REPLACEWIDGET_H
#define REPLACEWIDGET_H

#include "utils/CalamaresUtilsGui.h"

#include <QScopedPointer>
#include <QWidget>

class Ui_ReplaceWidget;
class QComboBox;
class PartitionCoreModule;
class Partition;

class ReplaceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ReplaceWidget( PartitionCoreModule* core, QComboBox* devicesComboBox, QWidget* parent = nullptr );
    virtual ~ReplaceWidget() override;

    bool isNextEnabled() const;

    void reset();

    void applyChanges();

signals:
    void nextStatusChanged( bool );

private slots:
    void onPartitionSelected();

private:
    QScopedPointer< Ui_ReplaceWidget > m_ui;
    void setNextEnabled( bool enabled );

    void updateStatus( CalamaresUtils::ImageType imageType, const QString& text );

    PartitionCoreModule* m_core;

    bool m_nextEnabled;

    bool m_isEfi;

    void updateFromCurrentDevice( QComboBox* devicesComboBox );
    void onPartitionViewActivated();
    void onPartitionModelReset();
};

#endif  // REPLACEWIDGET_H
