#include "mainwindow.h"
#include "ui_mainwindow.h"
typedef Set<QString> SetQ;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setGeometry(100, 50, 1200, 650);
    delTable = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updTables()
{
    bool flag = false;
    if (!first.size() && !second.size() && !third.size()){
        ui->clearButton->setEnabled(false);
        flag = true;
    }

    ui->listFirst->clear();
    ui->listSecond->clear();
    ui->listThird->clear();
    ui->listIdeal->clear();

    if (flag) return;

    ui->clearButton->setEnabled(true);

    int i = 0;
    for (auto it = first.begin(); it != first.end(); ++it)
        ui->listFirst->insertItem(i++, it.key());

    i = 0;
    for (auto it = second.begin(); it != second.end(); ++it)
        ui->listSecond->insertItem(i++, it.key());

    i = 0;
    for (auto it = third.begin(); it != third.end(); ++it)
        ui->listThird->insertItem(i++, it.key());

    SetQ common(first && second && third);
    i = 0;
    for (auto it = common.begin(); it != common.end(); ++it)
        ui->listIdeal->insertItem(i++, it.key());

}

void MainWindow::on_addButton_clicked()
{
    AddDialog *ad = new AddDialog(this);
    ad->exec();
    if (ad->ans){
        if (ad->f) first.insert(ad->name);
        if (ad->s) second.insert(ad->name);
        if (ad->t) third.insert(ad->name);
        updTables();
    }
}

void MainWindow::on_listFirst_itemSelectionChanged()
{
    auto lst = ui->listFirst->selectedItems();
    if (lst.size() == 1){
        ui->delButton->setEnabled(true);
        delStr = lst[0]->text();
        delTable = 1;
    }
    else{
        ui->delButton->setEnabled(false);
        delStr = "";
        delTable = 0;
    }
}

void MainWindow::on_listSecond_itemSelectionChanged()
{
    auto lst = ui->listSecond->selectedItems();
    if (lst.size() == 1){
        ui->delButton->setEnabled(true);
        delStr = lst[0]->text();
        delTable = 2;
    }
    else{
        ui->delButton->setEnabled(false);
        delStr = "";
        delTable = 0;
    }
}

void MainWindow::on_listThird_itemSelectionChanged()
{
    auto lst = ui->listThird->selectedItems();
    if (lst.size() == 1){
        ui->delButton->setEnabled(true);
        delStr = lst[0]->text();
        delTable = 3;
    }
    else{
        ui->delButton->setEnabled(false);
        delStr = "";
        delTable = 0;
    }
}

void MainWindow::on_delButton_clicked()
{
    if (delTable == 1)
        first.remove(delStr);
    if (delTable == 2)
        second.remove(delStr);
    if (delTable == 3)
        third.remove(delStr);
    ui->listFirst->clearSelection();
    ui->listSecond->clearSelection();
    ui->listThird->clearSelection();
    delStr = "";
    delTable = 0;
    updTables();
}

void MainWindow::on_clearButton_clicked()
{
    first.clear();
    second.clear();
    third.clear();
    updTables();
}

void MainWindow::on_exitButton_clicked()
{
    close();
}



void MainWindow::on_btnSave_clicked()
{
    std::cout << "1";
    QString fname = QFileDialog::getSaveFileName(this, "Save...",
                                                 QDir::currentPath(),
                                                 "dat files (*.dat)");

    QFile f(fname);
    if (f.open(QIODevice::WriteOnly))
    {
        QDataStream out(&f);
        out << first;
        out << second;
        out << third;
        f.close();
    }
}

void MainWindow::on_pushButton_clicked()
{
    first.clear();
    second.clear();
    third.clear();
    updTables();

    QString fname = QFileDialog::getOpenFileName(this, "Open...",
                                                 QDir::currentPath(),
                                                 "dat files (*.dat)");

    QFile f(fname);
    if (f.open(QIODevice::ReadOnly))
    {
        QDataStream in(&f);
        in >> first;
        in >> second;
        in >> third;
        f.close();
    }
    updTables();
}
