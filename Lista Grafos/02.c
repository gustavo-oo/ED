/* TAMANHO é um valor constante. */
#include <stdio.h>
#define TAMANHO 10

typedef struct {
    char vertices[TAMANHO];
    unsigned int arestas[TAMANHO][TAMANHO];
    unsigned int ordem;
} grafo_t;
/* Atenção, não  modifique o trecho acima! */

/* Retorna o índice do vértice no vetor, caso exista, -1 caso contrário. */
int idx_vertice(grafo_t* g, char v) {
    int i;

    if(g == NULL || v == '\0'){
        return -1;
    }

    for(i = 0; i < TAMANHO; i++){
        if(g -> vertices[i] == v){
            return i;
        }
    }
    return -1;
}

int main(){
    grafo_t grafo;

    grafo.vertices[0] = 'A';
    grafo.vertices[3] = 'B';

    printf("%d\n", idx_vertice(&grafo, 'B'));

    return 0;
}