#ifndef LISTA_ADJACENCIA_HPP
#define LISTA_ADJACENCIA_HPP
#include "listainteiros.hpp"
class Node{
    public:
    Node();
    ~Node();
    ListaEncadeada* getVizinhos(){ return vizinhos; };
    Node* getProx() { return prox; }
    private:
        ListaEncadeada *vizinhos = new ListaEncadeada();
        Node* prox;
    friend class ListaAdjacencia;

};
class ListaAdjacencia{
    public:
    ListaAdjacencia();
    ~ListaAdjacencia();
    //int getItem(int pos);
    //void setItem(int item, int pos);
    void insereFinal(int qtd);
    //void inserePosicao(int item, int pos);
    void imprime();
    void limpa();
    int getTam();
    Node* getHead();
    private:
    Node* head;
    Node* tail;
    int tamanho;
    Node* posiciona(int pos);
    friend class Grafo;
};

#endif