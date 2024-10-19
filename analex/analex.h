#ifndef ANALEX_H
#define ANALEX_H

#include <cmath>

#include "tabela_simbolos.h"
#include "scanner.h"
#include "../gera_tabela_dt/tabela.h"

enum {
    TOK_BEGIN = 0,
    TOK_END,
    TOK_MAIN,
    TOK_IF,
    TOK_THEN,
    TOK_ELSE,
    TOK_DO,
    TOK_WHILE,
    TOK_REPEAT,
    TOK_CHAR,
    TOK_INT,
    TOK_FLOAT,
    TOK_UNTIL,
    TOK_OPREL,
    TOK_ID,
    TOK_PAR_ESQ,
    TOK_PAR_DIR,
    TOK_PONTO_VIRG,
    TOK_VIRG,
    TOK_DOIS_PONTO,
    TOK_ATRIB,
    TOK_SUM,
    TOK_SUB,
    TOK_DIV,
    TOK_MUL,
    TOK_EXP,
    TOK_CONST_CHAR,
    TOK_CONST_NUM,
    ERRO,
    TOK_FIM_ARQ,
};

extern std::string Lexema;

typedef struct {
    int tipo;
    std::string atributo;
    int linha;
    int coluna;
} Token;

extern Token tok;

extern Token *token(int tipo, const std::string &atributo, int linha, int coluna);

extern Token *retorna_token();

extern std::string string_tipo(int tipo);

extern bool prepara_scanner(const std::string &filename);

extern void prepara_tabela_transicao(void);

extern void inicializar_tabela_simbolos(void);
extern void setID(const std::string &lexema);
extern void setInt(const std::string &lexema);
extern void setFloat(const std::string &lexema);
extern void setChar(const std::string &lexema);
extern void setExp(const std::string &lexema);
extern void erro(void);
extern void restart(void);

extern registro reg[];

#endif