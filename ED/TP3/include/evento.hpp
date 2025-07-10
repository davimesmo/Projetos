#ifndef EVENTO_HPP
#define EVENTO_HPP


#include <string>
class Evento {

public:
  Evento(int timestamp, std::string tipo, int idPacote, std::string remetente, std::string destinatario, int armazemOrig, int armazemDest, std::string linhaOriginal);
    int getTimestamp();
    int getIdPacote();
    std::string getTipo();
    std::string getRemetente();
    std::string getDestinatario();
    std::string getLinhaCompleta();
private:
  double timestamp;
    std::string tipoEvento;
    int idPacote;
    std::string remetente;
    std::string destinatario;
    int armazemOrigem;
    int armazemDestino;
    std::string linhaOriginal;
};
#endif