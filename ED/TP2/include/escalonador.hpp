#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP

#include "evento.hpp"

class Escalonador{
    public:

    Escalonador(int);
    ~Escalonador();

    void insere(Evento* e);
    Evento* removeMenor();
    
    bool isVazio();
    void testaImpressaoOrdenada();
    private:
    Evento** v; 
    int tam;
    int capacidade;
    void buildSub(int i);
    void swap(Evento** a, Evento** b);
};
#endif