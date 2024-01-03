#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include <wchar.h>
#include "ddinamico.h"
#include "listase.h"
#include "v2palavras.h"
#include "locale.h"
#include <ctype.h>

struct palavra
{
    char palavra[47];
    int chave;
};

struct pagina
{
    int pag;
    int ocorrencias;
    double tf;
};

struct dados
{
    int palavras;
    int paginas;
    t_lse *listaPalavras;
    t_lse *listaLinhas;
};

struct contador
{
    int quantidadePalavras;
};

struct nota
{
    double tfidf;
    int pag;
};

TPalavra *criarPalavra(char *palavra, int chave)
{
    TPalavra *p = malloc(sizeof(TPalavra));

    strcpy(p->palavra, palavra);
    p->chave = chave;
    return p;
}

TPagina *criarPag(int pag)
{
    TPagina *pagina = malloc(sizeof(TPagina));

    pagina->pag = pag;
    pagina->ocorrencias = 1;
    pagina->tf = 0;

    return pagina;
}

TDados *criarDados(TComparar comparar)
{
    TDados *dados = malloc(sizeof(TDados));

    dados->listaLinhas = criar_lse(NULL, NULL);
    dados->listaPalavras = criar_lse(NULL, comparar);
    dados->palavras = 0;
    dados->paginas = 0;

    return dados;
}

TContadorP *criarContador(int quantPalavras)
{
    TContadorP *c = malloc(sizeof(TContadorP));

    c->quantidadePalavras = quantPalavras;

    return c;
}

TNota *criarNota(double tfidf, int pag)
{
    TNota *nota = malloc(sizeof(TNota));

    nota->tfidf = tfidf;
    nota->pag = pag;

    return nota;
}

int n_containing_page(int num, t_dd *dicionario, TDados *dados)
{
    int n = 0;

    for (int i = 1; i <= tamanho_lse(dados->listaPalavras); i++)
    {
        TPalavra *p = acessar_lse(dados->listaPalavras, i);
        t_lse *listaPags = buscar_dd(dicionario, p->chave);
        int qnt_paginas = tamanho_lse(listaPags);

        for (int j = 1; j <= qnt_paginas; j++)
        {
            TPagina *pag = acessar_lse(listaPags, j);
            if (pag->pag == num)
                n++;
        }
    }

    return n;
}

int n_containing(int chave, t_dd *dicionario)
{
    return tamanho_lse(buscar_dd(dicionario, chave));
}

// qnt_ocorrencias = quantidade de vezes que uma palavra ocorre em um documento
// qnt_palavras = quantidade total de palavras no documento
double tf(int qnt_ocorrencias, int qnt_palavras)
{
    return (double)qnt_ocorrencias / (double)qnt_palavras;
}

// qnt_documentos = quantidade de documentos na coleção (qnt paginas)
// qnt_documento_ocorrem = quantidade de documentos que contêm a palavra
double idf(int qnt_paginas, int qnt_paginas_ocorrem)
{
    return log((double)qnt_paginas / (double)(qnt_paginas_ocorrem + 1));
}

double tf_idf(double tf, double idf)
{
    return tf * idf;
}

void calcula_tf(t_dd *dicionario, TDados *dados)
{
    for (int i = 1; i <= tamanho_lse(dados->listaPalavras); i++)
    {
        TPalavra *p = acessar_lse(dados->listaPalavras, i);
        t_lse *listaPags = buscar_dd(dicionario, p->chave);
        int qnt_paginas = tamanho_lse(listaPags);

        for (int j = 1; j <= qnt_paginas; j++)
        {
            TPagina *pag = acessar_lse(listaPags, j);
            TContadorP *c = acessar_lse(dados->listaLinhas, pag->pag);
            pag->tf = tf(pag->ocorrencias, c->quantidadePalavras);
        }
    }
}

double calcula_idf(TPalavra *p, t_dd *dicionario, TDados *dados)
{
    return idf(dados->paginas, n_containing(p->chave, dicionario));
}

int gerarChave(char *palavra)
{
    int chave = 0;
    int g = 31;
    int tam = strlen(palavra);

    for (int i = 0; i < tam; i++)
        chave = g * chave + (int)palavra[i];

    if (chave < 0)
        return (chave * -1) + strlen(palavra);
    else
        return chave + strlen(palavra);
}

static int verificaPrimeiraLetra(char *p)
{
    if (((p[0] > 64) && (p[0] < 91)) || ((p[0] > 96) && (p[0] < 123)))
        return 1;
    else
        return 0;
}

void leituraPalavras(t_dd *palavras, FILE *arquivo, TDados *dados)
{
    FILE *aux = fopen("palavras_e_chaves.txt", "w");
    FILE *indice = fopen("indice.txt", "w");

    char frase[255];
    char *palavra = NULL;
    int chave = 0;

    int palavras_linha = 0;
    while (fgets(frase, sizeof(frase), arquivo) != NULL)
    {
        palavra = strtok(frase, " ");

        while (palavra != NULL)
        {

            palavra[strcspn(palavra, "\r\n")] = 0;

            if (strcmp(palavra, "PA") != 0 && strlen(palavra) >= 3 && verificaPrimeiraLetra(palavra) == 1)
            {
                chave = gerarChave(palavra);
                dados->palavras++;
                palavras_linha++;

                if (buscar_dd(palavras, chave) == NULL)
                {
                    TPalavra *p = criarPalavra(palavra, chave);
                    inserir_conteudo_lse(dados->listaPalavras, p);
                    t_lse *listaPags = criar_lse(NULL, NULL); // cria a lista que ira conter as paginas que a palavra ocorre
                    TPagina *pag = criarPag(dados->paginas);    // cria a primeira pag que a palavra ocorre
                    inserir_lse(listaPags, pag);           // adiciona essa pagina na lista de paginas
                    fprintf(indice, "%s\n", palavra);
                    inserir_dd(palavras, chave, listaPags);     // faz a inserção da palavra (chave) e da lista de pags no dicionario dinamico
                    //palavras = faz_rehashing(palavras);
                }
                else
                {
                    t_lse *listaPags = buscar_dd(palavras, chave);
                    TPagina *pag = acessar_lse(listaPags, 1);

                    if (pag->pag == dados->paginas)
                    {
                        pag->ocorrencias++;
                    }
                    else
                    {
                        pag = criarPag(dados->paginas);   // cria uma nova pag que a palavra ocorre
                        inserir_lse(listaPags, pag); // adiciona a nova pagina na lista de paginas
                    }
                }
                fprintf(aux, "%s %d\n", palavra, chave); // guarda as chaves num arquivo auxiliar
            }
            else if (strcmp(palavra, "PA") == 0)
            {
                dados->paginas++;

                if (palavras_linha > 0)
                {
                    TContadorP *c = criarContador(palavras_linha);
                    inserir_final_lse(dados->listaLinhas, c);
                }
            }
            palavra = strtok(NULL, " ");
        }
    }

    TContadorP *c = criarContador(palavras_linha);
    inserir_final_lse(dados->listaLinhas, c);

    // Calcular o tf para cada pagina
    calcula_tf(palavras, dados);

    printf("Total de palavras: %d\n", dados->palavras);
    printf("Total de paginas: %d\n", dados->paginas);
}

// Imprime uma página
void imprimirPagina(TPagina *pag)
{
    if (pag->ocorrencias > 1)
    {
        printf("Pagina %d, %d vezes\n", pag->pag, pag->ocorrencias);
    }
    else
    {
        printf("Pagina %d, %d vez\n", pag->pag, pag->ocorrencias);
    }
}

// Mostra todas as paginas e as ocorrencias de uma palavra
void infoPalavra(t_lse *lista)
{
    int pos = tamanho_lse(lista);
    TPagina *pag;

    while (pos > 0)
    {
        pag = acessar_lse(lista, pos);
        imprimirPagina(pag);
        pos--;
    }
}

int compararPalavra(void *palavra1, void *palavra2)
{
    TPalavra *p1 = palavra1;
    TPalavra *p2 = palavra2;

    if (strcmp(p1->palavra, p2->palavra) < 0)
    {
        if (p2->palavra[0] > p1->palavra[0])
        {
            return 1;
        }
        else if (p2->palavra[0] == p1->palavra[0])
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
    else if (strcmp(p1->palavra, p2->palavra) > 0)
    {
        if (p1->palavra[0] > p2->palavra[0])
        {
            return -1;
        }
        else if (p1->palavra[0] == p2->palavra[0])
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 0;
    }
}

int compararTfidf(void *tfidf1, void *tfidf2)
{
    TNota *n1 = tfidf1;
    TNota *n2 = tfidf2;

    if (n1->tfidf > n2->tfidf)
    {
        return 1;
    }
    else if (n1->tfidf < n2->tfidf)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

void gerarIndiceRemissivo(TDados *dados, t_dd *dinamico)
{
    FILE *aux = fopen("indiceRemissivo.txt", "w");
    t_lse *listaPalavras = dados->listaPalavras;
    int pos = 1;
    while (pos <= tamanho_lse(listaPalavras))
    {
        TPalavra *p = acessar_lse(listaPalavras, pos);

        double idf = calcula_idf(p, dinamico, dados);
        // Imprime a palavra
        fprintf(aux, "%s ", p->palavra);

        t_lse *listaPags = buscar_dd(dinamico, p->chave);
        t_lse *listaNotas = criar_lse(NULL, compararTfidf);
        for (int j = tamanho_lse(listaPags); j > 0; j--)
        {
            TPagina *pag = acessar_lse(listaPags, j);
            TNota *nota = criarNota(tf_idf(pag->tf, idf), pag->pag);
            inserir_conteudo_lse(listaNotas, nota);
        }

        int qntNotas = tamanho_lse(listaNotas);
        if (qntNotas > 0) // Verifique se há notas antes de imprimir
        {
            for (int j = 1; j <= qntNotas; j++)
            {
                TNota *nota = acessar_lse(listaNotas, j);
                fprintf(aux, "- [Pag. %d TF-IDF: %.11lf] ", nota->pag, nota->tfidf);
            }
            fprintf(aux, "\n");
        }

        pos++;
    }

    fclose(aux); // Certifique-se de fechar o arquivo após escrever os dados.
}


void imprimir_com_letra(const char *nomeArquivo, char letra)
{
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char palavra[255];
    while (fscanf(arquivo, "%s", palavra) != EOF)
    {
        // Verifica se a primeira letra da palavra é igual à letra desejada
        if (isalpha(palavra[0]) && tolower(palavra[0]) == tolower(letra))
        {
            printf("%s\n", palavra);
        }
    }

    fclose(arquivo);
}

// Função de comparação para o qsort
int compararPalavras2(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void organizarEmOrdemAlfabetica(FILE* arquivo) {
    char **palavras = NULL;
    FILE* arq;
    char palavra[255];
    int numPalavras = 0;

    // Ler as palavras do arquivo e armazená-las dinamicamente em um array de strings
    while (fscanf(arquivo, "%s", palavra) != EOF) {
        if (isalpha(palavra[0])) {
            numPalavras++;
            palavras = (char **)realloc(palavras, numPalavras * sizeof(char *));
            palavras[numPalavras - 1] = strdup(palavra);
        }
    }


    // Ordenar as palavras em ordem alfabética usando qsort
    qsort(palavras, numPalavras, sizeof(char *), compararPalavras2);

    // Abrir o arquivo para escrita
    arq = fopen("palavras_ordenadas.txt", "w");

    if (arq == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Escrever as palavras ordenadas de volta no arquivo
    for (int i = 0; i < numPalavras; i++) {
        fprintf(arq, "%s\n", palavras[i]);
        free(palavras[i]); // Liberar a memória alocada para cada palavra
    }

    free(palavras); // Liberar o array de strings
    fclose(arq);
}

void imprimir_indice(FILE *arquivo) {
    setlocale(LC_ALL, "pt-BR.UTF-8");
    char linha[255];

    while (fgets(linha, sizeof(linha) / sizeof(char), arquivo) != NULL) {
        printf("%s", linha); // Use wprintf para imprimir caracteres wide
    }

    fclose(arquivo);
}

void removerPalavrasRepetidas(FILE* arquivo) {
    FILE *saida = fopen("lita_de_palavras.txt", "w");

    if (arquivo == NULL || saida == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        exit(1);
    }

    char palavraAnterior[100]; // Assumindo que nenhuma palavra tem mais de 100 caracteres
    char palavraAtual[100];

    if (fscanf(arquivo, "%s", palavraAnterior) == 1) {
        fprintf(saida, "%s\n", palavraAnterior); // Remova o espaço em branco após a palavra

        while (fscanf(arquivo, "%s", palavraAtual) == 1) {
            if (strcmp(palavraAnterior, palavraAtual) != 0) {
                fprintf(saida, "%s\n", palavraAtual); // Remova o espaço em branco após a palavra
                strcpy(palavraAnterior, palavraAtual);
            }
        }
    }

    fclose(saida);
}
