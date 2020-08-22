#ifndef ITER_H
#define ITER_H
#include <QDataStream>

template <typename T1>
struct Node
{
    Node(const T1 &k) {
        key = k; next = nullptr;
    }
    bool operator !=(const Node<T1> &other) const{
        return key != other.key;
    }
    bool operator ==(const Node<T1> &other) const{
        return key == other.key;
    }

    T1 key;
    Node<T1> *next;
};

template <typename T1>
QDataStream &operator <<(QDataStream &out, const Node<T1> &n){
    out << n.key;
}

template <typename T1>
QDataStream &operator >>(QDataStream &in, Node<T1> &n){
    in >> n.key;
}

template <typename T1>
class Iter
{
public:
    Iter(Node<T1> *p): ptr(p){}
    Node<T1> *&getPtr(){
        return ptr;
    }
    Iter<T1> &operator ++(){
        ptr = ptr->next; return *this;
    }
    Node<T1> &operator *() const{
        return *ptr;
    }
    T1 &key() const{
        return ptr->key;
    }
    bool operator !=(const Iter<T1> &other){
        return ptr != other.ptr;
    }

private:
    Node<T1> *ptr;
};

#endif // ITER_H
