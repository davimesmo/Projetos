#include "escalonador.hpp"
#include <iostream>
#include <stdexcept>
#include <iomanip>
using namespace std;

Escalonador::Escalonador(int capacidade){
    this->capacidade = capacidade;
    this->tam = 0;
    v = new Evento*[capacidade];
}


Escalonador::~Escalonador() {
  delete[] v;
}
// Função auxiliar para trocar dois ponteiros de Evento no vetor
void Escalonador::swap(Evento** a, Evento** b) {
    Evento* aux = *a;
    *a = *b;
    *b = aux;
}
// Função que mantém a propriedade do min-heap a partir do índice i
void Escalonador::buildSub(int i) {
    int menor = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < tam && v[l]->getChave() < v[menor]->getChave()) {
        menor = l;
    }
    if (r < tam && v[r]->getChave() < v[menor]->getChave()) {
        menor = r;
    }
    if (menor != i) {
        swap(&v[i], &v[menor]);
        buildSub(menor);
    }
}
// Insere um novo evento no heap, ajustando para manter a propriedade de min-heap
void Escalonador::insere(Evento* e) {
    if (tam == capacidade)
        throw std::runtime_error("Escalonador cheio");

    v[tam] = e;
    int i = tam;
    tam++;

    while (i > 0 && v[i]->getChave() < v[(i - 1) / 2]->getChave()) {
        swap(&v[i], &v[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
// Remove e retorna a raiz
Evento* Escalonador::removeMenor() {
    if (isVazio())
        throw std::runtime_error("Escalonador vazio");

    Evento* raiz = v[0];
    v[0] = v[tam - 1];
    tam--;
    buildSub(0);
    return raiz;
}

bool Escalonador::isVazio() {
    return tam == 0;
}

