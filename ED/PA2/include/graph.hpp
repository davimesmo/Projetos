#ifndef GRAPH_HPP
#define GRAPH_HPP
#include "listaadjacencia.hpp"
/*  Você pode inserir os includes necessários para que sua classe funcione.
 * Nenhuma outra alteração neste arquivo é permitida
 */


class Grafo{
    public:
        Grafo();
        ~Grafo();

        void InsereVertice();
        void InsereAresta(int v, int w);

        int QuantidadeVertices();
        int QuantidadeArestas();

        int GrauMinimo();
        int GrauMaximo();

        void ImprimeVizinhos(int v);
        
    //private:
        ListaAdjacencia vertices;
};

#endif