#include <iostream>
#include <ostream>
#include "HeapInt.hpp"

HeapInt::HeapInt(){
    hint = new int(0);
}
HeapInt::HeapInt(int num){
    hint = new int(num);
}
HeapInt::HeapInt(HeapInt& outro){
    hint = new int(*(outro.hint));
}
HeapInt& HeapInt::operator = (int num){
    *hint = num;
    return *this;
}
HeapInt& HeapInt::operator = (const HeapInt& outro){
    *hint = *(outro.hint);
    return *this;
}
HeapInt HeapInt::operator + (const HeapInt& outro){
    return HeapInt(*hint + *(outro.hint));
}
HeapInt HeapInt::operator - (const HeapInt& outro){
    return HeapInt(*hint - *(outro.hint));
}
bool HeapInt::operator == (const HeapInt& outro){
    return (*hint == *(outro.hint));
}
HeapInt::~HeapInt(){
    delete hint;
}
istream& operator >> (istream& in, HeapInt& outro){
        in >> *(outro.hint);
        return in;
    }
ostream& operator << (ostream& os, const HeapInt& outro){
        os << *(outro.hint);
       return os;
    }