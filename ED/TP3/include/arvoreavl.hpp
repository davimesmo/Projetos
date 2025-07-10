#ifndef ARVOREAVL_HPP
#define ARVOREAVL_HPP

#include <iostream>
#include <string>
#include "listainteiros.hpp"

template <typename Key, typename Value>
class ArvoreAVL {
public:
    ArvoreAVL();
    ~ArvoreAVL();
    void inserir(Key chave, Value valor);
    Value* buscar(Key chave);
    bool vazia();
    void obterTodosValores(ListaEncadeada<Value>& lista);
    int getNumeroNos(); // NOVO MÉTODO

private:
    struct Node {
        Key chave;
        Value valor;
        Node* esquerda;
        Node* direita;
        int altura;
        Node(Key k, Value v) : chave(k), valor(v), esquerda(nullptr), direita(nullptr), altura(1) {}
    };

    Node* raiz;
    int numeroNos; // NOVO MEMBRO PARA CONTAR OS NÓS

    // Métodos auxiliares
    int getAltura(Node* no);
    int getFatorBalanceamento(Node* no);
    Node* rotacaoDireita(Node* y);
    Node* rotacaoEsquerda(Node* x);
    Node* inserir(Node* no, Key chave, Value valor);
    Value* buscar(Node* no, Key chave);
    void limpar(Node* no);
    int max(int a, int b);
    void obterTodosValores(Node* no, ListaEncadeada<Value>& lista);
};

// --- IMPLEMENTAÇÃO ---

template <typename Key, typename Value>
int ArvoreAVL<Key, Value>::max(int a, int b) {
    return (a > b) ? a : b;
}

// CORRIGIDO: Inicializa o contador de nós
template <typename Key, typename Value>
ArvoreAVL<Key, Value>::ArvoreAVL() : raiz(nullptr), numeroNos(0) {}

template <typename Key, typename Value>
ArvoreAVL<Key, Value>::~ArvoreAVL() {
    limpar(raiz);
}

template <typename Key, typename Value>
void ArvoreAVL<Key, Value>::limpar(Node* no) {
    if (no != nullptr) {
        limpar(no->esquerda);
        limpar(no->direita);
        delete no;
    }
}

template <typename Key, typename Value>
bool ArvoreAVL<Key, Value>::vazia() {
    return raiz == nullptr;
}

template <typename Key, typename Value>
int ArvoreAVL<Key, Value>::getAltura(Node* no) {
    if (no == nullptr) return 0;
    return no->altura;
}

template <typename Key, typename Value>
int ArvoreAVL<Key, Value>::getFatorBalanceamento(Node* no) {
    if (no == nullptr) return 0;
    return getAltura(no->esquerda) - getAltura(no->direita);
}

template <typename Key, typename Value>
typename ArvoreAVL<Key, Value>::Node* ArvoreAVL<Key, Value>::rotacaoDireita(Node* y) {
    Node* x = y->esquerda;
    Node* T2 = x->direita;
    x->direita = y;
    y->esquerda = T2;
    y->altura = max(getAltura(y->esquerda), getAltura(y->direita)) + 1;
    x->altura = max(getAltura(x->esquerda), getAltura(x->direita)) + 1;
    return x;
}

template <typename Key, typename Value>
typename ArvoreAVL<Key, Value>::Node* ArvoreAVL<Key, Value>::rotacaoEsquerda(Node* x) {
    Node* y = x->direita;
    Node* T2 = y->esquerda;
    y->esquerda = x;
    x->direita = T2;
    x->altura = max(getAltura(x->esquerda), getAltura(x->direita)) + 1;
    y->altura = max(getAltura(y->esquerda), getAltura(y->direita)) + 1;
    return y;
}

template <typename Key, typename Value>
void ArvoreAVL<Key, Value>::inserir(Key chave, Value valor) {
    raiz = inserir(raiz, chave, valor);
}

template <typename Key, typename Value>
typename ArvoreAVL<Key, Value>::Node* ArvoreAVL<Key, Value>::inserir(Node* no, Key chave, Value valor) {
    if (no == nullptr) {
        numeroNos++; // CORRIGIDO: Incrementa o contador ao criar um novo nó
        return new Node(chave, valor);
    }

    if (chave < no->chave)
        no->esquerda = inserir(no->esquerda, chave, valor);
    else if (chave > no->chave)
        no->direita = inserir(no->direita, chave, valor);
    else {
        no->valor = valor;
        return no;
    }

    no->altura = 1 + max(getAltura(no->esquerda), getAltura(no->direita));
    int balance = getFatorBalanceamento(no);

    if (balance > 1 && chave < no->esquerda->chave) return rotacaoDireita(no);
    if (balance < -1 && chave > no->direita->chave) return rotacaoEsquerda(no);
    if (balance > 1 && chave > no->esquerda->chave) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }
    if (balance < -1 && chave < no->direita->chave) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }
    return no;
}

template <typename Key, typename Value>
Value* ArvoreAVL<Key, Value>::buscar(Key chave) {
    return buscar(raiz, chave);
}

template <typename Key, typename Value>
Value* ArvoreAVL<Key, Value>::buscar(Node* no, Key chave) {
    if (no == nullptr) return nullptr;
    if (chave == no->chave) return &(no->valor);
    if (chave < no->chave) return buscar(no->esquerda, chave);
    else return buscar(no->direita, chave);
}

template <typename Key, typename Value>
void ArvoreAVL<Key, Value>::obterTodosValores(ListaEncadeada<Value>& lista) {
    obterTodosValores(raiz, lista);
}

template <typename Key, typename Value>
void ArvoreAVL<Key, Value>::obterTodosValores(Node* no, ListaEncadeada<Value>& lista) {
    if (no == nullptr) return;
    obterTodosValores(no->esquerda, lista);
    lista.insereFinal(no->valor);
    obterTodosValores(no->direita, lista);
}

// NOVA IMPLEMENTAÇÃO
template <typename Key, typename Value>
int ArvoreAVL<Key, Value>::getNumeroNos() {
    return numeroNos;
}

#endif // ARVOREAVL_HPP
