#include "pilha.hpp"
#include <stdexcept>
#include <iostream>

using namespace std;

/*
Pilha de apontadores para pacote, implementação como a do slide
*/


Pilha::Pilha() : topo(nullptr), tam(0){}

Pilha::~Pilha(){
    Limpa();
}

void Pilha::Empilha(Pacote* p){
    NoPilha* No = new NoPilha(p);
    No->prox = topo;
    topo = No;
    tam++;
}

Pacote* Pilha::Desempilha(){
    if(topo == nullptr){
        throw runtime_error("Armazém Vazio");
    }
    NoPilha* no = topo;
    Pacote* removido = topo->dados;
    topo = topo->prox;
    delete no;
    tam --;
    return removido;    
}

void Pilha::Limpa(){
    while(topo != nullptr){
        Desempilha();
    }
}

bool Pilha::estaVazia(){
    return tam==0;
}
int Pilha::getTamanho() {return tam;}
