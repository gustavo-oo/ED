#include <stdio.h>
#include <stdlib.h>

typedef struct ab_char{
    char dado;
    struct ab_char * esq;
    struct ab_char * dir;
}ab_char;

ab_char* aloca(int dado){
    ab_char *node = (ab_char*) malloc (sizeof(ab_char));
    node -> dado = dado;
    node -> esq = NULL;
    node -> dir = NULL;
    return node;
}

int altura(ab_char *p_raiz){
    int nos_esq, nos_dir;

    if(p_raiz == NULL){
        return 0;
    }

    nos_esq = altura(p_raiz -> esq);
    nos_dir = altura(p_raiz -> dir);

    if(nos_esq > nos_dir){
        return nos_esq + 1;
    }else{
        return nos_dir + 1;
    }
}

void insere(ab_char** p_raiz, ab_char* e) {
    if (*p_raiz == NULL){
        *p_raiz = e;
    }else{

        if( altura((*p_raiz) -> esq) > altura((*p_raiz) -> dir)){
            insere(&(*p_raiz) -> dir, e);
        }else{
            insere(&(*p_raiz) -> esq, e);
        }
    }
}

void mostra_arvore(ab_char* raiz) {
    if (raiz != NULL){
        printf("(%c", raiz -> dado);
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

void rotaciona_esquerda(ab_char **p_raiz) {
    if((*p_raiz) -> dir != NULL){
        ab_char * aux_root = *p_raiz, *aux_leaf = (*p_raiz) -> dir -> esq;

        *p_raiz = (*p_raiz) -> dir;
        (*p_raiz) -> esq = aux_root;
        (*p_raiz) -> esq -> dir = aux_leaf;
    }
}

void em_lista(ab_char **p_raiz) {
    if(p_raiz != NULL && *p_raiz != NULL){
        while((*p_raiz) -> dir != NULL){
            rotaciona_esquerda(p_raiz);
        }
        em_lista(&(*p_raiz) -> esq);
    }
}

int main(){
    ab_char *p_raiz = NULL, *e;
    char dado;

    while(scanf("%c", &dado) > 0){
        e = aloca(dado);
        insere(&p_raiz, e);
    }
    mostra_arvore(p_raiz);
    printf("\n");
    printf("Altura: %d\n\n", altura(p_raiz));

    em_lista(&p_raiz);
    mostra_arvore(p_raiz);   

    return 0;
}