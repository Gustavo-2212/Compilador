#include <iostream>
#include "analex.h"

using namespace std;

int main(int argc, char **argv) {

    std::string baseDir = "../codigos_entrada/";
    std::string filename;

    if(argc <= 1) {
        cout << "Digite o nome do arquivo de entrada (lembre de salvá-lo no diretório codigos_entrada): ";
        cin >> filename;
    }
    else
        filename = argv[1];


    if(filename.empty()) filename = "entrada01.txt";

    bool preparado = prepara_scanner(baseDir + filename);

    if(!preparado) return -1;

    prepara_tabela_transicao();
    inicializar_tabela_simbolos();

    Token *tok = retorna_token();
    while(tok) {
        cout << '<' << string_tipo(tok->tipo) << ", " << tok->atributo << ", " << linha << ", " << coluna_inicio << ">\n";

        tok = retorna_token();
    }

    return 0;
}