#ifndef LIBCALAMARESUI_LOGWIDGET_H
#define LIBCALAMARESUI_LOGWIDGET_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QThread>

namespace Calamares
{

class LogThread : public QThread
{
    Q_OBJECT

    void run() override;

public:
    explicit LogThread(QObject *parent = nullptr);
    ~LogThread() override;

signals:
    void onLogChunk(const QString &logChunk);
};

class LogWidget : public QWidget
{
    Q_OBJECT

    QPlainTextEdit* m_text;
    LogThread m_log_thread;
public:
    explicit LogWidget(QWidget *parent = nullptr);

    void handleLogChunk(const QString &logChunk);
};

}
#endif // LOGWIDGET_H
