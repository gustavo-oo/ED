#include <stdio.h>
#include <stdlib.h>

typedef struct Elemento{
    struct Elemento *proximo, *anterior;
    int id;
}Elemento;

Elemento * alocar_elemento(int id){
    Elemento * celula;
    celula = (Elemento*)  malloc ( sizeof (Elemento) );

    celula -> id = id;
    celula -> proximo = NULL;
    celula -> anterior = NULL;

    return celula;
}

void print_lista(Elemento ** topo, int tamanho){
    Elemento * aux = *topo;
    int anterior, proximo;

    while(aux != NULL){
        anterior = 1;
        proximo = 1;

        if (aux -> anterior == NULL){
            anterior = 0;
        }
        if (aux -> proximo == NULL){
            proximo = 0;
        }

        printf("%d - %d - %d\n", aux -> id, anterior, proximo);
        aux = aux -> proximo;
    }
    printf("Tamanho: %d\n\n", tamanho);
}

void inserir_f(Elemento ** topo, Elemento * celula){
    Elemento * aux = *topo;

    if( (*topo) == NULL){
        (*topo) = celula;
    }else{
        while(aux -> proximo != NULL){
            aux = aux -> proximo;
        }
        aux -> proximo = celula;
        celula -> anterior = aux;
    }
}

void inserir_i(Elemento ** topo, Elemento * celula){
    celula -> proximo = (*topo);
    (*topo) = celula;
}

void inserir_p(Elemento ** topo, Elemento * celula, int posicao){
    Elemento * aux = (*topo), *aux2;
    int i;

    for(i = 0; i < posicao-2; i++){
        aux = aux -> proximo;
    }
    aux2 = aux -> proximo;
    aux -> proximo = celula;
    celula -> anterior = aux;
    celula -> proximo = aux2;
    aux2 -> anterior = celula;
}

void remove_f(Elemento ** topo){
    Elemento * aux = (*topo);

    while(aux -> proximo != NULL){
        aux = aux -> proximo;
    }
    aux -> anterior -> proximo = NULL;
    free(aux);
}

void remove_i(Elemento ** topo){
    (*topo) = (*topo) -> proximo;
    free((*topo) -> anterior);
    (*topo) -> anterior = NULL;
}

void remove_p(Elemento ** topo, int posicao){
    Elemento * aux = (*topo);
    int i;

    for(i = 0; i < posicao-1; i++){
        aux = aux -> proximo;
    }
    aux -> anterior ->proximo = aux -> proximo;
    aux -> proximo -> anterior = aux ->anterior;

    free(aux);
}

void print_lista_inverso(Elemento ** topo, int tamanho){
    Elemento * aux = (*topo);
    int anterior, proximo;

    while(aux -> proximo != NULL){
        aux = aux -> proximo;
    }

    while(aux != NULL){
        anterior = 1;
        proximo = 1;

        if (aux -> anterior == NULL){
            anterior = 0;
        }
        if (aux -> proximo == NULL){
            proximo = 0;
        }

        printf("%d - %d - %d\n", aux -> id, anterior, proximo);
        aux = aux -> anterior;
    }
    printf("Tamanho: %d\n\n", tamanho);
}

void libera(Elemento ** topo){
    while((*topo) -> proximo != NULL){
        (*topo) = (*topo) -> proximo;
        free((*topo) -> anterior);
    }
    free(*topo);
}

int main(){
    Elemento * topo = NULL, *celula;
    int id, tamanho = 0;

    while(scanf("%d", &id) > 0){
        celula = alocar_elemento(id);
        inserir_f(&topo, celula);
        tamanho++;
    }

    print_lista(&topo, tamanho);

    celula = alocar_elemento(43);
    inserir_f(&topo, celula);
    celula = alocar_elemento(65);
    inserir_f(&topo, celula);
    tamanho += 2;

    print_lista(&topo, tamanho);

    celula = alocar_elemento(56);
    inserir_i(&topo, celula);
    celula = alocar_elemento(12);
    inserir_i(&topo, celula);
    tamanho += 2;

    print_lista(&topo, tamanho);

    celula = alocar_elemento(10);
    inserir_p(&topo, celula, 3);
    celula = alocar_elemento(15);
    inserir_i(&topo, celula);
    tamanho += 2;

    print_lista(&topo, tamanho);

    remove_f(&topo);
    remove_f(&topo);
    remove_f(&topo);
    tamanho -= 3;

    print_lista(&topo, tamanho);

    remove_i(&topo);
    remove_i(&topo);
    remove_i(&topo);
    tamanho -= 3;

    print_lista(&topo, tamanho);

    remove_f(&topo);
    remove_p(&topo, 3);
    tamanho -= 2;

    print_lista(&topo, tamanho);

    print_lista_inverso(&topo, tamanho);

    libera(&topo);

    return 0;
}