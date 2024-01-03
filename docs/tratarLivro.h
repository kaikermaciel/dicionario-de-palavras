#include "dicionarioestatico.h"
typedef char t_sw;

void to_lower_case(char palavra[]);
t_sw* criar_sw(char palavra[]);
void imprimir_sw(void* p);
int comparar_sw(void* sw1, void* sw2);
int tamanho_livro(char nome_livro[]);
t_de* guardar_sw(char nome_livro[]);
void tratar_palavra(char palavra[]);
void to_lower_case(char *str);
void tratar_livro_sw(char nome_livro[], t_de* sw);
void tratar_livro_art(char nome_livro[], t_de* art);
