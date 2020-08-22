#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "set.h"
#include <QFile>
#include <QFileDialog>
#include <adddialog.h>
#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Set<QString> first;
    Set<QString> second;
    Set<QString> third;
    void updTables();
    QString delStr;
    int delTable;
private slots:
    void on_addButton_clicked();

    void on_listFirst_itemSelectionChanged();

    void on_listSecond_itemSelectionChanged();

    void on_listThird_itemSelectionChanged();

    void on_delButton_clicked();

    void on_clearButton_clicked();

    void on_exitButton_clicked();

    void on_btnSave_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
