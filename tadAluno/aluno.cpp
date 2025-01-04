#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "aluno.hpp"
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;
void Aluno::calculaMedia(vector<int> notas){
    int soma = 0;
    for (int i = 0; i < notas.size(); i++){
        
        soma += notas[i];
    }
    double sum = soma;
    media = sum / notas.size();
}
void Aluno:: maiorMenor(vector<int> notas){
    maior = notas[0];
    menor = notas[0];
    for (int j = 1; j < notas.size(); j++){
        if(maior < notas[j]){
            maior = notas[j];
        }
        if(menor > notas[j]){
            menor = notas[j];
        }
    }
    
}