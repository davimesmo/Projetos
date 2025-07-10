#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>

#include "arvoreavl.hpp"
#include "evento.hpp"
#include "listainteiros.hpp" // Renomeado de listainteiros.hpp

using namespace std;

// --- Funções Auxiliares (sem alterações) ---

void ordenarResultados(ListaEncadeada<Evento *> &lista) {
  int n = lista.getTam();
  if (n < 2) return;
  for (int i = 1; i < n; i++) {
    for (int j = 1; j < n; j++) {
      Evento *atual = lista.getItem(j);
      Evento *proximo = lista.getItem(j + 1);
      if ((atual->getTimestamp() > proximo->getTimestamp()) ||
          (atual->getTimestamp() == proximo->getTimestamp() && atual->getIdPacote() > proximo->getIdPacote())) {
        lista.setItem(proximo, j);
        lista.setItem(atual, j + 1);
      }
    }
  }
}

int prioridadeEvento(const string &tipo) {
  if (tipo == "EN") return 6;
  if (tipo == "TR") return 5;
  if (tipo == "UR") return 4;
  if (tipo == "RM") return 3;
  if (tipo == "AR") return 2;
  if (tipo == "RG") return 1;
  return 0;
}


// --- Função Principal ---

int main(int argc, char *argv[]) {
    // ---- 1. SETUP E LEITURA DO ARQUIVO ----

    // CORRIGIDO: Adicionada verificação de argumento
    if (argc < 2) {
        cerr << "Erro: Nome do arquivo de entrada nao fornecido." << endl;
        cerr << "Uso: " << argv[0] << " <arquivo_de_entrada>" << endl;
        return 1;
    }

    string nomeArquivo = argv[1];
    ifstream arquivoEntrada(nomeArquivo);
    if (!arquivoEntrada.is_open()) {
        // CORRIGIDO: Mensagem de erro mais clara
        cerr << "Erro: Nao foi possivel abrir o arquivo de entrada '" << nomeArquivo << "'" << endl;
        return 1;
    }

    auto inicio_leitura = std::chrono::high_resolution_clock::now();
    ListaEncadeada<string> linhas_da_entrada;
    string linha;
    while (getline(arquivoEntrada, linha)) {
        if (!linha.empty()) {
            linhas_da_entrada.insereFinal(linha);
        }
    }
    arquivoEntrada.close();
    auto fim_leitura = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tempo_leitura = fim_leitura - inicio_leitura;

    // ---- 2. PROCESSAMENTO PRINCIPAL ----
    auto inicio_processamento = std::chrono::high_resolution_clock::now();

    ListaEncadeada<Evento *> baseDeEventos;
    ArvoreAVL<int, ListaEncadeada<Evento *> *> indicePacotes;
    ArvoreAVL<string, ListaEncadeada<int> *> indiceClientes;

    int total_eventos_ev = 0;
    int total_consultas_pc = 0;
    int total_consultas_cl = 0;

    // O grande loop de processamento continua igual...
    for (int i = 1; i <= linhas_da_entrada.getTam(); ++i) {
        string linha_atual = linhas_da_entrada.getItem(i);
        stringstream ss(linha_atual);
        double timestamp; // Usando double para consistência
        string comando;
        ss >> timestamp >> comando;

        if (comando == "EV") {
            total_eventos_ev++;
            // ... Lógica para processar eventos ...
            string tipoEvento;
            int idPacote;
            ss >> tipoEvento >> idPacote;
            string remetente = "", destinatario = "";
            int armazemOrig = -1, armazemDest = -1;
            if (tipoEvento == "RG") ss >> remetente >> destinatario >> armazemOrig >> armazemDest;
            else if (tipoEvento == "TR") ss >> armazemOrig >> armazemDest;
            else if (tipoEvento == "AR" || tipoEvento == "RM" || tipoEvento == "UR") ss >> armazemOrig >> armazemDest;
            else if (tipoEvento == "EN") ss >> armazemDest;
            Evento *novoEvento = new Evento(timestamp, tipoEvento, idPacote, remetente, destinatario, armazemOrig, armazemDest, linha_atual);
            baseDeEventos.insereFinal(novoEvento);
            ListaEncadeada<Evento *> **listaEventosPtr = indicePacotes.buscar(idPacote);
            if (listaEventosPtr == nullptr) {
                ListaEncadeada<Evento *> *novaLista = new ListaEncadeada<Evento *>();
                novaLista->insereFinal(novoEvento);
                indicePacotes.inserir(idPacote, novaLista);
            } else { (*listaEventosPtr)->insereFinal(novoEvento); }
            if (tipoEvento == "RG") {
                ListaEncadeada<int> **listaPacotesRem = indiceClientes.buscar(remetente);
                if (listaPacotesRem == nullptr) {
                    ListaEncadeada<int> *novaLista = new ListaEncadeada<int>();
                    novaLista->insereFinal(idPacote);
                    indiceClientes.inserir(remetente, novaLista);
                } else if (!(*listaPacotesRem)->pesquisa(idPacote)) { (*listaPacotesRem)->insereFinal(idPacote); }
                ListaEncadeada<int> **listaPacotesDest = indiceClientes.buscar(destinatario);
                if (listaPacotesDest == nullptr) {
                    ListaEncadeada<int> *novaLista = new ListaEncadeada<int>();
                    novaLista->insereFinal(idPacote);
                    indiceClientes.inserir(destinatario, novaLista);
                } else if (!(*listaPacotesDest)->pesquisa(idPacote)) { (*listaPacotesDest)->insereFinal(idPacote); }
            }
        } else if (comando == "PC") {
            total_consultas_pc++;
            // ... Lógica para consulta de pacote ...
            int idPacote;
            ss >> idPacote;
            cout << setw(6) << setfill('0') << static_cast<int>(timestamp) << " " << comando << " " << setw(3) << setfill('0') << idPacote << endl;
            ListaEncadeada<Evento *> resultados;
            ListaEncadeada<Evento *> **listaEventosPtr = indicePacotes.buscar(idPacote);
            if (listaEventosPtr != nullptr) {
                ListaEncadeada<Evento *> *listaEventos = *listaEventosPtr;
                for (int j = 1; j <= listaEventos->getTam(); ++j) {
                    Evento *ev = listaEventos->getItem(j);
                    if (ev->getTimestamp() <= timestamp) { resultados.insereFinal(ev); }
                }
            }
            cout << resultados.getTam() << endl;
            for (int j = 1; j <= resultados.getTam(); ++j) { cout << resultados.getItem(j)->getLinhaCompleta() << endl; }
        } else if (comando == "CL") {
            total_consultas_cl++;
            // ... Lógica para consulta de cliente ...
            string nomeCliente;
            ss >> nomeCliente;
            cout << setw(6) << setfill('0') << static_cast<int>(timestamp) << " " << comando << " " << nomeCliente << endl;
            ListaEncadeada<Evento *> resultados;
            ListaEncadeada<int> **listaPacotesPtr = indiceClientes.buscar(nomeCliente);
            if (listaPacotesPtr != nullptr) {
                ListaEncadeada<int> *listaPacotes = *listaPacotesPtr;
                for (int j = 1; j <= listaPacotes->getTam(); ++j) {
                    int idPacote = listaPacotes->getItem(j);
                    ListaEncadeada<Evento *> **listaEventosPtr = indicePacotes.buscar(idPacote);
                    if (listaEventosPtr != nullptr) {
                        ListaEncadeada<Evento *> *listaEventos = *listaEventosPtr;
                        Evento *eventoRG = nullptr;
                        Evento *eventoMaisRecente = nullptr;
                        for (int k = 1; k <= listaEventos->getTam(); ++k) {
                            Evento *ev = listaEventos->getItem(k);
                            if (ev->getTimestamp() > timestamp) continue;
                            if (ev->getTipo() == "RG") eventoRG = ev;
                            if (eventoMaisRecente == nullptr) { eventoMaisRecente = ev; }
                            else {
                                if (ev->getTimestamp() > eventoMaisRecente->getTimestamp()) { eventoMaisRecente = ev; }
                                else if (ev->getTimestamp() == eventoMaisRecente->getTimestamp()) {
                                    if (prioridadeEvento(ev->getTipo()) > prioridadeEvento(eventoMaisRecente->getTipo())) { eventoMaisRecente = ev; }
                                }
                            }
                        }
                        if (eventoRG != nullptr) resultados.insereFinal(eventoRG);
                        if (eventoMaisRecente != nullptr && eventoMaisRecente != eventoRG) { resultados.insereFinal(eventoMaisRecente); }
                    }
                }
            }
            ordenarResultados(resultados);
            cout << resultados.getTam() << endl;
            for (int j = 1; j <= resultados.getTam(); ++j) { cout << resultados.getItem(j)->getLinhaCompleta() << endl; }
        }
    }
    auto fim_processamento = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tempo_processamento = fim_processamento - inicio_processamento;

    // ---- 3. SALVAR RESULTADOS DA ANÁLISE EXPERIMENTAL ----
    
    // CORRIGIDO: Usa um nome de arquivo padrão e verifica se foi possível abri-lo.
   cout << "DEBUG: Vai tentar escrever no CSV..." << endl;
cout << "Clientes: " << indiceClientes.getNumeroNos() << endl;
cout << "Pacotes: " << indicePacotes.getNumeroNos() << endl;
cout << "Eventos: " << total_eventos_ev << endl;
cout << "Consultas PC: " << total_consultas_pc << endl;
cout << "Consultas CL: " << total_consultas_cl << endl;
cout << "Tempo leitura: " << tempo_leitura.count() << endl;
cout << "Tempo processamento: " << tempo_processamento.count() << endl;
   
   
    string nomeArquivoCSV = "resultados.csv";
    ofstream arquivo_csv(nomeArquivoCSV, ios::app);
    
    if (arquivo_csv.is_open()) {
        arquivo_csv.seekp(0, ios::end);
        if (arquivo_csv.tellp() == 0) {
            arquivo_csv << "NumClientes,NumPacotes,NumEventos,NumConsultasPC,NumConsultasCL,TempoLeitura_s,TempoProcessamento_s" << endl;
        }
        arquivo_csv << indiceClientes.getNumeroNos() << ","
                    << indicePacotes.getNumeroNos() << ","
                    << total_eventos_ev << ","
                    << total_consultas_pc << ","
                    << total_consultas_cl << ","
                    << fixed << setprecision(6) << tempo_leitura.count() << ","
                    << fixed << setprecision(6) << tempo_processamento.count()
                    << endl;
        arquivo_csv.close();
        // Mensagem de sucesso
        cout << "\nResultados da execucao anexados em: " << nomeArquivoCSV << endl;
    } else {
        // Mensagem de erro se não conseguir abrir o CSV
        cerr << "Erro: Nao foi possivel abrir o arquivo de saida '" << nomeArquivoCSV << "' para escrita." << endl;
    }

    // ---- 4. LIMPEZA DE MEMÓRIA ----
    for (int i = 1; i <= baseDeEventos.getTam(); ++i) {
        delete baseDeEventos.getItem(i);
    }
    ListaEncadeada<ListaEncadeada<Evento *> *> listasDeEventos;
    indicePacotes.obterTodosValores(listasDeEventos);
    for (int i = 1; i <= listasDeEventos.getTam(); ++i) {
        delete listasDeEventos.getItem(i);
    }
    ListaEncadeada<ListaEncadeada<int> *> listasDePacotes;
    indiceClientes.obterTodosValores(listasDePacotes);
    for (int i = 1; i <= listasDePacotes.getTam(); ++i) {
        delete listasDePacotes.getItem(i);
    }

    return 0;
}
