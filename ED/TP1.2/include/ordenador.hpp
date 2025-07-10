#ifndef ORDENADOR_H
#define ORDENADOR_H

#include <string>
#include "item_t.hpp"

struct Estatisticas {
    Estatisticas() { cmp = 0; moves = 0; calls = 0; }
    int cmp, moves, calls;
    double custo;
};

template <typename T>
class OrdenadorUniversal {
public:
    OrdenadorUniversal(int tam, double limarCusto, double a_, double b_, double c_, int seed_, int limiarQuebras_, int minTamParticao_);
    ~OrdenadorUniversal();

    void ordenadorUniversal();
    void resetaEstatisticas();
    void determinaLimiarParticao();
    void determinaLimiarQuebras();
    void registraEstatisticas(int, Estatisticas*);
    int menorCusto(Estatisticas*, int);
    void imprimeEstatisticas(Estatisticas*, int, int);
    void calculaNovaFaixa(int, int&, int&, int&, int);
    int menorCustoQ(Estatisticas*, Estatisticas*, int);
    void imprimeEstatisticasQ(std::string, Estatisticas*, int, int);
    void calculaNovaFaixaQ(int*, int, int&, int&, int&, int);
    double calculaCusto(Estatisticas*, int*, int, int, int, int, int);
    double calculaLQdiff(Estatisticas*, int, double, int);

    T mediana3(T, T, T);
    void swap(T*, T*);
    void quicksort(int, int);
    void partition3(int, int, int*, int*);
    void insertion(int, int);
    
    int numeroDeQuebras();
    void restauraOriginal();
    void embaralha(int);

    void imprimeV();

    int getMoves();
    int getComps();
    int getCalls();

    void inccalls();
    void incmoves();
    void inccomps();
    void setLimiarQuebras(int);

    T* v;
    T* original;
    int tam;
    int limiarQuebras, minTamParticao, numQuebras;
    int comps, moves, calls;
    int seed;
    double a, b, c, limiarCusto;
};


#endif

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

template <typename T>
OrdenadorUniversal<T>::OrdenadorUniversal(int tam_, double limarCusto_, double a_, double b_, double c_, int seed_, int limiarQuebras_, int minTamParticao_) : tam(tam_), limiarQuebras(limiarQuebras_), minTamParticao(minTamParticao_), seed(seed_),  a(a_), b(b_), c(c_), limiarCusto(limarCusto_){
    v = new T[tam_];
    original = new T[tam_];
}

template <typename T>
OrdenadorUniversal<T>::~OrdenadorUniversal() {
    delete[] v;
    delete[] original;
}

template <typename T>
void OrdenadorUniversal<T>::setLimiarQuebras(int limiar) {
    limiarQuebras = limiar;
}

template <typename T>
void OrdenadorUniversal<T>::resetaEstatisticas() {
    comps = 0;
    moves = 0;
    calls = 0;
}

template <typename T>
void OrdenadorUniversal<T>::ordenadorUniversal() {
    int quebras = numeroDeQuebras();
    if (quebras < limiarQuebras) {
        insertion(0, tam - 1);
    } else {
        quicksort(0, tam - 1);
    }
}

template <typename T>
int OrdenadorUniversal<T>::numeroDeQuebras() {
    int quebras = 0;
    for (int i = 1; i < tam; i++) {
        if (v[i] < v[i - 1]) {
            quebras++;
        }
    }
    return quebras;
}

template <typename T>
void OrdenadorUniversal<T>::swap(T *xp, T *yp) {
    T temp = *xp;
    *xp = *yp;
    *yp = temp;
    incmoves();
    incmoves();
    incmoves();
}

template <typename T>
T OrdenadorUniversal<T>::mediana3(T a, T b, T c) {
    if ((a <= b) && (b <= c)) return b;
    if ((a <= c) && (c <= b)) return c;
    if ((b <= a) && (a <= c)) return a;
    if ((b <= c) && (c <= a)) return c;
    if ((c <= a) && (a <= b)) return a;
    return b;
}

template <typename T>
void OrdenadorUniversal<T>::inccalls() {
    calls++;
}

template <typename T>
void OrdenadorUniversal<T>::inccomps() {
    comps++;
}

template <typename T>
void OrdenadorUniversal<T>::incmoves() {
    moves++;
}

template <typename T>
void OrdenadorUniversal<T>::insertion(int l, int r) {
    inccalls();
    int j;
    T aux;
    for (int i = l + 1; i <= r; i++) {
        aux = v[i];
        incmoves();
        j = i - 1;
        while (j >= l) {
            inccomps();
            if (aux < v[j]) {
                v[j + 1] = v[j];
                incmoves();
                j--;
            } else {
                break;
            }
        }
        if (j < l) inccomps();
        incmoves();
        v[j + 1] = aux;
    }
}

template <typename T>
void OrdenadorUniversal<T>::partition3(int l, int r, int *i, int *j) {
    *i = l;
    *j = r;
    inccalls();

    int m = (l + r) / 2;
    T vl = v[*i], vm = v[m], vr = v[*j];
    T med = mediana3(vl, vm, vr);
    T x = med;

    do {
        while (inccomps(), v[*i] < x) (*i)++;
        while (inccomps(), v[*j] > x) (*j)--;
        if (*i <= *j) {
            swap(&v[*i], &v[*j]);
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

template <typename T>
void OrdenadorUniversal<T>::quicksort(int l, int r) {
    if (l >= r) return;
    if ((r - l + 1) <= minTamParticao) {
        insertion(l, r);
        return;
    }
    inccalls();
    int i, j;
    partition3(l, r, &i, &j);
    if (l < j) quicksort(l, j);
    if (i < r) quicksort(i, r);
}

template <typename T>
int OrdenadorUniversal<T>::getMoves() {
    return moves;
}

template <typename T>
int OrdenadorUniversal<T>::getCalls() {
    return calls;
}

template <typename T>
int OrdenadorUniversal<T>::getComps() {
    return comps;
}

template <typename T>
void OrdenadorUniversal<T>::restauraOriginal() {
    for (int i = 0; i < tam; i++) {
        v[i] = original[i];
    }
}

template <typename T>
void OrdenadorUniversal<T>::embaralha(int numShuffle) {
    srand48(seed);
    int p1 = 0, p2 = 0;
    T temp;

    for (int t = 0; t < numShuffle; t++) {
        do {
            p1 = static_cast<int>(drand48() * tam);
            p2 = static_cast<int>(drand48() * tam);
        } while (p1 == p2);
        temp = v[p1];
        v[p1] = v[p2];
        v[p2] = temp;
    }
}

template <typename T>
void OrdenadorUniversal<T>::imprimeV() {
    for (int i = 0; i < tam; i++) {
        cout << " " << v[i] << " ";
        if (i % 10 == 0) cout << endl;
    }
    cout << endl;
}
// Registra estatísticas
template <typename T>
void OrdenadorUniversal<T>::registraEstatisticas(int numMPS, Estatisticas *est) {
    est[numMPS].cmp = getComps();
    est[numMPS].moves = getMoves();
    est[numMPS].calls = getCalls();
    est[numMPS].custo = a * getComps() + b * getMoves() + c * getCalls();
}

// Menor custo para MPS
template <typename T>
int OrdenadorUniversal<T>::menorCusto(Estatisticas *est, int numMPS) {
    float menor = est[0].custo;
    int indice = 0;
    for (int i = 1; i < numMPS; i++) {
        if (est[i].custo < menor && est[i].custo != 0.0) {
            menor = est[i].custo;
            indice = i;
        }
    }
    return indice;
}

// Imprime estatísticas MPS
template <typename T>
void OrdenadorUniversal<T>::imprimeEstatisticas(Estatisticas *est, int t, int numMPS) {
    cout << fixed;
    cout << "mps " << t
         << " cost " << setprecision(9) << est[numMPS].custo
         << " cmp " << est[numMPS].cmp
         << " move " << est[numMPS].moves
         << " calls " << est[numMPS].calls
         << endl;
}

// Calcula nova faixa MPS
template <typename T>
void OrdenadorUniversal<T>::calculaNovaFaixa(int limParticao, int &minMPS, int &maxMPS, int &passoMPS, int numMPS) {
    int newMin, newMax;

    if (limParticao == 0) {
        newMin = minMPS;
        newMax = minMPS + 2 * passoMPS;
    } else if (limParticao == numMPS - 1) {
        newMin = minMPS + (numMPS - 3) * passoMPS;
        newMax = minMPS + (numMPS - 1) * passoMPS;
    } else {
        newMin = minMPS + (limParticao - 1) * passoMPS;
        newMax = minMPS + (limParticao + 1) * passoMPS;
    }

    minMPS = newMin;
    maxMPS = newMax;
    passoMPS = (maxMPS - minMPS) / 5;
    if (passoMPS == 0) passoMPS++;
}

// Menor custo para Quebras
template <typename T>
int OrdenadorUniversal<T>::menorCustoQ(Estatisticas *estqs, Estatisticas *estin, int numLQ) {
    int menor = 0;
    for (int c = 1; c < numLQ; c++) {
        if (fabs(estqs[c].custo - estin[c].custo) < fabs(estqs[menor].custo - estin[menor].custo)) {
            menor = c;
        }
    }
    return menor;
}

// Imprime estatísticas Quebras
template <typename T>
void OrdenadorUniversal<T>::imprimeEstatisticasQ(string alg, Estatisticas *est, int t, int numMPS) {
    cout << fixed;
    cout << alg << " lq " << t
         << " cost " << setprecision(9) << est[numMPS].custo
         << " cmp " << est[numMPS].cmp
         << " move " << est[numMPS].moves
         << " calls " << est[numMPS].calls
         << endl;
}

// Calcula nova faixa Quebras
template <typename T>
void OrdenadorUniversal<T>::calculaNovaFaixaQ(int *lqs, int indiceMelhorLQ, int &minLQ, int &maxLQ, int &passoLQ, int numLQ) {
    if (indiceMelhorLQ == 0 && numLQ >= 3) {
        minLQ = lqs[0];
        maxLQ = lqs[2];
    } else if (indiceMelhorLQ == numLQ - 1 && numLQ >= 3) {
        minLQ = lqs[numLQ - 3];
        maxLQ = lqs[numLQ - 1];
    } else {
        minLQ = lqs[indiceMelhorLQ - 1];
        maxLQ = lqs[indiceMelhorLQ + 1];
    }
    passoLQ = (maxLQ - minLQ) / 5;
    if (passoLQ == 0) passoLQ = 1;
}

// Calcula custo MPS diff
template <typename T>
double OrdenadorUniversal<T>::calculaCusto(Estatisticas *est, int *mps, int minMPS, int maxMPS, int passoMPS, int numMPS, int limParticao) {
    int newMin, newMax;
    if (limParticao == 0) {
        newMin = minMPS;
        newMax = minMPS + 2 * passoMPS;
    } else if (limParticao == numMPS - 1) {
        newMin = minMPS + (numMPS - 3) * passoMPS;
        newMax = minMPS + (numMPS - 1) * passoMPS;
    } else {
        newMin = minMPS + (limParticao - 1) * passoMPS;
        newMax = minMPS + (limParticao + 1) * passoMPS;
    }
    int indiceMin = -1, indiceMax = -1;
    for (int k = 0; k < numMPS; k++) {
        if (mps[k] == newMin) indiceMin = k;
        if (mps[k] == newMax) indiceMax = k;
    }
    return fabs(est[indiceMax].custo - est[indiceMin].custo);
}

// Calcula custo LQ diff
template <typename T>
double OrdenadorUniversal<T>::calculaLQdiff(Estatisticas *estin, int numLQ, double lqDiff, int indiceMelhorLQ) {
    if (numLQ < 3) {
        if (numLQ == 2) {
            return fabs(estin[1].custo - estin[0].custo);
        } else if (numLQ == 1) {
            return 0.0;
        }
        return limiarCusto + 1.0;
    }
    if (indiceMelhorLQ < 0 || indiceMelhorLQ >= numLQ) {
        return limiarCusto + 1.0;
    }
    int newMin, newMax;
    if (indiceMelhorLQ == 0) {
        newMin = 0;
        newMax = 2;
    } else if (indiceMelhorLQ == numLQ - 1) {
        newMin = numLQ - 3;
        newMax = numLQ - 1;
    } else {
        newMin = indiceMelhorLQ - 1;
        newMax = indiceMelhorLQ + 1;
    }
    lqDiff = fabs(estin[newMax].custo - estin[newMin].custo);
    return lqDiff;
}
template <typename T>
void OrdenadorUniversal<T>::determinaLimiarParticao() {
    int minMPS = 2;
    int maxMPS = tam;
    int passoMPS = (maxMPS - minMPS) / 5;
    if (passoMPS == 0) passoMPS++;
    int mps[9];
    double diffCusto = limiarCusto + 1;
    Estatisticas est[9];
    int numMPS = 5;
    int iter = 0;
    int limParticao;

    while (diffCusto > limiarCusto && numMPS >= 5) {
        cout << "iter " << iter++ << endl;
        numMPS = 0;

        for (int t = minMPS; t <= maxMPS; t += passoMPS) {
            mps[numMPS] = t;
            minTamParticao = t;
            setLimiarQuebras(0);
            for (int j = 0; j < tam; j++) v[j] = original[j];
            resetaEstatisticas();
            ordenadorUniversal();
            registraEstatisticas(numMPS, est);
            imprimeEstatisticas(est, t, numMPS);
            numMPS++;
        }

        limParticao = menorCusto(est, numMPS);
        minTamParticao = mps[limParticao];

        diffCusto = calculaCusto(est, mps, minMPS, maxMPS, passoMPS, numMPS, limParticao);
        calculaNovaFaixa(limParticao, minMPS, maxMPS, passoMPS, numMPS);

        cout << fixed;
        cout << "nummps " << numMPS << " limParticao " << mps[limParticao] 
             << " mpsdiff " << setprecision(6) << diffCusto << endl << endl;
    }
}
template <typename T>
void OrdenadorUniversal<T>::determinaLimiarQuebras() {
    int minLQ = 1;
    int maxLQ = tam / 2;
    int passoLQ = (maxLQ - minLQ) / 5;
    if (passoLQ == 0) passoLQ++;

    Estatisticas estin[15];
    Estatisticas estqs[15];
    int lqs[9];
    int numLQ = 7;
    int iter = 0;
    int aux = minTamParticao;
    double lqdiff = limiarCusto + 1;

    while (lqdiff > limiarCusto && numLQ >= 6) {
        if (iter != 0) cout << endl;
        cout << "iter " << iter++ << endl;
        numLQ = 0;

        for (int t = minLQ; t <= maxLQ; t += passoLQ) {
            lqs[numLQ] = t;
            minTamParticao = aux;
            insertion(0, tam - 1);
            resetaEstatisticas();
            embaralha(t);
            setLimiarQuebras(0);
            ordenadorUniversal();
            registraEstatisticas(numLQ, estqs);
            imprimeEstatisticasQ("qs", estqs, t, numLQ);
            setLimiarQuebras(tam + 1);
            insertion(0, tam - 1);
            resetaEstatisticas();
            embaralha(t);
            ordenadorUniversal();
            registraEstatisticas(numLQ, estin);
            imprimeEstatisticasQ("in", estin, t, numLQ);
            numLQ++;
        }

        int indiceMelhorLQ = menorCustoQ(estqs, estin, numLQ);
        lqdiff = calculaLQdiff(estin, numLQ, lqdiff, indiceMelhorLQ);
        cout << fixed;
        cout << "numlq " << numLQ << " limQuebras " << lqs[indiceMelhorLQ] 
             << " lqdiff " << setprecision(6) << lqdiff << endl;

        calculaNovaFaixaQ(lqs, indiceMelhorLQ, minLQ, maxLQ, passoLQ, numLQ);
    }
}
