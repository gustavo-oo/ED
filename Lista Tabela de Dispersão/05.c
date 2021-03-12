#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char nome[1000];
    int repeticoes;
}Elemento;

int main(){
    Elemento * pessoas;
    int i, j,qnt_pessoas;
    char nome[1000];

    scanf("%d", &qnt_pessoas);
    pessoas = (Elemento*) malloc ( sizeof(Elemento)*qnt_pessoas );

    for(i = 0; i < qnt_pessoas; i++){
        pessoas[i].repeticoes = 0;
        strcpy(pessoas[i].nome, "\0");
    }


    for(i = 0; i < qnt_pessoas; i++){
        scanf("%s", nome);
        strcpy(pessoas[i].nome, nome);

        for(j = 0; j < i; j++){
            if(strcmp(pessoas[i].nome, pessoas[j].nome) == 0){
                pessoas[j].repeticoes++;
                pessoas[i].repeticoes = -1;
                break;
            }
        }
    }

    for(i = 0; i < qnt_pessoas; i++){
        if(pessoas[i].repeticoes != -1){
            printf("%s %d\n", pessoas[i].nome, pessoas[i].repeticoes);
        }
    }

    free(pessoas);

    return 0;
}