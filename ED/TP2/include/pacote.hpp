#include "listainteiros.hpp"
#include <string>
#ifndef PACOTE_HPP
#define PACOTE_HPP
class Pacote{
    public:
    Pacote(int id, double tempoPostagem, int origem, int destino);
    ~Pacote();

    int getProximoDestinoId();
    int getId();
    int getArmazemAtualId();
    int getDestinoFinalId();
    double getTempoPost();
    double getUltimaAtt();
    std::string getEstado();
    //Construtor de Cópia
    Pacote(const Pacote& outro);

    void atualizarEstado(std:: string, double tempoSimulacao);
    void setRota(ListaEncadeada& rota);
    void avancarNaRota();
    void setArmazemAtual(int);
    void imprime();
    void registrarEvento(std::string, int, double&);

    private:
    int id;
    double tempoPostagem;
    int armazemOrigem;
    int armazemFinal;
    int armazemAtual;         
    std::string estado;         
    ListaEncadeada rota;
    int proxDest;
    double ultimaAtt;

    friend class Pilha;
    friend class Armazem;

};

#endif