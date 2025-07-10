#include <iostream>
#include <vector>
using namespace std;
/*
Respostas:
 - (obs. acesse a posição do vetor usando o método at( ). O que acontece caso o acesso for feito usando [ ]?):
 O comportamento quando é [] e uma posição inválida é acessada é undefined
 - Faça diferentes testes e observe as saídas. As exceções estão sendo tratadas de forma adequada?
 Parcialmente. Acredito que as exceções poderiam ser mais robustas, por exemplo, e se o usuário entrar com um
 valor não numérico na entrada? O código simplesmente crasha. Acho que poderia ter um catch do tipo (...) para
 casos gerais também.
*/
class NegativeResultException : public std::exception{
    public:
    int atributo;
    NegativeResultException(int num) : atributo(num){}
    const char* what() const throw() override{
        return "Erro: Resultado Negativo.";
    }
};
int main(int argc, char const *argv[]){
    vector<int> vetor = {-20, -10, 0, 10, 20};
    try{
        int ent;
        cin >> ent;
        //não explicitei o throw out of range pq .at() já faz isso caso seja uma posição inválida
        //em troca, o what não fica como eu quero, mas é um trade-off válido?
        //mas caso fosse fazer era só um if verificando se ent < 0 || ent >= .size() e um throw oor no if
        if(vetor.at(ent) < 0){
            throw NegativeResultException(vetor.at(ent));
        }else if(vetor.at(ent) == 0){
            throw logic_error("Erro: O resultado nao deve ser zero.");
        }else{
            cout << vetor.at(ent) << endl;
        }
    }catch(out_of_range& e){
        cerr << "Erro: Parametro invalido." << endl;
    }catch(logic_error& e){
        cerr << e.what() << endl;
    }catch(NegativeResultException& e){
        cerr << e.what() << endl;
        cerr << e.atributo << endl;
    }
    return 0;
}
