#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "aluno.hpp"
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;
bool compareByORDEMFEALODERIT( Aluno &a,  Aluno &b)
{
    return a.getNome() < b.getNome();
}
int main(){
    string entrada;
    int nota;
    vector<Aluno> alunos;
    cin >> entrada;
    while(entrada != "END"){
        string nome;
        nome = entrada;
        int matricula;
        cin >> matricula;
        cin >> nota;
        Aluno aluno(nome, matricula);
        while(nota != -1){
            aluno.appendNota(nota);
            cin >> nota;
        }
        alunos.push_back(aluno);
        cin >> entrada;
    }

    sort(alunos.begin(), alunos.end(), compareByORDEMFEALODERIT);
    for(auto alunoAtual : alunos){
        alunoAtual.imprimir();
    }
    
    return 0;
}