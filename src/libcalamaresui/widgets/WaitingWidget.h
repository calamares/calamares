/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef WAITINGWIDGET_H
#define WAITINGWIDGET_H

#include "widgets/waitingspinnerwidget.h"

#include <chrono>
#include <memory>

class QLabel;
class QTimer;

/** @brief A spinner and a label below it
 *
 * The spinner has a fixed size of 4* the font height,
 * and the text is displayed centered below it. Use this
 * to display a long-term waiting situation with a status report.
 */
class WaitingWidget : public WaitingSpinnerWidget
{
public:
    /// Create a WaitingWidget with initial @p text label.
    explicit WaitingWidget( const QString& text, QWidget* parent = nullptr );
    ~WaitingWidget() override;
};

/** @brief A spinner and a countdown inside it
 *
 * The spinner is sized to the text-height and displays a
 * numeric countdown iside the spinner. The countdown is updated
 * every second. The signal timeout() is sent every time
 * the countdown reaches 0.
 */
class CountdownWaitingWidget : public WaitingSpinnerWidget
{
    Q_OBJECT
public:
    /// Create a countdown widget with a given @p duration
    explicit CountdownWaitingWidget( std::chrono::seconds duration = std::chrono::seconds( 5 ),
                                     QWidget* parent = nullptr );
    ~CountdownWaitingWidget() override;

    /// Changes the duration used and resets the countdown
    void setInterval( std::chrono::seconds duration );

    /// Start the countdown, resets to the full duration
    void start();
    /// Stop the countdown
    void stop();

Q_SIGNALS:
    void timeout();

protected Q_SLOTS:
    void tick();

private:
    struct Private;
    std::unique_ptr< Private > d;
};

#endif  // WAITINGWIDGET_H
