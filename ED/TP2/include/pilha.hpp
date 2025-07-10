#ifndef PILHA_HPP
#define PILHA_HPP
#include "pacote.hpp"
struct NoPilha{
    Pacote* dados;
    NoPilha* prox;

    NoPilha(Pacote* p) : dados(p), prox(nullptr) {}
};
class Pilha{
    public:
    Pilha();
    ~Pilha();

    void Empilha(Pacote* item);
    Pacote* Desempilha();
    void Limpa();
    bool estaVazia();
    int getTamanho();
    void imprime();

    private:
        NoPilha* topo;
        int tam; 
};

#endif