# Projeto de Dicionário

## Trabalho em Grupo: Dicionários e Índice Remissivo com Uso de Arquivos e Stop Words

### Descrição do Projeto

Este projeto tem como objetivo a implementação de um sistema eficiente para manipulação de dicionários e criação de índice remissivo, utilizando linguagem C no curso de algoritmos e estrutura de dados. O foco principal é trabalhar com arquivos e lidar com stop words para otimizar a indexação.

### Integrantes do Grupo

- Kaike Maciel
- Ricardo Eliel
- Jhonntha Carvalho
- Lucas Martini
- Paulo Ricardo

### Funcionalidades Implementadas

1. **Leitura de Arquivos:**
   - Desenvolvemos um módulo para a leitura de arquivos textuais, permitindo a entrada de documentos para indexação.

2. **Tratamento de Stop Words:**
   - Implementamos um mecanismo para identificar e remover stop words, melhorando a qualidade do índice remissivo.

3. **Construção do Dicionário:**
   - Utilizamos estruturas de dados eficientes para construir um dicionário contendo as palavras-chave e suas ocorrências nos documentos.

4. **Índice Remissivo:**
   - Criamos um índice remissivo que facilita a busca rápida de termos nos documentos, fornecendo referências para suas localizações.

5. **Persistência de Dados:**
   - Implementamos métodos para salvar e carregar o estado do dicionário e do índice remissivo, garantindo a preservação dos dados entre execuções.

### Intruções de Execução

## Compilação Windows:

gcc -o NOME_DO_EXECUTAVEL .\main.c .\listase.c .\dicionarioestatico.c .\dicionariodinamico.c .\trataLivro.c .\v2palavras.c -lm

## Compilação Linux

gcc -o NOME_DO_EXECUTAVEL main.c listase.c dicionarioestatico.c dicionariodinamico.c trataLivro.c v2palavras.c -lm

## Execução

tdif local tdif global
arquivo dos artigos
arquivo das stop_words
arquivo do livro

C -> Ocorrencia das palavras || C amor
L -> Palavras que começam com determinada letra || L a
P -> Indice remissivo || P z
F -> Encerrar Programa
