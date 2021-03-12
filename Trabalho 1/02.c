/** Matricula: 19/0014113
 *       Nome: Gustavo Pereira Chaves
 *      Turma: A */


/*
    Ideia: Escanear individualmente cada caractere e fazer as seguintes operações:
        -Se for um número (operando), adicionar na string pós-fixa 
        -Se for um paretenses/colchete/chaves abrindo
            -Adicionar o paretenses/colchete/chaves na pilha
        -Se for operador verificar outras 2 coisas:
            -Se a precedencia do elemento atual (X) for menor do que um operador no topo da pilha (Y)
                -Desempilhar Y e colocar na string pós-fixa
                -Empilhar X
            -Se a precedencia do elemento atual (X) for maior do que um operador no topo da pilha (Y)
                -Empilhar X
        -Se for um paretenses/colchete/chaves fechando
            - Desempilhar tudo até achar outro paretenses/colchete/chaves 
*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Elemento{
    char simbolo;
    struct Elemento * proximo;
}Elemento;

Elemento * aloca_elemento(const char simbolo){

    Elemento * temp = (Elemento*) malloc (sizeof(Elemento));

    if (temp == NULL){
        return temp;
    }

    temp -> proximo = NULL;
    temp -> simbolo = simbolo;

    return temp;
}

void push(Elemento ** topo, const char simbolo){
    Elemento * celula = aloca_elemento(simbolo);

    if(celula != NULL){

        if(*topo == NULL){
            *topo = celula;
        }else{
            celula -> proximo = *topo;
            *topo = celula;
        }
    }
}

char pop(Elemento ** topo){
    Elemento * auxiliar;
    char simbolo;

    if(topo != NULL){

        auxiliar = *topo;
        *topo = (*topo) -> proximo;
        simbolo = auxiliar -> simbolo;
        free(auxiliar);

        return simbolo;
    }
    return '!';
}

void free_stack(Elemento ** topo){
    Elemento * auxiliar;

    while(*topo != NULL){
        auxiliar = *topo;
        *topo = (*topo) -> proximo;
        free(auxiliar);
    }
    auxiliar = NULL;
}

int priority(const char operador){
    switch(operador){
        case '+':
        case '-':
            return 1;
        break;

        case '*':
        case '/':
            return 2;
        break;

        case '^':
            return 3;
        break;
    }
    return 0;
}

int is_operator(const char simbolo){
    if(simbolo == '+' || simbolo == '-' || simbolo == '*' || simbolo == '/' || simbolo == '^'){
        return 1;
    }else{
        return 0;
    }
}

int is_opening(const char simbolo){
    if(simbolo == '(' || simbolo == '{' || simbolo == '['){
        return 1;
    }else{
        return 0;
    }
}

int is_closing(const char simbolo){
    if(simbolo == ')' || simbolo == '}' || simbolo == ']'){
        return 1;
    }else{
        return 0;
    }
}

void transforma(const char* infixa, char* posfixa) {
    Elemento * topo = NULL;
    int tamanho, i = 0, j = 0;
    tamanho = strlen(infixa);

    push(&topo ,'(');

    for(i = 0; i < tamanho; i++){
        //caso o valor escaneado seja um numero
        if( isdigit(infixa[i]) ){
            while(isdigit(infixa[i])){
                posfixa[j++] = infixa[i++];
            }
            if(infixa[i] == '.'){
                posfixa[j++] = infixa[i++];
                while(isdigit(infixa[i])){
                    posfixa[j++] = infixa[i++];
                }
            }
            posfixa[j++] = ' '; 
        }

        //caso o valor escaneado seja: [ { (

        if( is_opening(infixa[i]) ){
            push(&topo, infixa[i]);
        }

        if( is_closing(infixa[i]) ){
            while(topo && !is_opening(topo -> simbolo) ){
                posfixa[j++] = pop(&topo);
                posfixa[j++] = ' ';
            }
            pop(&topo);
        }

        //caso o valor escaneado seja: + - * / ^

        if( is_operator(infixa[i]) ){
            if( topo && is_operator(topo -> simbolo)){
                if( priority(topo -> simbolo) >= priority(infixa[i]) ){
                    while(topo && is_operator(topo -> simbolo)){
                        posfixa[j++] = pop(&topo);
                        posfixa[j++] = ' ';
                    }
                    push(&topo, infixa[i]);
                }else{
                    push(&topo, infixa[i]);
                }
            }else{
                push(&topo, infixa[i]);
            }
        }
    }

    //remover o restante da pilha
    while(topo && !is_opening(topo -> simbolo) ){
        posfixa[j++] = pop(&topo);
        posfixa[j++] = ' ';
    }
    pop(&topo);

    posfixa[j] = '\0';

    free_stack(&topo);
}


int main() {
    char infixa[101], posfixa[201];

    scanf("%100[^\n]", infixa);

    transforma(infixa, posfixa);
    printf("%s\n", posfixa);

    return 0;
}