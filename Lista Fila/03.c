#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Elemento {
    char nome[1000];
    int prioridade;
    struct Elemento * proximo;
}Elemento;

typedef struct Fila {
    Elemento * inicio;
    Elemento * fim;
}Fila;

void iniciar_fila(Fila * fila){
    int i;

    for(i = 0; i < 11; i++){
        fila[i].inicio = NULL;
        fila[i].fim = NULL;
    }
}



void inserir_fila(Fila * fila, Elemento * atividade){
    int prioridade = atividade -> prioridade;

    if( atividade != NULL ){
        if ( fila[prioridade].inicio == NULL){

            fila[prioridade].inicio = atividade;
            fila[prioridade].fim = atividade;

        }else{
            fila[prioridade].fim -> proximo = atividade;
            fila[prioridade].fim = atividade;
        }
    }
}

Elemento * alocar_elemento(char nome[1000], int prioridade){
    Elemento * elemento = (Elemento*) malloc ( sizeof(Elemento) );

    if(elemento == NULL){
        return NULL;
    }

    elemento -> proximo = NULL;
    elemento -> prioridade = prioridade;
    strcpy(elemento -> nome, nome);

    return elemento;
}

void remove_fila(Fila * fila){
    Elemento * aux;

    aux = fila -> inicio;
    fila -> inicio = fila -> inicio -> proximo;

    free(aux);
    aux = NULL;
}

void realiza(Fila * fila, int realizadas){
    int i, contador = 0;

    for(i = 1; i < 11;){
        if (contador == realizadas){
            break;
        }
        if(fila[i].inicio != NULL){
            remove_fila(&fila[i]);
            contador++;
        }else{
            i++;
        }
    }
}

void print_filas(Fila * fila){
    Elemento * aux;
    int i, contador = 0;

    for(i = 1; i < 11; i++){
        aux = fila[i].inicio;
        while(aux != NULL){
            contador++;
            aux = aux -> proximo;
        }
    }
    printf("Tamanho da fila: %d\n", contador);
    for(i = 1; i < 11; i++){
        while(fila[i].inicio != NULL){
            printf("Atividade: %s Prioridade: #%d\n", fila[i].inicio -> nome, fila[i].inicio -> prioridade);

            aux = fila[i].inicio;
            fila[i].inicio = fila[i].inicio -> proximo;
            free(aux);
        }
    }
    aux = NULL;
}



int main(){
    Fila fila[11];
    Elemento * atividade;
    char linha[10000], *ptr, nome[1000], *aux, delimitador[] = " ";
    int prioridade, realizadas;

    iniciar_fila(fila);

    scanf("%[^\n]s", linha);
    scanf("%d", &realizadas);
    ptr = strtok(linha, delimitador);
    do{
        strcpy(nome, ptr);
        ptr = strtok(NULL, delimitador);
        prioridade = strtol(ptr, &aux, 10);
        atividade = alocar_elemento(nome, prioridade);
        inserir_fila(fila, atividade);
        ptr = strtok(NULL, delimitador);

    }while(ptr != NULL);

    realiza(fila, realizadas);
    print_filas(fila);
    atividade = NULL;

    return 0;
}