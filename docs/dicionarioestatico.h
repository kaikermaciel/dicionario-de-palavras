typedef void(*t_imprimir_de)(void*);
typedef int (*t_comparar_de)(void*, void*);
typedef struct dicionario t_de;
typedef struct elem t_elem;

// t_elem criar_elem(int chave, void* info);


t_de* criar_de(t_imprimir_de imprimir, t_comparar_de comparar, int tamanho);
void inserir_de(t_de* de, void* elem);
void* buscar_de(t_de* de, void* chave);
int ocupacao_de(t_de* de);
