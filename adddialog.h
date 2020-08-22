#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = 0);
    ~AddDialog();

    bool f, s, t, ans;
    QString name;
protected:
    void changeEvent(QEvent *e);

private slots:
    void on_firstCheck_stateChanged(int arg1);

    void on_secondCheck_stateChanged(int arg1);

    void on_thirdCheck_stateChanged(int arg1);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::AddDialog *ui;
};

#endif // ADDDIALOG_H
