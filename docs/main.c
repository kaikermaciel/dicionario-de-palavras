#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ddinamico.h"
#include "dicionarioestatico.h"
#include "listase.h"
#include "tratarLivro.h"
#include "v2palavras.h"
#include <locale.h>

int main(int argc, char const *argv[]) {
    char select;
    char artigo[100];
    char livro[100];
    char stop[100];
    float limite_local, limite_global;
    scanf("%f %f", &limite_local, &limite_global);
    scanf("%s%*c", artigo);
    scanf("%s%*c", stop);
    scanf("%s%*c", livro);
    setlocale(LC_ALL, "pt-BR.UTF-8");
    t_de* sw = guardar_sw(stop);
    t_de* art = guardar_sw(artigo);
    tratar_livro_art(livro, art);
    tratar_livro_sw("livro_auxiliar.txt", sw);

    FILE *livro_tratado = fopen("livro_processado.txt", "r+");
    t_dd* word = criar_dd(2, 2);
    TDados* dados = criarDados(compararPalavra);
    leituraPalavras(word, livro_tratado, dados);
    gerarIndiceRemissivo(dados, word);

    printf("Quantidade de palavras no indice remissivo: %d\n", qtd_elementos(word));

    char palavra[47];
    char letra;
    FILE* fp = fopen("indice.txt", "r");
    scanf(" %c", &select);

    while (select != 'F') {
        switch (select) {
            case 'C':
                scanf("%s", palavra);
                to_lower_case(palavra);
                int chave = gerarChave(palavra);
                t_lse* pags = buscar_dd(word, chave);
                if (pags) {
                    printf("A palavra (%s) esta no indice e se encontra em:\n", palavra);
                    infoPalavra(pags);
                } else {
                    printf("A palavra (%s) nao esta no indice\n", palavra);
                }
                break;

            case 'L':
                scanf(" %c", &letra);
                printf("As palavras que começam com a letra (%c) sao:\n", letra);
                imprimir_com_letra("palavras_e_chaves.txt", letra);
                break;

            case 'P':
                organizarEmOrdemAlfabetica(fp);
                fclose(fp);
                fp = fopen("palavras_ordenadas.txt", "r");
                removerPalavrasRepetidas(fp);
                fclose(fp);
                fp = fopen("lita_de_palavras.txt", "r");
                imprimir_indice(fp);
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }

        // Ler a próxima seleção do usuário
        scanf(" %c", &select);
    }
    return 0;
}
