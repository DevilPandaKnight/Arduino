//
//  LinkList.cpp
//  LinkList
//
//  Created by Jin on 9/5/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#ifndef __JIN_LINKLIST__
#define __JIN_LINKLIST__
#include <Arduino.h>

template <typename type>
class LinkList {
public:
    LinkList();
    LinkList(const LinkList& other);
    ~LinkList();
    
    bool empty() const;
    unsigned long size() const;
    void insert(const type &value);
    void insert(const type &value,unsigned long pos);
    type& pop();
    type& pop(unsigned long pos);
    type& get(unsigned long pos) const;
    long find(type& value) const;
    
    LinkList& operator=(const LinkList& rhs);
private:
    struct cell{
        type value;
        cell* next;
        cell* prev;
    };
    unsigned long length;
    cell* root;
    cell* last;
    void init();
    void swap(LinkList<type>& other);
    cell* getCellAtIndex(unsigned long pos) const;
};

template <typename type>
void LinkList<type>::init(){
    length = 0;
    root = NULL;
    last = NULL;
}

template <typename type>
LinkList<type>::LinkList() {
    init();
}

template <typename type>
LinkList<type>::~LinkList(){
    cell* temp;
    cell* c = root;
    while (c) {
        temp = c;
        c = temp->next;
        delete temp;
    }
}


template <typename type>
LinkList<type>::LinkList(const LinkList<type>& other) {
    init();
    cell* c = other.root;
    while (c) {
        insert(c->value);
        c = c->next;
    }
}

template <typename type>
void LinkList<type>::swap(LinkList<type>& other){
    cell* tempRoot = root;
    root = other.root;
    other.root = tempRoot;
    
    cell* tempLast = last;
    last = other.last;
    other.last = tempLast;
    
    unsigned long tempLen = length;
    length = other.length;
    other.length = tempLen;
}

template <typename type>
LinkList<type>& LinkList<type>::operator=(const LinkList<type> &rhs) {
    if (this != &rhs) {
        LinkList temp(rhs);
        swap(temp);
    }
    return *this;
}

template <typename type>
typename LinkList<type>::cell* LinkList<type>::getCellAtIndex(unsigned long pos) const{
    if (pos>=length) {
        return NULL;
    }
    unsigned long mid = length/2;
    cell* c;
    if (pos<=mid) {
        c = root;
        for (unsigned long i = 0; i<pos; i++) {
            c = c->next;
        }
    }
    else{
        c = last;
        for (unsigned long i = length-1; i>pos; i--) {
            c=c->prev;
        }
    }
    return c;
}

template <typename type>
void LinkList<type>::insert(const type &value) {
    cell* temp = new cell;
    temp->next = NULL;
    temp->value = value;
    
    if (length == 0) {
        root = temp;
        temp->prev = NULL;
    }
    if (last) {
        last->next = temp;
        temp->prev = last;
    }
    last = temp;
    
    length++;
}

template <typename type>
void LinkList<type>::insert(const type &value,unsigned long pos) {
    cell* indexCell = getCellAtIndex(pos);
    if (!indexCell) {insert(value);return;}
    cell* temp = new cell;
    temp->value = value;

    temp->next = indexCell;
    temp->prev = indexCell->prev;
    if (indexCell->prev) {
        indexCell->prev->next = temp;
    }
    else{
        root = temp;
    }
    indexCell->prev = temp;
    
    length++;
}

template <typename type>
type& LinkList<type>::pop() {
    if(length==0){Serial.println("LinkList Index Error.");type a;return a;};;
    if (root == last) {
        root = NULL;
    }
    cell* c = last;
    last = c->prev;
    if (c->prev) {
        c->prev->next = NULL;
    }
    length--;
    type& temp = c->value;
    delete c;
    return temp;
}

template <typename type>
type& LinkList<type>::pop(unsigned long pos) {
    if(pos>=length){Serial.println("LinkList Index Error.");type a;return a;};;
    cell* indexCell = getCellAtIndex(pos);
    if (indexCell->next) {
        indexCell->next->prev = indexCell->prev;
    }
    
    if (indexCell->prev) {
        indexCell->prev->next = indexCell->next;
    }
    
    if (indexCell == root) {
        root = indexCell->next;
    }
    
    if (indexCell == last) {
        last = indexCell->prev;
    }
    
    length--;
    type& temp = indexCell->value;
    delete indexCell;
    return temp;
}

template <typename type>
bool LinkList<type>::empty() const{
    return length==0;
}

template <typename type>
unsigned long LinkList<type>::size() const{
    return length;
}

template <typename type>
type& LinkList<type>::get(unsigned long pos) const{
    if(pos>=length) {Serial.println("LinkList Index Error.");type a;return a;};
    cell* indexCell = getCellAtIndex(pos);
    return indexCell->value;
}

template <typename type>
long LinkList<type>::find(type &value) const{
    long index = 0;
    cell* c = root;
    while (c) {
        if (c->value == value) {
            return index;
        }
        c = c->next;
        index++;
    }
    return -1;
}



#endif
