#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//escanear uma palavra e aplicar o programa, depois ler a proxima
//estrutura de pilha
//

typedef struct Elemento{
    char letra;
    struct Elemento *proximo, *anterior;
}Elemento;

Elemento * alocar_elemento(char letra){
    Elemento * celula = (Elemento*) malloc (sizeof(Elemento));

    if(celula == NULL){
        return NULL;
    }

    celula -> proximo = NULL;
    celula -> anterior = NULL;
    celula -> letra = letra;

    return celula;
}

void insere(Elemento ** topo, Elemento * letra){
    Elemento * aux = *topo;

    

    if (letra != NULL){
        if(*topo == NULL){
            *topo = letra;

        }else{

            while(aux -> proximo != NULL){
                aux = aux -> proximo;
            }
            aux -> proximo = letra;
            letra -> anterior = aux;
        }
    }
}

void libera(Elemento * topo){
    while(topo != NULL){
        topo = topo -> proximo;
        free(topo -> anterior);
    }
    topo = NULL;
}

int compara(Elemento * esquerda, Elemento * direita, int * flag){
    int contador = 0;
    *flag = 0;

    if(esquerda != NULL && direita != NULL){
        if(esquerda -> letra == direita -> letra){
            contador += compara(esquerda -> anterior, direita -> proximo, flag);
         
        }else{
            if(contador == 0 && direita -> proximo != NULL && esquerda -> letra == direita -> proximo -> letra ){
                contador++;
                contador = compara(esquerda, direita -> proximo, flag);
                *flag = 1;
            }
        }
    }
    return contador+1;
}

int verificar_repetido(char dicionario[1000][1000], Elemento * celula, int verificador, int flag){
    int i;
    char palindrome[1000];

    //qnd o flag == 1 o palindrome tem uma letra central, ex: ama  ABXcXBA

    if(flag == 0){

        for(i = 1; i < verificador - 1; i++){
            celula = celula -> anterior;
        }
        strcpy(palindrome, &celula -> letra);

        for (i = 0; i < verificador; i++){
            celula = celula -> proximo;
            strcat(palindrome, &celula -> letra);
        }

    }else{

        for(i = 1; i < verificador - 2; i++){
            celula = celula -> anterior;
        }
        strcpy(palindrome, &celula -> letra);

        for (i = 0; i < verificador - 1; i++){
            celula = celula -> proximo;
            strcat(palindrome, &celula -> letra);
        }        


    }

    //printf("%s\n", palindrome);


    for (i = 0; i < 1000; i++){
        if(strcmp(palindrome, dicionario[i]) == 0){
            return 2;
        }else{
            if(strcmp(dicionario[i], "\0") == 0){
                strcpy(dicionario[i], palindrome);
                break;
            }
        }
    }

    return 3;

}

int main(){
    Elemento * letra, *topo = NULL, *aux;
    char palavra[1000], dicionario[1000][1000];
    int i, verificador, contador = 0, flag;

    for(i = 0; i < 1000; i++){
        strcpy(dicionario[i], "\0");
    }


    while(scanf("%s", palavra) > 0){
        for(i = 0; i < strlen(palavra); i++){
            letra = alocar_elemento( palavra[i] );
            insere(&topo, letra);
        }

        aux = topo;

        while(aux != NULL){
            verificador = compara(aux, aux -> proximo, &flag);
            //printf("Letras pra esq/dir: %d\n\n", verificador);

            if (verificador >= 3){
                verificador = verificar_repetido(dicionario, aux, verificador, flag);

                if( verificador == 3){
                    contador++;
                }
            }
            aux = aux -> proximo;
        }
        //printf("Qnt palindromes: %d\n", contador);

        if(contador >= 2){
            printf("%s\n", palavra);
        }


        topo = NULL;
        letra = NULL;
        aux = NULL;
        contador = 0;
    }

    libera(topo);

    topo = NULL;
    letra = NULL;
    aux = NULL;

    return 0;
}