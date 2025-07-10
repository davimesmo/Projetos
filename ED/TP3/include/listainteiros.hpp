#ifndef LISTA_ENCADEADA_HPP
#define LISTA_ENCADEADA_HPP

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;
template <typename T>
class ListaEncadeada {
public:
    ListaEncadeada();
    ~ListaEncadeada();
    ListaEncadeada(const ListaEncadeada<T>& outra);
    ListaEncadeada<T>& operator=(const ListaEncadeada<T>& outra);

    void insereFinal(T valor);
    void removeInicio();
    bool pesquisa(T valor);
    void limpa();
    T getItem(int pos);
    void setItem(T valor, int pos);
    int getTam();
    void imprime();
    bool estaVazia();
private:
    struct No {
        T valor;
        No* prox;
        No(T v) : valor(v), prox(nullptr) {}
        No() : prox(nullptr) {}
    };
    No* head;
    No* tail;
    int tamanho;
    No* posiciona(int pos);
};


template <typename T>
ListaEncadeada<T>::ListaEncadeada() {
    head = new No();
    tail = head;
    tamanho = 0;
}

template <typename T>
ListaEncadeada<T>::~ListaEncadeada() {
    limpa();
    delete head;
}

template <typename T>
void ListaEncadeada<T>::limpa() {
    No* p = head->prox;
    while (p != nullptr) {
        head->prox = p->prox;
        delete p;
        p = head->prox;
    }
    tail = head;
    tamanho = 0;
}

template <typename T>
ListaEncadeada<T>::ListaEncadeada(const ListaEncadeada<T>& outra) {
    head = new No();
    tail = head;
    tamanho = 0;
    No* p = outra.head->prox;
    while (p != nullptr) {
        this->insereFinal(p->valor);
        p = p->prox;
    }
}

template <typename T>
ListaEncadeada<T>& ListaEncadeada<T>::operator=(const ListaEncadeada<T>& outra) {
    if (this == &outra) {
        return *this;
    }
    this->limpa();
    No* p = outra.head->prox;
    while (p != nullptr) {
        this->insereFinal(p->valor);
        p = p->prox;
    }
    return *this;
}

template <typename T>
void ListaEncadeada<T>::insereFinal(T valor) {
    No* novo = new No(valor);
    tail->prox = novo;
    tail = novo;
    tamanho++;
}

template <typename T>
void ListaEncadeada<T>::removeInicio() {
    if (estaVazia()) {
        return;
    }
    No* no_a_remover = head->prox;
    head->prox = no_a_remover->prox;
    if (tail == no_a_remover) {
        tail = head;
    }
    delete no_a_remover;
    tamanho--;
}

template <typename T>
typename ListaEncadeada<T>::No* ListaEncadeada<T>::posiciona(int pos) {
    if (pos <= 0 || pos > tamanho) {
        throw out_of_range("Posicao invalida" + to_string(pos));
    }
    No* p = head;
    for (int i = 0; i < pos; i++) {
        p = p->prox;
    }
    return p;
}

template <typename T>
T ListaEncadeada<T>::getItem(int pos){
    No* p = posiciona(pos);
    return p->valor;
}

template <typename T>
void ListaEncadeada<T>::setItem(T valor, int pos) {
    No* p = posiciona(pos);
    p->valor = valor;
}

template <typename T>
bool ListaEncadeada<T>::pesquisa(T valor){
    No* p = head->prox;
    while (p != nullptr) {
        if (p->valor == valor) {
            return true;
        }
        p = p->prox;
    }
    return false;
}

template <typename T>
bool ListaEncadeada<T>::estaVazia(){
    return tamanho == 0;
}

template <typename T>
int ListaEncadeada<T>::getTam(){
    return tamanho;
}

template <typename T>
void ListaEncadeada<T>::imprime(){
    No* p = head->prox;
    while (p != nullptr) {
        cout << p->valor << " ";
        p = p->prox;
    }
}

#endif