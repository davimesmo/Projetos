#include <iostream>
#include "Lista.hpp"
using namespace std;

Node::Node() : dado(0), prox(NULL){}
Node::~Node(){
    delete vizinhos;
}
Lista::Lista() : head(new Node()), tail(head), tamanho(0){}
Lista::~Lista(){
    limpa();
    delete head;
}
Node* Lista::posiciona(int pos){
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
int Lista::getItem(int pos){
    Node* p;
    p = posiciona(pos);
    return p->dado;
}
void Lista::setItem(int item, int pos){
    Node* p;
    p = posiciona(pos);
    p->dado = item;
}
void Lista::insereInicio(int item){
    Node* nova = new Node();
    nova->dado = item;
    nova->prox = head->prox;
    head->prox = nova;
    tamanho++;
    if(nova->prox == NULL){
        tail = nova;

    }

}
void Lista::insereFinal(int item){
    Node* nova = new Node();
    nova->dado = item;
    tail->prox = nova;
    tail = nova;
    tamanho++;
}
void Lista::inserePosicao(int item, int pos){
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
void Lista::limpa(){
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
void Lista::imprime(){
    Node* p;
    p = head->prox;
    while(p!=NULL){
        cout << p->dado << endl;
        p = p->prox;
    }
}
