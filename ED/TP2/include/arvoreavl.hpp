#ifndef ARVOREAVL_H
#define ARVPREAVL_H
struct Node{
    public:
        Node(int dado){}
        void setChave(int valor){this->chave = valor; }
        int getChave(){ return chave;}
        int getAltura(){if(direita == nullptr && esquerda == nullptr ){
            return 0;
        }
        if(direita->getAltura() >= esquerda->getAltura()){
            return 1 + direita->getAltura();
        }else{
            return 1 + esquerda->getAltura();
        }
    }
        int getBalanço(){
            balanço = direita->getAltura(); - esquerda->getAltura();
        }
        Node* inserir(Node* raiz, int dado){
            Node *novo = new Node(dado);
            if(dado > raiz->chave){
                
                raiz->direita = inserir(direita, dado);
                if(raiz->direita->getBalanço() == -2){
                    if(dado > raiz->direita->getChave()){
                        raiz->direita = raiz->direita->rotacaoDD();
                    }else{
                        raiz->direita = raiz->direita->rotacaoDE();
                    }
                }
            
            }else if(dado < raiz->chave){
                raiz->esquerda = inserir(raiz->esquerda, dado);
                if(raiz->esquerda->getBalanço() == 2){
                    if(dado < raiz->esquerda->getChave()){
                        raiz = raiz->esquerda->rotacaoEE();
                    }else{
                        raiz = raiz->esquerda->rotacaoED();
                    }
                }
            }
            
        }
Node* rotacaoDD(){
    
    
    
    return nullptr;}

Node* rotacaoDE(){return nullptr;}
Node* rotacaoEE(){return nullptr;}
Node* rotacaoED(){return nullptr;}
    private:
    int chave;
    int altura;
    int balanço;
    Node* pai;
    Node* direita;
    Node* esquerda;
};

#endif