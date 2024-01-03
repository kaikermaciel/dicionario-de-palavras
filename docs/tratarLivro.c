#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "dicionarioestatico.h"
#include "locale.h"
#include "tratarLivro.h"
#include "ctype.h"
#include "wchar.h"
#include "wctype.h"

typedef char t_sw;

t_sw* criar_sw(char palavra[]){      // Criar uma stop word. 
    t_sw* sw = malloc(sizeof(char)*47);
    strcpy(sw, palavra);

    return sw;
}

void imprimir_sw(void* p){      // Imprimir uma stop word.
    t_sw* sw = (t_sw*)p;
    printf("%s\n", sw);
}

int comparar_sw(void* sw1, void* sw2){      // Comparar stop words.
    t_sw* s1 = (t_sw*)sw1;
    t_sw* s2 = (t_sw*)sw2;

    return strcmp(s1, s2);
}

int tamanho_livro(char nome_livro[]){       // Tamanho total do livro.
    FILE* stop_words;
    t_sw palavra[47];
    int tam = 0;
    stop_words = fopen(nome_livro, "r");
    if(!stop_words){
        printf("tamanho livro Erro ao ler o livro de sw!\n");
        exit(1);
    }

    while(fscanf(stop_words, "%[^\n]%*c", palavra) == 1){
        tam++;
    }
    fclose(stop_words);
    return tam;
}

t_de* guardar_sw(char stopwords[]){ // O nome do arquivo das stop words deve ser passado aqui.   // Armazenar Sw no dicionario estatico.
    setlocale(LC_ALL, "pt-BR.UTF-8");
    t_de* de = criar_de(imprimir_sw, comparar_sw, tamanho_livro(stopwords));
    FILE* stop_words;
    void* palavra = malloc(sizeof(t_sw)*47);
    stop_words = fopen(stopwords, "r");
    if(!stop_words){
        printf("Erro ao ler o livro de sw!\n");
        exit(1);
    }
    while(fscanf(stop_words, "%[^\n}%*c]", (char*) palavra) == 1){
        t_sw* sw = criar_sw(palavra);
        inserir_de(de, sw);
        palavra = malloc(sizeof(t_sw)*47);
    }

    fclose(stop_words);

    return de;
}

void tratar_palavra(char palavra[]) {       // Remove numeros e pontuações.
    char nova_palavra[47];
    const char pontuacao[7][2] = {",", ".", ";", "!", ":", "?", ")"};
    const char numbers[10][2] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    char *token;
    

    if (strlen(palavra) <= 2) {
        if (strcmp(palavra, "PA") != 0) {
            strcpy(palavra, "");
            return;
        }
    }

    if (strcmp(palavra,"”") == 0){
        strcpy(palavra,"");
        return;
    }

  if (strcmp(palavra,"—") == 0){
            strcpy(palavra,"");
            return;
    }

    char str_aux[strlen(palavra)];
  if (palavra[0] == '(' || palavra[0] == '[' || palavra[0] == '=' || palavra[0] == '-'){
        for(int i = 1; i <= strlen(palavra); i++){
            str_aux[i-1] = palavra[i];
        }
        strcpy(palavra,str_aux);
        return;
    }

  
  if (palavra[0]=='.'){
    strcpy(palavra,"");
    return;
  }

    if ((strncmp(palavra, "“", 3) == 0) || (strncmp(palavra, "‘", 3) == 0)) {
        for (int i = 0; palavra[i]; i++) {
            nova_palavra[i] = palavra[3 + i];
        }
        strcpy(palavra, nova_palavra);
    }

    if (strpbrk(palavra, "”") && (strcspn(palavra, "”") > 2)) {
        palavra = strtok(palavra, "”");
    }

    char *num;

    for (int i = 0; i < 10; i++) {
        num = strpbrk(palavra, numbers[i]);
        if (num) {
            palavra = strtok(palavra, pontuacao[i]);
            strcpy(palavra, "");
            return;
        }
    }

    char *ret;
    for (int i = 0; i < 7; i++) {
        ret = strpbrk(palavra, pontuacao[i]);
        if (ret) {
            palavra = strtok(palavra, pontuacao[i]);
            return;
        }
    }
}

void to_lower_case(char palavra[]) {   // Transforma as letras maiusculas em minusculas.
    
    if (strlen(palavra) <= 2) {
        if (strcmp(palavra, "PA") != 0) {
            strcpy(palavra, "");
            return;
        }
    }
    else{
        for (int i = 0; palavra[i] != '\0'; i++) {
            palavra[i] = tolower(palavra[i]);
        }
    }
}

void tratar_livro_sw(char nomeArquivo[], t_de* sw){

  FILE *livro_original;
  FILE *livro_aux;
  char frase[3000];
  char* p = NULL;
  int pag = 0;

  setlocale(LC_ALL,"pt_BR.UTF-8");
  livro_original = fopen(nomeArquivo,"r+");
  if (livro_original == NULL){
    printf("tratar livro - Erro ao Abrir o Arquivo\n");
    exit(1);
  } 

  livro_aux = fopen("livro_processado.txt","w");
  if (livro_aux == NULL){
    printf("tratar livro -  Erro ao Criar o Arquivo\n");
    exit(1);
  } 
  
  while (fgets(frase, sizeof(frase),livro_original) != NULL){ 

    p = strtok(frase," ");

    while(p != NULL){
      if(p[0] != '[' && p[0] != '('){
        p[strcspn(p, "”)]!:,.'|[(+\"")] = 0;
      }else{
        p[strcspn(p, "”)]!:,.'|+\"")] = 0;
      }
      
      if(strcmp(p," ") != 0 && strcmp(p,"\t") != 0){

        tratar_palavra(p);
        to_lower_case(p);
        if (buscar_de(sw,p) == NULL){
          if ((strcmp(p,"") != 0) && (strcmp(p," ") != 0) && (strcmp(p,"\t") != 0) && (strcmp(p,"\n") != 0) && (strcmp(p,"\b") != 0)){
            fprintf(livro_aux," %s",p);
          }
        }
      }

      p = strtok(NULL," ");
    }
    
  }
  fclose(livro_aux);
  fclose(livro_original);
}

void tratar_livro_art(char nomeArquivo[], t_de* art){

  FILE *livro_original;
  FILE *livro_aux;
  char frase[3000];
  char* p = NULL;
  int pag = 0;

  setlocale(LC_ALL,"pt_BR.UTF-8");
  livro_original = fopen(nomeArquivo,"r+");
  if (livro_original == NULL){
    printf("tratar livro - Erro ao Abrir o Arquivo\n");
    exit(1);
  } 

  livro_aux = fopen("livro_auxiliar.txt","w");
  if (livro_aux == NULL){
    printf("tratar livro -  Erro ao Criar o Arquivo\n");
    exit(1);
  } 
  
  while (fgets(frase, sizeof(frase),livro_original) != NULL){ 

    p = strtok(frase," ");

    while(p != NULL){
      if(p[0] != '[' && p[0] != '('){
        p[strcspn(p, "”)]!:,.'|[(+\"")] = 0;
      }else{
        p[strcspn(p, "”)]!:,.'|+\"")] = 0;
      }
      
      if(strcmp(p," ") != 0 && strcmp(p,"\t") != 0){

        tratar_palavra(p);
        to_lower_case(p);
        if (buscar_de(art,p) == NULL){
          if ((strcmp(p,"") != 0) && (strcmp(p," ") != 0) && (strcmp(p,"\t") != 0) && (strcmp(p,"\n") != 0) && (strcmp(p,"\b") != 0)){
            fprintf(livro_aux," %s",p);
          }
        }
      }

      p = strtok(NULL," ");
    }
    
  }
  fclose(livro_aux);
  fclose(livro_original);
}

/*Exemplo de uso:
int main(int argc, char const *argv[]){
    setlocale(LC_ALL, "pt-BR.UTF-8");
    char livro[100];
    scanf("%s",livro);
    t_de * sw = guardar_sw("stop_words.txt");
    tratar_livro(livro, sw);
}

//gcc -o a .\tratarLivro.c .\dicionarioestatico.c

*/
