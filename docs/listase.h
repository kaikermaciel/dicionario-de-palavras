
typedef void (*t_imprimir_lse)(void*);
typedef int (*t_comparar_lse)(void*, void*);

typedef struct lse t_lse;
typedef struct elem_se t_elemento_lse;

t_lse* criar_lse(t_imprimir_lse imprimir, t_comparar_lse comparar);


void inserir_final_lse(t_lse* lse, void*carga_util);
void inserir_lse(t_lse* lse, void* carga_util);
void inserir_conteudo_lse(t_lse* lse, void* carga);
int tamanho_lse(t_lse* lse);
void* primeiro_lse(t_lse* lse);
void* remover_lse(t_lse* lse);
void* acessar_lse(t_lse* lse, int pos);
void* buscar_lse(t_lse* lse, void* carga_util);
void* remover_procurado_lse(t_lse* lse, void* carga);
void imprimir_lse(t_lse *lse);
void imprimir_unico_lse(t_lse* lse, void* carga);
t_elemento_lse* ultimo(t_lse* lse);
void destruir_lse(t_lse* *rl);