#ifndef LISTA_INTEIROS_HPP
#define LISTA_INTEIROS_HPP
class No{
    public:
    No() : valor(-1), prox(nullptr){}
    int getVal() {return valor;};
    No* getProx(){return prox;};
    private:
    int valor;
    No* prox;
    friend class ListaEncadeada;
};
class ListaEncadeada{
    public:
    ListaEncadeada();
    ~ListaEncadeada();
    int getItem(int pos);
    bool pesquisa(int val);
    void setItem(int val, int pos);
    void insereFinal(int val);
    void inserePosicao(int item, int pos);
    void imprime();
    void limpa();
    int getTam();
    No* getHead();
    private:
    No *head;
    No* tail;
    int tamanho;   
    No* posiciona(int pos);
    
};
#endif