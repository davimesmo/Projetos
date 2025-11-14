#ifndef PONTO_HPP
#define PONTO_HPP

#include <iomanip>
#include <sstream>
#include <iostream>
#include <vector>
#include <list>
struct Triangulo{
    int x, y, z;
    double perimetro;  
    Triangulo() : x(0), y(0), z(0), perimetro(0){}
    Triangulo(const Triangulo&outro){
        this->x = outro.x;
        this->y = outro.y;
        this->z = outro.z;
        this->perimetro = outro.perimetro;
    }  
    Triangulo& operator=(const Triangulo &outro) {
    if (this != &outro) {
        x = outro.x;
        y = outro.y;
        z = outro.z;
        perimetro = outro.perimetro;
    }
    return *this;
}
};
class Ponto{
    public:    
        Ponto(int x, int y, int id);
        ~Ponto();
        static double calculaDist(Ponto& a, Ponto& b);
        static Triangulo menorTri(std::vector<Ponto> &vetor, size_t l, size_t r);
        //double calculaP(Ponto a, Ponto b, Ponto c);
        
        int x, y, id;
};
#endif