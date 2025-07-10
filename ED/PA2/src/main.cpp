#include <iostream>
#include "graph.hpp"
#include "listaadjacencia.hpp"
#include "listainteiros.hpp"
#include <string>
using namespace std;

int main(int argc, char const *argv[]){
    //criei na stack para maior eficiência e desalocamento automático
    Grafo g;
    string opcao = argv[1];
    if(opcao == "-d"){
       cout << g.vertices.getTam() << endl << g.QuantidadeArestas() << endl << g.GrauMinimo() << endl << g.GrauMaximo() << endl; 
    }
    
    if(opcao == "-n"){
        g.vertices.imprime();
    }
    if(opcao == "-k"){
        int k = g.vertices.getTam();
        Node* p = g.vertices.getHead()->getProx();
        while (p != nullptr) {
            if(p->getVizinhos()->getTam() != (k - 1)){
                cout << "0" << endl;
                break;}
            p = p->getProx();
        }
    
        cout << "1" << endl;
    }
    return 0;
}
