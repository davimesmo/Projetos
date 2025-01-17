#ifndef ALUNO_H
#define ALUNO_H
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;
class Aluno{
    private:
    string nome;
    int matricula;
    vector<int> notas;
    public:
    Aluno(string, int);
    string getNome();
    int getMatricula();
    vector<int> getNotas();
    double calculaMedia();
    int maiorNota();
    int menorNota();
    void appendNota(int nota);
    void imprimir();
};

#endif