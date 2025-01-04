#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
static const size_t npos = -1;
int main(int argc, char const *argv[])
{
    ifstream in("palavras.txt", fstream::in);
    if (!in.is_open())
    {
        return 1;
    }
    string line;
    getline(in, line);
    int palavras = stoi(line);
    palavras+=1;
    string *stringues;
    stringues = new string[palavras];
    int cont = 0;
    while (in >> line) {
        stringues[cont] = line;
        cont++;
    }
    int input = 0;
    cin >>input;
    input-=1;
    string chave;
    chave = stringues[input];
    string entrada, retorno, lixo;
    retorno = "*****";
    cont =0;
    int aux = 0;
    while(cont<5){
        cin >> entrada;
    
        for(int j=0; j<5; j++){
            if(entrada[j] == chave[j]){
                retorno[j] = entrada[j];
            }else if(chave.find(entrada[j]) != string::npos){
                
                retorno[j] = tolower(entrada[j]);
            }else{
                retorno[j] = '*';
                if(lixo.find(entrada[j]) == string::npos){
                    lixo = lixo + entrada[j];
                }
            } 
        }
        
        cout << retorno << " (" << lixo << ") " << endl;
        cont++;
        
        if(entrada == chave){
            
            cout << "GANHOU!" << endl;
            aux = 1;
            break;
        }
    }
    if(aux == 0){
            cout << "PERDEU! " << chave;
        }
    in.close();
    return 0;
}
