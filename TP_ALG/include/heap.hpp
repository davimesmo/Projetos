#include <iomanip>
#include <sstream>
#include <iostream>
#include <vector>
#ifndef HEAP_HPP
#define HEAP_HPP
struct No; 
class Heap{
    public:
    Heap(No* primeiro);
    ~Heap();
    void insereHeap(No* no);
    No* removeTopo();
    
    void imprimeHeap();
    bool estaVazia();
    private:
    std::vector<No*>fila;
    void heapifyUp(size_t i);
    void heapifyDown(size_t i);
    void swap(size_t, size_t);
};

#endif