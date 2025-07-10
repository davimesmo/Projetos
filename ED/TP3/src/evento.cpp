#include "evento.hpp"
#include <iomanip>
#include <sstream>
#include <iostream>

using namespace std;

#include "evento.hpp"

Evento::Evento(int timestamp, string tipo, int idPacote, string remetente, string destinatario, int armazemOrig, int armazemDest, string linhaOriginal) : timestamp(timestamp), tipoEvento(tipo), idPacote(idPacote), remetente(remetente), destinatario(destinatario), armazemOrigem(armazemOrig), armazemDestino(armazemDest), linhaOriginal(linhaOriginal) {}


int Evento::getTimestamp() {
    return timestamp;
}

int Evento::getIdPacote() {
    return idPacote;
}

string Evento::getTipo() {
    return tipoEvento;
}

string Evento::getRemetente() {
    return remetente;
}

string Evento::getDestinatario() {
    return destinatario;
}

string Evento::getLinhaCompleta() {
    return linhaOriginal;
}

