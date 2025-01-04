#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "aluno.hpp"
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;
bool compareByORDEMFEALODERIT(const Aluno &a, const Aluno &b)
{
    return a.nome < b.nome;
}
int main(){
    string entrada;
    int nota;
    vector<Aluno> aluno;
    cin >> entrada;
    while(entrada != "END"){
        Aluno p1;
        p1.nome = entrada;
        cin >> p1.matricula;
        cin >> nota;
        while(nota != -1){
            p1.notas.push_back(nota);
            cin >> nota;
        }
        aluno.push_back(p1);
        cin >> entrada;
    }

    sort(aluno.begin(), aluno.end(), compareByORDEMFEALODERIT);

    for (int k = 0; k < aluno.size(); k++){
        cout << aluno.at(k).matricula << " " << aluno.at(k).nome << " ";
        for (int c = 0; c < (aluno.at(k).notas.size() - 1) ; c++){
            cout << aluno.at(k).notas[c] << " ";
        }
        cout << aluno.at(k).notas[(aluno.at(k).notas.size() -1)] << endl;
        aluno.at(k).calculaMedia(aluno.at(k).notas);
        aluno.at(k).maiorMenor(aluno.at(k).notas);
        std::cout << std::fixed << std::setprecision(2) << aluno.at(k).media << " " << aluno.at(k).maior << " " << aluno.at(k).menor;
        cout << endl;
    }
    
    return 0;
}