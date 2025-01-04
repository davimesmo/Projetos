#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
using namespace std;

class Ponto{
    private:
    int x, y;
    public:
    Ponto(int x, int y){
        this->x = x;
        this->y = y;
    }
    int getCordX(){
        return x;
    }
    int getCordY(){
        return y;
    }
};

class FiguraGeometrica{
    protected:
    Ponto *centro;
    public:
    FiguraGeometrica(int x, int y){
        centro = new Ponto(x, y);
    }
    virtual void Desenha() const {
        int x, y;
        x = centro->getCordX();
        y = centro ->getCordY();
        cout  << x << " " << y;
    }
    virtual float CalculaArea() const = 0;
    virtual ~FiguraGeometrica() {
    delete centro;
    }
};
class Circulo : public FiguraGeometrica{
    private:
    int raio; 
    public: 
    Circulo(int x, int y, int raio) : FiguraGeometrica(x, y){
        this->raio = raio;
    }
    void Desenha()const override{
        FiguraGeometrica::Desenha();
        cout << " CIRCULO" << endl;
        
    }
    float CalculaArea() const override{
        return M_PI * raio * raio;
    }
};

class Retangulo : public FiguraGeometrica{
    private:
    int  lado1, lado2;
    public:
    Retangulo(int x, int y, int l1, int l2) : FiguraGeometrica(x, y){    
        this->lado1 = l1;
        this->lado2 = l2;
 
    }
    void Desenha()const override{
        FiguraGeometrica::Desenha();
        cout << " RETANGULO" << endl;
        
    }
    float CalculaArea() const override{
        return lado1 * lado2;
    }

};
class Triangulo : public FiguraGeometrica{
    private:
    int base, altura;
    public:
    Triangulo(int x, int y, int base, int altura):FiguraGeometrica(x, y){
        this->base = base;
        this->altura = altura;
    }
    void Desenha()const override{
        FiguraGeometrica::Desenha();
        cout << " TRIANGULO" << endl;
        
    }
    float CalculaArea() const override{
        return (base * altura)/2;
    }
};
int main(int argc, char const *argv[]){
    char entrada = '0';
    vector<FiguraGeometrica*> vetor;
    int c1 = 0, c2 = 0, l1 = 0, l2 = 0;
    while (entrada != 'E'){
        cin >> entrada;
        if(entrada == 'R'){
            
            cin >> c1 >> c2 >> l1 >> l2;
            vetor.push_back(new Retangulo(c1, c2, l1, l2));
        }else if (entrada == 'C'){
            cin >> c1 >> c2 >> l1;
            vetor.push_back(new Circulo(c1, c2, l1));
        }else if (entrada == 'T'){
            cin >> c1 >> c2 >> l1 >> l2;
            vetor.push_back(new Triangulo(c1, c2, l1, l2));
        }else if (entrada  == 'D'){
            for(int i = 0; i < vetor.size(); i++){
            vetor[i]->Desenha();
            }
        }else if( entrada == 'A'){
            float soma = 0.0;
            for (int k =0; k < vetor.size(); k++){
                soma += vetor[k]->CalculaArea();
            }
            cout << fixed << setprecision(2) << soma << endl;
        }
    }
    for (auto figura : vetor) {
    delete figura;
    }
    
    return 0;
}
