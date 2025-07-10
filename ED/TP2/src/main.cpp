#include "armazem.hpp"
#include "escalonador.hpp"
#include "evento.hpp"
#include "graph.hpp"
#include "pacote.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <chrono>
using namespace std;
// Função auxiliar para imprimir o tempo no formato com zeros à esquerda
void imprimeTempo(double tempo) {
  cout << fixed << setprecision(0) << setw(7) << setfill('0') << tempo;
}

int main(int argc, char *argv[]) {

  int capacidadeTransporte, latenciaTransporte, intervaloTransportes, custoRemocao;
  int numeroArmazens, numeroPacotes;
  ifstream entrada(argv[1]);
  if (!entrada.is_open()) {
    cerr << "Erro ao abrir os arquivos." << endl;
    return 1;
  }
   string nome_csv = "resultados_tp2.csv";
    if (argc > 2) { // Permite especificar um nome de arquivo CSV diferente
        nome_csv = argv[2];
    }
    
    // Abre o arquivo em modo 'append' (adicionar ao final)
    ofstream arquivo_csv(nome_csv, ios::app);
    if (!arquivo_csv.is_open()) {
        cerr << "Erro ao abrir o arquivo CSV para escrita!" << endl;
        return 1;
    }

    // Verifica se o arquivo está vazio para escrever o cabeçalho apenas uma vez
    arquivo_csv.seekp(0, std::ios::end);
    if (arquivo_csv.tellp() == 0) {
        arquivo_csv << "NumArmazens,NumPacotes,Capacidade,Latencia,Intervalo,CustoRemocao,"
                    << "TempoExecucao_ms,TempoSimulacao_total,TotalRearmazenamentos\n";
    }
  entrada >> capacidadeTransporte >> latenciaTransporte >> intervaloTransportes >> custoRemocao >> numeroArmazens;
  //Lê o grafo
  
  Grafo grafo(numeroArmazens, entrada);

  //Constroi os armazens
  Armazem **armazens = new Armazem *[numeroArmazens];
  for (int i = 0; i < numeroArmazens; i++) {
    ListaEncadeada vizinhos = grafo.getVizinhos(i);
    armazens[i] = new Armazem(i, vizinhos, capacidadeTransporte, custoRemocao);
  }
    auto inicio_execucao = chrono::high_resolution_clock::now();
  int num_arestas = grafo.QuantidadeArestas();
  entrada >> numeroPacotes;

  //Inicia escalonador com tamanho máximo + guarda
  int tamanhoEscalonador = numeroPacotes + (2*num_arestas) + 20;
  Escalonador escalonador(tamanhoEscalonador);

 //Inicia os pacotes e seus eventos de chegada, com lista para limpeza no final
  Pacote** pacotes = new Pacote*[numeroPacotes];
  string pac, orgStr, dstStr;
  
  //Constroi os pacotes
  for(int i = 0; i<numeroPacotes; i++){
    double tempoChegada;
    int id, org, dst;
    int idcont = i;
    entrada >> tempoChegada >> pac >> id >> orgStr >> org >> dstStr >> dst;
    Pacote* p = new Pacote(idcont, tempoChegada, org, dst);
    idcont++;
    pacotes[i] = p;
    ListaEncadeada rota = grafo.buscaLargura(org, dst);
    p->setRota(rota);
    Evento* ev_chegada = new Evento(tempoChegada, 1, p, org, dst);
    escalonador.insere(ev_chegada);
}

    
 //Agenda os primeiros transportes
    for(int i = 0; i < numeroArmazens; i++){
        ListaEncadeada vizinhos = grafo.getVizinhos(i);
        No* no = vizinhos.getHead();
        while(no != nullptr){
            int j = no->getVal();
            Evento* ev_transporte = new Evento(intervaloTransportes + pacotes[0]->getTempoPost(), 2, nullptr, i, j);
            escalonador.insere(ev_transporte);
            no = no->getProx();
        }
    }
 //SED
 int total_rearmazenamentos = 0;
 double tempo_total_entrega_acumulado = 0.0; 
double relogioAtual = 0.0;
int cont = 0;
int pacotesEntregues = 0;

while (!escalonador.isVazio() && pacotesEntregues < numeroPacotes) {
    cont++;
    //Pega o próximo evento e avança o tempo da simulação
    Evento* evento = escalonador.removeMenor();
    relogioAtual = evento->getTempo();

    if (evento->getTipo() == 1) {//Se for chegada:
        Pacote* p = evento->getPacote();
        int armazemChegadaId = p->getArmazemAtualId();

        if (armazemChegadaId == p->getDestinoFinalId()) {//Se for o destino final
            p->atualizarEstado("entregue", relogioAtual);
            imprimeTempo(relogioAtual);
            cout << " pacote " << setw(3) << setfill('0') << p->getId() << " entregue em " << setw(3) << setfill('0') << armazemChegadaId << endl;
            pacotesEntregues++;
            tempo_total_entrega_acumulado += (relogioAtual - p->getTempoPost());
        } else {
            //Senao vai precisar ser armazenado em armazem intermediario
            int proximoDestinoId = p->getProximoDestinoId();
            armazens[armazemChegadaId]->armazenaPacote(p, relogioAtual);
            imprimeTempo(relogioAtual);
            cout << " pacote " << setw(3) << setfill('0') << p->getId() << " armazenado em " << setw(3) << setfill('0') << armazemChegadaId << " na secao " << setw(3) << setfill('0') << proximoDestinoId << endl;
        }

    } else if (evento->getTipo() == 2) {// Evento de transporte entre armazéns
    int idOrg = evento->getOrigem();
    int idDst = evento->getDestino();

    //Rearmazena e coloca os pacotes para transporte, ver armazem.cpp
    ResultadoSelecao res = armazens[idOrg]->recuperaPacotes(idDst, relogioAtual);
        total_rearmazenamentos += res.pacotesRearmazenados.getTamanho();
    // Tempo após toda a manipulação
    double tempoAposManipulacao = relogioAtual + res.tempoDeManipulacaoGasto;

    //Agendamento dos pacotes em trânsito
    while (!res.pacotesSelecionados.estaVazia()) {
        Pacote* transportado = res.pacotesSelecionados.Desempilha();

        double tempoChegada = tempoAposManipulacao + latenciaTransporte;

        transportado->setArmazemAtual(idDst);
        transportado->avancarNaRota();
        transportado->atualizarEstado("Chegada Escalonada", tempoAposManipulacao);

        Evento* evChegada = new Evento(tempoChegada, 1, transportado, idOrg, idDst);
        escalonador.insere(evChegada);
    }

    // Reagendar o próximo transporte
    double proximoTransTempo = relogioAtual + intervaloTransportes;
    Evento* proximoTransEv = new Evento(proximoTransTempo, 2, nullptr, idOrg, idDst);
    escalonador.insere(proximoTransEv);
}
    delete evento; 
}
 auto fim_execucao = chrono::high_resolution_clock::now();
    auto duracao_ms = chrono::duration_cast<chrono::milliseconds>(fim_execucao - inicio_execucao).count();
double tempo_medio_entrega = 0.0;
if (numeroPacotes > 0) {
    tempo_medio_entrega = tempo_total_entrega_acumulado / numeroPacotes;
}
    // Escreve a linha de resultado no arquivo CSV
    arquivo_csv << numeroArmazens << ","
                << numeroPacotes << ","
                << capacidadeTransporte << ","
                << latenciaTransporte << ","
                << intervaloTransportes << ","
                << custoRemocao << ","
                << duracao_ms << ","
                << relogioAtual << ","
                << total_rearmazenamentos
                << "\n";

    arquivo_csv.close();
    
    cout << "\nSimulacao concluida. Tempo de execucao: " << duracao_ms << " ms." << endl;
    cout << "Resultados anexados em: " << nome_csv << endl;
//Gerenciamento de memória
for (int i = 0; i < numeroArmazens; i++) {
    delete armazens[i];
}
delete[] armazens;
while (!escalonador.isVazio()) {
    Evento* eventoRestante = escalonador.removeMenor();
    delete eventoRestante;
}
for (int i = 0; i < numeroPacotes; i++) {
    delete pacotes[i];
}
delete[] pacotes;
  return 0;
}