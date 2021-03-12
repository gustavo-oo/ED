#include <stdbool.h>
#include <stdio.h>
#define TAMANHO 10

typedef struct {
    char vertices[TAMANHO];
    unsigned int arestas[TAMANHO][TAMANHO];
    unsigned int ordem;
} grafo_t;

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

_Bool aresta(grafo_t* grafo, char origem, char destino) {
    int id1, id2;

    id1 = idx_vertice(grafo, origem);
    id2 = idx_vertice(grafo, destino);

    if(id1 != -1 && id2 != -1){
        grafo -> arestas[id1][id2] = 1;
        grafo -> arestas[id2][id1] = 1;
        return true;
    }

    return false;
}

int main(){
    grafo_t grafo;

    grafo.vertices[0] = 'A';
    grafo.vertices[3] = 'B';

    printf("%d\n", idx_vertice(&grafo, 'B'));

    printf("\n%d\n", aresta(&grafo, 'A', 'Z'));

    return 0;
}