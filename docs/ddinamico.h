typedef struct ddinamico t_dd;

t_dd* criar_dd(int fator_carga, int tamanho);

void inserir_dd(t_dd *dd, int chave, void* info);
void* buscar_dd(t_dd *dd, int chave);
void* remover_dd(t_dd *dd, int chave);
void imprimir_dd(t_dd *dd);
int comparar_entrada_dd(void* e1, void* e2);

int qtd_elementos(t_dd* dd);
void* buscar_index_dd(t_dd* dd, int index);
int tamanho_dd(t_dd* dd);
int colisoes(t_dd *dicionario);
t_dd* re_hashing_dd(t_dd *atual);
t_dd* faz_rehashing(t_dd *dd);
void destruir_dd(t_dd *dd);

void imprimir_dd(t_dd *dd);