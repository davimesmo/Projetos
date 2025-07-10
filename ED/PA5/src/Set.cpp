#include "../include/Set.hpp"
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;


StringSet::StringSet(int tamanho) : tamanhoOriginal(tamanho), tamanhoTabela(tamanho), tamanhoConjunto(0){
    tabela = new ElementoTabela[tamanho];
    for(int i = 0; i < tamanho; i++){
      tabela[i].vazio = true;
      tabela[i].retirada = false;

    }
}
StringSet::~StringSet(){
    delete[] tabela;
}

void StringSet::Inserir(string s) {
  if (((float)tamanhoConjunto / tamanhoTabela) >= 0.8) {
        Resize(tamanhoTabela * 2);
    }
  if(this->Pertence(s)) return;
  int pos = Hash(s);
  int i = 0;
  while (i < tamanhoTabela &&
           tabela[(pos + i) % tamanhoTabela].vazio == false &&
           tabela[(pos + i) % tamanhoTabela].retirada == false) {
        i++;
    }
  if (i == tamanhoTabela) {
        Resize(tamanhoTabela * 2);
        Inserir(s); 
        return;
    }
  int final = (pos + i) % tamanhoTabela;
  tabela[final].dado = s;
  tabela[final].vazio = false;
  tabela[final].retirada = false; 
  tamanhoConjunto++; 
}

void StringSet::Remover(string s) {
   int posIni = Hash(s);
    for (int i = 0; i < tamanhoTabela; i++) {
        int pos = (posIni + i) % tamanhoTabela;
        if (tabela[pos].vazio) {
            return; 
        }

        if (tabela[pos].dado == s && tabela[pos].retirada == false) {
            tabela[pos].retirada = true;
            tamanhoConjunto--;
            return;
        }
    }

}

bool StringSet::Pertence(string s) {
      int posIni = Hash(s);
    for (int i = 0; i < tamanhoTabela; i++) {
        int pos = (posIni + i) % tamanhoTabela;
        if (tabela[pos].vazio) {
            return false;
        }
        if (tabela[pos].retirada == false && tabela[pos].dado == s) {
            return true; 
        }
    }
    return false;

}

StringSet *StringSet::Intersecao(StringSet *S) {
  StringSet* resultado;
  if(this->tamanhoConjunto <= S->tamanhoConjunto){
    resultado = new StringSet(this->tamanhoConjunto);
  }else{
    resultado = new StringSet(S->tamanhoConjunto);
  }
   for (int i = 0; i < this->tamanhoTabela; i++) {
        if (this->tabela[i].vazio == false && this->tabela[i].retirada == false) {
            string elementoAtual = this->tabela[i].dado;
            if (S->Pertence(elementoAtual)) {
                resultado->Inserir(elementoAtual);
            }
        }
    }
  return resultado;
}

StringSet *StringSet::Uniao(StringSet *S) {
  StringSet *resultado = new StringSet(this->tamanhoConjunto + S->tamanhoConjunto);
  for (int i = 0; i < this->tamanhoTabela; i++) {
        if (this->tabela[i].vazio == false && this->tabela[i].retirada == false) {
            resultado->Inserir(this->tabela[i].dado);
        }
    }
  for (int i = 0; i < S->tamanhoTabela; i++) {
        if (S->tabela[i].vazio == false && S->tabela[i].retirada == false) {
            resultado->Inserir(S->tabela[i].dado);
        }
    }  
  return resultado;
}

StringSet *StringSet::DiferencaSimetrica(StringSet *S) {
   StringSet* resultado = new StringSet(this->tamanhoConjunto + S->tamanhoConjunto);
  for (int i = 0; i < this->tamanhoTabela; i++) {
        if (this->tabela[i].vazio == false && this->tabela[i].retirada == false) {
            string elementoAtual = this->tabela[i].dado;
            if (!S->Pertence(elementoAtual)) {
                resultado->Inserir(elementoAtual);
            }
        }
    }
    for (int i = 0; i < S->tamanhoTabela; i++) {
        if (S->tabela[i].vazio == false && S->tabela[i].retirada == false) {
            string elementoAtual = S->tabela[i].dado;
            if (!this->Pertence(elementoAtual)) {
                resultado->Inserir(elementoAtual);
            }
        }
    }
   return resultado;
}

void StringSet::Imprimir() {
  for(int i = 0; i< tamanhoTabela; i++){
    if (tabela[i].vazio == false && tabela[i].retirada == false) {

            std::cout << tabela[i].dado << std::endl;
        }
  }
}

int StringSet::Hash(string s) {
  int hash;
  long long soma = 0;
  int pos = 1;
  for(char c : s){
    soma += c * pos;
    pos++;
  }
  hash = soma % tamanhoTabela;

  return hash;
}

void StringSet::Rehash(int pos) {

}

void StringSet::Resize(size_t tamanho) {
  ElementoTabela* antiga = tabela;
  int tamAnt = tamanhoTabela;
  tamanhoTabela = tamanho;
  tamanhoConjunto = 0;
  tabela = new ElementoTabela[tamanho];
  for(int i = 0; i < tamanho; i++){
      tabela[i].vazio = true;
      tabela[i].retirada = false;

    }
  for(int j = 0; j<tamAnt; j++){
    if(antiga[j].vazio == false && antiga[j].retirada == false){
      Inserir(antiga[j].dado);
    }

  }
  delete[] antiga;
}