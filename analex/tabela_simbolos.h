#ifndef TABELA_SIMBOLOS_H
#define TABELA_SIMBOLOS_H

#include <string>
#include <vector>

#define TAMANHO 503

typedef union {
    int valor_int;
    float valor_float;
} vlr;

typedef struct {
    std::string lexema;
    int tipo;
    vlr valor;
    std::string tipo_dado;
} registro;

struct hash_node {
    std::string chave;
    registro valor;
    hash_node *proximo;

    hash_node(const std::string &chave,const registro &valor) : chave(chave), valor(valor), proximo(nullptr) {}
};

class hash_table {
    std::vector<hash_node *> tabela;

public:
    hash_table();
    ~hash_table();

    unsigned int hash(const std::string &chave);
    void inserir(const std::string &chave, const registro &valor);
    registro *buscar(const std::string &chave);
    void inicializar();
};

#endif