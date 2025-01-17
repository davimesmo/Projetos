#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "aluno.hpp"
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;
Aluno::Aluno(string nome, int matricula) : nome(nome), matricula(matricula){}
string Aluno:: getNome(){
    return nome;
}
int Aluno::getMatricula(){
    return matricula;
}
vector<int> Aluno::getNotas(){
    return notas;
}
void Aluno::appendNota(int nota){
    if(nota != -1){
        notas.push_back(nota);
    }
}
double Aluno::calculaMedia(){
    double soma = 0.0;
    for(int i : notas){
         soma += i;
    }
    return soma / notas.size();

}
int Aluno::maiorNota(){
    return *max_element(notas.begin(), notas.end());
}
int Aluno::menorNota(){
    return *min_element(notas.begin(), notas.end());
}
void Aluno::imprimir(){
    cout << matricula << " " << nome << " ";
    for(int i = 0; i < notas.size(); i++){
        if(i != notas.size() - 1){
            cout << notas[i] << " ";
        }else{
            cout << notas[i] << endl;
        }
    }
    cout << fixed << setprecision(2) << calculaMedia() << " " << maiorNota() << " " << menorNota() << endl;
}