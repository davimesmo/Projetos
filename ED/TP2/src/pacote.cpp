#include "pacote.hpp"
#include <string>
#include <iostream>
using namespace std;


Pacote::Pacote(int id, double tempoPostagem, int origem, int destino) : id(id), tempoPostagem(tempoPostagem), armazemOrigem(origem), armazemFinal(destino), armazemAtual(origem), estado("NAO_POSTADO"), proxDest(0), ultimaAtt(tempoPostagem){}

Pacote::~Pacote() {
}
//Construtor de cópia
Pacote::Pacote(const Pacote& outro) : id(outro.id), tempoPostagem(outro.tempoPostagem), armazemOrigem(outro.armazemOrigem),  armazemFinal(outro.armazemFinal), armazemAtual(outro.armazemAtual), estado(outro.estado), rota(outro.rota), proxDest(outro.proxDest), ultimaAtt(outro.ultimaAtt){

}
// Retorna o próximo destino na rota ou -1 se não houver mais destinos
int Pacote::getProximoDestinoId() {
  if (rota.getTam() == 0 || proxDest >= rota.getTam()) {
        return -1; 
    }
    return rota.getItem(proxDest + 1);
}

void Pacote::atualizarEstado(string estadoNovo, double tempoSimulacao) {
  this->estado = estadoNovo;
  this->ultimaAtt = tempoSimulacao;
}

void Pacote::setRota(ListaEncadeada &rota_) {
  this->rota = rota_;
  this->proxDest = 1;
}

void Pacote::avancarNaRota() {
   if (proxDest < rota.getTam()) {
        this->proxDest++;
    }
}

int Pacote::getId() {
  return id;
}

int Pacote::getArmazemAtualId() {
  return armazemAtual;
}

void Pacote::setArmazemAtual(int id) {
  this->armazemAtual = id;
}

int Pacote::getDestinoFinalId() {
  return armazemFinal;
}

double Pacote::getTempoPost() {
  return tempoPostagem;
}

double Pacote::getUltimaAtt() {
  return ultimaAtt;
}

string Pacote::getEstado() {
  return estado;
}

void Pacote::registrarEvento(string, int, double&) {
}
