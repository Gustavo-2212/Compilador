#ifndef ANASIN_H
#define ANASIN_H

#include "tree.h"
#include "../analex/analex.h"

void erro_sintatico(int tok_tipo_esperado, const Token *token_recebido);

extern shared_ptr<No> asp_recursivo(void);

extern shared_ptr<No> procedimento_programa(void);
extern shared_ptr<No> procedimento_bloco(void);
extern shared_ptr<No> procedimento_decvaropt(void);
extern shared_ptr<No> procedimento_decvars(void);
extern shared_ptr<No> procedimento_decvarsl(void);
extern shared_ptr<No> procedimento_decvar(void);
extern shared_ptr<No> procedimento_tipo(void);
extern shared_ptr<No> procedimento_ids(void);
extern shared_ptr<No> procedimento_idsl(void);
extern shared_ptr<No> procedimento_selecao(void);
extern shared_ptr<No> procedimento_elseopt(void);
extern shared_ptr<No> procedimento_repeticao(void);
extern shared_ptr<No> procedimento_repeticao_while(void);
extern shared_ptr<No> procedimento_repeticao_repeat(void);
extern shared_ptr<No> procedimento_atribuicao(void);
extern shared_ptr<No> procedimento_condicao(void);
extern shared_ptr<No> procedimento_oprel(void);
extern shared_ptr<No> procedimento_expr(void);
extern shared_ptr<No> procedimento_exprl(void);
extern shared_ptr<No> procedimento_termo(void);
extern shared_ptr<No> procedimento_termol(void);
extern shared_ptr<No> procedimento_fator(void);
extern shared_ptr<No> procedimento_fatorl(void);
extern shared_ptr<No> procedimento_pot(void);
extern shared_ptr<No> procedimento_constante(void);
extern shared_ptr<No> procedimento_seqcom(void);
extern shared_ptr<No> procedimento_seqcoml(void);
extern shared_ptr<No> procedimento_bloco_ou_comando(void);
extern shared_ptr<No> procedimento_comando(void);

#endif