#ifndef EVENTO_HPP
#define EVENTO_HPP

#include "pacote.hpp"

class Evento {

public:
  Evento(double tempo, int tipo, Pacote *pacote, int origem, int destino);

  long long getChave();
  double getTempo();
  int getTipo();
  Pacote *getPacote();
  int getOrigem();
  int getDestino();
  
  void imprimeDetalhes() const;
private:
  long long chave;
  double tempo;
  int tipo;
  Pacote *pacote;
  int origem;
  int destino;
};
#endif