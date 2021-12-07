/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Artem Grinev <agrinev@manjaro.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef LIBCALAMARESUI_ERRORDIALOG_H
#define LIBCALAMARESUI_ERRORDIALOG_H

#include <QDialog>

namespace Ui
{
class ErrorDialog;
}

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
    ~ErrorDialog() override;

    /** @brief The heading (title) of the error dialog
     *
     * This is a short (one-line) title. It is human-readable, so should
     * be translated at the time it is set.
     */
    QString heading() const;
    void setHeading( const QString& newHeading );

    /** @brief The description of the problem
     *
     * Longer, human-readable, description of the problem. This text
     * is word-wrapped as necessary.
     */
    QString informativeText() const;
    void setInformativeText( const QString& newInformativeText );

    /** @brief Details of the problem
     *
     * This is generally command-output; it might not be translated
     * when set. It should be considered "background to the informative
     * text", or maybe "the reasons". Write the informative text for
     * the end-user.
     */
    QString details() const;
    void setDetails( const QString& newDetails );

    /** @brief Enable web-paste button
     *
     * The web-paste button can be configured at a global level,
     * but each individual error dialog can be set separately.
     */
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

#endif  // LIBCALAMARESUI_ERRORDIALOG_H
