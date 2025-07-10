#ifndef HEAPINT_HPP
#define HEAPINT_HPP

#include <iostream>
class HeapInt {
    private:
        int* hint;
    public:
        HeapInt();
        HeapInt(int valor);
        HeapInt(const HeapInt& outro);
        ~HeapInt();
        HeapInt& operator=(int valor);
        HeapInt& operator=(const HeapInt& outro);
        HeapInt operator+(const HeapInt& outro);
        HeapInt operator-(const HeapInt& outro);
        bool operator==(const HeapInt& outro);


        friend std::istream& operator>>(std::istream& in, HeapInt& obj);
        friend std::ostream& operator<<(std::ostream& out, const HeapInt& obj);
    };
#endif