#include <iostream>
#include <stdexcept>
#include "listaadjacencia.hpp"
#include "listainteiros.hpp"
using namespace std;
/*

Lista de Listas da PA2, nada demais


*/
Node::Node() : prox(nullptr){
    vizinhos = new ListaEncadeada();
}
Node::~Node(){
    delete vizinhos;
}
ListaAdjacencia::ListaAdjacencia() : head(new Node()), tail(head), tamanho(0){}
ListaAdjacencia::~ListaAdjacencia(){
    limpa();
    delete head;
}
Node* ListaAdjacencia::posiciona(int pos){
    Node* p;
    int i;
    if(pos > tamanho || pos <= 0){
       throw std::out_of_range("Posição inválida em ListaAdjacencia: " + std::to_string(pos));
    }
    p = head;
    for(i = 1; i<=pos; i++){
        p = p->prox;
    }
    return p;
}




void ListaAdjacencia::insereFinal(istream& entrada, int qtd){
    Node* nova = new Node();
    int viz;
    for(int i = 0; i < qtd; i++){
        entrada >> viz;
        if(viz == 1)
        nova->vizinhos->insereFinal(i);
        
    }
    tail->prox = nova;
    tail = nova;
    tamanho++;

}


void ListaAdjacencia::limpa(){
    Node* p;
    p = head->prox;
    while(p!=NULL){
        head->prox = p->prox;
        delete p;
        p = head->prox;

    }
    tail = head;
    tamanho = 0;
}
void ListaAdjacencia::imprime(){
    Node* p;
    p = head->prox;
    while(p!=NULL){
        p->vizinhos->imprime();
        cout << endl;
        p = p->prox;
    }
}
int ListaAdjacencia::getTam(){
    return tamanho;
}
Node* ListaAdjacencia::getHead(){
    Node* prim;
    prim = head->prox;
    return prim;
}
//Metodos que nao sao importantes para essa implementação, deveria ter apagado, mas nao sabia se usaria no futuro
/*
int ListaAdjacencia::getItem(int pos){
    Node* p;
    p = posiciona(pos);
    return p->dado;
}
void ListaAdjacencia::setItem(int item, int pos){
    Node* p;
    p = posiciona(pos);
    p->dado = item;
}
*/
/*
void ListaAdjacencia::inserePosicao(int item, int pos){
    Node*p, *nova;
    p = posiciona((pos-1));
    nova = new Node();
    nova->dado = item;
    nova->prox = p->prox;
    p->prox = nova;
    tamanho++;
    if(nova->prox == NULL){
        tail = nova;
    }


}
*/