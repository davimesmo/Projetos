#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Onibus.hpp"
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;
Onibus::Onibus(string placa, int capMax){
    _placa = placa;
    _capMax = capMax;
    _lotAt = 0;
}
void Onibus::subir_passageiros(int quant){
    _lotAt += quant;
}
void Onibus::descer_passageiros(int quant){
    _lotAt -= quant;
}
void Onibus::transfere_passageiros(Onibus* outro, int quant){
    _lotAt -= quant;
    outro->_lotAt += quant;
}
void Onibus::imprimir_estado(){
    cout << _placa << " (" << _lotAt << "/" << _capMax << ")\n";
}