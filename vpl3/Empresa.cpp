#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Empresa.hpp"
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

Empresa::Empresa() {
    totalBus = 0;
    for(int j = 0; j < 20; j++){
        vetor[j] = nullptr;
    }
}

Onibus *Empresa::adcionar_onibus(string placa, int capacidade) {
  for (int i = 0; i < totalBus; i++) {
    if (vetor[i] != nullptr && vetor[i]->_placa == placa) {
      return nullptr;
    }
  }
  vetor[totalBus] = new Onibus(placa, capacidade);
  Onibus *novo_onibus = vetor[totalBus];
  totalBus++;
  return novo_onibus;
}
Onibus* Empresa::busca_onibus(string placa){
    for(int k = 0; k<totalBus; k++){
      if(vetor[k]->_placa == placa){
        return vetor[k];
      }
    }
    return nullptr;
}
void Empresa::imprimir_estado(){
  for(int j = 0; j < totalBus; j++){
    vetor[j]->imprimir_estado();
  }
}