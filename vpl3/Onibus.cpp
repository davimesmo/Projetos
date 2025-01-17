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
    if(_lotAt + quant > _capMax){
        cout << "ERRO : onibus lotado" << endl;
    }else{
    _lotAt += quant;
        cout << "passageiros subiram com sucesso" << endl;
    }
}
void Onibus::descer_passageiros(int quant){
    if(_lotAt - quant < 0){
        cout << "ERRO : faltam passageiros" << endl;
    }else{
    _lotAt -= quant;
        cout << "passageiros desceram com sucesso" << endl;
    }
}
void Onibus::transfere_passageiros(Onibus* outro, int quant){
    if(_lotAt < quant || outro->_lotAt + quant > outro->_capMax){
        cout << "ERRO : transferencia cancelada" << endl;
    }else{
    _lotAt -= quant;
    outro->_lotAt += quant;
    }
}
void Onibus::imprimir_estado(){
    cout << _placa << " (" << _lotAt << "/" << _capMax << ")\n";
}