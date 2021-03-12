#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    int cor; //2 varias cores, 1 preto, 0 branco
    struct Node *quadrante_1, *quadrante_2, *quadrante_3, *quadrante_4;
    int quadrantes_cheios;
}Node;

Node * aloca(char letra){
    int cor = 0;
    Node *temp = (Node*) malloc ( sizeof(Node) );

    if(temp == NULL){
        return temp;
    }

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
    temp -> quadrantes_cheios = 0;
    temp -> quadrante_1 = NULL;
    temp -> quadrante_2 = NULL;
    temp -> quadrante_3 = NULL;
    temp -> quadrante_4 = NULL;

    return temp;
}

int is_free(Node * raiz){
    //Quadrante 1 é nulo ou "p"
    if(raiz -> quadrante_1 == NULL || (raiz -> quadrante_1 -> cor == 2 && raiz -> quadrante_1 -> quadrantes_cheios < 4)){
        return 1;
    }

    //Quadrante 2 é nulo ou "p"
    if(raiz -> quadrante_2 == NULL || (raiz -> quadrante_2 -> cor == 2 && raiz -> quadrante_2 -> quadrantes_cheios < 4)){
        return 2;
    }

    //Quadrante 3 é nulo ou "p"
    if(raiz -> quadrante_3 == NULL || (raiz -> quadrante_3 -> cor == 2 && raiz -> quadrante_3 -> quadrantes_cheios < 4)){
        return 3;
    }

    //Quadrante 4 é nulo ou "p"
    if(raiz -> quadrante_4 == NULL || (raiz -> quadrante_4 -> cor == 2 && raiz -> quadrante_4 -> quadrantes_cheios < 4)){
        return 4;
    }

    return 0;
}


void insere(Node ** raiz, Node * node){
    int quadrante;

    if(*raiz == NULL){
        *raiz = node;
        if(node -> quadrantes_cheios != 4){
            (*raiz) -> quadrantes_cheios = 0;
        }
        //printf("Inserindo: %d\n", node -> cor);    
    }else{
        if((*raiz) -> cor == 2 && (*raiz) -> quadrantes_cheios < 4){
            quadrante = is_free(*raiz);
            switch(quadrante){
                case 1:
                    //printf("Indo para o quadrante 1...\n");
                    insere(&(*raiz) -> quadrante_1, node);
                    if((*raiz) -> quadrante_1 -> cor == 2){
                        if((*raiz) -> quadrante_1 -> quadrantes_cheios == 4){
                            (*raiz) -> quadrantes_cheios++;
                        }
                    }else{
                        (*raiz) -> quadrantes_cheios++;
                    }
                break;

                case 2:
                    //printf("Indo para o quadrante 2...\n");
                    insere(&(*raiz) -> quadrante_2, node);
                    if((*raiz) -> quadrante_2 -> cor == 2){
                        if((*raiz) -> quadrante_2 -> quadrantes_cheios == 4){
                            (*raiz) -> quadrantes_cheios++;
                        }
                    }else{
                        (*raiz) -> quadrantes_cheios++;
                    }
                break;

                case 3:
                    //printf("Indo para o quadrante 3...\n");
                    insere(&(*raiz) -> quadrante_3, node);
                    if((*raiz) -> quadrante_3 -> cor == 2){
                        if((*raiz) -> quadrante_3 -> quadrantes_cheios == 4){
                            (*raiz) -> quadrantes_cheios++;
                        }
                    }else{
                        (*raiz) -> quadrantes_cheios++;
                    }
                break;

                case 4:
                    //printf("Indo para o quadrante 4...\n");
                    insere(&(*raiz) -> quadrante_4, node);
                    if((*raiz) -> quadrante_4 -> cor == 2){
                        if((*raiz) -> quadrante_4 -> quadrantes_cheios == 4){
                            (*raiz) -> quadrantes_cheios++; 
                        }
                    }else{
                        (*raiz) -> quadrantes_cheios++;
                    }
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
            *raiz = NULL;
        }else{
            free(*raiz);
            *raiz = NULL;
        }
    }
}

char * sum_tree(char * arvore_1, char * arvore_2){
    int i = 0, j = 0, k = 0, l = 0;
    char * arvore_result = (char *) malloc (sizeof(char) * 10000);

    while(arvore_1[i] != '\0' && arvore_2[j] != '\0'){

        if(arvore_1[i] == 'f' || arvore_2[j] == 'f'){
            arvore_result[k] = 'f';
            k++;

            if(arvore_1[i] == 'p'){
                i++;

                for(l = 0; l < 4; l++){
                    if(arvore_1[i] == 'p'){
                        l -= 4;
                    }
                    i++;
                }
                j++;
            }else{

                if(arvore_2[j] == 'p'){
                    j++;

                    for(l = 0; l < 4; l++){
                        if(arvore_2[j] == 'p'){
                            l -= 4;
                        }
                        j++;
                    }
                    i++;
                }else{
                    i++;
                    j++;
                }
            }
            
        }else{

            if(arvore_1[i] == 'e' && arvore_2[j] == 'e'){
                arvore_result[k] = 'e';
                i++;
                j++;
                k++;
            }else{

                if(arvore_1[i] == 'p' || arvore_2[j] == 'p'){
                    arvore_result[k] = 'p';
                    k++;

                    if(arvore_1[i] == arvore_2[j]){
                        i++;
                        j++;
                    }else{
                        if(arvore_1[i] == 'p'){
                            i++;

                            for(l = 0; l < 4; l++){
                                if(arvore_1[i] == 'p'){
                                    l -= 4;
                                }

                                arvore_result[k] = arvore_1[i];
                                k++;
                                i++;
                            }

                            j++;
                        }else{
                            if(arvore_2[j] == 'p'){
                                j++;

                                for(l = 0; l < 4; l++){
                                    if(arvore_2[j] == 'p'){
                                        l -= 4;
                                    }

                                    arvore_result[k] = arvore_2[j];
                                    k++;
                                    j++;
                                }

                                i++;
                            }
                        }
                    }
                }
            }

        }

        if(k >= 5 && arvore_result[k-5] == 'p'){
            while(arvore_result[k-1] == arvore_result[k-2] && arvore_result[k-1] == arvore_result[k-3] && arvore_result[k-1] == arvore_result[k-4]){
                arvore_result[k-5] = arvore_result[k-1];
                k -= 4;
            }
        }
    }

    arvore_result[k] = '\0';
    return arvore_result;
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
    int i = 0;
    char arvore_1[10000], arvore_2[10000], *arvore_result;
    Node *raiz_soma = NULL, *node;
    

    //Arvore 1
    scanf("%s", arvore_1);
    //printf("\n\nÁrvores:\n%s", arvore_1);

    //Arvore 2
    scanf("%s", arvore_2);
    //printf("\n%s", arvore_2);
   
    //printf("\n\nÁrvore 3:\n\n");
    arvore_result = sum_tree(arvore_1, arvore_2);


    //printf("%s\n", arvore_result);
    for(i = 0; i < strlen(arvore_result); i++){
        node = aloca(arvore_result[i]);
        insere(&raiz_soma, node);
    }
    

    printf("%d", count_black_pixels(raiz_soma, 32));

    free_tree(&raiz_soma);

    return 0;
}
