#ifndef GRAPH_HPP
#define GRAPH_HPP
#include "../include/heap.hpp"
#include <iomanip>
#include <sstream>
#include <iostream>
#include <vector>
#include <list>


struct Aresta{
    int origem;
    int destino;
    long long peso;
    int id;
    Aresta(){}
    Aresta(int destino, long long peso, int id){
        this->destino = destino;
        this->peso = peso;
        this->id = id;
    }
    Aresta(int origem, int destino, long long peso, int id){
        this->origem = origem;
        this->destino = destino;
        this->peso = peso;
        this->id = id;
    }

};


struct No{
    std::vector<Aresta> Arestas;
    long long estimativa;
    int id;
    bool visitado;
    No(){
        //atributos para Dijkstra
        this->estimativa = -1;
        this->visitado = false;
    }
    No(const No&outro){
        //Construtor de cópia
        this->Arestas = outro.Arestas;
        this->estimativa = outro.estimativa;
        this->visitado = outro.visitado;
    }
    std::vector<Aresta> getArestas(){
        return Arestas;
    }
    void AdcionaAresta(int destino, long long peso, int id){
        Aresta nova = Aresta(destino, peso, id);
        Arestas.push_back(nova);
    }
}; 

class Graph{
    public:
    No* vertices;
    int tam;
    int m;
    std::vector<Aresta> arestas;
    Graph(int n, int m);
    Graph(std::vector<Aresta> arestas, int tam);
    std::vector<int> achaPontes();
    void dfs(int u, int parent, long long &timer, std::vector<long long> &tin, std::vector<long long> &low, std::vector<bool> &vis, std::vector<int> &pontes);
    ~Graph();
    int getTam();
    long long* Dijkstra(int s);
    std::vector<Aresta> getArestas();
    void imprimeGrafo();
    void insereAresta(int primeiro, int segundo, long long peso, int id);
    
    
};
#endif