#include <stdio.h>
#include <stdlib.h>

typedef struct abb_int{
    int dado;
    struct abb_int *esq;
    struct abb_int *dir;
}abb_int;

abb_int* aloca(int dado){
    abb_int *node = (abb_int*) malloc (sizeof(abb_int));
    node -> dado = dado;
    node -> esq = NULL;
    node -> dir = NULL;
    return node;
}

void insere(abb_int **raiz, abb_int *node){

    if (*raiz == NULL){
        //printf("Elemento inserido: %d\n", node -> dado);
        *raiz = node;
    }else{

        if( (*raiz) -> dado < node -> dado){
            //printf("%d é maior que %d, indo para a direita...\n", node -> dado, (*raiz) -> dado );
            insere(&(*raiz) -> dir, node);
        }else{
            //printf("%d é menor que %d, indo para a esquerda...\n", node -> dado, (*raiz) -> dado );
            insere(&(*raiz) -> esq, node);      
        }
    }
}


void mostra_arvore(abb_int* raiz) {
    if (raiz != NULL){
        printf("(%d", raiz -> dado);
        printf(" ");
        
        if(raiz -> esq == NULL){
            printf("() ");
        }else{
            mostra_arvore(raiz -> esq);
            printf(" ");
        }

        if(raiz -> dir == NULL){
            printf("()");
        }else{
            mostra_arvore(raiz -> dir);
        }
        
        printf(")");
    }else{
        printf("()");
    }
}

int main(){
    int qnt_nos;
    int i, valor;
    abb_int * node, *raiz = NULL;

    scanf("%d", &qnt_nos);

    for(i = 0; i < qnt_nos; i++){
        scanf("%d", &valor);
        node = aloca(valor);
        insere(&raiz, node);
    }

    mostra_arvore(raiz);

}