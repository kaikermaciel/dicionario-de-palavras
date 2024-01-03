#include "stdio.h"
#include "assert.h"
#include "stdlib.h"
#include "listase.h"
#include "ddinamico.h"

struct ddinamico{
  // dados
  int tamanho;
  int nro_elementos;
  int fc;

  t_lse* *entradas;
  // estatistica


  int nro_remocao;
  int nro_busca;
  int nro_insercao;
  long int nro_cmps_por_rmc;
  long int nro_cmps_por_bsc;
};

struct entrada{
  int chave;
  void* info;
};

typedef struct entrada t_entrada_dd;

t_entrada_dd* criar_entrada_dd(int chave, void* info){
  t_entrada_dd* entrada = malloc(sizeof(t_entrada_dd));

  entrada->chave = chave;
  entrada->info = info;

  return entrada;
}

static int hashing(t_dd* dd, int chave){
  return (chave % dd->tamanho);
}

static int primo_proximo(int num){
  short encontrou = 0;
  while(!encontrou){
    int i=2;
    while( (i<num) && ( (num%i) != 0) ){
      i++;
    }
    if (i==num){
      encontrou=1;
    }else{
      num+=1;
    }
  }
  return num;
}

int comparar_entrada_dd(void* e1, void* e2){
  t_entrada_dd* ee1 = e1;
  t_entrada_dd* ee2 = e2;

  return (ee1->chave - ee2->chave);
}

t_dd* criar_dd(int fator_carga, int tamanho){
    t_dd* dd = malloc(sizeof(t_dd));
    dd->fc = fator_carga;

    dd->tamanho = primo_proximo(tamanho);
    dd->nro_elementos = 0;
    dd->entradas = malloc(sizeof(t_lse*)*dd->tamanho);

    for(int i=0;i<dd->tamanho;i++){
      dd->entradas[i] = criar_lse(NULL,comparar_entrada_dd);
    }
    dd->nro_busca = dd->nro_remocao = dd->nro_insercao = 0;
    dd->nro_cmps_por_bsc = dd->nro_cmps_por_rmc = 0;

    return dd;

}

void inserir_dd(t_dd *dd, int chave, void* info){
  int k = hashing(dd,chave);
  t_lse* lista =  dd->entradas[k];
  inserir_lse(lista, criar_entrada_dd(chave,info));

  dd->nro_elementos++;
  dd->nro_insercao++;
}

int qtd_elementos(t_dd* dd){
  return dd->nro_elementos;
}

void* buscar_dd(t_dd *dd, int chave){
  int k = hashing(dd,chave);
  t_lse* lista =  dd->entradas[k];

  t_entrada_dd* entrada = buscar_lse(lista, &chave);

  dd->nro_busca++;
  dd->nro_cmps_por_bsc += tamanho_lse(lista); //assume que toda busca a gente faz o numero máximo de comparações (tamanho da lista)

  return (entrada?entrada->info:entrada);
}

void* buscar_index_dd(t_dd* dd, int index){
  if(index <= dd->tamanho){
    return dd->entradas[index];
  }else{
    return NULL;
  }
}

int tamanho_dd(t_dd* dd){
  return dd->tamanho;
}

void* remover_dd(t_dd *dd, int chave){
  int k = hashing(dd,chave);
  t_lse* lista =  dd->entradas[k];

  t_entrada_dd* entrada = remover_procurado_lse(lista, &chave);
  void* info = NULL;

  if(entrada!=NULL){
    info = entrada->info;
    free(entrada);
  }

  dd->nro_remocao++;
  dd->nro_cmps_por_rmc += tamanho_lse(lista);

  return info;
}

int colisoes(t_dd *dicionario){
  int c = 0;
  
  for(int i = 0; i < dicionario->tamanho;i++){
    t_lse* l = dicionario->entradas[i];
    int tam_l = tamanho_lse(l);
    if(tam_l > 1){
      c += 1;
    }
  }

  return c;
}

t_dd* re_hashing_dd(t_dd *atual){
    t_dd *novo;


    int fator_carga = atual->fc;
    int tamanho = atual->tamanho + 1;
    novo = criar_dd(fator_carga, tamanho);
    
    for(int i=0;i<atual->tamanho;i++){
      t_lse *lse = atual->entradas[i];

      t_entrada_dd *e = remover_lse(lse);
      while(e!=NULL){
        inserir_dd(novo, e->chave, e->info);
        free(e);
        e = remover_lse(lse);
      }

    }
    destruir_dd(atual);
    return novo;
}

t_dd* faz_rehashing(t_dd *dd){

  int s_x=0, n = 0;
  for(int x, i=0; i < dd->tamanho; i++){
    t_lse* lse = dd->entradas[i];
     x = tamanho_lse(lse);
     s_x += x*x;
     n += x;
  }
  double C = (double)s_x/(double)n - dd->fc;

  if (C > 1.0){
    return re_hashing_dd(dd);
  }else{
    return dd;
  }
}

void destruir_dd(t_dd *dd){
  for(int i=0; i<dd->tamanho;i++){
    destruir_lse(&(dd->entradas[i]));
  }
  free(dd->entradas);
  free(dd);
}

void imprimir_dd(t_dd *dd) {
    if (dd) {
        printf("Numero de elementos: %d\n", dd->nro_elementos);
        printf("Numero de insercoes: %d\n", dd->nro_insercao);
        printf("Numero de buscas: %d\n", dd->nro_busca);
        }
}