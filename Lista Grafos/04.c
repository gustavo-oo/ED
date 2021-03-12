#include <stdio.h>
#define TAMANHO 10

/* TAMANHO é um valor constante. */

/* Define a estrutura da informação relevante. */
typedef struct {
    int dia, mes, ano;
    char descricao[50];
} data_t;

/* Define a estrutura do vértice. */
typedef struct {
    char chave;
    data_t data;
} vertice_t; 


typedef struct {
    vertice_t vertices[TAMANHO];
    unsigned int arestas[TAMANHO][TAMANHO];
    unsigned int ordem;
} grafo_t;
/* Atenção, não  modifique o trecho acima! */

/* Retorna o ponteiro para o vértice identificado pela chave, caso exista, NULL caso contrário. */
vertice_t* vertice(grafo_t* g, char chave) {
   int i;

   if(chave < 65 || chave > 122){
       return NULL;
   }

   if(chave > 90 && chave < 97){
       return NULL;
   }

   if(g == NULL){
       return NULL;
   }

   for(i = 0; i < TAMANHO; i++){
       if(g -> vertices[i].chave == chave){
           return &(g -> vertices[i]);
       }
   }
   return NULL;
}


int main(){
    grafo_t grafo;

    grafo.vertices[0].chave = 'b';
    grafo.vertices[3].chave = 'A';

    printf("\n%p\n", vertice(&grafo, 'A'));
    printf("%p", &grafo.vertices[3].chave);
    return 0;

}