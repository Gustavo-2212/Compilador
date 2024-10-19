#ifndef FIRST_FOLLOW_H
#define FIRST_FOLLOW_H

#include <vector>
#include <set>

using namespace std;

#define EPSILON -1

enum {
    TOK_EQ = 30,
    TOK_NE,
    TOK_LT,
    TOK_GT,
    TOK_LE,
    TOK_GE,
};

extern void calcula_first_follow(void);
extern bool token_in_first(int producao, int token);
extern bool token_in_follow(int producao, int token);

extern vector<set<int>> first;
extern vector<set<int>> follow;

enum {
    PROGRAMA = 0,
    BLOCO,
    DECVAROPT,
    DECVARS,
    DECVARSL,
    DECVAR,
    TIPO,
    IDS,
    IDSL,
    SELECAO,
    ELSEOPT,
    REPETICAO,
    REPETICAO_WHILE,
    REPETICAO_REPEAT,
    ATRIBUICAO,
    CONDICAO,
    OPREL,
    EXPR,
    EXPRL,
    TERMO,
    TERMOL,
    FATOR,
    FATORL,
    POT,
    CONSTANTE,
    SEQCOM,
    SEQCOML,
    BLOCO_OU_COMANDO,
    COMANDO,
};

#endif