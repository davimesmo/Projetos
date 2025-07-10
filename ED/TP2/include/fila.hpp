#ifndef FILA_HPP
#define FILA_HPP

#include "listainteiros.hpp"
#include <stdexcept>
class Fila{
    public:
    Fila(){}
    ~Fila(){}

    void enfileira(int item) {
        lista.insereFinal(item);
    }
    
    int desenfileira() {
        if (estaVazia()) {
            throw std::runtime_error("Fila vazia!");
        }
        int item = lista.getItem(1);
        lista.removeInicio();
        return item;
    }

    bool estaVazia(){
        return lista.getTam() == 0;
    }

    int getTamanho(){
        return lista.getTam();
    }
    private:
    ListaEncadeada lista;
};
#endif