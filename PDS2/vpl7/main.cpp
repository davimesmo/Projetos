
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <list>
int estagio;
    char axioma[] = "F+F+F+F";
    char regra[] = "F+F-F-FFF+F+F-F";
using namespace std;
class Lista{
    private:
    int id;
    static int cont;
    static int autocont;
    public:
    
    Lista(){
        id = autocont;
        autocont++;
        cont++;
    }
    Lista(int y){
        this->id = y;
        cont++;
    }
    ~Lista(){
        cont--;
    }
    int getId(){
        return this -> id;
    }
    Lista* getEnde(){
        return this;
    }
    static int getNumObjetos() {
        return cont;
    }
};
int Lista::cont = 0;
int Lista::autocont = 1;




int main(int argc, char const *argv[]){
   list<Lista*> lista;
   int uai = 1;
   char entrada;
   int n;
   while(uai = 1){
    cin >> entrada;
    if(entrada == 'A'){
        lista.push_back(new Lista());
        cout << lista.back()->getId() << " " << lista.back()->getEnde() << endl;
        
    }else if(entrada == 'C'){
        cin >> n;
        if(n<0){
        lista.push_front(new Lista(n));
        cout << lista.front()->getId() << " " << lista.front()->getEnde() << endl;
        }
        else{
            cout << "ERRO\n"; }
        
    }else if(entrada == 'R'){
        if(!lista.empty()){
        Lista* objeto = lista.front();
        lista.pop_front();
        cout << objeto->getId() << " " << objeto->getEnde() << endl;
        delete objeto;
        }else{
            cout << "ERRO\n";
        }
    }else if(entrada == 'N'){
        cout << Lista::getNumObjetos() << endl;
    }else if(entrada == 'P'){
        int indice;
        cin >> indice;
        if (indice < 1 || indice > static_cast<int>(lista.size())) {
            cout << "ERRO" << endl;
        } else {
            auto it = lista.begin();
            advance(it, indice - 1);
            cout << (*it)->getId() << " " << (*it)->getEnde() << endl;
            }
    }else if(entrada == 'L'){
        for (const auto& objeto : lista) {
            cout << objeto->getId() << " " << objeto->getEnde() << endl;
            }
    }else if(entrada == 'E'){
        break;
    }
   }

    return 0;
}
