/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Artem Grinev <agrinev@manjaro.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef ERRORDIALOG_H
#define ERRORDIALOG_H

#include <QDialog>


namespace Ui
{
class ErrorDialog;
}
class QDialogButtonBox;
namespace Calamares
{
class ErrorDialog : public QDialog
{
    Q_OBJECT

    Q_PROPERTY( QString heading READ heading WRITE setHeading NOTIFY headingChanged )
    Q_PROPERTY( QString informativeText READ informativeText WRITE setInformativeText NOTIFY informativeTextChanged )
    Q_PROPERTY( QString details READ details WRITE setDetails NOTIFY detailsChanged )
    Q_PROPERTY( bool shouldOfferWebPaste READ shouldOfferWebPaste WRITE setShouldOfferWebPaste NOTIFY
                    shouldOfferWebPasteChanged )

public:
    explicit ErrorDialog( QWidget* parent = nullptr );
    ~ErrorDialog();

    QString heading() const;

    QString informativeText() const;

    QString details() const;

    void setHeading( const QString& newHeading );

    void setInformativeText( const QString& newInformativeText );

    void setDetails( const QString& newDetails );

    bool shouldOfferWebPaste() const;
    void setShouldOfferWebPaste( bool newShouldOfferWebPaste );

signals:
    void headingChanged();

    void informativeTextChanged();

    void detailsChanged();

    void shouldOfferWebPasteChanged();

private:
    Ui::ErrorDialog* ui;
    bool m_shouldOfferWebPaste = false;
};

};  // namespace Calamares

#endif  // ERRORDIALOG_H
