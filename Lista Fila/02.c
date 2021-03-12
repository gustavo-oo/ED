#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pessoa{
    char nome[100];
    struct Pessoa * proximo;
}Pessoa;

Pessoa * alocar_pessoa(char nome[100]){
    Pessoa * pessoa = (Pessoa*) malloc (sizeof(Pessoa));

    if(pessoa == NULL){
        return NULL;
    }

    pessoa -> proximo = NULL;
    strcpy(pessoa -> nome, nome);

    return pessoa;
}

void inserir_fila(Pessoa ** topo, Pessoa ** fim, Pessoa * pessoa){
    if (pessoa != NULL){
        if ( *topo == NULL ){
            (*topo) = pessoa;
            (*fim) = pessoa;
        }else{
            (*fim) -> proximo = pessoa;
            (*fim) = pessoa;
        }
    }
}

Pessoa * remover_fila(Pessoa ** topo){
    Pessoa * aux = (*topo);

    if (*topo != NULL){
        (*topo) = (*topo) -> proximo;
        aux -> proximo = NULL;
        return aux;
    }
    return NULL;
}

void rotacionar(Pessoa ** topo, Pessoa ** fim, int posicao){
    int i;

    for (i = 0; i < posicao; i++){
        Pessoa * aux = remover_fila(topo);
        inserir_fila(topo, fim, aux);
    }
}

void libera(Pessoa ** topo, Pessoa ** fim){
    Pessoa * aux = (*topo);

    while( (*topo) != NULL){
        aux = (*topo);
        (*topo) = (*topo) -> proximo;
        free(aux);
        aux = NULL;
    }
    *fim = NULL;
    *topo = NULL;
}


int main(){
    char nome[1000];
    char *ptr = NULL;
    long posicao;
    Pessoa * pessoa, * topo = NULL, *fim = NULL;

    while(1){
        scanf("%s", nome);
        posicao = strtol(nome, &ptr, 10);
        if (strlen(ptr) > 0){
            pessoa = alocar_pessoa(ptr);
            inserir_fila(&topo, &fim, pessoa);
        }else{
            break;
        }
    }

    rotacionar(&topo, &fim, posicao);

    printf("Pessoa da frente: %s\n", topo -> nome);
    printf("Pessoa do fim: %s", fim -> nome);

    libera(&topo, &fim);
    pessoa = NULL;

    return 0;
}