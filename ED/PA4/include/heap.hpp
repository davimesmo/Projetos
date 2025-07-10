#ifndef HEAP_HPP
#define HEAP_HPP
#include "unionFind.hpp"

class Heap{
    public:
    Heap();
    ~Heap();
    //int getAncestral();
    int getNextR(int i);
    int getNextL(int i);
    void heapfy();
    void buildSub(int raiz);
    //void insere();
    Aresta removeMenor();
    bool isvazio();
    private:
    Aresta* v;
    int tam;
    void swap(Aresta*, Aresta*);
};
#endif