#ifndef SET_H
#define SET_H

#include "iter.h"

#include <QDataStream>
#include <QString>

template <typename T1>
class Set
{
public:
    Set();
    Set(QString name);
    Set(const Set &other);

    int hash(T1 key) const;
    void insert(T1 key);
    bool contains(T1 key) const;
    void remove(T1 key);
    void clear();
    int size() const{
        return count;
    }
    Iter<T1> begin() const;
    Iter<T1> end() const{
        return Iter<T1>(nullptr);
    }
    bool operator ==(const Set &other);
    bool operator !=(const Set &other);
    Set<T1> operator &&(const Set &other);
    QString &getName(){
        return name;
    }
protected:
    Node<T1> **data;
    int count;
    QString name;
};

template <typename T1>
QDataStream &operator <<(QDataStream &out, Set<T1> &ht){
    out << ht.getName() << ht.size();
    for (auto it = ht.begin(); it != ht.end(); ++it)
        out << *it;
}

template <typename T1>
QDataStream &operator >>(QDataStream &in, Set<T1> &ht){
    T1 key; QString name; int count;
    in >> name >> count;
    ht.getName() = name;
    for (int i = 0; i < count; i++) {
        in >> key;
        ht.insert(key);
    }
}

#endif // Set_H
