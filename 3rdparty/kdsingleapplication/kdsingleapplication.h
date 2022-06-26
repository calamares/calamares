/*
    MIT License

    Copyright (C) 2019-2021 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/
#ifndef KDSINGLEAPPLICATION_H
#define KDSINGLEAPPLICATION_H

#include <QtCore/QObject>

#include <memory>

#include "kdsingleapplication_lib.h"

class KDSingleApplicationPrivate;

class KDSINGLEAPPLICATION_EXPORT KDSingleApplication : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(bool isPrimaryInstance READ isPrimaryInstance CONSTANT)

public:
    explicit KDSingleApplication(QObject *parent = nullptr);
    explicit KDSingleApplication(const QString &name, QObject *parent = nullptr);
    ~KDSingleApplication();

    QString name() const;
    bool isPrimaryInstance() const;

public Q_SLOTS:
    // avoid default arguments and overloads, as they don't mix with connections
    bool sendMessage(const QByteArray &message);
    bool sendMessageWithTimeout(const QByteArray &message, int timeout);

Q_SIGNALS:
    void messageReceived(const QByteArray &message);

private:
    Q_DECLARE_PRIVATE(KDSingleApplication)
    std::unique_ptr<KDSingleApplicationPrivate> d_ptr;
};

#endif // KDSINGLEAPPLICATION_H
