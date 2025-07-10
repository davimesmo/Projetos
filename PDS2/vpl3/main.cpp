#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Empresa.hpp"
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;
int main(){
    Empresa empresa;
    char entrada;
    cin >> entrada;
    while(entrada != 'F'){
        if(entrada == 'C'){
            string placa;
            int capMax;
            cin >> placa;
            cin >> capMax;
            if(empresa.adcionar_onibus(placa, capMax) == nullptr){
                cout << "ERRO : onibus repetido" << endl;
            }else{
                cout << "novo onibus cadastrado" << endl;
            }       
            
        }else if(entrada == 'S'){
            string placa;
            int num;
            cin >> placa >> num;
            Onibus* buzao = empresa.busca_onibus(placa);
            if (buzao == nullptr) {
                cout << "ERRO : onibus inexistente" << endl;
            } else{
                buzao ->subir_passageiros(num);
            }
        }else if(entrada == 'D'){
            string placa;
            int num;
            cin >> placa >> num;
            Onibus* buzao = empresa.busca_onibus(placa);
            if (buzao == nullptr) {
                cout << "ERRO : onibus inexistente" << endl;
            } else{
                buzao ->descer_passageiros(num);
            }
        }else if(entrada == 'T'){
            string placa1, placa2;
            int num;
            cin >> placa1 >> placa2 >> num;
            Onibus* buzao1 = empresa.busca_onibus(placa1);
            Onibus* buzao2 = empresa.busca_onibus(placa2);
            if(buzao1 == nullptr || buzao2 == nullptr){
                cout << "ERRO : onibus inexistente" << endl;
            }else{
                buzao1->transfere_passageiros(buzao2, num);
            }
        }else if(entrada == 'I'){
            empresa.imprimir_estado();
        }
       cin >> entrada; 
    }
    
    
    
    
    
    
    return 0;

}