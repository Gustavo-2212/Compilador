#include "tabela_simbolos.h"
#include <iostream>

hash_table::hash_table() : tabela(TAMANHO, nullptr) {}

hash_table::~hash_table() {
    for(auto node : tabela) {
        while(node != nullptr) {
            hash_node *temp = node;
            node = node->proximo;
            delete temp;
        }
    }
}

unsigned int hash_table::hash(const std::string &chave) {
    unsigned long int hash = 0;
    for(char c : chave) {
        hash = hash * 37 + c;
    }

    return hash % TAMANHO;
}

void hash_table::inserir(const std::string &chave, const registro &valor) {
    unsigned int indice = hash(chave);
    hash_node *node = new hash_node(chave, valor);
    node->proximo = tabela[indice];
    tabela[indice] = node;
}

registro *hash_table::buscar(const std::string &chave) {
    unsigned int indice = hash(chave);
    hash_node *node = tabela[indice];
    while(node != nullptr) {
        if(node->chave == chave) {
            return &node->valor;
        }
    }

    return nullptr;
}
