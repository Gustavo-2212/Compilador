# 🛠️ Analisador Léxico de Compilador

> Este projeto implementa o **analisador léxico** (ou scanner) de um compilador para uma linguagem simplificada. O analisador léxico é uma das primeiras fases de um compilador e é responsável por ler o código-fonte de entrada e convertê-lo em uma sequência de tokens que serão utilizados pelas próximas fases do compilador.

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

## 🚀 Utilização do Projeto

Para utilizar o analisador léxico, siga os passos abaixo:

1. Navegue até o diretório `analex`:
   ```bash
   cd analex
   ```

2. Execute o comando:
    ```bash
    ./anasin [NOME ARQUIVO].txt
    ```

**Obs.:** Tenha certeza que esse arquivo texto esteja no diretório `codigos_entrada`.

3. O analisador léxico processará o arquivo e retornará a lista de tokens identificados no terminal, juntamente com informações como tipo de token e lexema.

## 📂 Estrutura de Diretórios

```bash
.
├── analex/
│   ├── anasin/           # Executável do analisador
│   ├── anasin.cpp       # Arquivo de implementação (simula) o analisador sintático
│   ├── scanner.cpp        # Implementação do scanner
│   ├── scanner.h        # Arquivo de cabeçalho do scanner
│   ├── tabela_simbolos.cpp # Implementação da tabela de símbolos
│   ├── tabela_simbolos.h # Arquivo de cabeçalho da tabela de símbolos
│   ├── analex.cpp      # Implementação do analisador léxico
│   ├── analex.h      # Arquivo de cabeçalho do analisador léxico
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