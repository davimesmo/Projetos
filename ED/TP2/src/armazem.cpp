#include "armazem.hpp"
#include <iostream>
#include <iomanip>
using namespace std;
//Construtor inicia cada seção de acordo com a quantidade de vizinhos
//Alocando um vetor de pilhas
Armazem::Armazem(int armazem, ListaEncadeada& destinos, int capacidade, int custo) : id(armazem), qtdVizinhos(destinos.getTam()), capacidade(capacidade), custo(custo){
    this->secoes = new Pilha*[qtdVizinhos];
    No* p = destinos.getHead();
    for(int i = 0; i < qtdVizinhos; i++){
        secoes[i] = new Pilha();
        this->vizinhos.insereFinal(p->getVal());
        p = p->getProx();
    }
}

Armazem::~Armazem() {
    if (secoes != nullptr) {
        for (int i = 0; i < qtdVizinhos; i++) {
            delete secoes[i];   
        }
        delete[] secoes; 
    }
}
// Armazena um pacote na pilha correspondente ao seu próximo destino
void Armazem::armazenaPacote(Pacote *pacote, double tempo) {
    int proxDestino = pacote->getProximoDestinoId();
    int indice = localizaIndiceSecao(proxDestino);
    if(indice != -1) 
        secoes[indice]->Empilha(pacote);
}

// Recupera pacotes de uma seção específica para transporte ou rearmazenamento
ResultadoSelecao Armazem::recuperaPacotes(int destino, double tempoAtual) {
   ResultadoSelecao resultado;
    // Localiza a seção do destino
    int indice = localizaIndiceSecao(destino);
    if (indice == -1 || secoes[indice]->estaVazia()) {
        return resultado;
    }

    Pilha& secaoAlvo = *(secoes[indice]);
    // Pilha auxiliar usada para inverter a ordem de desempilhamento
    Pilha aux;

    double tempoRemocao = 0;
    
    double tempoManipulacaoCumulativo = 0;
    // Primeira etapa: desempilha todos os pacotes da seção e empilha na auxiliar
    // Já calcula o tempo de remoção de cada pacote
    while (!secaoAlvo.estaVazia()) {

        Pacote* p = secaoAlvo.Desempilha();
        aux.Empilha(p);
        tempoManipulacaoCumulativo += this->custo;
        tempoRemocao = tempoAtual + tempoManipulacaoCumulativo;
        
        // Impressão da remoção
        cout << setw(7) << setfill('0') << static_cast<int>(tempoRemocao) << " pacote " << setw(3) << setfill('0') << p->getId() << " removido de " << setw(3) << setfill('0') << this->id << " na secao " << setw(3) << setfill('0') << destino << endl;
    }
    
    int transportados = 0;
    // Segunda etapa: desempilha da pilha auxiliar e decide transporte ou rearmazenamento
     while (!aux.estaVazia()) {
        Pacote* p = aux.Desempilha();

        p->atualizarEstado("removido", tempoRemocao);


        if (transportados < this->capacidade) {
            resultado.pacotesSelecionados.Empilha(p);
            cout << setw(7) << setfill('0') << static_cast<int>(tempoRemocao) << " pacote " << setw(3) << setfill('0') << p->getId() << " em transito de " << setw(3) << setfill('0') << this->id << " para " << setw(3) << setfill('0') << destino << endl;

            transportados++;
        } else {
            // Se excedeu a capacidade, reempilha na seção original
            secaoAlvo.Empilha(p);
            p->atualizarEstado("rearmazenado", tempoRemocao);

            cout << setw(7) << setfill('0') << static_cast<int>(tempoRemocao) << " pacote " << setw(3) << setfill('0') << p->getId() << " rearmazenado em " << setw(3) << setfill('0') << this->id << " na secao " << setw(3) << setfill('0') << destino << endl;

            resultado.pacotesRearmazenados.Empilha(p);
        }
    }

    resultado.tempoDeManipulacaoGasto = tempoManipulacaoCumulativo;

    return resultado;
}

// Localiza o índice da seção correspondente ao destino
int Armazem::localizaIndiceSecao(int destino) {
    No* p = vizinhos.getHead();
    for(int i = 0; i<qtdVizinhos; i++){
        if(p->getVal() == destino) return i;
        p = p->getProx();
    }
  
    return -1;
}

bool Armazem::estaVazio() {
  for (int i = 0; i < qtdVizinhos; i++) {
        if (!secoes[i]->estaVazia())
            return false;
    }
    
    return true;}



