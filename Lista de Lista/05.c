#include <stdio.h>
#include <stdlib.h>

typedef struct Elemento{
    struct Elemento *proximo, *anterior;
    int id;
    int posicao;
    int nova_posicao;
}Elemento;

Elemento * alocar_elemento(int id, int * posicao){
    struct Elemento * celula;
    celula = malloc ( sizeof (Elemento) );
    celula -> proximo = NULL;
    celula -> anterior = NULL;
    celula -> id = id;
    celula -> posicao = *posicao;
    *posicao += 1;
    return celula;
}

void inserir(Elemento ** topo, Elemento * pessoa){
    Elemento * aux = *topo;
    if( (*topo) == NULL){
        (*topo) = pessoa;
    }else{
        while(aux -> proximo != NULL){
            aux = aux -> proximo;
        }
        aux -> proximo = pessoa;
        pessoa -> anterior = aux;
    }
}

void print_fila(Elemento ** topo, char * texto){
    Elemento * aux = *topo;
    printf("%s\n", texto);
    while(aux != NULL){
        printf("%d - %d\n", aux -> posicao, aux -> id);
        aux = aux -> proximo;
    }
    printf("\n");
}

void print_posicao(Elemento ** topo, char * texto){
    Elemento * aux = *topo;
    printf("%s\n", texto);
    while(aux != NULL){
        printf("%d - %d\n", aux -> nova_posicao, aux -> posicao);
        aux = aux -> proximo;
    }
    printf("\n");
}

void libera(Elemento ** topo){
    while((*topo) -> proximo != NULL){
        (*topo) = (*topo) -> proximo;
        free((*topo) -> anterior);
    }
    free(*topo);
}

void separa(Elemento ** topo_geral, Elemento ** topo_preferencial){
    Elemento * aux = *topo_geral, *aux2;

    while(aux != NULL){
        aux2 = aux -> proximo;
        if( (aux -> id) >= 60){
            if (aux -> anterior != NULL){
                aux -> anterior -> proximo = aux -> proximo;
            }else{
                (*topo_geral) = aux -> proximo;
            }
            if (aux -> proximo != NULL){
                aux -> proximo -> anterior = aux -> anterior;
            }
            aux -> anterior = NULL;
            aux -> proximo = NULL;
            inserir(topo_preferencial, aux);
        }
        aux = aux2;
    }
}
void atualizar(Elemento ** topo){
    Elemento * aux = *topo;
    int i;

    for(i = 1; aux != NULL; i++){
        aux -> nova_posicao = i;
        aux = aux -> proximo;
    }
}

int main(){
    int id, posicao = 1;
    Elemento * pessoa;
    Elemento * topo_geral = NULL;
    Elemento * topo_preferencial = NULL;

    while(scanf("%d", &id) > 0){
        pessoa = alocar_elemento(id, &posicao);
        inserir(&topo_geral, pessoa);
    }
    print_fila(&topo_geral, "Fila geral original");

    separa(&topo_geral, &topo_preferencial);
    print_fila(&topo_preferencial, "Fila preferencial");

    atualizar(&topo_geral);
    print_fila(&topo_geral, "Fila geral atualizada");

    atualizar(&topo_preferencial);
    print_posicao(&topo_preferencial, "Resultado esperado fila preferencial");

    atualizar(&topo_geral);
    print_posicao(&topo_geral, "Resultado esperado fila geral");

    //libera(&topo_geral);
    //libera(&topo_preferencial);

    return 0;
}