#include <iomanip>
#include <sstream>
#include <iostream>
#include <vector>
#include <list>

using namespace std;
//funcao para desempate lexicografico
bool lexMenor(long long maskA, long long maskB) {
    if (maskA == maskB) return false;
    long long diff = maskA ^ maskB;
    long long lsb = diff & -diff;
    return (maskA & lsb);
}
//lado b da divisao
void ladoB(int A, int B, vector<long long>&adj, vector<long long>&optTam, vector<long long>&optSol){
    long long maxMask = 1 << B;
    //para cada conjunto do lado b
    for(long long mask =0; mask < maxMask; mask++){
        bool valido = true;
        //verifica se o subconjunto e independente
        for(int i = 0; i < B; i++){
            //se i esta no conjunto e a mascara tem algum vizinho de i invalida
            if((mask >> i) & 1){
                long long vizinhos = adj[A + i];
                vizinhos = (vizinhos >> A);
                if(mask & vizinhos){
                    valido = false;
                    break;
                }
            }
        }
        if(valido){
            //conta os bits 1 da mascara para descobrir o tamanho
            long long tam = mask;
            long long count = 0;
            while(tam > 0){
                count += (tam & 1);
                tam >>=1;
            }
            optTam[mask] = count;
            optSol[mask] = mask;
        }else{
            optTam[mask] = -1;
            optSol[mask] = 0;
        }
    }
    //dp para propagar o melhor subconjunto independente para cada mascara
    for(int i = 0; i < B; i++){
        for (long long mask = 0; mask < maxMask; mask++) {
            if ((mask >> i) & 1) {
                long long maskAnt = mask ^ (1LL << i);
                bool atualiza = false;
                if (optTam[maskAnt] > optTam[mask]) {
                    atualiza = true;
                } 
                else if (optTam[maskAnt] == optTam[mask]) {
                    if (lexMenor(optSol[maskAnt], optSol[mask])) {
                        atualiza = true;
                    }
                }
                if (atualiza) {
                    optTam[mask] = optTam[maskAnt];
                    optSol[mask] = optSol[maskAnt];
                }
            }
        }
    }
        
    
}
int main(){
    int n, m;
    cin >> n >> m;
    int A = n/2;
    int B = n - A;
    long long tamanho = 1 << B;
    //lista de adjacencia dos duendes com seus vizinhos brigados em bitmasks
    vector<long long> adj(n, 0);
    int p1, p2;
    for(int i = 0; i < m; i++){
        cin >> p1 >> p2;
        adj[p1] = adj[p1] | (1LL << p2);
        adj[p2] = adj[p2] | (1LL << p1);
    }
    vector<long long> optTam(tamanho);
    vector<long long> optSol(tamanho);
    ladoB(A, B, adj, optTam, optSol);
    long long maxK = 0;
    long long melhorMask = 0;
    long long maxMaskA = (1LL << A);
    //faz o lado a
    for(long long maskA = 0; maskA < maxMaskA; maskA++){
        bool valido = true;
        long long vizinhosB = 0;
        //verifica se o subconj e independente
        for(int i = 0; i< A; i++){
            if ((maskA >> i) & 1) {
                if (maskA & adj[i]) { 
                    valido = false;
                    break;
                }
                //acumula os vizinhos do lado b
                vizinhosB = vizinhosB | (adj[i] >> A);
            }
        }
        if(!valido) continue;
        //inverte para pegar os livres a serem pareados 
        long long livresB = ((1LL << B) - 1) & (~vizinhosB);
        long long tam = maskA;
        int count = 0;
        //conta os bits 1 para o tamanho
        while(tam > 0){
                count += (tam & 1);
                tam >>=1;
            }
        long long tamTotal = count + optTam[livresB];
        long long solB = optSol[livresB];
        //combina a solucao em uma mesma mascara
        long long maskTotal = maskA | (solB << A);
        if(tamTotal > maxK){
            maxK = tamTotal;
            melhorMask = maskTotal;

        }else if(tamTotal == maxK){
            if(lexMenor(maskTotal, melhorMask)){
                melhorMask = maskTotal;
            }
        }
    }
    cout << maxK << endl;
    bool primeiro = true;
    for (int i = 0; i < n; i++) {
        if ((melhorMask >> i) & 1) {
            if (!primeiro) cout << " ";
            cout << i;
            primeiro = false;
        }
    }
    cout << endl;
    return 0;
}
