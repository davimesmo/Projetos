#include <iostream>
#include <stdexcept>
#include "listainteiros.hpp"
using namespace std;

/*

    Lista Encadeada normal, porém com construtor de cópia e sobrecarga de operador


*/

ListaEncadeada::ListaEncadeada(){
    head = new No();
    tail = head;
    tamanho = 0;
}
ListaEncadeada::ListaEncadeada(const ListaEncadeada& outra) {
    head = new No();
    tail = head;
    tamanho = 0;

    No* p = outra.head->prox;

    while (p != nullptr) {
        insereFinal(p->valor); 
        p = p->prox;
    }
}
ListaEncadeada& ListaEncadeada::operator=(const ListaEncadeada& outra) {

    if (this == &outra) {
        return *this;
    }

    this->limpa();

    No* p = outra.head->prox; 
    while (p != nullptr) {
        this->insereFinal(p->getVal()); 
        p = p->getProx();
    }

    return *this;
}
void ListaEncadeada::removeInicio() {
    if (tamanho == 0) { 
        return; 
    }
    No* no_a_remover = head->prox; 
    head->prox = no_a_remover->prox; 
    if (no_a_remover == tail) {
        tail = head;
    }
    delete no_a_remover; 
    tamanho--;
}
ListaEncadeada::~ListaEncadeada() {
  limpa();
  delete head;
}
No* ListaEncadeada::posiciona(int pos){
    No* p;
    int i;
    if(pos > tamanho || pos <= 0){
        throw std::out_of_range("Posição inválida em ListaEncadeada: " + std::to_string(pos));
    }
    p = head;
    for(i = 1; i<=pos; i++){
        p = p->prox;
    }
    return p;
}
int ListaEncadeada::getItem(int pos){
    No* p;
    p = posiciona(pos);
    return p->valor;
}
void ListaEncadeada::setItem(int item, int pos){
    No* p;
    p = posiciona(pos);
    p->valor = item;
}
/*void ListaEncadeada::insereInicio(int item){
    No* nova = new No();
    nova->valor = item;
    nova->prox = head->prox;
    head->prox = nova;
    tamanho++;
    if(nova->prox == NULL){
        tail = nova;

    }

}
*/

void ListaEncadeada::insereFinal(int item){
    No* nova = new No();
    nova->valor = item;
    tail->prox = nova;
    tail = nova;
    tamanho++;
}
void ListaEncadeada::inserePosicao(int item, int pos){
    No*p, *nova;
    p = posiciona((pos-1));
    nova = new No();
    nova->valor = item;
    nova->prox = p->prox;
    p->prox = nova;
    tamanho++;
    if(nova->prox == NULL){
        tail = nova;
    }


}
void ListaEncadeada::limpa(){
    No* p;
    p = head->prox;
    while(p!=NULL){
        head->prox = p->prox;
        delete p;
        p = head->prox;

    }
    tail = head;
    tamanho = 0;
}
void ListaEncadeada::imprime(){
    No* p;
    p = head->prox;
    while(p!=NULL){
        cout << p->valor << " ";
        p = p->prox;
    }
}
int ListaEncadeada::getTam(){
    return tamanho;
}
bool ListaEncadeada::pesquisa(int val){
    No* p;
    p = head->prox;
    while(p!=NULL){
        if(p->valor == val){
            return true;
        }
        p = p->prox;
    }
    return false;
}
No* ListaEncadeada::getHead(){
    No *prim;
    prim = head->prox;
    return prim;
}