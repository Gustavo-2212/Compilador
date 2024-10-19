#ifndef TREE_H
#define TREE_H

#include <string>
#include <vector>
#include <memory>
using namespace std;

typedef struct No {
    string valor;
    vector<shared_ptr<No>> filhos;

    No(string _valor) : valor(_valor) {}
} No;

void adiciona_filho(shared_ptr<No> pai, shared_ptr<No> filho);
void imprime_arvore(const shared_ptr<No> &root, int nivel);

#endif