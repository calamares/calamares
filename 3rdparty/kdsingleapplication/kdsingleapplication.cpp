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

#include "kdsingleapplication.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QFileInfo>

// TODO: make this pluggable.
#include "kdsingleapplication_localsocket_p.h"

// Avoiding dragging in Qt private APIs for now, so this does not inherit
// from QObjectPrivate.
class KDSingleApplicationPrivate
{
public:
    explicit KDSingleApplicationPrivate(const QString &name, KDSingleApplication *q);

    void initialize();

    QString name() const
    {
        return m_name;
    }

    bool isPrimaryInstance() const
    {
        return m_impl.isPrimaryInstance();
    }

    bool sendMessage(const QByteArray &message, int timeout)
    {
        return m_impl.sendMessage(message, timeout);
    }

private:
    Q_DECLARE_PUBLIC(KDSingleApplication)

    KDSingleApplication *q_ptr;
    QString m_name;

    KDSingleApplicationLocalSocket m_impl;
};

KDSingleApplicationPrivate::KDSingleApplicationPrivate(const QString &name, KDSingleApplication *q)
    : q_ptr(q)
    , m_name(name)
    , m_impl(name)
{
    if (Q_UNLIKELY(name.isEmpty()))
        qFatal("KDSingleApplication requires a non-empty application name");

    if (isPrimaryInstance()) {
        QObject::connect(&m_impl, &KDSingleApplicationLocalSocket::messageReceived,
                         q, &KDSingleApplication::messageReceived);
    }
}

static QString extractExecutableName(const QString &applicationFilePath)
{
    return QFileInfo(applicationFilePath).fileName();
}

KDSingleApplication::KDSingleApplication(QObject *parent)
    : KDSingleApplication(extractExecutableName(QCoreApplication::applicationFilePath()), parent)
{
}

KDSingleApplication::KDSingleApplication(const QString &name, QObject *parent)
    : QObject(parent)
    , d_ptr(new KDSingleApplicationPrivate(name, this))
{
}

QString KDSingleApplication::name() const
{
    Q_D(const KDSingleApplication);
    return d->name();
}

bool KDSingleApplication::isPrimaryInstance() const
{
    Q_D(const KDSingleApplication);
    return d->isPrimaryInstance();
}

bool KDSingleApplication::sendMessage(const QByteArray &message)
{
    return sendMessageWithTimeout(message, 5000);
}

bool KDSingleApplication::sendMessageWithTimeout(const QByteArray &message, int timeout)
{
    Q_ASSERT(!isPrimaryInstance());

    Q_D(KDSingleApplication);
    return d->sendMessage(message, timeout);
}


KDSingleApplication::~KDSingleApplication() = default;

