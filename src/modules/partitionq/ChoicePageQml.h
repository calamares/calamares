/* === This file is part of Calamares - <https://calamares.io> ===
 *   SPDX-FileCopyrightText: 2014-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2014-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2019 Collabora Ltd
 *   SPDX-FileCopyrightText: 2022 Aditya Mehra <aix.m@outlook.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CHOICEPAGEQML_H
#define CHOICEPAGEQML_H

#include <QMutex>
#include <QPointer>
#include <QSet>
#include "Config.h"
#include "core/OsproberEntry.h"

namespace Calamares
{
}

class Config;
class PartitionCoreModule;
class PartitionSplitterWidget;
class PartitionModel;
class Device;

using SwapChoiceSet = Config::SwapChoiceSet;

/**
 * @brief The ChoicePage class is the first page of the partitioning interface.
 * It offers a choice between partitioning operations and initiates all automated
 * partitioning modes. For manual partitioning, see PartitionPage.
 */
class ChoicePageQml : public QObject
{
    Q_OBJECT
    Q_ENUMS(InstallChoiceType)

    Q_PROPERTY( bool eraseButtonEnabled READ eraseButtonEnabled WRITE setEraseButtonEnabled NOTIFY eraseButtonEnabledChanged )
    Q_PROPERTY( bool alongSideButtonEnabled READ alongSideButtonEnabled WRITE setAlongSideButtonEnabled NOTIFY alongSideButtonEnabledChanged )
    Q_PROPERTY( bool replaceButtonEnabled READ replaceButtonEnabled WRITE setReplaceButtonEnabled NOTIFY replaceButtonEnabledChanged )
    Q_PROPERTY( bool manualButtonEnabled READ manualButtonEnabled WRITE setManualButtonEnabled NOTIFY manualButtonEnabledChanged )

    Q_PROPERTY( QString messageLabel READ messageLabel WRITE setMessageLabel NOTIFY messageLabelChanged )
    Q_PROPERTY( QString eraseButtonLabel READ eraseButtonLabel WRITE setEraseButtonLabel NOTIFY eraseButtonLabelChanged )
    Q_PROPERTY( QString alongSideButtonLabel READ alongSideButtonLabel WRITE setAlongSideButtonLabel NOTIFY alongSideButtonLabelChanged )
    Q_PROPERTY( QString replaceButtonLabel READ replaceButtonLabel WRITE setReplaceButtonLabel NOTIFY replaceButtonLabelChanged )
    Q_PROPERTY( QString somethingElseButtonLabel READ somethingElseButtonLabel WRITE setSomethingElseButtonLabel NOTIFY somethingElseButtonLabelChanged )

    Q_PROPERTY( QAbstractItemModel* partitionModel READ partitionModel CONSTANT FINAL )

public:
    explicit ChoicePageQml( Config* config, QObject* parent = nullptr );

    enum InstallChoiceType
    {
        EraseChoice,
        AlongSideChoice,
        ReplaceChoice,
        ManualChoice
    };
    Q_ENUMS(InstallChoiceType)

    /**
     * @brief init runs when the PartitionViewStep and the PartitionCoreModule are
     *      ready. Sets up the rest of the UI based on os-prober output.
     * @param core the PartitionCoreModule pointer.
     */
    void init( PartitionCoreModule* core );

    /**
     * @brief isNextEnabled answers whether the current state of the page is such
     * that progressing to the next page should be allowed.
     * @return true if next is allowed, otherwise false.
     */
    bool isNextEnabled() const;

    /**
     * @brief onLeave runs when control passes from this page to another one.
     */
    void onLeave();

    /**
     * @brief applyActionChoice reacts to a choice of partitioning mode.
     * @param choice the partitioning action choice.
     */
    void applyActionChoice( Config::InstallChoice choice );

    int lastSelectedDeviceIndex();
    void setLastSelectedDeviceIndex( int index );

    void onActionChanged();
    
    bool eraseButtonEnabled();
    bool alongSideButtonEnabled();
    bool replaceButtonEnabled();
    bool manualButtonEnabled();

    void setEraseButtonEnabled( bool eraseButtonEnabled );
    void setAlongSideButtonEnabled( bool alongSideButtonEnabled );
    void setReplaceButtonEnabled( bool replaceButtonEnabled );
    void setManualButtonEnabled( bool manualButtonEnabled );

    QString messageLabel() const;
    QString eraseButtonLabel() const;
    QString alongSideButtonLabel() const;
    QString replaceButtonLabel() const;
    QString somethingElseButtonLabel() const;

    void setMessageLabel( QString messageLabel );
    void setEraseButtonLabel( QString eraseButtonLabel );
    void setAlongSideButtonLabel( QString alongSideButtonLabel );
    void setReplaceButtonLabel( QString replaceButtonLabel );
    void setSomethingElseButtonLabel( QString somethingElseButtonLabel );

    PartitionModel* partitionModel() const;
    void setPartitionModelForDevice();

public Q_SLOTS:
    void setDeviceIndex(int index);
    void setupActions();
    QString getCurrentDevicePartitionType() const;
    void setInstallChoice(int installChoice);
    QVariantList getEraseSwapChoices() const;
    int getInitialSwapChoice() const;
    void setSwapChoice(int selectedSwapChoice);
    bool encryptWidgetEnabled() const;
    void setEncryptionSelected(bool enabled);
    void setEncryptionPhrase(const QString& phrase);

Q_SIGNALS:
    void labelsUpdated();
    void setEFIMessageLabel( const QString& message );
    void scanningDialogShow();
    void scanningDialogHide();

    void eraseButtonEnabledChanged();
    void alongSideButtonEnabledChanged();
    void replaceButtonEnabledChanged();
    void manualButtonEnabledChanged();

    void messageLabelChanged();
    void eraseButtonLabelChanged();
    void alongSideButtonLabelChanged();
    void replaceButtonLabelChanged();
    void somethingElseButtonLabelChanged();

signals:
    void nextStatusChanged( bool );
    void actionChosen();
    void deviceChosen();

private:
    bool calculateNextEnabled() const;
    void updateNextEnabled();
    Device* selectedDevice();

    void applyDeviceChoice();  // Start scanning new device
    void continueApplyDeviceChoice();  // .. called after scan

    OsproberEntryList getOsproberEntriesForDevice( Device* device ) const;
    void setupEfiSystemPartitionSelector();

    Config* m_config;
    bool m_nextEnabled;
    PartitionCoreModule* m_core;
    PartitionModel* m_partitionModel;

    QMutex m_previewsMutex;

    bool m_isEfi;

    int m_lastSelectedDeviceIndex = -1;
    int m_lastSelectedActionIndex = -1;

    bool m_enableEncryptionWidget;
    bool m_encryptionSelected;

    bool m_alongSideButtonEnabled;
    bool m_eraseButtonEnabled;
    bool m_replaceButtonEnabled;
    bool m_somethingElseButtonEnabled;

    int m_selectedDeviceIndex = -1;
    int m_deviceIndex = -1;

    QString m_messageLabel;
    QString m_eraseButtonLabel;
    QString m_alongSideButtonLabel;
    QString m_replaceButtonLabel;
    QString m_somethingElseButtonLabel;

    QPointer< PartitionSplitterWidget > m_afterPartitionSplitterWidget;

    QString m_currentDevicePartitionType;
    QString m_currentDevicePartitionTypeName;

    QString m_encryptPassphrase;
    
    QMutex m_coreMutex;
};

#endif  // CHOICEPAGEQML_H
