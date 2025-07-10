#include <iostream>
#include <ostream>
#include "HeapInt.hpp"
using namespace std;
HeapInt::HeapInt(){
    hint = new int(0);
}
HeapInt::HeapInt(int num){
    hint = new int(num);
}
HeapInt::HeapInt(const HeapInt& outro){
    hint = new int(*(outro.hint));
}
HeapInt& HeapInt::operator=(int num){
    *hint = num;
    return *this;
}
HeapInt& HeapInt::operator=(const HeapInt& outro){
    *hint = *(outro.hint);
    return *this;
}
HeapInt HeapInt::operator+(const HeapInt& outro){
    int resultado = *hint + *(outro.hint);
    return HeapInt(resultado);
}
HeapInt HeapInt::operator-(const HeapInt& outro){
    int resultado = *hint - *(outro.hint);
    return HeapInt(resultado);
}
bool HeapInt::operator==(const HeapInt& outro){
    return (*hint == *(outro.hint));
}
HeapInt::~HeapInt(){
    delete hint;
}
istream& operator>>(istream& in, HeapInt& outro){
        int entrada;
        in >> entrada; 
        *(outro.hint) = entrada;
        return in;
    }
ostream& operator<<(ostream& os, const HeapInt& outro){
        os << *(outro.hint);
       return os;
    }