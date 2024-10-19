# 🛠️ Analisador Léxico e Analisador Sintático de um Compilador

> Este projeto implementa o **analisador léxico** (ou scanner) de um compilador para uma linguagem simplificada. O analisador léxico é uma das primeiras fases de um compilador e é responsável por ler o código-fonte de entrada e convertê-lo em uma sequência de tokens que serão utilizados pelas próximas fases do compilador.<br>O projeto também conta com a implementação de um **analisador sintático** (ou parser), sendo responsável por verificar se a estrutura dos tokens de um arquivo de entrada está escrito de acordo com as especificações da linguagem.


## 🧩 Estrutura do Compilador

O compilador é composto por várias partes principais, descritas a seguir:

### 1. 🔍 **Analisador Léxico (Scanner)**
O scanner lê o código-fonte de entrada caractere por caractere e agrupa esses caracteres em **tokens** (como palavras-chave, identificadores, operadores, etc.). Ele também é responsável por descartar espaços em branco e comentários.

### 2. 🗃️ **Tabela de Símbolos**
A tabela de símbolos armazena informações sobre identificadores (como variáveis e funções) encontrados no código-fonte. Cada entrada na tabela contém informações como o nome do identificador, seu tipo e seu escopo.

### 3. 🛠️ **Tradução Dirigida por Tabela**
Nesta fase, uma tabela de tradução mapeia a sequência de tokens para ações que serão executadas, como a geração de código intermediário ou a construção de estruturas abstratas.

### 4. 🔄 **Autômatos Finitos**
O analisador léxico é frequentemente implementado usando **autômatos finitos**, que permitem modelar o processo de identificação de tokens. Um autômato finito pode ser determinístico (AFD) ou não determinístico (AFN), e neste projeto utilizamos **AFD** para garantir uma análise eficiente.

### 5. 📝 **Diagramas de Transição**
Os autômatos finitos podem ser visualizados através de **diagramas de transição**, que mostram como o analisador se move entre diferentes estados conforme lê os caracteres de entrada. Cada transição é baseada nos caracteres recebidos, levando o autômato a um novo estado até que um token válido seja reconhecido.

### 6. 📐 **Analisador Sintático e Técnicas de Parsing**

O **analisador sintático** (ou **parser**) é uma das etapas centrais de um compilador. Ele recebe a sequência de **tokens** gerada pelo analisador léxico e verifica se essa sequência obedece às regras da **gramática** da linguagem. Esta fase é essencial para garantir que o código-fonte tenha uma estrutura válida e que possa ser traduzido para etapas posteriores, como a geração de código intermediário.

### 7. 🧱 **Tradução Dirigida por Sintaxe**
A **tradução dirigida por sintaxe** é uma técnica que associa **ações semânticas** a produções da gramática. Essas ações são executadas durante o processo de parsing e podem incluir a geração de código intermediário, preenchimento da tabela de símbolos ou criação da árvore abstrata. Essa abordagem é útil para construir uma ponte entre a análise sintática e a geração de código.

### 8. 🌲 **Geração da Árvore Abstrata dos Tokens**
Durante o parsing, o compilador pode construir uma **árvore sintática abstrata (AST - Abstract Syntax Tree)**. A AST é uma estrutura hierárquica que representa a organização lógica do código-fonte, eliminando detalhes irrelevantes da sintaxe concreta. Cada nó da árvore representa uma construção da linguagem (como expressões, comandos, ou declarações).


### 9. 🔄 **Funções FIRST e FOLLOW**
As funções **FIRST** e **FOLLOW** ajudam a prever quais produções da gramática devem ser utilizadas durante o parsing.

- **FIRST(X)**: Conjunto de tokens que podem aparecer como primeiro símbolo de uma cadeia derivada do não-terminal `X`.
- **FOLLOW(X)**: Conjunto de tokens que podem aparecer imediatamente após uma derivação do não-terminal `X`.

Essas funções são essenciais para construir **parsers preditivos** que tomam decisões de parsing com base nos tokens antecipados.

### 10. 🔽 **Descida Recursiva (LL Parsing) - [ESCOLHIDA](#)** 
A **descida recursiva** é um método **descendente** (ou **top-down**) de parsing, que constrói a árvore sintática do topo para a base. O **LL(1)** é um exemplo típico desse método, onde:

- O primeiro `L` indica que o parser lê a entrada da esquerda para a direita.
- O segundo `L` significa que ele constrói uma derivação mais à esquerda.
- O número `1` indica que ele utiliza **apenas um símbolo de lookahead** para decidir a produção a ser utilizada.

Vantagens:
- Fácil de implementar usando recursão.
- Funciona bem para gramáticas simples e livres de ambiguidade.

Limitações:
- Não lida bem com gramáticas ambíguas ou recursão à esquerda.

### 11. ⬆️ **Métodos Shift-Reduce (LR Parsing)** 
Os métodos **shift-reduce** são exemplos de parsing **ascendente** (ou **bottom-up**), onde a árvore é construída das folhas até a raiz. O **LR(1)** é um exemplo popular desse método. Neste processo:

- **Shift**: Lê um símbolo da entrada e o adiciona à pilha.
- **Reduce**: Substitui um conjunto de símbolos na pilha por um não-terminal, aplicando uma produção da gramática.

Vantagens:
- Capaz de lidar com gramáticas complexas e ambíguas.
- Mais poderoso que o LL(1).

Tipos comuns de parsing LR incluem:
- **SLR(1)**: Simple LR, mais simples e eficiente, mas com suporte limitado para algumas gramáticas.
- **LR(1)**: Full LR, mais poderoso, mas com tabelas maiores.
- **LALR(1)**: Look-Ahead LR, uma versão otimizada e frequentemente usada em compiladores.

---

>Essas técnicas de parsing são fundamentais para garantir que o compilador interprete corretamente a estrutura sintática do código, facilitando as etapas de geração de código e execução. Cada método tem suas vantagens e limitações, sendo escolhido com base na complexidade da linguagem e nas necessidades específicas do compilador.


## 🚀 Utilização do Projeto

Para utilizar o analisador léxico e sintático, siga os passos abaixo:

1. Navegue até o diretório `anasin`:
   ```bash
   cd anasin
   ```

2. Execute o comando:
    ```bash
    ./anasin [NOME ARQUIVO].txt
    ```

**Obs.:** Tenha certeza que esse arquivo texto esteja no diretório `codigos_entrada`.

3. O analisador sintático processará o arquivo e retornará a árvore abstrata dos tokens caso a entrada esteja sintaticamente correta.

## 📂 Estrutura de Diretórios

```bash
.
├── analex/
│   ├── scanner.cpp        # Implementação do scanner
│   ├── scanner.h        # Arquivo de cabeçalho do scanner
│   ├── tabela_simbolos.cpp # Implementação da tabela de símbolos
│   ├── tabela_simbolos.h # Arquivo de cabeçalho da tabela de símbolos
│   ├── analex.cpp      # Implementação do analisador léxico
│   ├── analex.h      # Arquivo de cabeçalho do analisador léxico
└── anasin/  
│   ├── anasin/           # Executável do analisador
│   ├── anasin.cpp        # Implementação do analisador sintático usando o método descida recursiva
│   ├── anasin.h          # Arquivo de interface
│   ├── tree.cpp          # Implementação da estrutra de árvore
│   ├── tree.h            # Arquivo de interface
│   ├── first_follow.cpp  # Cálculo das funções FIRST e FOLLOW
│   ├── first_follow.h    # Arquivo de interface
└── codigos_entrada/      # Diretório contendo arquivos de entrada .txt
└── conversao/       # Algoritmo de conversão AFND -> AFD
└── gera_tabela_dt/  # Algoritmo que lê sobre o arquivo que representa o AFD e cria a tabela de transição (TAD)
```

## 🛠️ Dependências

O projeto é escrito em C/C++, então você precisará de um compilador como o GCC.  
Certifique-se de que os arquivos de entrada sigam a sintaxe definida pela linguagem simplificada.

## 🤝 Contribuições

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou pull requests.

### 👤 Gustavo Alves de Oliveira