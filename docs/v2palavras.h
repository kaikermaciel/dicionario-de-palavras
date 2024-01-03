#include "ddinamico.h"
#include "listase.h"

typedef struct palavra TPalavra;
typedef struct pagina TPagina;
typedef struct dados TDados;
typedef struct contador TContadorP;
typedef struct nota TNota;

typedef int (* TComparar)(void*, void*);

TPalavra* criarPalavra(char* palavra, int chave);
TPagina* criarPag(int pag);
TDados* criarDados(TComparar comparar);

int gerarChave(char* palavra);
void leituraPalavras(t_dd* palavras, FILE* arquivo, TDados* dados);
void imprimirPagina(TPagina* pag);
void infoPalavra(t_lse* lista);
int compararPalavra(void *palavra1, void *palavra2);
void gerarIndiceRemissivo(TDados* dados, t_dd* palavras);
void imprimir_com_letra(const char *nomeArquivo, char letra);
int compararPalavras2(const void *a, const void *b);
void organizarEmOrdemAlfabetica(FILE *nomeArquivo);
void imprimir_indice(FILE *arquivo);
void removerPalavrasRepetidas(FILE* arquivo);