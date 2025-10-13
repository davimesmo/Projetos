#include "../include/graph.hpp"
#include <iomanip>
#include <sstream>
#include <iostream>
#include <vector>
#include <list>
using namespace std;
Graph::Graph(int n, int m) {
    this->tam = n;
    vertices = new No[n + 1];
    this->m = m;
    int vertice, segundo;
    long long peso;
    for(int i = 0; i< m; i++){
        cin >> vertice >> segundo >> peso;
        insereAresta(vertice, segundo, peso, (i+1));
    }
}

Graph::Graph(std::vector<Aresta> arestas, int tam) {
    vertices = new No[tam +1]; 
    this->tam = tam;
    for(auto i : arestas){
        insereAresta(i.origem, i.destino, i.peso, i.id);
    }
}
//Algoritmo de Tarjan para achar Bridges
std::vector<int> Graph::achaPontes() {
    vector<int> pontes;
    vector<bool> vis;
    vector<long long> tin;
    vector<long long> low;
    long long timer = 1;
    for(int i = 0; i<=tam; i++){
        tin.push_back(-1);
        low.push_back(-1);
        vis.push_back(false);
    }
    dfs(1, -1, timer, tin, low, vis, pontes);
    return pontes;
}
//Dfs com timer que pega o timer menor do vizinho e compara, Tarjan
void Graph::dfs(int u, int parent, long long &timer, std::vector<long long> &tin, std::vector<long long> &low, std::vector<bool> &vis, std::vector<int> &pontes) {
    vis[u] = true;
    tin[u] = low[u] = ++timer;
    for(auto i: vertices[u].Arestas){
        int v = i.destino;
        if(v == parent)
            continue;
        if(!vis[v]){
            dfs(v, u, timer, tin, low, vis, pontes);
            if(low[u] > low[v])
                low[u] = low[v];
            if(low[v] > tin[u])
                pontes.push_back(i.id);
        }else{
            if(low[u] > tin[v])
                low[u] = tin[v];
        }
    }
}

Graph::~Graph() {
    delete[] vertices;
}

int Graph::getTam() {
  return tam;
}
//Dijkstra clássico com Min-Heap para fila de prioridade
long long* Graph::Dijkstra(int s) {
    long long* dist = new long long int[tam+1];
    for(int i =0; i<=tam; i++){
        dist[i] = -1;
        //Provavelmente não é o lugar correto para iniciar isso, mas queria otimizar
        //Tava tendo problemas com o vetor de distancias aí criei o id para "conversão" mais fácil
        vertices[i].id = i;
        
        vertices[i].estimativa = -1;
        vertices[i].visitado = false;
    }
    dist[s] = 0;
    vertices[s].estimativa = 0;
    Heap fila(&vertices[s]);
    while(!fila.estaVazia()){
        No* u = fila.removeTopo();
        if(!u->visitado){
            u->visitado = true;
            dist[u->id] = u->estimativa;
            for (auto aresta : vertices[u->id].Arestas) {
            int v_id = aresta.destino;
            long long peso = aresta.peso;
            if (dist[v_id] == -1 || dist[u->id] + peso < dist[v_id]) {
                dist[v_id] = dist[u->id] + peso;
                vertices[v_id].estimativa = dist[v_id];
                fila.insereHeap(&vertices[v_id]);
            }
        }
        }
    }
    return dist;
}

//Metodo de Debug
void Graph::imprimeGrafo() {
    for(int i=1; i < 6; i++){
        cout << i << " ";
        vector<Aresta> result = vertices[i].getArestas();

        for (auto it : result) {
            cout << "("<<it.destino <<", " <<it.peso << ")";
        }
        cout << endl;
    }
}

void Graph::insereAresta(int primeiro, int segundo, long long peso, int id) {
  vertices[primeiro].AdcionaAresta(segundo, peso, id);
  vertices[segundo].AdcionaAresta(primeiro, peso, id);

    Aresta aresta(primeiro, segundo, peso, id);
    arestas.push_back(aresta);
  
  
}
vector<Aresta> Graph::getArestas(){
    return arestas;
}