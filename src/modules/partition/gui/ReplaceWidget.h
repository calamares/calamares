/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
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

#ifndef REPLACEWIDGET_H
#define REPLACEWIDGET_H

#include <QWidget>
#include <QScopedPointer>

class Ui_ReplaceWidget;
class QComboBox;
class PartitionCoreModule;
class Partition;

namespace CalamaresUtils
{
enum ImageType : int;
}

class ReplaceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ReplaceWidget( PartitionCoreModule* core,
                            QComboBox* devicesComboBox,
                            QWidget* parent = nullptr );
    virtual ~ReplaceWidget();

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

#endif // REPLACEWIDGET_H
