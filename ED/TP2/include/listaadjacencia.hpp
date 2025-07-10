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
        ListaEncadeada *vizinhos;
        Node* prox;
    friend class ListaAdjacencia;

};
class ListaAdjacencia{
    public:
    ListaAdjacencia();
    ~ListaAdjacencia();



    
    void insereFinal(std::istream& entrada, int qtd);
    
    void imprime();
    void limpa();
    int getTam();
    Node* getHead();
    //Metodos importantes para Lista de adjacencia e encadeada, mas que nao sao importantes nesse caso
    //void inserePosicao(int item, int pos);
    //int getItem(int pos);
    //void setItem(int item, int pos);
    private:
    Node* head;
    Node* tail;
    int tamanho;
    Node* posiciona(int pos);
    friend class Grafo;
};

#endif