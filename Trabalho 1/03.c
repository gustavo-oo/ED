/** Matricula: 19/0014113
 *       Nome: Gustavo Pereira Chaves
 *      Turma: A */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

typedef struct Elemento{
    double valor;
    struct Elemento * proximo;
}Elemento;

Elemento * aloca_elemento(double valor){

    Elemento * temp = (Elemento*) malloc (sizeof(Elemento));

    if (temp == NULL){
        return temp;
    }

    temp -> proximo = NULL;
    temp -> valor = valor;

    return temp;
}

void push(Elemento ** topo, double valor){
    Elemento * celula = aloca_elemento(valor);

    if(celula != NULL){

        if(*topo == NULL){
            *topo = celula;
        }else{
            celula -> proximo = *topo;
            *topo = celula;
        }
    }
}

double pop(Elemento ** topo){
    Elemento * auxiliar;
    double valor;

    if(topo != NULL){

        auxiliar = *topo;
        *topo = (*topo) -> proximo;
        valor = auxiliar -> valor;
        free(auxiliar);

        return valor;
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

double calcula(const char* posfixa) {
    Elemento * topo = NULL, *aux;
    int i = 0, k, tamanho = strlen(posfixa);
    double digito, j = 1, resultado = 0;

    for(i = 0; i < tamanho; i++){
        digito = 0;
        j = 1;

        if( isdigit(posfixa[i]) ){
            k = i;

            while(isdigit(posfixa[k+1])){
                k++;
                j *= 10;
            }

            for(i = i; i <= k; i++){
                digito += ( posfixa[i] - '0') * j;
                j /= 10;
            }
            j = 0.1;
            if(posfixa[i] == '.'){
                while(isdigit(posfixa[i+1])){
                    digito += ( posfixa[i+1] - '0' ) * j;
                    j /= 10;
                    i++;
                }
            }
            push(&topo, digito); 
        }

        if(is_operator(posfixa[i])){
            switch(posfixa[i]){
                case '+':
                    digito = pop(&topo) + pop(&topo);
                break;

                case '-':
                    digito = pop(&topo)*(-1);
                    digito += pop(&topo);
                break;

                case '*':
                    digito = pop(&topo) * pop(&topo);
                break;

                case '/':
                    digito = pow( pop(&topo), -1) * pop(&topo);
                break;

                case '^':
                    digito = pop(&topo);
                    digito = pow(pop(&topo), digito);
                break;
            }
            push(&topo, digito);
/*
            aux = topo;
            printf("Pilha: ");
            while( aux != NULL){
                printf("%lf ", aux -> valor);
                aux = aux -> proximo;
            }
            printf("\n");
            */
        }
    }

    resultado = topo -> valor;

    free_stack(&topo);

    return resultado;
}

int main() {
    char posfixa[201];

    scanf("%200[^\n]", posfixa);
    calcula(posfixa);
    printf("%.5lf\n", calcula(posfixa));

    return 0;
}