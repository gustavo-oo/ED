#include <stdio.h>
#include <stdlib.h>

typedef struct ab_int{
    int dado;
    struct ab_int *esq;
    struct ab_int *dir;
}ab_int;

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

void rotaciona_esquerda(ab_int **p_raiz) {
    if((*p_raiz) -> dir != NULL){
        ab_int * aux_root = *p_raiz, *aux_leaf = (*p_raiz) -> dir -> esq;

        *p_raiz = (*p_raiz) -> dir;
        (*p_raiz) -> esq = aux_root;
        (*p_raiz) -> esq -> dir = aux_leaf;
    }
}

void rotaciona_direita(ab_int **p_raiz){
    if((*p_raiz) -> esq != NULL){
        ab_int * aux_root = *p_raiz, *aux_leaf = (*p_raiz) -> esq -> dir;

        *p_raiz = (*p_raiz) -> esq;
        (*p_raiz) -> dir = aux_root;
        (*p_raiz) -> dir -> esq = aux_leaf;
    }
}

//--------------------------- Parte para enviar para o Moodle ---------------------------

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

void em_lista(ab_int **p_raiz) {
    if(p_raiz != NULL && *p_raiz != NULL){
        while((*p_raiz) -> esq != NULL){
            rotaciona_direita(p_raiz);
        }
        em_lista(&(*p_raiz) -> dir);
    }
}

void comprime(ab_int **p_raiz, int rotacoes) {

    if(rotacoes > 0){
        rotaciona_esquerda(p_raiz);
        comprime(&(*p_raiz) -> dir, rotacoes - 1);
    }
}

void dsw(ab_int **p_raiz) {
    int rotacoes;

    em_lista(p_raiz);
    rotacoes = (altura(*p_raiz) - 1) / 2;

    while(rotacoes > 0){
        
        comprime(p_raiz, rotacoes);
        rotacoes /= 2;
    }
}

//--------------------------- Parte para enviar para o Moodle ---------------------------


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

    printf("\nForma reordenada:\n");
    dsw(&raiz);
    mostra_arvore(raiz);
    printf("\n");
   
    return 0;
}
 