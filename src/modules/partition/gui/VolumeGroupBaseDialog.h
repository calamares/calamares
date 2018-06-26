/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2018, Caio Jordão Carvalho <caiojcarvalho@gmail.com>
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

#ifndef VOLUMEGROUPBASEDIALOG_H
#define VOLUMEGROUPBASEDIALOG_H

#include <kpmcore/core/partition.h>

#include <QDialog>

namespace Ui {
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
    explicit VolumeGroupBaseDialog( QString& vgName,
                                    QVector< const Partition* > pvList,
                                    QWidget* parent = nullptr );
    ~VolumeGroupBaseDialog();

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

#endif // VOLUMEGROUPBASEDIALOG_H
