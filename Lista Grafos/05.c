/* TAMANHO é um valor constante. */
#include <stdio.h>
#include <stdbool.h>
#define TAMANHO 10

typedef struct {
    char vertices[TAMANHO];
    unsigned int arestas[TAMANHO][TAMANHO];
    unsigned int ordem;
} grafo_t;
/* Atenção, não  modifique o trecho acima! */

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

/* Retorna a quantidade de arestas que incidem sobre um vértice. */
int grau_de_entrada(grafo_t* g, char vertice) {
    int id, i, contador = 0;

    if(g == NULL){
        return 0;
    }

    id = idx_vertice(g, vertice);

    if(id == -1){
        return 0;
    }

    for(i = 0; i < TAMANHO; i++){
        if(g -> arestas[i][id]){
            contador++;
        }
    }

    return contador;
}

_Bool aresta(grafo_t* grafo, char origem, char destino) {
    int id1, id2;

    id1 = idx_vertice(grafo, origem);
    id2 = idx_vertice(grafo, destino);

    if(id1 != -1 && id2 != -1){
        grafo -> arestas[id1][id2] = 1;
        return true;
    }

    return false;
}

int main(){
    int i, j;
    grafo_t grafo;

    for(i = 0; i < TAMANHO; i++){
        for(j = 0; j < TAMANHO; j++){
            grafo.arestas[i][j] = 0;
        }
    }

    grafo.vertices[0] = 'a';
    grafo.vertices[1] = 'b';
    grafo.vertices[2] = 'c';

    aresta(&grafo, 'a', 'b');
    aresta(&grafo, 'a', 'c');

    printf("%d\n", grau_de_entrada(&grafo, 'c'));

    return 0;
}