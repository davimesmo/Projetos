#include "../include/ponto.hpp"
#include <algorithm> //min e sort, no moodle disse que pode
#include <cmath>
#include <iomanip>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>
using namespace std;

Ponto::Ponto(int x, int y, int id) : x(x), y(y), id(id) {}

Ponto::~Ponto() {
}
Triangulo Ponto::menorTri(vector<Ponto> &vetor, size_t l, size_t r) {
  // Caso base: força bruta para <= 10 pontos
  if (r - l + 1 <= 10) {
    Triangulo best;
    best.x = -1;
    best.y = -1;
    best.z = -1;
    best.perimetro = -1;
    double p = -1;
    // Testa todas as combinações de 3 pontos
    for (size_t a = l; a <= r; ++a) {
      for (size_t b = a + 1; b <= r; ++b) {
        for (size_t c = b + 1; c <= r; ++c) {
          double ab = Ponto::calculaDist(vetor[a], vetor[b]);
          double ac = Ponto::calculaDist(vetor[a], vetor[c]);
          double bc = Ponto::calculaDist(vetor[b], vetor[c]);
          double peri = ab + ac + bc;
          // Ordenação lexicográfica
          int id1 = vetor[a].id;
          int id2 = vetor[b].id;
          int id3 = vetor[c].id;
          if (id2 < id1)
            swap(id1, id2);
          if (id3 < id2)
            swap(id2, id3);
          if (id2 < id1)
            swap(id1, id2);

          if (peri < p || p == -1) {
            p = peri;
            best.x = id1;
            best.y = id2;
            best.z = id3;
            best.perimetro = peri;
          } else if (peri == p) {
            // Ordenacao lexicografica
            if (best.x == -1 || id1 < best.x || (id1 == best.x && id2 < best.y) || (id1 == best.x && id2 == best.y && id3 < best.z)) {
              best.x = id1;
              best.y = id2;
              best.z = id3;
              best.perimetro = peri;
            }
          }
        }
      }
    }
    return best;
  }
  size_t mid = (l + r) / 2;
  //seleciona o menor p
  Triangulo esquerda = Ponto::menorTri(vetor, l, mid);
  Triangulo direita = Ponto::menorTri(vetor, mid + 1, r);
  double p = min(esquerda.perimetro, direita.perimetro);
  Triangulo menor;
  // ordenacao lexicografica na mão ignore
  if (p == esquerda.perimetro && p == direita.perimetro) {
    if (esquerda.x > direita.x) {
      menor = direita;
    } else if (esquerda.x == direita.x && esquerda.y > direita.y) {
      menor = direita;
    } else if (esquerda.x == direita.x && esquerda.y == direita.y && esquerda.z > direita.z) {
      menor = direita;
    } else {
      menor = esquerda;
    }
    // fim ordenacao lexicografica
  } else if (p == esquerda.perimetro) {
    menor = esquerda;
  } else {
    menor = direita;
  }
  vector<Ponto> strip;
  double L = vetor[mid].x;
  //filtra a faixa central
  for (size_t i = l; i <= r; i++) {
    if (fabs(vetor[i].x - L) <= p / 2) {
      strip.push_back(vetor[i]);
    }
  }
  //ordena verticalmente
  sort(strip.begin(), strip.end(), [](const Ponto &a, const Ponto &b) {
    return a.y < b.y;
  });
  //verifica os possiveis triangulos
  for (size_t i = 0; i < strip.size(); i++) {
    for (size_t j = i + 1; j < strip.size(); j++) {
      //testa a validade do triangulo
      if (strip[j].y - strip[i].y > p)
        break;
      double ij = Ponto::calculaDist(strip[i], strip[j]);
      if (ij > p / 2)
        continue;
      for (size_t k = j + 1; k < strip.size(); k++) {
        if (strip[k].y - strip[i].y > p)
          break;
        double ik = Ponto::calculaDist(strip[i], strip[k]);
        if (ik > p / 2)
          continue;
        //caso seja um triangulo valido, calcula o perimetro e compara com o menor atual
        double jk = Ponto::calculaDist(strip[j], strip[k]);
        double peri = ij + ik + jk;
        if (peri <= p) {
          //ordem lexicografica
          int id1 = strip[i].id;
          int id2 = strip[j].id;
          int id3 = strip[k].id;

          if (id2 < id1)
            swap(id1, id2);
          if (id3 < id2)
            swap(id2, id3);
          if (id2 < id1)
            swap(id1, id2);
          Triangulo meio;
          meio.x = id1;
          meio.y = id2;
          meio.z = id3;
          meio.perimetro = peri;
          if (peri == p) {
            // ordenacao lexicografica
            if (menor.x > id1) {
              menor = meio;
            } else if (menor.x == id1 && menor.y > id2) {
              menor = meio;
            } else if (menor.x == id1 && menor.y == id2 && menor.z > id3) {
              menor = meio;
            }
          } else {
            menor = meio;
            p = peri;
          }
        }
      }
    }
  }

  return menor;
}
double Ponto::calculaDist(Ponto &a, Ponto &b) {
  double dx = double(a.x - b.x);
  double dy = double(a.y - b.y);
  return sqrt(dx * dx + dy * dy);
}
/*




double Ponto::calculaP(Ponto a, Ponto b, Ponto c) {
  return 0.0;
}
*/