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
    explicit VolumeGroupBaseDialog( QString& vgName, QVector< const Partition* > pvList, QWidget* parent = nullptr );
    ~VolumeGroupBaseDialog() override;

protected:
    virtual void updateOkButton();

    void setUsedSizeValue( qint64 usedSize );

    void setLVQuantity( qint32 lvQuantity );

    void updateTotalSize();

    void updateTotalSectors();

    QVector< const Partition* > checkedItems() const;

    bool isSizeValid() const;

    QString& vgNameValue() const;

    QLineEdit* vgName() const;

    QComboBox* vgType() const;

    QSpinBox* peSize() const;

    QListWidget* pvList() const;

    QPushButton* okButton() const;

private:
    Ui::VolumeGroupBaseDialog* ui;

    QString& m_vgNameValue;

    qint64 m_totalSizeValue;
    qint64 m_usedSizeValue;
};

#endif  // VOLUMEGROUPBASEDIALOG_H
