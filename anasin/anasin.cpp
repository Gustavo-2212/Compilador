#include "anasin.h"
#include "first_follow.h"

Token *_tok;

int main(int argc, char *argv[]) {
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
    calcula_first_follow();

    shared_ptr<No> root = asp_recursivo();
    imprime_arvore(root, 0);
    cout << endl;
}

void erro_sintatico(int tok_tipo_esperado, const Token *token_recebido) {
    cout << "Token esperado: [" << string_tipo(tok_tipo_esperado) << "]. Token encontrado: [" << string_tipo(token_recebido->tipo) << "]. (" << token_recebido->linha << ", " << token_recebido->coluna << ").\n";
    exit(1);
}

shared_ptr<No> asp_recursivo(void) {
    _tok = retorna_token();

    shared_ptr<No> root = procedimento_programa();

    if(_tok->tipo == TOK_FIM_ARQ) {
        cout << "\t[Programa sintaticamente correto!]\n\n";
    }
    else {
        cout << "\t[Programa sintaticamente incorreto!]\n";
    }

    return root;
}

shared_ptr<No> procedimento_programa(void) {
    shared_ptr<No> programa = make_shared<No>("<programa>");
    if(_tok->tipo == TOK_MAIN) {
        _tok = retorna_token();
        shared_ptr<No> main = make_shared<No>("main");
        adiciona_filho(programa, main);

        if(_tok->tipo == TOK_ID) {
            _tok = retorna_token();
            shared_ptr<No> id = make_shared<No>("id");
            adiciona_filho(programa, id);

            shared_ptr<No> bloco = procedimento_bloco();
            if(bloco) adiciona_filho(programa, bloco);
            else return nullptr;

            return programa;
        }
        else {
            erro_sintatico(TOK_ID, _tok);
            return nullptr;
        }
    }
    else {
        erro_sintatico(TOK_MAIN, _tok);
        return nullptr;
    }
}

shared_ptr<No> procedimento_bloco(void) {
    shared_ptr<No> bloco = make_shared<No>("<bloco>");

    if(_tok->tipo == TOK_BEGIN) {
        _tok = retorna_token();
        shared_ptr<No> begin = make_shared<No>("begin");
        adiciona_filho(bloco, begin);

        shared_ptr<No> decvaropt = procedimento_decvaropt();
        if(decvaropt) adiciona_filho(bloco, decvaropt);

        shared_ptr<No> seqcom = procedimento_seqcom();
        if(seqcom) adiciona_filho(bloco, seqcom);
        else return nullptr;

        if(_tok->tipo == TOK_END) {
            _tok = retorna_token();
            shared_ptr<No> end = make_shared<No>("end");
            adiciona_filho(bloco, end);

            return bloco;
        }
        else {
            erro_sintatico(TOK_END, _tok);
            return nullptr;
        }
    }
    else {
        erro_sintatico(TOK_BEGIN, _tok);
        return nullptr;
    }
}

shared_ptr<No> procedimento_decvaropt(void) {
    shared_ptr<No> decvaropt = make_shared<No>("<decvaropt>");

    if( token_in_first(DECVARS, _tok->tipo) ) {
        shared_ptr<No> decvars = procedimento_decvars();
        if(decvars) adiciona_filho(decvaropt, decvars);

        return decvaropt;
    }
    else return nullptr;
}

shared_ptr<No> procedimento_decvars(void) {
    shared_ptr<No> decvars = make_shared<No>("<decvars>");

    shared_ptr<No> decvar = procedimento_decvar();
    if(decvar) adiciona_filho(decvars, decvar);
    else return nullptr;

    shared_ptr<No> decvarsl = procedimento_decvarsl();
    if(decvarsl) adiciona_filho(decvars, decvarsl);

    return decvars;
}

shared_ptr<No> procedimento_decvarsl(void) {
    shared_ptr<No> decvarsl = make_shared<No>("<decvarsl>");

    if( token_in_first(DECVARS, _tok->tipo) ) {
        shared_ptr<No> decvars = procedimento_decvars();

        if(decvars) adiciona_filho(decvarsl, decvars);

        return decvarsl;
    }
    else return nullptr;
}

shared_ptr<No> procedimento_decvar(void) {
    shared_ptr<No> decvar = make_shared<No>("<decvar>");

    shared_ptr<No> tipo = procedimento_tipo();
    if(tipo) adiciona_filho(decvar, tipo);
    else return nullptr;

    if(_tok->tipo == TOK_DOIS_PONTO) {
        _tok = retorna_token();
        shared_ptr<No> dois_ponto = make_shared<No>(":");
        adiciona_filho(decvar, dois_ponto);

        shared_ptr<No> ids = procedimento_ids();
        if(ids) adiciona_filho(decvar, ids);
        else return nullptr;

        if(_tok->tipo == TOK_PONTO_VIRG) {
            _tok = retorna_token();
            shared_ptr<No> ponto_virgula = make_shared<No>(";");
            adiciona_filho(decvar, ponto_virgula);

            return decvar;
        }
        else {
            erro_sintatico(TOK_PONTO_VIRG, _tok);
            return nullptr;    
        }
    }
    else {
        erro_sintatico(TOK_DOIS_PONTO, _tok);
        return nullptr;
    }
}

shared_ptr<No> procedimento_tipo(void) {
    shared_ptr<No> tipo = make_shared<No>("<tipo>");

    if(_tok->tipo == TOK_INT) {
        _tok = retorna_token();
        shared_ptr<No> _int = make_shared<No>("int");
        adiciona_filho(tipo, _int);

        return tipo;
    }
    else if(_tok->tipo == TOK_FLOAT) {
        _tok = retorna_token();
        shared_ptr<No> _float = make_shared<No>("float");
        adiciona_filho(tipo, _float);

        return tipo;
    }
    else if(_tok->tipo == TOK_CHAR) {
        _tok = retorna_token();
        shared_ptr<No> _char = make_shared<No>("char");
        adiciona_filho(tipo, _char);

        return tipo;
    }
    else {
        erro_sintatico(TOK_INT, _tok);
        erro_sintatico(TOK_FLOAT, _tok);
        erro_sintatico(TOK_CHAR, _tok);

        return nullptr;
    }
}

shared_ptr<No> procedimento_ids(void) {
    shared_ptr<No> ids = make_shared<No>("<ids>");

    if(_tok->tipo == TOK_ID) {
        _tok = retorna_token();
        shared_ptr<No> id = make_shared<No>("id");
        adiciona_filho(ids, id);

        shared_ptr<No> idsl = procedimento_idsl();
        if(idsl) adiciona_filho(ids, idsl);

        return ids;
    }
    else {
        erro_sintatico(TOK_ID, _tok);
        return nullptr;
    }
}

shared_ptr<No> procedimento_idsl(void) {
    shared_ptr<No> idsl = make_shared<No>("<idsl>");

    if(_tok->tipo == TOK_VIRG) {
        _tok = retorna_token();
        shared_ptr<No> virgula = make_shared<No>(",");
        adiciona_filho(idsl, virgula);

        shared_ptr<No> ids = procedimento_ids();
        if(ids) adiciona_filho(idsl, ids);
        else return nullptr;

        return idsl;
    }
    else if( !token_in_follow(IDSL, _tok->tipo) ) { // token not in follow(idsl)
        erro_sintatico(TOK_VIRG, _tok);
        erro_sintatico(TOK_PONTO_VIRG, _tok);
        return nullptr;
    }
    else return nullptr;
}

shared_ptr<No> procedimento_selecao(void) {
    shared_ptr<No> selecao = make_shared<No>("<selecao>");

    if(_tok->tipo == TOK_IF) {
        _tok = retorna_token();
        shared_ptr<No> _if = make_shared<No>("if");
        adiciona_filho(selecao, _if);

        if(_tok->tipo == TOK_PAR_ESQ) {
            _tok = retorna_token();
            shared_ptr<No> par_esq = make_shared<No>("(");
            adiciona_filho(selecao, par_esq);

            shared_ptr<No> condicao = procedimento_condicao();
            if(condicao) adiciona_filho(selecao, condicao);
            else return nullptr;

            if(_tok->tipo == TOK_PAR_DIR) {
                _tok = retorna_token();
                shared_ptr<No> par_dir = make_shared<No>(")");
                adiciona_filho(selecao, par_dir);

                if(_tok->tipo == TOK_THEN) {
                    _tok = retorna_token();
                    shared_ptr<No> then = make_shared<No>("then");
                    adiciona_filho(selecao, then);

                    shared_ptr<No> bloco_ou_comando = procedimento_bloco_ou_comando();
                    if(bloco_ou_comando) adiciona_filho(selecao, bloco_ou_comando);
                    else return nullptr;

                    shared_ptr<No> elseopt = procedimento_elseopt();
                    if(elseopt) adiciona_filho(selecao, elseopt);

                    return selecao;
                }
                else {
                    erro_sintatico(TOK_THEN, _tok);
                    return nullptr;
                }

            }
            else {
                erro_sintatico(TOK_PAR_DIR, _tok);
                return nullptr;
            }

        }
        else {
            erro_sintatico(TOK_PAR_ESQ, _tok);
            return nullptr;
        }
    }
    else {
        erro_sintatico(TOK_IF, _tok);
        return nullptr;
    }
}

shared_ptr<No> procedimento_elseopt(void) {
    shared_ptr<No> elseopt = make_shared<No>("<elseopt>");

    if(_tok->tipo == TOK_ELSE) {
        _tok = retorna_token();
        shared_ptr<No> _else = make_shared<No>("else");
        adiciona_filho(elseopt, _else);

        shared_ptr<No> bloco_ou_comando = procedimento_bloco_ou_comando();
        if(bloco_ou_comando) adiciona_filho(elseopt, bloco_ou_comando);
        else return nullptr;

        return elseopt;
    }
    else if( !token_in_follow(ELSEOPT, _tok->tipo) ) {
        for(auto token = follow[ELSEOPT].begin(); token != follow[ELSEOPT].end(); token++) {
            erro_sintatico(*token, _tok);
        }
        return nullptr;
    }
    else return nullptr;
}

shared_ptr<No> procedimento_repeticao(void) {
    shared_ptr<No> repeticao = make_shared<No>("<repeticao>");

    if( token_in_first(REPETICAO_WHILE, _tok->tipo) ) {
        shared_ptr<No> repeticao_while = procedimento_repeticao_while();
        if(repeticao_while) adiciona_filho(repeticao, repeticao_while);
        else return nullptr;

        return repeticao;
    }
    else if( token_in_first(REPETICAO_REPEAT, _tok->tipo) ) {
        shared_ptr<No> repeticao_repeat = procedimento_repeticao_repeat();
        if(repeticao_repeat) adiciona_filho(repeticao, repeticao_repeat);
        else return nullptr;

        return repeticao;
    }
    else {
        for(auto token = first[REPETICAO_WHILE].begin(); token != first[REPETICAO_WHILE].end(); token++)
            erro_sintatico(*token, _tok);
        
        for(auto token = first[REPETICAO_REPEAT].begin(); token != first[REPETICAO_REPEAT].end(); token++)
            erro_sintatico(*token, _tok);

        return nullptr;
    }
}

shared_ptr<No> procedimento_repeticao_while(void) {
    shared_ptr<No> repeticao_while = make_shared<No>("<repeticao_while>");

    if(_tok->tipo == TOK_WHILE) {
        _tok = retorna_token();
        shared_ptr<No> _while = make_shared<No>("while");
        adiciona_filho(repeticao_while, _while);

        if(_tok->tipo == TOK_PAR_ESQ) {
            _tok = retorna_token();
            shared_ptr<No> par_esq = make_shared<No>("(");
            adiciona_filho(repeticao_while, par_esq);

            shared_ptr<No> condicao = procedimento_condicao();
            if(condicao) adiciona_filho(repeticao_while, condicao);
            else return nullptr;

            if(_tok->tipo == TOK_PAR_DIR) {
                _tok = retorna_token();
                shared_ptr<No> par_dir = make_shared<No>(")");
                adiciona_filho(repeticao_while, par_dir);

                if(_tok->tipo == TOK_DO) {
                    _tok = retorna_token();
                    shared_ptr<No> _do = make_shared<No>("do");
                    adiciona_filho(repeticao_while, _do);

                    shared_ptr<No> bloco_ou_comando = procedimento_bloco_ou_comando();
                    if(bloco_ou_comando) adiciona_filho(repeticao_while, bloco_ou_comando);
                    else return nullptr;

                    return repeticao_while;
                }
                else {
                    erro_sintatico(TOK_DO, _tok);
                    return nullptr;
                }
            }
            else {
                erro_sintatico(TOK_PAR_DIR, _tok);
                return nullptr;
            }
        }
        else {
            erro_sintatico(TOK_PAR_ESQ, _tok);
            return nullptr;
        }
    }
    else {
        erro_sintatico(TOK_WHILE, _tok);
        return nullptr;
    }
}

shared_ptr<No> procedimento_repeticao_repeat(void) {
    shared_ptr<No> repeticao_repeat = make_shared<No>("<repeticao_repeat>");

    if(_tok->tipo == TOK_REPEAT) {
        _tok = retorna_token();
        shared_ptr<No> repeat = make_shared<No>("repeat");
        adiciona_filho(repeticao_repeat, repeat);

        shared_ptr<No> bloco_ou_comando = procedimento_bloco_ou_comando();
        if(bloco_ou_comando) adiciona_filho(repeticao_repeat, bloco_ou_comando);
        else return nullptr;

        if(_tok->tipo == TOK_UNTIL) {
            _tok = retorna_token();
            shared_ptr<No> until = make_shared<No>("until");
            adiciona_filho(repeticao_repeat, until);

            if(_tok->tipo == TOK_PAR_ESQ) {
                _tok = retorna_token();
                shared_ptr<No> par_esq = make_shared<No>("(");
                adiciona_filho(repeticao_repeat, par_esq);

                shared_ptr<No> condicao = procedimento_condicao();
                if(condicao) adiciona_filho(repeticao_repeat, condicao);
                else return nullptr;

                if(_tok->tipo == TOK_PAR_DIR) {
                    _tok = retorna_token();
                    shared_ptr<No> par_dir = make_shared<No>(")");
                    adiciona_filho(repeticao_repeat, par_dir);

                    if(_tok->tipo == TOK_PONTO_VIRG) {
                        _tok = retorna_token();
                        shared_ptr<No> ponto_virgula = make_shared<No>(";");
                        adiciona_filho(repeticao_repeat, ponto_virgula);

                        return repeticao_repeat;
                    }
                    else {
                        erro_sintatico(TOK_PONTO_VIRG, _tok);
                        return nullptr;
                    }
                }
                else {
                    erro_sintatico(TOK_PAR_DIR, _tok);
                    return nullptr;
                }
            }
            else {
                erro_sintatico(TOK_PAR_ESQ, _tok);
                return nullptr;
            }
        }
        else {
            erro_sintatico(TOK_UNTIL, _tok);
            return nullptr;
        }
    }
    else {
        erro_sintatico(TOK_REPEAT, _tok);
        return nullptr;
    }
}

shared_ptr<No> procedimento_atribuicao(void) {
    shared_ptr<No> atribuicao = make_shared<No>("<atribuicao>");

    if(_tok->tipo == TOK_ID) {
        _tok = retorna_token();
        shared_ptr<No> id = make_shared<No>("id");
        adiciona_filho(atribuicao, id);

        if(_tok->tipo == TOK_ATRIB) {
            _tok = retorna_token();
            shared_ptr<No> atrib = make_shared<No>(":=");
            adiciona_filho(atribuicao, atrib);

            shared_ptr<No> expr = procedimento_expr();
            if(expr) adiciona_filho(atribuicao, expr);
            else return nullptr;

            if(_tok->tipo == TOK_PONTO_VIRG) {
                _tok = retorna_token();
                shared_ptr<No> ponto_virgula = make_shared<No>(";");
                adiciona_filho(atribuicao, ponto_virgula);

                return atribuicao;
            }
            else {
                erro_sintatico(TOK_PONTO_VIRG, _tok);
                return nullptr;
            }
        }
        else {
            erro_sintatico(TOK_ATRIB, _tok);
            return nullptr;
        }
    }
    else {
        erro_sintatico(TOK_ID, _tok);
        return nullptr;
    }
}

shared_ptr<No> procedimento_condicao(void) {
    shared_ptr<No> condicao = make_shared<No>("<condicao>");

    shared_ptr<No> expr_a = procedimento_expr();
    shared_ptr<No> oprel = procedimento_oprel();
    shared_ptr<No> expr_b = procedimento_expr();

    if(expr_a) adiciona_filho(condicao, expr_a);
    else return nullptr;

    if(oprel) adiciona_filho(condicao, oprel);
    else return nullptr;

    if(expr_b) adiciona_filho(condicao, expr_b);
    else return nullptr;

    return condicao;
}

shared_ptr<No> procedimento_oprel(void) {
    shared_ptr<No> oprel = make_shared<No>("<oprel>");

    if(_tok->tipo == TOK_OPREL) {
        if(_tok->atributo == "EQ") {
            _tok = retorna_token();
            shared_ptr<No> eq = make_shared<No>("==");
            adiciona_filho(oprel, eq);
        }
        else if(_tok->atributo == "NE") {
            _tok = retorna_token();
            shared_ptr<No> ne = make_shared<No>("!=");
            adiciona_filho(oprel, ne);
        }
        else if(_tok->atributo == "LT") {
            _tok = retorna_token();
            shared_ptr<No> lt = make_shared<No>("<");
            adiciona_filho(oprel, lt);
        }
        else if(_tok->atributo == "GT") {
            _tok = retorna_token();
            shared_ptr<No> gt = make_shared<No>(">");
            adiciona_filho(oprel, gt);
        }
        else if(_tok->atributo == "LE") {
            _tok = retorna_token();
            shared_ptr<No> le = make_shared<No>("<=");
            adiciona_filho(oprel, le);
        }
        else if(_tok->atributo == "GE") {
            _tok = retorna_token();
            shared_ptr<No> ge = make_shared<No>(">=");
            adiciona_filho(oprel, ge);
        }

        return oprel;
    }
    else {
        erro_sintatico(TOK_OPREL, _tok);
        return nullptr;
    }
}

shared_ptr<No> procedimento_expr(void) {
    shared_ptr<No> expr = make_shared<No>("<expr>");

    shared_ptr<No> termo = procedimento_termo();
    if(termo) adiciona_filho(expr, termo);
    else return nullptr;

    shared_ptr<No> exprl = procedimento_exprl();
    if(exprl) adiciona_filho(expr, exprl);

    return expr;
}

shared_ptr<No> procedimento_exprl(void) {
    shared_ptr<No> exprl = make_shared<No>("<exprl>");

    while( token_in_first(EXPRL, _tok->tipo) ) {
        if(_tok->tipo == TOK_SUM) {
            _tok = retorna_token();
            shared_ptr<No> soma = make_shared<No>("+");
            adiciona_filho(exprl, soma);

            shared_ptr<No> termo = procedimento_termo();
            if(termo) adiciona_filho(exprl, termo);
            else return nullptr;
        }
        else if(_tok->tipo == TOK_SUB) {
            _tok = retorna_token();
            shared_ptr<No> subt = make_shared<No>("-");
            adiciona_filho(exprl, subt);

            shared_ptr<No> termo = procedimento_termo();
            if(termo) adiciona_filho(exprl, termo);
            else return nullptr;
        }
        else {
            erro_sintatico(TOK_SUM, _tok);
            erro_sintatico(TOK_SUB, _tok);
            return nullptr;
        }
    }

    if(exprl->filhos.empty()) return nullptr;
    else return exprl;
}

shared_ptr<No> procedimento_termo(void) {
    shared_ptr<No> termo = make_shared<No>("<termo>");

    shared_ptr<No> fator = procedimento_fator();
    if(fator) adiciona_filho(termo, fator);
    else return nullptr;

    shared_ptr<No> termol = procedimento_termol();
    if(termol) adiciona_filho(termo, termol);

    return termo;
}

shared_ptr<No> procedimento_termol(void) {
    shared_ptr<No> termol = make_shared<No>("<termol>");

    while( token_in_first(TERMOL, _tok->tipo) ) {
        if(_tok->tipo == TOK_MUL) {
            _tok = retorna_token();
            shared_ptr<No> mult = make_shared<No>("*");
            adiciona_filho(termol, mult);

            shared_ptr<No> fator = procedimento_fator();
            if(fator) adiciona_filho(termol, fator);
            else return nullptr;
        }
        else if(_tok->tipo == TOK_DIV) {
            _tok = retorna_token();
            shared_ptr<No> div = make_shared<No>("/");
            adiciona_filho(termol, div);

            shared_ptr<No> fator = procedimento_fator();
            if(fator) adiciona_filho(termol, fator);
            else return nullptr;
        }
        else {
            erro_sintatico(TOK_MUL, _tok);
            erro_sintatico(TOK_DIV, _tok);
            return nullptr;
        }
    }

    if(termol->filhos.empty()) return nullptr;
    else return termol;
}

shared_ptr<No> procedimento_fator(void) {
    shared_ptr<No> fator = make_shared<No>("<fator>");

    shared_ptr<No> pot = procedimento_pot();
    if(pot) adiciona_filho(fator, pot);
    else return nullptr;

    shared_ptr<No> fatorl = procedimento_fatorl();
    if(fatorl) adiciona_filho(fator, fatorl);

    return fator;
}

shared_ptr<No> procedimento_fatorl(void) {
    shared_ptr<No> fatorl = make_shared<No>("<fatorl>");

    if(_tok->tipo == TOK_EXP) {
        _tok = retorna_token();
        shared_ptr<No> _exp = make_shared<No>("**");
        adiciona_filho(fatorl, _exp);

        shared_ptr<No> fator = procedimento_fator();
        if(fator) adiciona_filho(fatorl, fator);
        else return nullptr;

        return fatorl;
    }
    else if( !token_in_follow(FATORL, _tok->tipo) ){
        for(auto token = follow[FATORL].begin(); token != follow[FATORL].end(); token++) erro_sintatico(*token, _tok);
        return nullptr;
    }
    else return nullptr; // EPSILON
}

shared_ptr<No> procedimento_pot(void) {
    shared_ptr<No> pot = make_shared<No>("<pot>");

    if(_tok->tipo == TOK_ID) {
        _tok = retorna_token();
        shared_ptr<No> id = make_shared<No>("id");
        adiciona_filho(pot, id);

        return pot;
    }
    else if( token_in_first(CONSTANTE, _tok->tipo) ) {
        shared_ptr<No> constante = procedimento_constante();
        if(constante) adiciona_filho(pot, constante);
        else return nullptr;

        return pot;
    }
    else if(_tok->tipo == TOK_PAR_ESQ) {
        _tok = retorna_token();
        shared_ptr<No> par_esq = make_shared<No>("(");
        adiciona_filho(pot, par_esq);

        shared_ptr<No> expr = procedimento_expr();
        if(expr) adiciona_filho(pot, expr);
        else return nullptr;

        if(_tok->tipo == TOK_PAR_DIR) {
            _tok = retorna_token();
            shared_ptr<No> par_dir = make_shared<No>(")");
            adiciona_filho(pot, par_dir);
        }
        else {
            erro_sintatico(TOK_PAR_DIR, _tok);
            return nullptr;
        }

        return pot;
    }
    else if(_tok->tipo == TOK_SUB) {
        _tok = retorna_token();
        shared_ptr<No> sub = make_shared<No>("-");
        adiciona_filho(pot, sub);

        shared_ptr<No> _pot = procedimento_pot();
        if(_pot) adiciona_filho(pot, _pot);
        else return nullptr;

        return pot;
    }
    else {
        for(auto token = first[POT].begin(); token != first[POT].end(); token++)
            erro_sintatico(*token, _tok);
        return nullptr;
    }
}

shared_ptr<No> procedimento_constante(void) {
    shared_ptr<No> constante = make_shared<No>("<constante>");

    if(_tok->tipo == TOK_CONST_NUM) {
        _tok = retorna_token();
        shared_ptr<No> const_num = make_shared<No>("const_num");
        adiciona_filho(constante, const_num);

        return constante;
    }
    else if(_tok->tipo == TOK_CONST_CHAR) {
        _tok = retorna_token();
        shared_ptr<No> const_char = make_shared<No>("const_char");
        adiciona_filho(constante, const_char);

        return constante;
    }
    else {
        erro_sintatico(TOK_CONST_NUM, _tok);
        erro_sintatico(TOK_CONST_CHAR, _tok);
        return nullptr;
    }
}

shared_ptr<No> procedimento_seqcom(void) {
    shared_ptr<No> seqcom = make_shared<No>("<seqcom>");

    shared_ptr<No> comando = procedimento_comando();
    if(comando) adiciona_filho(seqcom, comando);
    else return nullptr;

    shared_ptr<No> seqcoml = procedimento_seqcoml();
    if(seqcoml) adiciona_filho(seqcom, seqcoml);

    return seqcom;
}

shared_ptr<No> procedimento_seqcoml(void) {
    shared_ptr<No> seqcoml = make_shared<No>("<seqcoml>");

    if( token_in_first(SEQCOM, _tok->tipo) ) {
        shared_ptr<No> seqcom = procedimento_seqcom();
        if(seqcom) adiciona_filho(seqcoml, seqcom);
        else return nullptr;
    }
    else if( !token_in_follow(SEQCOML, _tok->tipo) ) {
        erro_sintatico(SEQCOM, _tok);
        return nullptr;
    }

    return nullptr;
}

shared_ptr<No> procedimento_bloco_ou_comando(void) {
    shared_ptr<No> bloco_ou_comando = make_shared<No>("<bloco_ou_comando>");

    if( token_in_first(BLOCO, _tok->tipo) ) {
        shared_ptr<No> bloco = procedimento_bloco();
        if(bloco) adiciona_filho(bloco_ou_comando, bloco);
        else return nullptr;

        return bloco_ou_comando;
    }
    else if( token_in_first(COMANDO, _tok->tipo) ) {
        shared_ptr<No> comando = procedimento_comando();
        if(comando) adiciona_filho(bloco_ou_comando, comando);
        else return nullptr;

        return bloco_ou_comando;
    }
    else {
        for(auto token = first[BLOCO].begin(); token != first[BLOCO].end(); token++)
            erro_sintatico(*token, _tok);

        for(auto token = first[COMANDO].begin(); token != first[COMANDO].end(); token++)
            erro_sintatico(*token, _tok);

        return nullptr;
    }
}

shared_ptr<No> procedimento_comando(void) {
    shared_ptr<No> comando = make_shared<No>("<comando>");

    if( token_in_first(ATRIBUICAO, _tok->tipo) ) {
        shared_ptr<No> atribuicao = procedimento_atribuicao();
        if(atribuicao) adiciona_filho(comando, atribuicao);
        else return nullptr;

        return comando;
    }
    else if( token_in_first(SELECAO, _tok->tipo) ) {
        shared_ptr<No> selecao = procedimento_selecao();
        if(selecao) adiciona_filho(comando, selecao);
        else return nullptr;

        return comando;
    }
    else if( token_in_first(REPETICAO, _tok->tipo) ) {
        shared_ptr<No> repeticao = procedimento_repeticao();
        if(repeticao) adiciona_filho(comando, repeticao);
        else return nullptr;

        return comando;
    }
    else {
        for(auto token = first[ATRIBUICAO].begin(); token != first[ATRIBUICAO].end(); token++)
            erro_sintatico(ATRIBUICAO, _tok);
    
        for(auto token = first[SELECAO].begin(); token != first[SELECAO].end(); token++)
            erro_sintatico(SELECAO, _tok);

        for(auto token = first[REPETICAO].begin(); token != first[REPETICAO].end(); token++)
            erro_sintatico(REPETICAO, _tok);
    
        return nullptr;
    }
}