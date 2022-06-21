/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2022 Bob van der Linden <bobvanderlinden@gmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef LIBCALAMARESUI_LOGWIDGET_H
#define LIBCALAMARESUI_LOGWIDGET_H

#include <QPlainTextEdit>
#include <QThread>
#include <QWidget>

namespace Calamares
{

class LogThread : public QThread
{
    Q_OBJECT

    void run() override;

public:
    explicit LogThread( QObject* parent = nullptr );
    ~LogThread() override;

Q_SIGNALS:
    void onLogChunk( const QString& logChunk );
};

class LogWidget : public QWidget
{
    Q_OBJECT

    QPlainTextEdit* m_text;
    LogThread m_log_thread;

public:
    explicit LogWidget( QWidget* parent = nullptr );

public Q_SLOTS:
    /// @brief Called by the thread when there is new data
    void handleLogChunk( const QString& logChunk );

    /// @brief Stop watching for log data
    void stop();
    /// @brief Start watching for new log data
    void start();
};

}  // namespace Calamares
#endif  // LOGWIDGET_H
