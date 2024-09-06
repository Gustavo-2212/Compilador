#include <fstream>
#include "scanner.h"

std::vector<char> buffer_1(4097);
std::vector<char> buffer_2(4097);

std::vector<char>::iterator prox;
std::streampos posicao_arq;
std::string nome_arq;

int coluna_inicio = 1;
int linha = 1;
int coluna = 1;
bool eof = false;

bool carrega_buffer(std::vector<char> &buffer, std::streampos &pos) {
    std::ifstream file(nome_arq, std::ios::binary);

    if(!file.is_open()) {
        std::cerr << "Não foi possível abrir o arquivo: " << nome_arq << std::endl;
        return false;
    }

    file.seekg(posicao_arq);
    
    std::fill(buffer.begin(), buffer.end() - 2, '\0');
    file.read(buffer.data(), buffer.size() - 1);

    if(file.eof()) {
        eof = true;
        std::fill(buffer.begin() + file.gcount(), buffer.end() - 1, EOF);
    }

    posicao_arq = file.tellg();
    file.close();

    return true;
}

void define_filename(std::string filename) {
    nome_arq = filename;
}

bool inicializa_buffers(std::string filename) {
    buffer_1[4096] = EOF;
    buffer_2[4096] = EOF;

    posicao_arq = 0;
    eof = false;
    define_filename(filename);
    bool carregou = carrega_buffer(buffer_1, posicao_arq);

    if(!carregou) return false;

    prox = buffer_1.begin();
    return true;
}

char proximo_char() {

    if(nome_arq.empty()) {
        std::cout << "Inicialize os buffers com a função inicializa_buffer(filename);\n";
        return '\0';
    }

    char caractere = *prox;

    if(caractere == '\n') {
        linha++;
        coluna = 1;
    }
    else if(caractere == '\t') {
        coluna += 4;
    }
    else {
        coluna++;
    }
    
    prox++;
    if(prox == buffer_1.end() - 1) {
        if(eof) {
            return EOF;
        }

        carrega_buffer(buffer_2, posicao_arq);
        prox = buffer_2.begin();
    }
    else if(prox == buffer_2.end() - 1) {
        if(eof) {
            return EOF;
        }
        
        carrega_buffer(buffer_1, posicao_arq);
        prox = buffer_1.begin();
    }

    return caractere;
}

void retorna_prox() {
    if(prox == buffer_2.begin()) {
        prox = buffer_1.end() - 1;
    }
    else if(prox == buffer_1.begin()) {
        prox = buffer_2.end() - 1;
    }
    else {
        prox--;
    }

    char c = *prox;

    if(c == '\n') {
        linha--;
    }
    else if(c == '\t') {
        coluna -= 4;
    }
    else {
        coluna--;
    }

}