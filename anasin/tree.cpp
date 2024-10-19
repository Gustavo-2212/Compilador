#include <iostream>
#include <queue>
#include "tree.h"

using namespace std;

void adiciona_filho(shared_ptr<No> pai, shared_ptr<No> filho) {
    pai->filhos.push_back(filho);
}

void imprime_arvore(const shared_ptr<No> &root, int nivel = 0) {
    if (!root) return;

    cout << string(nivel * 3, ' ') << root->valor << '\n';

    for (const auto& filho : root->filhos) {
        imprime_arvore(filho, nivel + 1);
    }
}
