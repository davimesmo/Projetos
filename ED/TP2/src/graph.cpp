#include <iostream>
#include "graph.hpp"
#include "fila.hpp"
using namespace std;

Grafo::Grafo(int n, istream& entrada){

    for(int i = 0; i < n; i++){

        InsereVertice(entrada, n);

    }
    
}
void Grafo::InsereVertice(istream& entrada, int qtd){

    vertices.insereFinal(entrada, qtd);

    
}
// Função auxiliar para reconstruir a rota encontrada na busca em largura, recursivamente como foi sugerido pelo Meira
void Grafo::reconstruirRota(int u, int v, int *pred, ListaEncadeada &rota) {
    if (u == v) {
    } else if (pred[v] == -1) {
    } else {
        reconstruirRota(u, pred[v], pred, rota);
        rota.insereFinal(v);
    }
}
int Grafo::QuantidadeVertices() {
  return vertices.getTam();
}
int Grafo::QuantidadeArestas(){
    Node* p = vertices.getHead();
    No* q;
    ListaEncadeada percorridos;
    int arestas = 0;
    int cont = 0;
    while(p!=NULL){
        q = p->getVizinhos()->getHead();
        while(q!=NULL){
            
            if(!percorridos.pesquisa(q->getVal()))
                arestas++;
            q = q->getProx();
        }
        percorridos.insereFinal(cont);
        cont++;
        p = p->getProx();
    }
    return arestas;
}
int Grafo::GrauMinimo(){
    int min;
    Node* p;
    p = vertices.getHead();
    min = p->getVizinhos()->getTam();
    while(p!=NULL){
        if(p->getVizinhos()->getTam() < min)
            min = p->getVizinhos()->getTam();
        p = p->getProx();
    }
    return min;
}
int Grafo::GrauMaximo(){
    int max;
    Node* p;
    p = vertices.getHead();
    max = p->getVizinhos()->getTam();
    while(p!=NULL){
        if(p->getVizinhos()->getTam() > max)
            max = p->getVizinhos()->getTam();
        p = p->getProx();
    }
    return max;
}


Grafo::~Grafo(){
    vertices.limpa();
}
// Busca em largura: encontra o caminho mais curto entre dois vértices
ListaEncadeada Grafo::buscaLargura(int inicio, int fim) {
    int num = QuantidadeVertices();
    int* pred = new int[num];
    bool*   visitado = new bool[num];

    for(int i = 0; i<num; i++){
        pred[i] = -1;
        visitado[i] = false;
    }
    Fila fila;
    visitado[inicio] = true;
    fila.enfileira(inicio);
    while(!fila.estaVazia()){
        int u = fila.desenfileira();
        if(u == fim) break;
        Node* vertice = vertices.posiciona(u+1);
        ListaEncadeada& vizinhos = *(vertice->getVizinhos());
        No* vizinhoAtual = vizinhos.getHead();
        while(vizinhoAtual != nullptr){
            int v = vizinhoAtual->getVal();
            if(!visitado[v]){
                visitado[v] = true;
                pred[v] = u;
                fila.enfileira(v);

            }
            vizinhoAtual = vizinhoAtual->getProx();
        }

    }
    ListaEncadeada rota;
    if(pred[fim] != -1 || inicio == fim){
        rota.insereFinal(inicio);
        reconstruirRota(inicio, fim, pred, rota);
    }
    delete[] pred;
    delete[] visitado;
    return rota;
}

// Retorna a lista de vizinhos do vertice
ListaEncadeada Grafo::getVizinhos(int id) {
    Node* node = vertices.posiciona(id + 1);
    return *(node->getVizinhos()); 
}

// Retorna o ponteiro para o primeiro vizinho de um vértice
No* Grafo::getVizinhosDoArmazem(int id) {
    Node* node = vertices.posiciona(id+1);
    return node->getVizinhos()->getHead(); 
}