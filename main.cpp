#include "mainwindow.h"
#include <QApplication>
#include <set.h>
#include <cassert>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    Set<QString> first;
    assert(first.size() == 0);

    first.insert("test");
    assert(first.size() == 1);

    first.insert("test");
    assert(first.size() == 1);

    assert(first.contains("test"));

    first.remove("no");
    assert(first.size() == 1);

    first.remove("test");
    assert(first.size() == 0);

    assert(first.contains("test") == false);

    first.insert("let's check");
    first.clear();
    Set<QString> second;
    assert(first == second);

    second.insert("okay");
    assert((first && second).size() == 0);

    first.insert("okay");
    assert((first && second) == first);

    Set<QString> third(first);
    assert(third == first);

    third.remove("okay");
    assert(third != first);

    QFile file("data.dat");
    if (file.open(QIODevice::WriteOnly)){
        QDataStream stream(&file);
        stream << first;
        file.close();
    }
    if (file.open(QIODevice::ReadOnly)){
        QDataStream stream(&file);
        stream >> third;
        file.close();
    }
    assert(first == third);

    for (auto i = first.begin(); i != first.end(); ++i){
        qDebug() << i.key();
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
