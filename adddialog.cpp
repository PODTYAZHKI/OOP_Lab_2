#include "adddialog.h"
#include "ui_adddialog.h"

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);

    f = false;
    s = false;
    t = false;
    ans = false;
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void AddDialog::on_firstCheck_stateChanged(int arg1)
{
    if (ui->lineEdit->text() != "" && (ui->firstCheck->isChecked() || ui->secondCheck->isChecked() || ui->thirdCheck->isChecked()))
        ui->pushButton->setEnabled(true);
    else
        ui->pushButton->setEnabled(false);
}

void AddDialog::on_secondCheck_stateChanged(int arg1)
{
    if (ui->lineEdit->text() != "" && (ui->firstCheck->isChecked() || ui->secondCheck->isChecked() || ui->thirdCheck->isChecked()))
        ui->pushButton->setEnabled(true);
    else
        ui->pushButton->setEnabled(false);
}

void AddDialog::on_thirdCheck_stateChanged(int arg1)
{
    if (ui->lineEdit->text() != "" && (ui->firstCheck->isChecked() || ui->secondCheck->isChecked() || ui->thirdCheck->isChecked()))
        ui->pushButton->setEnabled(true);
    else
        ui->pushButton->setEnabled(false);
}

void AddDialog::on_lineEdit_textChanged(const QString &arg1)
{
    if (ui->lineEdit->text() != "" && (ui->firstCheck->isChecked() || ui->secondCheck->isChecked() || ui->thirdCheck->isChecked()))
        ui->pushButton->setEnabled(true);
    else
        ui->pushButton->setEnabled(false);
}

void AddDialog::on_pushButton_clicked()
{
    ans = true;
    f = ui->firstCheck->isChecked();
    s = ui->secondCheck->isChecked();
    t = ui->thirdCheck->isChecked();
    name = ui->lineEdit->text();
    close();
}
