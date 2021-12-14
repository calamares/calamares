/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Caio Jordão Carvalho <caiojcarvalho@gmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef VOLUMEGROUPBASEDIALOG_H
#define VOLUMEGROUPBASEDIALOG_H

#include <kpmcore/core/partition.h>

#include <QDialog>

namespace Ui
{
class VolumeGroupBaseDialog;
}

class QComboBox;
class QLineEdit;
class QListWidget;
class QSpinBox;

class VolumeGroupBaseDialog : public QDialog
{
    Q_OBJECT

public:
    using PartitionVector = QVector< const Partition* >;

    explicit VolumeGroupBaseDialog( QWidget* parent, const QString& vgName, PartitionVector pvList );
    ~VolumeGroupBaseDialog() override;

    qint32 physicalExtentSize() const { return m_physicalExtentSize; }
    QString volumeGroupName() const { return m_volumeGroupName; }
    /** @brief Which PVs (partitions) are selected for this VG
     *
     * The vector contains non-owned pointers.
     */
    PartitionVector selectedPVs() const;

protected:
    virtual void updateOkButton();

    void setUsedSizeValue( qint64 usedSize );
    void setLVQuantity( qint32 lvQuantity );
    bool isSizeValid() const;

    void updateTotalSize();
    void updateTotalSectors();


    /** @section UI-widget accessors
     *
     * These methods get UI internal widgets, so that subclasses
     * can manipulate the values in those widgets.
     */
    QLineEdit* vgNameWidget() const;
    QComboBox* vgTypeWidget() const;
    QSpinBox* peSizeWidget() const;
    QListWidget* pvListWidget() const;
    QPushButton* okButtonWidget() const;

private:
    Ui::VolumeGroupBaseDialog* ui;

    QString m_volumeGroupName;
    qint64 m_totalSizeValue;
    qint64 m_usedSizeValue;
    qint32 m_physicalExtentSize;
};

#endif  // VOLUMEGROUPBASEDIALOG_H
