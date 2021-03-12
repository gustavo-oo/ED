#include <stdio.h>
#include <stdlib.h>

typedef struct ab_int{
    int dado;
    struct ab_int *esq;
    struct ab_int *dir;
}ab_int;

int altura(ab_int *raiz){
    int nos_esq, nos_dir;

    if(raiz == NULL){
        return 0;
    }

    nos_esq = altura(raiz -> esq);
    nos_dir = altura(raiz -> dir);

    if(nos_esq > nos_dir){
        return nos_esq + 1;
    }else{
        return nos_dir + 1;
    }
}

ab_int* aloca(int dado){
    ab_int *node = (ab_int*) malloc (sizeof(ab_int));
    node -> dado = dado;
    node -> esq = NULL;
    node -> dir = NULL;
    return node;
}

void insere(ab_int **raiz, ab_int *node){

    if (*raiz == NULL){
        printf("Elemento inserido: %d\n", node -> dado);
        *raiz = node;
    }else{

        if( (*raiz) -> dado < node -> dado){
            printf("%d é maior que %d, indo para a direita...\n", node -> dado, (*raiz) -> dado );
            insere(&(*raiz) -> dir, node);
        }else{
            printf("%d é menor que %d, indo para a esquerda...\n", node -> dado, (*raiz) -> dado );
            insere(&(*raiz) -> esq, node);
        }
    }
}


void mostra_arvore(ab_int* raiz) {
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
    ab_int *raiz = NULL, *node;
    int dado;

    while(scanf("%d", &dado) > 0){
        node = aloca(dado);
        insere(&raiz, node);
    }

    printf("\nAltura da Árvore: %d\n", altura(raiz));
    printf("\nForma Aninhada: ");
    mostra_arvore(raiz);
    printf("\n");
   
    return 0;
}
