#include "ordenador.hpp" // Assume que este header já inclui o .tpp com as implementações template
#include <chrono>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <numeric>   // Para std::iota
#include <algorithm> // Para std::reverse, std::sort (para gerar vetores)

// using namespace std; // Evitado no escopo global

// Função auxiliar para preencher 'v' e 'original' do objeto ordenador
void popularVetorParaExperimento(OrdenadorUniversal<int>& ordenador, const std::vector<int>& dados_originais) {
    if (static_cast<int>(dados_originais.size()) != ordenador.tam) {
        std::cerr << "Erro fatal: Tamanho do vetor de dados gerado (" << dados_originais.size() 
                  << ") nao corresponde ao 'tam' do ordenador (" << ordenador.tam << ")." << std::endl;
        exit(1); 
    }
    for (int i = 0; i < ordenador.tam; ++i) {
        ordenador.v[i] = dados_originais[i];
        ordenador.original[i] = dados_originais[i];
    }
}

// Função para gerar um vetor aleatório controlado
// Cria um vetor ordenado e depois aplica 'percentual_shuffles' em relação ao tamanho
std::vector<int> gerarVetorAleatorioControlado(int tamanho, int seed_para_embaralhar, double percentual_shuffles) {
    std::vector<int> dados(tamanho);
    if (tamanho == 0) {
        return dados; // Retorna vetor vazio se tamanho for 0
    }

    std::iota(dados.begin(), dados.end(), 0); // Começa ordenado: 0, 1, 2...

    if (percentual_shuffles > 0) {
        // Usa um objeto OrdenadorUniversal temporário apenas para acessar o método embaralha
        // Os outros parâmetros do construtor do temp_shuffler não são críticos para esta etapa.
        OrdenadorUniversal<int> temp_shuffler(tamanho, 10.0, 0.01, 0.01, 0.01, seed_para_embaralhar, 10, 10);
        
        // Copia os dados ordenados para o objeto temporário para que o embaralha opere nele
        for(int i=0; i<tamanho; ++i) temp_shuffler.v[i] = dados[i];
        // original não precisa ser populado no temp_shuffler para esta finalidade

        int num_shuffles = static_cast<int>(percentual_shuffles * tamanho);
        if (num_shuffles == 0 && percentual_shuffles > 0) num_shuffles = 1; // Garante ao menos 1 shuffle
        
        if (tamanho >= 2) { // Embaralhar só faz sentido com pelo menos 2 elementos
            temp_shuffler.embaralha(num_shuffles); // Embaralha temp_shuffler.v
            for(int i=0; i<tamanho; ++i) dados[i] = temp_shuffler.v[i]; // Pega o resultado embaralhado
        }
        // Não precisamos de delete[] para temp_shuffler.v se OrdenadorUniversal gerencia sua própria memória
        // e o destrutor de temp_shuffler será chamado. Se v fosse alocado externamente, seria diferente.
        // A sua classe OrdenadorUniversal aloca v e original no construtor e deleta no destrutor.
    }
    return dados;
}


int main() { // Removido argc, argv pois não leremos de arquivo de config
    
    // --- Parâmetros Fixos para este Conjunto de Experimentos ---
    const int SEED_EXPERIMENTO = 12345; // Semente fixa para reprodutibilidade do embaralhamento
    const double LIMIAR_CUSTO_EXPERIMENTO = 10.0; // Limiar de custo para convergência nas calibrações

    // Coeficientes 'a, b, c' (baseados nos seus resultados para tam=15.000)
    const double A_COEF = -0.22920217900344528;
    const double B_COEF =  0.23604196632791263;
    const double C_COEF = 14.355011852742471;

    // Configuração fixa do tipo de vetor para variar 'tam'
    const std::string CONFIG_FIXA_DESC = "Aleatorio_50perc_Shuffle";
    const double PERCENTUAL_SHUFFLES_FIXO = 0.50;

    // --- Arquivo CSV de Saída ---
    std::ofstream arquivo_csv("resultados_experimentos.csv");
    if (!arquivo_csv.is_open()) {
        std::cerr << "Erro ao abrir arquivo CSV para escrita!" << std::endl;
        return 1;
    }

    arquivo_csv << "TAMANHO_VETOR,CONFIG_DESC,NUM_QUEBRAS_INICIAL,ALGORITMO,TEMPO_MS,CMP,MOV,CALLS,LP_CALIBRADO_TAD,LQ_CALIBRADO_TAD,A_COEF_USADO,B_COEF_USADO,C_COEF_USADO" << std::endl;

    // --- Tamanhos de Vetor para Testar ---
    std::vector<int> tamanhos_para_testar = {100, 1000, 5000, 10000, 15000, 30000, 50000}; // Adicionei os que você usou para os coefs
    // std::vector<int> tamanhos_para_testar = {1000, 10000, 50000, 100000}; // Exemplo menor

    for (int tam_atual : tamanhos_para_testar) {
        if (tam_atual == 0 && PERCENTUAL_SHUFFLES_FIXO > 0) {
            std::cout << "\n--- Pulando Tam: " << tam_atual << " para " << CONFIG_FIXA_DESC << " (sem elementos para embaralhar) ---" << std::endl;
            continue;
        }
        std::cout << "\n--- Iniciando Experimento para TAMANHO_VETOR: " << tam_atual 
                  << " (Config: " << CONFIG_FIXA_DESC << ") ---" << std::endl;

        // 1. Gerar vetor de dados para esta configuração e tamanho
        std::vector<int> dados_configurados = gerarVetorAleatorioControlado(tam_atual, SEED_EXPERIMENTO, PERCENTUAL_SHUFFLES_FIXO);

        // 2. Criar objeto OrdenadorUniversal para este teste
        // Os valores iniciais de limiarQuebras (e.g. 3) e minTamParticao (e.g. 5) no construtor
        // são apenas placeholders, pois serão sobrepostos pela calibração.
        OrdenadorUniversal<int> ordenador(tam_atual, LIMIAR_CUSTO_EXPERIMENTO, A_COEF, B_COEF, C_COEF, SEED_EXPERIMENTO, 3, 5);
        popularVetorParaExperimento(ordenador, dados_configurados);
        int quebras_iniciais = ordenador.numeroDeQuebras();

        // 3. Etapa (b) do PDF: Calibrar o TAD 
        std::cout << "  Calibrando limiares para tam=" << tam_atual << "..." << std::endl;
        ordenador.determinaLimiarParticao(); 
        ordenador.determinaLimiarQuebras();  
        
        int lp_calibrado = ordenador.minTamParticao; // Captura os limiares calibrados
        int lq_calibrado = ordenador.limiarQuebras;
        std::cout << "  Limiares calibrados: LP=" << lp_calibrado << ", LQ=" << lq_calibrado << std::endl;

        // 4. Etapa (c) do PDF - Testar TAD Universal com limiares calibrados
        std::cout << "  Testando TAD Universal..." << std::endl;
        popularVetorParaExperimento(ordenador, dados_configurados); 
        ordenador.resetaEstatisticas();
        // Garante que os limiares calibrados sejam usados
        ordenador.minTamParticao = lp_calibrado;
        ordenador.limiarQuebras = lq_calibrado;

        auto t_inicio_tad = std::chrono::high_resolution_clock::now();
        ordenador.ordenadorUniversal();
        auto t_fim_tad = std::chrono::high_resolution_clock::now();
        long long dur_us_tad = std::chrono::duration_cast<std::chrono::microseconds>(t_fim_tad - t_inicio_tad).count();

        arquivo_csv << ordenador.tam << ","
                    << CONFIG_FIXA_DESC << ","
                    << quebras_iniciais << ","
                    << "TAD_Universal" << ","
                    << std::fixed << std::setprecision(3) << (dur_us_tad / 1000.0) << ","
                    << ordenador.getComps() << "," << ordenador.getMoves() << "," << ordenador.getCalls() << ","
                    << lp_calibrado << "," << lq_calibrado << ","
                    << A_COEF << "," << B_COEF << "," << C_COEF << std::endl;
        std::cout << "    TAD Universal: " << (dur_us_tad / 1000.0) << " ms, CMP: " << ordenador.getComps() << std::endl;


        // 5. Etapa (c) do PDF - Testar Insertion Sort Puro
        std::cout << "  Testando Insertion Puro..." << std::endl;
        popularVetorParaExperimento(ordenador, dados_configurados); 
        ordenador.resetaEstatisticas();
        auto t_inicio_ins = std::chrono::high_resolution_clock::now();
        ordenador.insertion(0, ordenador.tam - 1);
        auto t_fim_ins = std::chrono::high_resolution_clock::now();
        long long dur_us_ins = std::chrono::duration_cast<std::chrono::microseconds>(t_fim_ins - t_inicio_ins).count();
        arquivo_csv << ordenador.tam << ","
                    << CONFIG_FIXA_DESC << ","
                    << quebras_iniciais << ","
                    << "InsertionPuro" << ","
                    << std::fixed << std::setprecision(3) << (dur_us_ins / 1000.0) << ","
                    << ordenador.getComps() << "," << ordenador.getMoves() << "," << ordenador.getCalls() << ","
                    << "N/A" << "," << "N/A" << "," 
                    << A_COEF << "," << B_COEF << "," << C_COEF << std::endl;
        std::cout << "    Insertion Puro: " << (dur_us_ins / 1000.0) << " ms, CMP: " << ordenador.getComps() << std::endl;


        // 6. Etapa (c) do PDF - Testar Quicksort "Puro" (Híbrido, usando o minTamParticao que o TAD usaria)
        std::cout << "  Testando Quicksort Hibrido (com LP do TAD)..." << std::endl;
        popularVetorParaExperimento(ordenador, dados_configurados); 
        ordenador.resetaEstatisticas();
        ordenador.setLimiarQuebras(0); // Força caminho do quicksort se houver quebras
        ordenador.minTamParticao = lp_calibrado; // Usa o limiar de partição que o TAD calibrou
        
        auto t_inicio_qs = std::chrono::high_resolution_clock::now();
        ordenador.ordenadorUniversal(); // Executará Quicksort com os parâmetros definidos
        auto t_fim_qs = std::chrono::high_resolution_clock::now();
        long long dur_us_qs = std::chrono::duration_cast<std::chrono::microseconds>(t_fim_qs - t_inicio_qs).count();
        arquivo_csv << ordenador.tam << ","
                    << CONFIG_FIXA_DESC << ","
                    << quebras_iniciais << ","
                    << "QuicksortHibrido_LPcal" << ","
                    << std::fixed << std::setprecision(3) << (dur_us_qs / 1000.0) << ","
                    << ordenador.getComps() << "," << ordenador.getMoves() << "," << ordenador.getCalls() << ","
                    << lp_calibrado << "," << 0 << "," // LQ foi "forçado" para este teste
                    << A_COEF << "," << B_COEF << "," << C_COEF << std::endl;
        std::cout << "    Quicksort Hibrido (LP=" << lp_calibrado << ", LQ forçado=0): " 
                  << (dur_us_qs / 1000.0) << " ms, CMP: " << ordenador.getComps() << std::endl;
    }

    arquivo_csv.close();
    std::cout << "\nResultados da analise de tamanho do vetor (coeficientes fixos) salvos em resultados_tam_vetor_coeffs_fixos.csv" << std::endl;

    return 0;
}