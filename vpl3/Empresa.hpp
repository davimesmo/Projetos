#ifndef EMPRESA_H
#define EMPRESA_H
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "Onibus.hpp"
using namespace std;
struct Empresa{
    int totalBus;
    Onibus* vetor[20];
    Empresa();
    Onibus* adcionar_onibus(string placa, int capMax);
    Onibus* busca_onibus(string placa);
    void imprimir_estado();
};
#endif