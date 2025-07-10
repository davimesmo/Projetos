#ifndef LISTA_H
#define LISTA_H
class Node{
    public:
    Node();
    ~Node();
    private:
        Lista *vizinhos;
        Node* prox;
    friend class Lista;

};
class Lista{
    public:
    Lista();
    ~Lista();
    int getItem(int pos);
    void setItem(int item, int pos);
    void insereInicio(int item);
    void insereFinal(int item);
    void inserePosicao(int item, int pos);
    int removeInicio();
    int removeFinal();
    int removePosicao(int pos);
    void imprime();
    void limpa();
    private:
    Node* head;
    Node* tail;
    int tamanho;
    Node* posiciona(int pos);
};

#endif
