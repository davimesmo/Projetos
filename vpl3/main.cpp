#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Onibus.hpp"
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;
int main(){
    char entrada;
    cin >> entrada;
    while(entrada != 'F'){
        if(entrada == 'C'){
            string placa;
            int capMax;
            cin >> placa;
            cin >> capMax;
            Onibus* o1 = new Onibus(placa, capMax);
            Onibus o2 = Onibus("abcd", 10);
            o1->subir_passageiros(10);
            o1->imprimir_estado();
            o1->transfere_passageiros(&o2, 10);
            o1 -> imprimir_estado();
            o2.imprimir_estado();
            cin >> entrada;
        }else if(entrada == 'F'){
            break;
        }
    }
    
    
    
    
    
    
    return 0;

}