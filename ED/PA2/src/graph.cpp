#include <iostream>
#include "graph.hpp"

using namespace std;

Grafo::Grafo(){
    int n;
    cin >> n;
    for(int i =0; i < n; i++){
        InsereVertice();
    }
}
void Grafo::InsereVertice(){
    int qtd;
    cin >> qtd;
    vertices.insereFinal(qtd);
}
int Grafo::QuantidadeVertices(){
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