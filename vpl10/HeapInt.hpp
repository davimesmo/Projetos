#ifndef HEAPINT_H
#define HEAPINT_H

#include <iostream>
using namespace std;
class HeapInt{
    public:
    int* hint;
    HeapInt();
    HeapInt(int num);
    HeapInt(HeapInt& outro);
    ~HeapInt();
    HeapInt& operator = (int num);
    HeapInt& operator = (const HeapInt& outro);
    HeapInt operator + (const HeapInt& outro);
    HeapInt operator - (const HeapInt& outro);
    bool operator == (const HeapInt& outro);
    friend istream& operator >> (istream& in, const HeapInt& outro);
    friend ostream& operator << (ostream& os, const HeapInt& outro);
};

#endif