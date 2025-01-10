#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;
template <typename T> class Vetor{
    private:
    T* array;
    int size;
    int capacidade;
    public:
    Vetor(int n);
    Vetor(Vetor& outro);
    void AdicionaElemento(T elem);
    T GetElemento(int i);
    void SetElemento(int i, T elem);
    void Imprime();
    ~Vetor();
};

template <typename T> Vetor<T>::Vetor(int n){
    this->array = new T[n];
    this->capacidade = n;
    this->size =0;
}
template <typename T> Vetor<T>::Vetor(Vetor& outro){
    this->size = outro.size;
    this->capacidade = outro.capacidade;
    this->array = new T[capacidade];
    for(int i = 0; i<size; i++){
        this->array[i] = outro.array[i];
    }
}
template <typename T> void Vetor<T>::AdicionaElemento(T elem){
    T* arraytemp = new T[capacidade + 1];
    for(int i =0; i < size; i++){
        arraytemp[i] = array[i];
    }
    delete[] array;
    array = arraytemp;
    array[size] = elem;
    size++;
    capacidade++;   
}
template <typename T> T Vetor<T>::GetElemento(int i){
    
    return array[i];
}
template <typename T> void Vetor<T>::SetElemento(int i, T elem){
    array[i] = elem;
}
template <typename T> Vetor<T>::~Vetor() {
    delete[] array;
}
template <typename T> void Vetor<T>::Imprime(){
    for(int i = 0; i < size; i++){
        cout << array[i] << " ";
    }
    cout << endl;
}