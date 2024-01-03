#include "stdio.h"
#include "stdlib.h"
#include "listase.h"

typedef struct elem_se{
    void* carga_util;
    struct elem_se* prox;
} t_elemento_lse;

/**
 * cria um elemento da LSE
*/
t_elemento_lse* criar_elemento_lse(void* carga_util){
    t_elemento_lse* novo = malloc(sizeof(t_elemento_lse));
    novo->carga_util = carga_util;
    novo->prox = NULL;

    return novo;
}

typedef struct lse t_lse;
struct lse{
    t_elemento_lse* inicio;
    t_elemento_lse* fim;
    int tamanho;
    // operacoes
    t_imprimir_lse imprimir;
    t_comparar_lse comparar;

};

t_elemento_lse* ultimo(t_lse* lse){
    return lse->fim;
}

t_lse* criar_lse(t_imprimir_lse imprimir, t_comparar_lse comparar){
    t_lse *l = malloc(sizeof(t_lse));
    l->inicio = l->fim = NULL;
    l->tamanho = 0;
    l->imprimir = imprimir;
    l->comparar = comparar;
    return l;
}

void inserir_lse(t_lse* lse, void* carga_util){
    t_elemento_lse* novo = criar_elemento_lse(carga_util);

    if (lse->inicio == NULL){
        lse->inicio = lse->fim = novo; 
    }else{
        novo->prox = lse->inicio;
        lse->inicio = novo;
    }

    lse->tamanho++;
}

void inserir_conteudo_lse(t_lse* lse, void* carga){
    if(lse){
        if(lse->inicio == NULL){
            inserir_lse(lse, carga);
        }
        else{
            t_elemento_lse* cam = lse->inicio;
            if(lse->comparar(cam->carga_util, carga) > 0){
                inserir_lse(lse, carga);
            }
            else{
                while((cam->prox != NULL) && (lse->comparar(cam->prox->carga_util, carga) < 0)){
                    cam = cam->prox;
                }
                if(cam->prox == NULL){
                    inserir_final_lse(lse, carga);
                }
                else{
                    t_elemento_lse* novo = criar_elemento_lse(carga);
                    novo->prox = cam->prox;
                    cam->prox = novo;
                    
                }
            }
        }
    }
    

}

t_lse* proximo_lse(t_lse* lse){
    t_elemento_lse* cam = lse->inicio;
    if(lse->inicio){
        lse->inicio = cam->prox;
        return lse;
    }
}

void inserir_final_lse(t_lse* lse, void*carga_util){
    t_elemento_lse* novo = criar_elemento_lse(carga_util);

    if(!lse->inicio){
        lse->inicio=lse->fim=novo;
    }
    else{
        lse->fim->prox = novo;
        lse->fim = novo;
    }
    lse->tamanho++;
}

void* remover_lse(t_lse* lse){
    void* carga_util = NULL;
    t_elemento_lse *removivel = lse->inicio;
    if (lse->inicio != NULL){
        carga_util = removivel->carga_util;
        lse->inicio = removivel->prox;
        free(removivel);
        lse->tamanho--;
    }
    return carga_util;
}

void* acessar_lse(t_lse* lse, int pos){
    pos = (pos>lse->tamanho?pos%lse->tamanho:pos);
    t_elemento_lse *cam = lse->inicio;
    void* carga_util=NULL;

    if (lse->inicio){
        int i=1;
        while(i<pos){
            cam = cam->prox;
            i++;
        }
        carga_util = cam->carga_util;  
    }
    return carga_util;
}

void imprimir_lse(t_lse *lse){
    t_elemento_lse *cam = lse->inicio;
    if(cam){
        while(cam){
            lse->imprimir(cam->carga_util);
            cam = cam->prox;
        }
    }
    else{printf("nao tem inicio\n");}
}

void imprimir_unico_lse(t_lse* lse, void* carga_util){
    lse->imprimir(carga_util);
}

int tamanho_lse(t_lse* lse){
    if(lse){return lse->tamanho;}
}

void* primeiro_lse(t_lse* lse){
    if(lse){
        if(lse->inicio){
            return lse->inicio->carga_util;
        }
        else{return NULL;}
    }
}

void* buscar_lse(t_lse* lse, void* carga_util){
    t_elemento_lse* procurador;
    if(lse && lse->inicio){
        procurador = lse->inicio;
        while (procurador)
        {
            if(lse->comparar(procurador->carga_util, carga_util) == 0){
                return procurador->carga_util;
            }
            else{
                procurador = procurador->prox;
            }
        }
        return NULL;
        
    }
}

void* remover_procurado_lse(t_lse* lse, void* carga){
    t_elemento_lse* procurador;
    if(lse && lse->inicio){
        procurador = lse->inicio;
        if(lse->comparar(procurador->carga_util, carga) == 0){
            remover_lse(lse);
        }
        else{
            while (procurador->prox)
            {
                if(lse->comparar(procurador->prox->carga_util, carga) == 0){
                    break;
                }
                else{
                    procurador = procurador->prox;
                }
            }
            if(!procurador->prox){
                return NULL;
            }
            else{
                t_elemento_lse* eliminado = procurador->prox;
                procurador->prox = eliminado->prox;
                void* carga_util = eliminado ->carga_util;
                free(eliminado);
            }
        }
        
        
    }
}
void destruir_lse(t_lse* *rl){

  while((*rl)->inicio != NULL){
      void* carga = remover_lse(*rl);
      //free(carga);
  }
  free(*rl);
  *rl = NULL;
}