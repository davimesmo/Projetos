#ifndef ARMAZEM_HPP
#define ARMAZEM_HPP

#include "pilha.hpp"
#include "pacote.hpp"
#include "listainteiros.hpp"
// Struct utilizada para o retorno dos parametros para a main
struct ResultadoSelecao {
    Pilha pacotesSelecionados;    
    Pilha pacotesRearmazenados;
    double tempoDeManipulacaoGasto;
    ResultadoSelecao() : tempoDeManipulacaoGasto(0){}
};


class Armazem{
    public:
    //Construtor e Destrutor
    Armazem(int armazem, ListaEncadeada& destinos, int, int);
    ~Armazem();
    //Metodos Principais
    void armazenaPacote(Pacote* pacote, double tempo);
    ResultadoSelecao recuperaPacotes(int id_armazem_destino, double tempo_atual);
    int localizaIndiceSecao(int destino);
    //Metodos Auxiliares
    bool estaVazio();
    void imprimeInfo();

    private:
    ListaEncadeada vizinhos;
    int id;
    int qtdVizinhos;
    Pilha** secoes;
    int capacidade;
    int custo;
    
};

#endif