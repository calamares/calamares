#include "ErrorDialog.h"
#include "ui_ErrorDialog.h"

#include <QIcon>
#include <QDialogButtonBox>
#include "widgets/TranslationFix.h"

namespace Calamares {


ErrorDialog::ErrorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorDialog)
{
    ui->setupUi(this);
    ui->iconLabel->setPixmap(QIcon::fromTheme("dialog-error").pixmap(64));
    ui->detailsWidget->hide();
    ui->offerWebPasteLabel->hide();
}

ErrorDialog::~ErrorDialog()
{
    delete ui;
}


QString ErrorDialog::heading() const
{
    return ui->headingLabel->text();
}

QString ErrorDialog::informativeText() const
{
    return ui->informativeTextLabel->text();
}

QString ErrorDialog::details() const
{
    return ui->detailsBrowser->toPlainText();
}

void ErrorDialog::setHeading(const QString &newHeading)
{
    if (ui->headingLabel->text() == newHeading)
        return;
    ui->headingLabel->setText(newHeading);
    emit headingChanged();
}

void ErrorDialog::setInformativeText(const QString &newInformativeText)
{
    if (ui->informativeTextLabel->text() == newInformativeText)
        return;
    ui->informativeTextLabel->setText(newInformativeText);
    emit informativeTextChanged();
}

void ErrorDialog::setDetails(const QString &newDetails)
{
    if (ui->detailsBrowser->toPlainText() == newDetails)
        return;   
    ui->detailsBrowser->setPlainText(newDetails);
    
    ui->detailsWidget->setVisible(!ui->detailsBrowser->toPlainText().trimmed().isEmpty());
    
    emit detailsChanged();
}

bool ErrorDialog::shouldOfferWebPaste() const
{
    return m_shouldOfferWebPaste;
}

void ErrorDialog::setShouldOfferWebPaste(bool newShouldOfferWebPaste)
{
    if (m_shouldOfferWebPaste == newShouldOfferWebPaste)
        return;
    m_shouldOfferWebPaste = newShouldOfferWebPaste;
    
    ui->offerWebPasteLabel->setVisible(m_shouldOfferWebPaste);
    
    ui->buttonBox->setStandardButtons( m_shouldOfferWebPaste
                                           ? (QDialogButtonBox::Yes | QDialogButtonBox::No)
                                            : QDialogButtonBox::Close );
    
    fixButtonLabels(ui->buttonBox);    
    
    emit shouldOfferWebPasteChanged();
}

} // namespace Calamares
