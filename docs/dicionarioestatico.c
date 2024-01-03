#include <stdio.h>
#include <stdlib.h>
#include "dicionarioestatico.h"
#include <string.h>

struct dicionario{    // Estrutura do dicionario estatico.
    void* *elem;
    int tamanho;
    int ocupacao;
    t_imprimir_de imprimir;
    t_comparar_de comparar;
};

t_de* criar_de(t_imprimir_de imprimir, t_comparar_de comparar, int tamanho){    //criar dicionario estatico.
    t_de* de = malloc(sizeof(t_de));
    de->tamanho = tamanho;
    de->elem = malloc(sizeof(void*)*de->tamanho);
    de->imprimir = imprimir;
    de->comparar = comparar;
    de->ocupacao = 0;

    return de;
}

void inserir_de(t_de* de, void* elem){  // inserir elementos no dicionario estatico, nesse caso as stop words.
    int pos = de->ocupacao;
    de->elem[pos] = elem;
    de->ocupacao++;

}

void* buscar_de(t_de* de, void* chave){   // buscar elementos no dicionario estatico.
    void* elem = NULL;

    if(de->ocupacao > 0){
        for(int i = 0; i < de->ocupacao; i++){
            if(de->comparar(de->elem[i], chave) == 0){
                elem = de->elem[i];
                break;
            }
        }
    }   

    return elem;
}

int ocupacao_de(t_de* de){  // Retorna o número total de elementos no dicionario.
    return de->ocupacao;
}