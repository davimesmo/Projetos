#ifndef ONIBUS_H
#define ONIBUS_H
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;
struct Onibus{
    string _placa;
    int _capMax, _lotAt;
    Onibus(string, int);
    void subir_passageiros(int);
    void descer_passageiros(int);
    void transfere_passageiros( Onibus*, int);
    void imprimir_estado();
};
#endif