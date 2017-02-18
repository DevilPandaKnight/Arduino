//
//  Array.cpp
//  tempC++
//
//  Created by Jin on 9/11/15.
//  Copyright (c) 2015 Jin. All rights reserved.
//

#ifndef __tempC____Array__
#define __tempC____Array__

#include <assert.h>
#define NULL 0
template <typename type>
class Array {
public:
    Array();
    Array(const Array<type>& other);
    ~Array();
    void pushBack(const type& value);
    void insert(const type& value);
    void insert(const type& value,unsigned long pos);
    type& get(unsigned long pos) const;
    type& remove(unsigned long pos);
    type& removeLast();
    void clear();
    unsigned long size() const;
    long find(type& value) const;
    bool empty() const;
    Array& operator=(const Array<type>& rhs);
private:
    type* memory;
    unsigned long length;
    unsigned long capacity;
    void expand();
    void shift(unsigned long pos,bool toRight);
    void swap(Array<type>& other);
};

template <typename type>
Array<type>::Array() {
    memory = NULL;
    capacity = 0;
    length = 0;
}

template <typename type>
Array<type>::~Array(){
    delete [] memory;
}

template <typename type>
Array<type>::Array(const Array<type>& other){
    memory = NULL;
    length = 0;
    capacity = 0;
    for (unsigned long i = 0; i<other.length; i++) {
        pushBack(other.get(i));
    }
}

#define copyArray() {for(unsigned long i = 0;i<length;i++)temp[i]=memory[i];}

template <typename type>
void Array<type>::expand(){
    if (memory==NULL) {
        memory = new type[1];
        capacity = 1;
        return;
    }
    capacity *= 2;
    type* temp = new type[capacity];
    assert(temp);
    
    copyArray();
    delete [] memory;
    memory = temp;
}

template <typename type>
void Array<type>::pushBack(const type &value){
    if (length >=capacity) {expand();}
    
    memory[length] = value;
    length++;
}

template <typename type>
void Array<type>::insert(const type &value){
    pushBack(value);
}

template <typename type>
void Array<type>::shift(unsigned long pos,bool toRight){
    type* temp;
    unsigned long i;
    if (toRight) {
        i = length;
        unsigned long counter = i-pos;
        while (counter--) {
            temp = &memory[--i];
            memory[i+1] = *temp;
        }
    }
    else{
        for (unsigned long i = pos; i<length; i++) {
            temp = &memory[i+1];
            memory[i] = *temp;
        }
    }
}

template <typename type>
void Array<type>::insert(const type &value, unsigned long pos){
    if (pos >= length) {pushBack(value);return;}
    if (length >= capacity) {expand();}
    
    shift(pos, true);
    memory[pos] = value;
    length++;
}

template <typename type>
type& Array<type>::get(unsigned long pos) const{
    if (pos >= length) {pos = length-1;}
    return memory[pos];
}

template <typename type>
type& Array<type>::removeLast(){
    assert(length!=0);
    length--;
    return memory[length];
}

template <typename type>
type& Array<type>::remove(unsigned long pos){
    if (pos >= length) {return removeLast();}
    type& temp = memory[pos];
    length--;
    shift(pos, false);
    return temp;
}

template <typename type>
void Array<type>::clear(){
    length = 0;
}

template <typename type>
unsigned long Array<type>::size() const{
    return length;
}

template <typename type>
long Array<type>::find(type &value) const{
    for (unsigned long i = 0; i<length; i++) {
        if (memory[i]==value) {
            return i;
        }
    }
    return -1;
}

template <typename type>
bool Array<type>::empty() const{
    return length==0;
}

template <typename type>
void Array<type>::swap(Array<type>& other){
    type* tempMem = memory;
    memory = other.memory;
    other.memory = tempMem;
    
    unsigned long len = length;
    length = other.length;
    other.length = len;
    
    unsigned long tempCap = capacity;
    capacity = other.capacity;
    other.capacity = tempCap;
}

template <typename type>
Array<type>& Array<type>::operator=(const Array<type> &rhs){
    if (&rhs != this) {
        Array temp(rhs);
        swap(temp);
    }
    return *this;
}

#endif
