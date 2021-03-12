#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    int cor; //2 varias cores, 1 preto, 0 branco
    struct Node *quadrante_1, *quadrante_2, *quadrante_3, *quadrante_4;
}Node;

Node * aloca(char letra){
    int cor;
    Node *temp = (Node*) malloc ( sizeof(Node) );

    switch(letra){
        case 'p':
            cor = 2;
        break;

        case 'f':
            cor = 1;
        break;

        case 'e':
            cor = 0;
        break;
    }
    
    temp -> cor = cor;
    temp -> quadrante_1 = NULL;
    temp -> quadrante_2 = NULL;
    temp -> quadrante_3 = NULL;
    temp -> quadrante_4 = NULL;

    return temp;
}

int is_free(Node * raiz){
    if(raiz -> cor == 0 || raiz -> cor == 1){
        return 0;
    }

    if(raiz -> quadrante_1 == NULL){
        return 1;
    }

    if(raiz -> quadrante_1 -> cor == 2 && is_free(raiz -> quadrante_1)){
        return 1;
    }

    if(raiz -> quadrante_2 == NULL){
        return 2;
    }

    if(raiz -> quadrante_2 -> cor == 2 && is_free(raiz -> quadrante_2)){
        return 2;
    }

    if(raiz -> quadrante_3 == NULL){
        return 3;
    }

     if(raiz -> quadrante_3 -> cor == 2 && is_free(raiz -> quadrante_3)){
        return 3;
    }

    if(raiz -> quadrante_4 == NULL){
        return 4;
    }

    if(raiz -> quadrante_4 -> cor == 2 && is_free(raiz -> quadrante_4)){
        return 4;
    }

    return 0;
}


void insere(Node ** raiz, Node * node){
    int quadrante;

    if(*raiz == NULL){
        *raiz = node;
        printf("Inserindo: %d\n", node -> cor);
    }else{
        quadrante = is_free(*raiz);
        if(quadrante){
            switch(quadrante){
                case 1:
                    printf("Indo para o quadrante 1...\n");
                    insere(&(*raiz) -> quadrante_1, node);
                break;

                case 2:
                    printf("Indo para o quadrante 2...\n");
                    insere(&(*raiz) -> quadrante_2, node);                    
                break;

                case 3:
                    printf("Indo para o quadrante 3...\n");
                    insere(&(*raiz) -> quadrante_3, node);
                break;

                case 4:
                    printf("Indo para o quadrante 4...\n");
                    insere(&(*raiz) -> quadrante_4, node);
                break;

            }
        }

    }  
}

void free_tree(Node ** raiz){
    if(*raiz != NULL){
        if((*raiz) -> cor == 2){

            free_tree( &(*raiz) -> quadrante_1 );
            free_tree( &(*raiz) -> quadrante_2 );
            free_tree( &(*raiz) -> quadrante_3 );
            free_tree( &(*raiz) -> quadrante_4 );

            free(*raiz);
        }else{
            free(*raiz);
        }
    }
}

void sum_tree(Node * raiz_1, Node * raiz_2, Node ** raiz_soma){
    Node * node;

    if( raiz_1 -> cor == 1 || raiz_2 -> cor == 1 ){
        node = aloca('f');
        insere(raiz_soma, node);
    }else{
        if(raiz_1 -> cor == 0 && raiz_2 -> cor == 0){
            node = aloca('e');
            insere(raiz_soma, node);
        }else{
            if(raiz_1 -> cor == 2 && raiz_2 -> cor == 0){
                node = raiz_1;
                insere(raiz_soma, node);
            }else{
                if(raiz_1 -> cor == 0 && raiz_2 -> cor == 2){
                    node = raiz_2;
                    insere(raiz_soma, node);
                }else{
                    if(raiz_1 -> cor == 2 && raiz_2 -> cor == 2){
                        node = aloca('p');
                        insere(raiz_soma, node);

                        sum_tree(raiz_1 -> quadrante_1, raiz_2 -> quadrante_1, raiz_soma);
                        sum_tree(raiz_1 -> quadrante_2, raiz_2 -> quadrante_2, raiz_soma);
                        sum_tree(raiz_1 -> quadrante_3, raiz_2 -> quadrante_3, raiz_soma);
                        sum_tree(raiz_1 -> quadrante_4, raiz_2 -> quadrante_4, raiz_soma);
                    }
                }
            }
        }
    }
}

int count_black_pixels(Node * raiz, int tamanho){
    int black_pixels = 0;

    if(raiz -> cor == 1){
        return tamanho*tamanho;
    }else{
        if(raiz -> cor == 2){
            black_pixels += count_black_pixels(raiz -> quadrante_1, tamanho/2);
            black_pixels += count_black_pixels(raiz -> quadrante_2, tamanho/2);
            black_pixels += count_black_pixels(raiz -> quadrante_3, tamanho/2);
            black_pixels += count_black_pixels(raiz -> quadrante_4, tamanho/2);

            return black_pixels;
        }
    }
    return 0;
}

int main(){
    int i;
    char arvore[10000];
    Node *raiz_1 = NULL, *raiz_2 = NULL, *raiz_soma = NULL, *node;

    //Arvore 1
    scanf("%s", arvore);

    printf("Àrvore 1:\n\n");
    for(i = 0; i < strlen(arvore) - 1; i++){
        node = aloca(arvore[i]);
        insere(&raiz_1, node);
    }

    
    //Arvore 2
    scanf("%s", arvore);

    printf("\nÁrvore 2:\n\n");
    for(i = 0; i < strlen(arvore); i++){
        node = aloca(arvore[i]);
        insere(&raiz_2, node);
    }

    printf("\n\nÁrvore 3:\n\n");
    sum_tree(raiz_1, raiz_2, &raiz_soma);

    printf("%d", count_black_pixels(raiz_soma, 32));

    free_tree(&raiz_1);
    free_tree(&raiz_2);

    return 0;
}
