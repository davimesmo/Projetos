#include <iostream>
#include "listaadjacencia.hpp"
#include "listainteiros.hpp"
using namespace std;

Node::Node() : prox(NULL){}
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
        throw "ERRO: Posição Inválida";
    }
    p = head;
    for(i = 1; i<=pos; i++){
        p = p->prox;
    }
    return p;
}


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

void ListaAdjacencia::insereFinal(int qtd){
    Node* nova = new Node();
    int viz;
    for(int i = 0; i < qtd; i++){
        cin >> viz;
        nova->vizinhos->insereFinal(viz);
    }
    tail->prox = nova;
    tail = nova;
    tamanho++;
}
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