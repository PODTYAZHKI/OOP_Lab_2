#include "set.h"

template<typename T1>
Set<T1>::Set()
{
    data = new Node<T1> * [60];
    for (int i = 0; i < 60; i++)
        data[i] = nullptr;
    count = 0;
}

template<typename T1>
Set<T1>::Set(QString name)
{
    this->name = name;
    data = new Node<T1> * [60];
    for (int i = 0; i < 60; i++)
        data[i] = nullptr;
    count = 0;
}

template<typename T1>
Set<T1>::Set(const Set &other)
{
    data = new Node<T1> * [60];
    for (int i = 0; i < 60; i++){
        if (other.data[i])
            data[i] = new Node<T1>( *other.data[i]);
        else
            data[i] = nullptr;
    }
    count = other.count;
    name = other.name;
}

template<typename T1>
void Set<T1>::insert(T1 key)
{
    int pos = hash(key);
    if (!data[pos])
        data[pos] = new Node<T1>(key);
    else{
        Node<T1> *curr = data[pos];
        if (data[pos]->key == key) return;
        while (curr->next && pos == hash(curr->next->key)){
            if (curr->key == key) return;
            curr = curr->next;
        }
        Node<T1> *tmp = new Node<T1>(key);
        tmp->next = curr->next;
        curr->next = tmp;
        count++;
        return;
    }

    if (count++){
        int j = pos; int i = pos;
        while(j >= 0 && !data[ --j]);
        while(i <= 59 && !data[ ++i]);
        if (j >= 0){
            Node<T1> *curr = data[j];
            while (curr->next && j == hash(curr->next->key)) curr = curr->next;
            curr->next = data[pos];
        }
        if (i <= 59){
            Node<T1> *curr = data[pos];
            while (curr->next && pos == hash(curr->next->key)) curr = curr->next;
            curr->next = data[i];
        }
    }
}

template<typename T1>
bool Set<T1>::contains(T1 key) const
{
    int pos = hash(key);
    if (data[pos]){
        Node<T1> *curr = data[pos];
        while (curr && pos == hash(curr->key)){
            if (curr->key == key) return true;
            curr = curr->next;
        }
    }
    return false;
}

template<typename T1>
void Set<T1>::remove(T1 key)
{
    if (!contains(key)) return;
    int pos = hash(key);
    Node<T1> *curr = data[pos];
    while (curr->key != key) curr = curr->next;
    if (!begin().getPtr()->next){
        clear();
        return;
    }
    else if (!curr->next){
        if (data[pos] == curr){
            int j = pos;
            while (j >= 0 && !data[--j]);
            if (j >= 0){
                Node<T1> *curr1 = data[j];
                while (j == hash(curr1->next->key)) curr1 = curr1->next;
                curr1->next = nullptr;
            }
        }
        else{
            Node<T1> *curr1 = data[pos];
            while (curr1->next != curr) curr1 = curr1->next;
            curr1->next = nullptr;
        }
        delete curr;
    }
    else if (pos != hash(curr->next->key)){
        int j = pos;
        while (j >= 0 && !data[--j]);
        if (j >= 0){
            Node<T1> *curr1 = data[j];
            while (j == hash(curr1->next->key)) curr1 = curr1->next;
            curr1->next = data[pos]->next;
        }
        delete data[pos];
        data[pos] = nullptr;
    }
    else if (curr->key == data[pos]->key){
        curr = curr->next;
        delete data[pos];
        data[pos] = curr;
        int j = pos;
        while (j >= 0 && !data[--j]);
        if (j >= 0){
            Node<T1> *curr1 = data[j];
            while (j == hash(curr1->next->key)) curr1 = curr1->next;
            curr1->next = curr;
        }
    }
    else{
        Node<T1> *curr1 = data[pos];
        while (curr1->next != curr) curr1 = curr1->next;
        curr1->next = curr->next;
        delete curr;
    }
    count--;
}

template<typename T1>
void Set<T1>::clear()
{
    Iter<T1> it = begin();
    while (it != end()){
        int pos = hash(it.key());
        Node<T1> *nxt = it.getPtr()->next;
        delete it.getPtr();
        data[pos] = nullptr;
        it.getPtr() = nxt;
    }
    count = 0;
}

template<typename T1>
Iter<T1> Set<T1>::begin() const
{
    if (count){
        int i = 0;
        while(!data[i++ ]);
        return Iter<T1>(data[i-1]);
    }
    else
        return Iter<T1>(nullptr);
}

template<typename T1>
bool Set<T1>::operator == (const Set &other)
{
    if (count != other.count) return false;
    for (Iter<T1> it1 = begin(), it2 = other.begin();
         it1 != end() && it2 != end(); ++it1, ++it2)
            if (*it1 != *it2)
                return false;
    return true;
}

template<typename T1>
bool Set<T1>::operator !=(const Set &other)
{
    return !(*this == other);
}

template<typename T1>
Set<T1> Set<T1>::operator &&(const Set &other)
{
    Set<T1> *nset = new Set<T1>;
    for (Iter<T1> it1 = begin(); it1 != end(); ++it1){
        for (Iter<T1> it2 = other.begin(); it2 != other.end(); ++it2){
            if (*it1 == *it2){
                nset->insert(it1.key());
            }
        }
    }
    return *nset;
}


template<typename T1>
int Set<T1>::hash(T1 key) const
{
    int result = 14;
    for (int i = 0; i < key.size(); i++){
        result += (result*21) ^ (key.at(i).toLatin1()*8);
    }
    result = result % 60;
    return abs(result);
}

template class Set<QString>;
