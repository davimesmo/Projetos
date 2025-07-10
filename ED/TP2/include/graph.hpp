#ifndef GRAPH_HPP
#define GRAPH_HPP
#include "listaadjacencia.hpp"
#include "listainteiros.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <istream>
class Grafo{
    public:
        Grafo(int n, std::istream& entrada);
        ~Grafo();
        //Algoritmo de BFS para econtrar o caminho mais curto entre dois armazens e coletar a rota do pacote
        ListaEncadeada buscaLargura(int inicio, int fim);

        void InsereVertice(std::istream& entrada, int qtd);
        void reconstruirRota(int inicio, int fim, int* pred, ListaEncadeada& rota);
        int QuantidadeVertices();
        int QuantidadeArestas();
        int GrauMinimo();
        int GrauMaximo();

        ListaEncadeada getVizinhos(int id);
        No* getVizinhosDoArmazem(int id);
        void imprimeGrafo();

        
    private:
        ListaAdjacencia vertices;
};

#endif