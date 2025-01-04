#ifndef EMPRESA_H
#define EMPRESA_H
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;
struct Empresa{
    int totalBus;
    Onibus* vetor[20];
    Empresa(totalBus = 0);
    Onibus* adcionar_onibus();
    Onibus* busca_onibus();
    void imprimir_estado();
};
#endif