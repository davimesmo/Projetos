#include "evento.hpp"
#include <iomanip>
#include <sstream>
#include <iostream>
// Construtor da classe Evento
using namespace std;
Evento::Evento(double tempo, int tipo, Pacote* pacote, int origem, int destino) : tempo(tempo), tipo(tipo), pacote(pacote), origem(origem), destino(destino) {
    // Constrói a chave de prioridade com uma dica do grupo da sala
    ostringstream oss;
    oss << setw(6) << setfill('0') << (int)tempo;
    if (tipo == 1) {
        oss << setw(6) << setfill('0') << (pacote ? pacote->getId() : 0);
        oss << "1";
    } else { 
        oss << setw(3) << setfill('0') << origem;
        oss << setw(3) << setfill('0') << destino;
        oss << "2";
    }
    //Converte pra long long
    chave = stoll(oss.str());
}

long long Evento::getChave() { 
    return chave; 
}
double Evento::getTempo() { 
    return tempo; 
}
int Evento::getTipo() { 
    return tipo; 
}
Pacote* Evento::getPacote() { 
    return pacote; 
}
int Evento::getOrigem() { 
    return origem; 
}
int Evento::getDestino() { 
    return destino; 
}
