#include "first_follow.h"
#include "../analex/analex.h"

vector<set<int>> first;
vector<set<int>> follow;

bool token_in_first(int producao, int token) {
    return (first[producao].find(token) != first[producao].end());
}

bool token_in_follow(int producao, int token) {
    return (follow[producao].find(token) != follow[producao].end());
}

void calcula_first_follow(void) {
    first.push_back({TOK_MAIN});
    first.push_back({TOK_BEGIN});
    first.push_back({EPSILON, TOK_INT, TOK_FLOAT, TOK_CHAR});
    first.push_back({TOK_INT, TOK_FLOAT, TOK_CHAR});
    first.push_back({EPSILON, TOK_INT, TOK_FLOAT, TOK_CHAR});
    first.push_back({TOK_INT, TOK_FLOAT, TOK_CHAR});
    first.push_back({TOK_INT, TOK_FLOAT, TOK_CHAR});
    first.push_back({TOK_ID});
    first.push_back({EPSILON, TOK_VIRG});
    first.push_back({TOK_IF});
    first.push_back({EPSILON, TOK_ELSE});
    first.push_back({TOK_WHILE, TOK_REPEAT});
    first.push_back({TOK_WHILE});
    first.push_back({TOK_REPEAT});
    first.push_back({TOK_ID});
    first.push_back({TOK_ID, TOK_PAR_ESQ, TOK_SUB, TOK_CONST_NUM, TOK_CONST_CHAR});
    first.push_back({TOK_EQ, TOK_NE, TOK_LT, TOK_GT, TOK_LE, TOK_GE});
    first.push_back({TOK_ID, TOK_SUB, TOK_PAR_ESQ, TOK_CONST_NUM, TOK_CONST_CHAR});
    first.push_back({EPSILON, TOK_SUM, TOK_SUB});
    first.push_back({TOK_ID, TOK_PAR_ESQ, TOK_SUB, TOK_CONST_NUM, TOK_CONST_CHAR});
    first.push_back({EPSILON, TOK_MUL, TOK_DIV});
    first.push_back({TOK_ID, TOK_PAR_ESQ, TOK_SUB, TOK_CONST_NUM, TOK_CONST_CHAR});
    first.push_back({EPSILON, TOK_EXP});
    first.push_back({TOK_ID, TOK_PAR_ESQ, TOK_SUB, TOK_CONST_NUM, TOK_CONST_CHAR});
    first.push_back({TOK_CONST_NUM, TOK_CONST_CHAR});
    first.push_back({TOK_ID, TOK_WHILE, TOK_REPEAT, TOK_IF});
    first.push_back({EPSILON, TOK_ID, TOK_WHILE, TOK_REPEAT, TOK_IF});
    first.push_back({TOK_ID, TOK_WHILE, TOK_REPEAT, TOK_IF});
    first.push_back({TOK_BEGIN, TOK_ID, TOK_WHILE, TOK_REPEAT, TOK_IF});

    follow.push_back({TOK_FIM_ARQ});
    follow.push_back({TOK_FIM_ARQ, TOK_UNTIL, TOK_ELSE, TOK_ID, TOK_WHILE, TOK_REPEAT, TOK_IF,TOK_END});
    follow.push_back({TOK_ID, TOK_WHILE, TOK_REPEAT, TOK_IF});
    follow.push_back({TOK_ID, TOK_WHILE, TOK_REPEAT, TOK_IF});
    follow.push_back({TOK_ID, TOK_WHILE, TOK_REPEAT, TOK_IF});
    follow.push_back({TOK_INT, TOK_FLOAT, TOK_CHAR, TOK_ID, TOK_WHILE, TOK_REPEAT, TOK_IF});
    follow.push_back({TOK_DOIS_PONTO});
    follow.push_back({TOK_PONTO_VIRG});
    follow.push_back({TOK_PONTO_VIRG});
    follow.push_back({TOK_ID, TOK_WHILE, TOK_REPEAT, TOK_IF, TOK_END, TOK_UNTIL, TOK_ELSE});
    follow.push_back({TOK_ID, TOK_WHILE, TOK_REPEAT, TOK_IF, TOK_END, TOK_UNTIL, TOK_ELSE});
    follow.push_back({TOK_ID, TOK_WHILE, TOK_REPEAT, TOK_IF, TOK_END, TOK_UNTIL, TOK_ELSE});
    follow.push_back({TOK_ID, TOK_WHILE, TOK_REPEAT, TOK_IF, TOK_END, TOK_UNTIL, TOK_ELSE});
    follow.push_back({TOK_ID, TOK_WHILE, TOK_REPEAT, TOK_IF, TOK_END, TOK_UNTIL, TOK_ELSE});
    follow.push_back({TOK_ID, TOK_WHILE, TOK_REPEAT, TOK_IF, TOK_END, TOK_UNTIL, TOK_ELSE});
    follow.push_back({TOK_PAR_DIR});
    follow.push_back({TOK_ID, TOK_PAR_ESQ, TOK_SUB, TOK_CONST_NUM, TOK_CONST_CHAR});
    follow.push_back({TOK_OPREL, TOK_EQ, TOK_NE, TOK_LT, TOK_GT, TOK_LE, TOK_GE, TOK_PAR_DIR, TOK_PONTO_VIRG});
    follow.push_back({TOK_OPREL, TOK_EQ, TOK_NE, TOK_LT, TOK_GT, TOK_LE, TOK_GE, TOK_PAR_DIR, TOK_PONTO_VIRG});
    follow.push_back({TOK_SUM, TOK_SUB, TOK_OPREL, TOK_EQ, TOK_NE, TOK_LT, TOK_GT, TOK_LE, TOK_GE, TOK_PAR_DIR, TOK_PONTO_VIRG});
    follow.push_back({TOK_SUM, TOK_SUB, TOK_OPREL, TOK_EQ, TOK_NE, TOK_LT, TOK_GT, TOK_LE, TOK_GE, TOK_PAR_DIR, TOK_PONTO_VIRG});
    follow.push_back({TOK_MUL, TOK_DIV, TOK_SUM, TOK_SUB, TOK_OPREL, TOK_EQ, TOK_NE, TOK_LT, TOK_GT, TOK_LE, TOK_GE, TOK_PAR_DIR, TOK_PONTO_VIRG});
    follow.push_back({TOK_MUL, TOK_DIV, TOK_SUM, TOK_SUB, TOK_OPREL, TOK_EQ, TOK_NE, TOK_LT, TOK_GT, TOK_LE, TOK_GE, TOK_PAR_DIR, TOK_PONTO_VIRG});
    follow.push_back({TOK_EXP, TOK_MUL, TOK_DIV, TOK_SUM, TOK_SUB, TOK_OPREL, TOK_EQ, TOK_NE, TOK_LT, TOK_GT, TOK_LE, TOK_GE, TOK_PAR_DIR, TOK_PONTO_VIRG});
    follow.push_back({TOK_EXP, TOK_MUL, TOK_DIV, TOK_SUM, TOK_SUB, TOK_OPREL, TOK_EQ, TOK_NE, TOK_LT, TOK_GT, TOK_LE, TOK_GE, TOK_PAR_DIR, TOK_PONTO_VIRG});
    follow.push_back({TOK_END});
    follow.push_back({TOK_END});
    follow.push_back({TOK_ID, TOK_WHILE, TOK_REPEAT, TOK_IF, TOK_END});
    follow.push_back({TOK_UNTIL, TOK_ELSE, TOK_ID, TOK_WHILE, TOK_REPEAT, TOK_IF, TOK_END});
}