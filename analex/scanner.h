#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <vector>

#define EOF (-1)

extern std::vector<char> buffer_1;
extern std::vector<char> buffer_2;
extern std::string nome_arq;
extern int linha;
extern int coluna;
extern int coluna_inicio;

char proximo_char();
bool inicializa_buffers(std::string filename);
void define_filename(std::string filename);
bool carrega_buffer(std::vector<char> &buffer, std::streampos &pos);
void retorna_prox();

#endif