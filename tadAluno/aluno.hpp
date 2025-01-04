#ifndef ALUNO_H
#define ALUNO_H
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;
struct Aluno{
    string nome;
    int matricula;
    vector<int> notas;
    double media;
    int maior, menor;
    void calculaMedia(vector<int> notas);
    void maiorMenor(vector<int> notas);
};

#endif