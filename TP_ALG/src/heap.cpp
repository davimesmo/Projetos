#include "../include/heap.hpp"
#include "../include/graph.hpp"

Heap::Heap(No* primeiro) {
    primeiro->estimativa = 0;
    fila.push_back(primeiro);
}
Heap::~Heap() {
}
void Heap::insereHeap(No *no) {
  fila.push_back(no);

  heapifyUp(fila.size()-1);
}
No* Heap::removeTopo(){
    swap(0, fila.size()-1);
    No* retorno = fila.back();
    fila.pop_back();
    heapifyDown(0);
    return retorno;
}
void Heap::heapifyUp(size_t i){
    while(i > 0){
        size_t parent = (i-1)/2;
        if(fila[i]->estimativa < fila[parent]->estimativa){
            swap(i, parent);
            i = parent;
        }else break;
        
    }
}
void Heap::heapifyDown(size_t i){
    size_t n = fila.size();
    while(true){
        size_t esquerda = 2 * i + 1;
        size_t direita = 2 * i + 2;
        size_t menor = i;
        if(esquerda < n && fila[esquerda]->estimativa < fila[menor]->estimativa)
            menor = esquerda;
        if(direita < n && fila[direita]->estimativa < fila[menor]->estimativa)
            menor = direita;
        if(menor != i){
            swap(i, menor);
            i = menor;
        }else break;
            

    }
}
void Heap::swap(size_t i, size_t j){
    No* temp = fila[i];
    fila[i] = fila[j];
    fila[j] = temp;
}
//Metodo de Debug
void Heap::imprimeHeap() {
    std::cout << "Heap (estimativas): ";
    for (auto no : fila) {
        std::cout << no->estimativa << " ";
    }
    std::cout << std::endl;
}

bool Heap::estaVazia() {
    
    return fila.empty();
}
