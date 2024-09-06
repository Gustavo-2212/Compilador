#include <iostream>
#include <fstream>
#include <regex>
#include <map>

#include "../analex/analex.h"
#include "tabela.h"

using namespace std;

int tabela_transicao[107][257];
const int estado_inicial = 0;

void constroi_tabela() {
    ifstream file("../gera_tabela_dt/diagrama_det.txt");
    string line;
    
    regex state_regex(R"(^\s*([0-9]+))");             // Captura o estado na linha
    regex trans_regex(R"('([^']*)':\s*([0-9]+))");    // Captura as transições de estado

    int estado_atual;
    // map<char, int> transicoes;
    
    prepara_tabela();
    
    if (file.is_open()) {
        int line_number = 0;
        while (getline(file, line)) {
            line_number++;
            smatch match;

            // Captura os estados das linhas 1, 5 e qualquer outra linha que não contenha transições
            if (regex_search(line, match, state_regex)) {
                estado_atual = stoi(match[1]);
                // cout << "Estado na linha " << line_number << ": " << estado_atual << endl;
            }

            // Captura as transições das linhas 2 e 6 (ou outras que contenham transições)
            if (line.find('{') != string::npos) {
                auto transicoes_begin = sregex_iterator(line.begin(), line.end(), trans_regex);
                auto transicoes_end = sregex_iterator();

                for (sregex_iterator i = transicoes_begin; i != transicoes_end; ++i) {
                    smatch match = *i;

                    unsigned char simbolo;

                    if(match[1].str().size() >= 2)
                        simbolo = mapeia_caractere(match[1].str());
                    else
                        simbolo = match[1].str()[0];

                    int estado_alvo = stoi(match[2]);
                    // transicoes[simbolo] = estado_alvo;
                    tabela_transicao[estado_atual][simbolo] = estado_alvo;
                    
                    // cout << "Simbolo: " << simbolo << ", Estado Alvo: " << estado_alvo << endl;
                }
            }
        }
    } else {
        cerr << "Não foi possível abrir o arquivo diagrama_det.txt." << '\n';
    }
    file.close();

    // imprime_tabela();
}

void prepara_tabela() {
    for(int i = 0; i < 107; i++)
        for(int j = 0; j < 257; j++)
            tabela_transicao[i][j] = ESTADO_ERRO;
        
}

void imprime_tabela() {
    for(int i = 0; i < 107; i++) {
        cout << i << ": " << tabela_transicao[i]['\n'] << '\n';
        // for(int j = 0; j < 257; j++) {
        //     cout << '\t' << tabela_transicao[i][j] << " \n";
        // }
        // cout << endl;
    }
}

int mover(int estado, char simbolo) {
    return tabela_transicao[estado][simbolo];
}

void acoes(int estado) {
    std::string atributo = "-";
    switch(estado) {
        
        case 101: // begin
            token(TOK_BEGIN, atributo);
            break;
        
        case 88: // end
            token(TOK_END, atributo);
            break;
        
        case 95:
            token(TOK_MAIN, atributo);
            break;
        
        case 71:
            token(TOK_IF, atributo);
            break;
        
        case 96:
            token(TOK_THEN, atributo);
            break;
        
        case 98:
            token(TOK_ELSE, atributo);
            break;
        
        case 68:
            token(TOK_DO, atributo);
            break;
        
        case 100:
            token(TOK_WHILE, atributo);
            break;
        
        case 105:
            token(TOK_REPEAT, atributo);
            break;
        
        case 86:
            atributo = "int";
            token(TOK_INT, atributo);
            break;
        
        case 102:
            atributo = "float\0";
            token(TOK_FLOAT, atributo);
            break;
        
        case 94:
            atributo = "char\0";
            token(TOK_CHAR, atributo);
            break;

        case 103:
            token(TOK_UNTIL, atributo);
            break;
        
        case 46:
            atributo = "EQ\0";
            token(TOK_OPREL, atributo);
            break;

        case 51:
            atributo = "NE\0";
            token(TOK_OPREL, atributo);
            break;

        case 73:
            atributo = "GE\0";
            token(TOK_OPREL, atributo);
            break;

        case 59:
            atributo = "GT\0";
            token(TOK_OPREL, atributo);
            break;

        case 48:
            atributo = "LE\0";
            token(TOK_OPREL, atributo);
            break;

        case 47:
            atributo = "LT\0";
            token(TOK_OPREL, atributo);
            break;

        case 31:
            setID(Lexema);
            break;

        case 13:
            token(TOK_PAR_ESQ, atributo);
            break;

        case 23:
            token(TOK_PAR_DIR, atributo);
            break;

        case 7:
            token(TOK_PONTO_VIRG, atributo);
            break;

        case 6:
            token(TOK_VIRG, atributo);
            break;

        case 52:
            token(TOK_DOIS_PONTO, atributo);
            break;

        case 53:
            token(TOK_ATRIB, atributo);
            break;

        case 20:
            token(TOK_SUM, atributo);
            break;

        case 15:
            token(TOK_SUB, atributo);
            break;

        case 18:
            token(TOK_DIV, atributo);
            break;

        case 49:
            token(TOK_MUL, atributo);
            break;

        case 50:
            token(TOK_EXP, atributo);
            break;

        case 67:
            token(TOK_CONST_CHAR, Lexema);
            break;

        case 32:
            setInt(Lexema);
            break;

        case 79:
            setFloat(Lexema);
            break;

        case 78:
            setExp(Lexema);
            break;

        case 55:
            restart();
            break;

        case 43:
            restart();
            break;

        case 106:
            erro();

        default:
            break;
    }
}

unsigned char mapeia_caractere(const std::string &sequencia_escape) {
    static const std::map<std::string, char> escapeMap = {
        {"\\0", 0},
        {"\\x01", 1},
        {"\\x02", 2},
        {"\\x03", 3},
        {"\\x04", 4},
        {"\\x05", 5},
        {"\\x06", 6},
        {"\\a", 7},
        {"\\b", 8},
        {"\\t", 9},
        {"\\n", 10},
        {"\\v", 11},
        {"\\f", 12},
        {"\\r", 13},
        {"\\x0e", 14},
        {"\\x0f", 15},
        {"\\x10", 16},
        {"\\x11", 17},
        {"\\x12", 18},
        {"\\x13", 19},
        {"\\x14", 20},
        {"\\x15", 21},
        {"\\x16", 22},
        {"\\x17", 23},
        {"\\x18", 24},
        {"\\x19", 25},
        {"\\x1a", 26},
        {"\\x1b", 27},
        {"\\x1c", 28},
        {"\\x1d", 29},
        {"\\x1e", 30},
        {"\\x1f", 31},
        {"\\x20", 32},
        {"39", 39},         // '\''
        {"\\x7f", 127},
        {"\\x9d", 157},
        {"\\x89", 137},
        {"\\x8e", 142},
        {"\\x91", 145},
        {"\\x81", 129},
        {"\\x88", 136},
        {"\\x98", 152},
        {"\\x94", 148},
        {"\\x93", 147},
        {"\\x8d", 141},
        {"\\x82", 130},
        {"\\x99", 153},
        {"\\x8b", 139},
        {"\\x08", 8},
        {"\\x92", 146},
        {"\\x9b", 155},
        {"\\x86", 134},
        {"\\x95", 149},
        {"\\x9a", 154},
        {"\\x0b", 11},
        {"\\x84", 132},
        {"\\x97", 151},
        {"\\x8a", 138},
        {"\\x80", 128},
        {"\\x0c", 12},
        {"\\x8c", 140},
        {"\\x80", 128},
        {"\\x8c", 140},
        {"\\x87", 135},
        {"\\x9c", 156},
        {"\\x9f", 159},
        {"\\xad", 173},
        {"\\xa0", 160},
        {"\\x85", 133},
        {"\\x07", 7},
        {"\\x90", 144},
        {"\\x83", 131},
        {"\\x9e", 158},
        {"\\x8f", 143},
        {"\\x96", 150},
        {"\\x0f", 15}
    };

    auto it = escapeMap.find(sequencia_escape);
    if (it != escapeMap.end()) {
        return it->second;
    }
    
    // TODO Precisa ser tratado melhor
    return ESTADO_ERRO; // Retorna ERRO para sequências inválidas
}