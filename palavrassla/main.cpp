#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <algorithm>
#include <cctype>
using namespace std;
void limpaPalavra(string &word){
     word.erase(std::remove_if(word.begin(), word.end(), [](unsigned char c) {
        return !std::isalnum(c);
    }), word.end());
}
int main(int argc, char const *argv[])
{
    string nomeArquivo;
    cin >> nomeArquivo;
    ifstream in(nomeArquivo, fstream::in);
    if(!in.is_open())
        return 1;
    string s;
    string str("   ");    
    map<string, int> contPal;
    while(in >> s){
       /*size_t i = 0;
        size_t len = s.length();
        while(i < len){
             if (!isalnum(s[i])){
            
            s.erase(i,1);
            len--;
        }else{
            i++;}
        }*/
       limpaPalavra(s);
    
    transform(s.begin(), s.end(), s.begin(),::tolower);
    if(!s.empty()){
        contPal[s]++;
    }}
    for(const auto &[s, cont] : contPal){
        cout << s << " " << cont << endl;
    }
    return 0;
}
