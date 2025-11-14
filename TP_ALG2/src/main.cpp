#include <iomanip>
#include <sstream>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm> //sort
#include "ponto.hpp"
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> parede(n);
    for(int i =0; i < n; i++){
        cin >> parede[i];
    }
    int z;
    cin >> z;
    vector<Ponto> pontos;
    for(int c = 0; c < z; c++){
        int x, y;
        cin >>  x >>  y;
        pontos.push_back(Ponto(x, y, c+1));
    }
    std::sort(pontos.begin(), pontos.end(), [](const Ponto &a, const Ponto &b) {
        if (a.x != b.x) {
            return a.x < b.x;
        }
        return a.y < b.y; 
    });
    int maiorA = 0, att=0, indice;
    for(int j = 0; j < n; j ++){
       
        if(parede[j] < att){
            att = parede[j];
        }

        if(parede[j]>maiorA || parede[j] > att){
            att++;
            indice = att-1;
            int k = j+1;
            bool testador = false;
            if(indice == 0){
                testador = true;
            }
            if(parede[j] <= maiorA)
                continue;
            while(indice){
                
                if(k >= n){
                    testador = false;
                    
                    break;
                }else if(parede[k] < indice){
                    testador = false;
                    
                    break;
                }
                testador = true;
                indice --;
                k++;
            }
            if(testador){
                if(maiorA < att){
                    maiorA = att;
                }
            }
        }
 
    }

    Triangulo t = Ponto::menorTri(pontos, 0, pontos.size() - 1);

    cout << "Parte 1: " << maiorA << endl;
    cout << "Parte 2: " << fixed << setprecision(4) << t.perimetro << " " << t.x << " " << t.y << " " << t.z << endl;
    return 0;
}
