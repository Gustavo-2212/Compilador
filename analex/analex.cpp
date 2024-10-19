#include <iostream>

#include "analex.h"

registro reg[] = {
    { .lexema = "begin", .tipo = TOK_BEGIN, .tipo_dado = "" },
    { .lexema = "end", .tipo = TOK_END, .tipo_dado = "" },
    { .lexema = "main", .tipo = TOK_MAIN, .tipo_dado = "" },
    { .lexema = "if", .tipo = TOK_IF, .tipo_dado = "" },
    { .lexema = "then", .tipo = TOK_THEN, .tipo_dado = "" },
    { .lexema = "else", .tipo = TOK_ELSE, .tipo_dado = "" },
    { .lexema = "do", .tipo = TOK_DO, .tipo_dado = "" },
    { .lexema = "while", .tipo = TOK_WHILE, .tipo_dado = "" },
    { .lexema = "repeat", .tipo = TOK_REPEAT, .tipo_dado = "" },
    { .lexema = "char", .tipo = TOK_CHAR, .tipo_dado = "" },
    { .lexema = "int", .tipo = TOK_INT, .tipo_dado = "" },
    { .lexema = "float", .tipo = TOK_FLOAT, .tipo_dado = "" }
};

std::string Lexema;

Token tok;

hash_table tabela_simbolos;

Token *token(int tipo, const std::string &atributo, int linha, int coluna) {
    tok.tipo = tipo;
    tok.atributo = atributo;
    tok.linha = linha;
    tok.coluna = coluna;

    return &tok;
}

bool prepara_scanner(const std::string &filename) {
    bool inicializado = inicializa_buffers(filename);

    return inicializado;
}

void prepara_tabela_transicao(void) {
    constroi_tabela();
}

void inicializar_tabela_simbolos(void) {
    for(registro r : reg) {
        tabela_simbolos.inserir(r.lexema, r);
    }
}

void setID(const std::string &lexema) {
    registro *reg = tabela_simbolos.buscar(lexema);
    unsigned int indice = tabela_simbolos.hash(lexema);

    if(reg != nullptr) {
        token(TOK_ID, std::to_string(indice), linha, coluna_inicio);
    }
    else {
        registro reg = { .lexema=lexema, .tipo=TOK_ID, .tipo_dado="" };
        tabela_simbolos.inserir(lexema, reg);
        token(TOK_ID, std::to_string(indice), linha, coluna_inicio);
    }
}

void setInt(const std::string &lexema) {
    registro *reg = tabela_simbolos.buscar(lexema);
    unsigned int indice = tabela_simbolos.hash(lexema);
    
    if(reg != nullptr) {
        token(TOK_CONST_NUM, std::to_string(indice), linha, coluna_inicio);
    }
    else {
        vlr valor = { .valor_int=std::stoi(lexema) };

        registro reg = { .lexema=lexema, .tipo=TOK_CONST_NUM, .valor=valor, .tipo_dado="int" };

        tabela_simbolos.inserir(lexema, reg);

        token(TOK_CONST_NUM, std::to_string(indice), linha, coluna_inicio);
    }
}

void setFloat(const std::string &lexema) {
    registro *reg = tabela_simbolos.buscar(lexema);
    unsigned int indice = tabela_simbolos.hash(lexema);

    if(reg != nullptr) {
        token(TOK_CONST_NUM, std::to_string(indice), linha, coluna_inicio);
    }
    else {
        vlr valor = { .valor_float=std::stof(lexema) };

        registro reg = { .lexema=lexema, .tipo=TOK_CONST_NUM, .valor=valor, .tipo_dado="float" };

        tabela_simbolos.inserir(lexema, reg);

        token(TOK_CONST_NUM, std::to_string(indice), linha, coluna_inicio);
    }

}

void setExp(const std::string &lexema) {

    registro *reg = tabela_simbolos.buscar(lexema);
    unsigned int indice = tabela_simbolos.hash(lexema);

    if(reg != nullptr) {
        token(TOK_CONST_NUM, std::to_string(indice), linha, coluna_inicio);
    }
    else {
        std::string parte_nominal;
        std::string parte_expo;
        int i = 0;

        while(lexema[i] != 'E') {
            parte_nominal += lexema[i];
            i++;
        }
        i++;
        while(i < lexema.size()) {
            parte_expo += lexema[i];
            i++;
        }

        float tmp = std::stof(parte_nominal);
        int expo = std::stoi(parte_expo);

        vlr valor = { .valor_float=(float) (tmp * (std::pow(10.0, expo))) };
        registro reg = { .lexema=lexema, .tipo=TOK_CONST_NUM, .valor=valor, .tipo_dado="float" };

        tabela_simbolos.inserir(lexema, reg);

        token(TOK_CONST_NUM, std::to_string(indice), linha, coluna_inicio);
    }
}

void setChar(const std::string &lexema) {
    registro *reg = tabela_simbolos.buscar(lexema);
    unsigned int indice = tabela_simbolos.hash(lexema);

    if(reg != nullptr) {
        token(TOK_CONST_CHAR, std::to_string(indice), linha, coluna_inicio);
    }
    else {
        registro reg = { .lexema=lexema, .tipo=TOK_CONST_CHAR, .tipo_dado="char" };

        tabela_simbolos.inserir(lexema, reg);

        token(TOK_CONST_CHAR, std::to_string(indice), linha, coluna_inicio);
    }
}

void restart() {
    retorna_token();
}

void erro(void) {
    std::cout << "Transição não prevista - token não reconhecido: " << Lexema << ".\n";
    token(ERRO, "-", linha, coluna_inicio);
}

std::string string_tipo(int tipo) {
    std::string tipo_s;
    switch(tipo) {
        case TOK_BEGIN:
            tipo_s = "TOK_BEGIN";
            break;

        case TOK_END:
            tipo_s = "TOK_END";
            break;

        case TOK_MAIN:
            tipo_s = "TOK_MAIN";
            break;

        case TOK_IF:
            tipo_s = "TOK_IF";
            break;

        case TOK_THEN:
            tipo_s = "TOK_THEN";
            break;

        case TOK_ELSE:
            tipo_s = "TOK_ELSE";
            break;

        case TOK_DO:
            tipo_s = "TOK_DO";
            break;

        case TOK_WHILE:
            tipo_s = "TOK_WHILE";
            break;

        case TOK_REPEAT:
            tipo_s = "TOK_REPEAT";
            break;

        case TOK_CHAR:
            tipo_s = "TOK_CHAR";
            break;

        case TOK_INT:
            tipo_s = "TOK_INT";
            break;

        case TOK_FLOAT:
            tipo_s = "TOK_FLOAT";
            break;

        case TOK_UNTIL:
            tipo_s = "TOK_UNTIL";
            break;

        case TOK_OPREL:
            tipo_s = "TOK_OPREL";
            break;

        case TOK_ID:
            tipo_s = "TOK_ID";
            break;

        case TOK_PAR_ESQ:
            tipo_s = "TOK_PAR_ESQ";
            break;

        case TOK_PAR_DIR:
            tipo_s = "TOK_PAR_DIR";
            break;

        case TOK_PONTO_VIRG:
            tipo_s = "TOK_PONTO_VIRG";
            break;

        case TOK_VIRG:
            tipo_s = "TOK_VIRG";
            break;

        case TOK_DOIS_PONTO:
            tipo_s = "TOK_DOIS_PONTO";
            break;

        case TOK_ATRIB:
            tipo_s = "TOK_ATRIB";
            break;

        case TOK_SUM:
            tipo_s = "TOK_SUM";
            break;

        case TOK_SUB:
            tipo_s = "TOK_SUB";
            break;

        case TOK_DIV:
            tipo_s = "TOK_DIV";
            break;

        case TOK_MUL:
            tipo_s = "TOK_MUL";
            break;

        case TOK_EXP:
            tipo_s = "TOK_EXP";
            break;

        case TOK_CONST_CHAR:
            tipo_s = "TOK_CONST_CHAR";
            break;

        case TOK_CONST_NUM:
            tipo_s = "TOK_CONST_NUM";
            break;
        
        case TOK_FIM_ARQ:
            tipo_s = "$";
            break;

        default:
            tipo_s = "ERRO";
            break;
    }

    return tipo_s;
}

Token *retorna_token(void) {
    Lexema = "";
    int s = estado_inicial;
    char c;

    coluna_inicio = coluna;
    while(estados_finais[s] == false) {
        c = proximo_char();

        if(c == EOF) {
            token(TOK_FIM_ARQ, "-", linha, coluna_inicio);
            return &tok;
        }

        s = mover(s, c);
        Lexema += c;
    }

    if(lookahead[s]) {
        Lexema = Lexema.substr(0, Lexema.size() - 1);
        retorna_prox();
    }

    acoes(s);

    return &tok;
}