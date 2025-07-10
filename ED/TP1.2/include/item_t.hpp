#ifndef ITEM_T_HPP // Se for em um novo header
#define ITEM_T_HPP

#include <cstring> // Para strcmp, strcpy
#include <iostream> // Para std::ostream (operador<<)

// Definições default caso não sejam passadas pelo compilador
// Para testes locais, você pode querer descomentar ou definir via compilação
#ifndef KEYSZ
#define KEYSZ 10 // Tamanho padrão da chave
#endif
#ifndef PLSZ
#define PLSZ 20  // Tamanho padrão do payload
#endif

struct item_t {
    char key[KEYSZ];
    char payload[PLSZ];

    // Construtor padrão (opcional, mas bom para inicialização)
    item_t() {
        if (KEYSZ > 0) key[0] = '\0';
        if (PLSZ > 0) payload[0] = '\0';
    }

    // Construtor para facilitar a criação (opcional)
    item_t(const char* k, const char* p) {
        strncpy(key, k, KEYSZ - 1);
        key[KEYSZ - 1] = '\0'; // Garante terminação nula
        strncpy(payload, p, PLSZ - 1);
        payload[PLSZ - 1] = '\0'; // Garante terminação nula
    }

    // Operadores de comparação (essenciais para os algoritmos de ordenação)
    // O Quicksort e o Insertion Sort no seu código usam principalmente '<'.
    // O mediana3 usa '<='.
    // Vamos definir todos para completude, baseados na 'key'.

    bool operator<(const item_t& other) const {
        return strcmp(key, other.key) < 0;
    }

    bool operator<=(const item_t& other) const {
        return strcmp(key, other.key) <= 0;
    }

    bool operator>(const item_t& other) const {
        return strcmp(key, other.key) > 0;
    }

    bool operator>=(const item_t& other) const {
        return strcmp(key, other.key) >= 0;
    }

    bool operator==(const item_t& other) const {
        return strcmp(key, other.key) == 0;
    }

    bool operator!=(const item_t& other) const {
        return strcmp(key, other.key) != 0;
    }

    // Operador de atribuição (o compilador gera um padrão que funciona para esta struct,
    // mas se tivesse ponteiros, precisaria de um customizado - não é o caso aqui)
    // item_t& operator=(const item_t& other) {
    //     if (this != &other) {
    //         strncpy(key, other.key, KEYSZ -1);
    //         key[KEYSZ-1] = '\0';
    //         strncpy(payload, other.payload, PLSZ-1);
    //         payload[PLSZ-1] = '\0';
    //     }
    //     return *this;
    // }

    // Para facilitar a impressão (opcional, mas útil para debug)
    friend std::ostream& operator<<(std::ostream& os, const item_t& item) {
        os << "Key: " << item.key << ", Payload: " << item.payload;
        return os;
    }
};

#endif 