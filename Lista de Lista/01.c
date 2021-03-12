#include <stdio.h>
#include <stdlib.h>

//implementar uma lista de chaves

//I - inserir o numero no inicio da lista
//F - inserir o numero no final da lista
//P - remove o ultimo numero e imprime o valor removido
//D - remove o primeiro numero e imprime o valor removido
//X - indica o final e imprime a lista resultante

typedef struct Elemento{
    int dado;
    struct Elemento * prox;
}Elemento;

//****Definições das Funções***//

Elemento * alocar_celula(int dado){
    Elemento * celula = (Elemento*) malloc( sizeof(Elemento) );
    celula -> dado = dado;
    celula -> prox = NULL;
    return celula;
}

void inserir_i(Elemento * celula, Elemento ** topo){
    celula -> prox = *topo;
    *topo = celula;
}

void inserir_f(Elemento * celula, Elemento ** topo){
    Elemento * aux = *topo;

    if (*topo == NULL){
        *topo = celula;
    }else{
        while( aux -> prox != NULL){
            aux = aux -> prox;
        }
        aux -> prox = celula;    
    }
}

int remove_p(Elemento ** topo){
    Elemento * aux = *topo;
    int dado;

    if(*topo != NULL){
        if ( (*topo) -> prox != NULL){
            while( aux -> prox -> prox != NULL ){
                aux = aux -> prox;
            }
            dado = (aux -> prox -> dado); 
            free(aux -> prox);
            aux -> prox = NULL;
            return dado;
        }else{
            dado = (*topo) -> dado;
            free(*topo);
            *topo = NULL;
            return dado;
        }
    }else{
        return -1;
    }
}

int remove_d(Elemento ** topo){
    int dado;
    Elemento * aux = *topo;

    dado = (*topo) -> dado;
    *topo = (*topo) -> prox;

    free(aux); 

    return dado;
}

void imprime_lista(Elemento * topo){
    Elemento * aux;
    printf("\n");
    while(topo != NULL){
        printf("%d\n", topo -> dado);
        aux = topo;
        free(aux);
        topo = topo -> prox;
    }
}

//****Definições das Funções***//

int main(){
    char operacao;
    Elemento * celula, *topo = NULL; 
    int dado;
    
    while(scanf("%c", &operacao)){
        if(operacao == 'X'){
            imprime_lista(topo);
            break;
        }else{
            switch(operacao){
                case 'I':
                scanf("%d", &dado);
                    celula = alocar_celula(dado);
                    inserir_i(celula, &topo);                
                break;

                case 'F':
                    scanf("%d", &dado);
                    celula = alocar_celula(dado);
                    inserir_f(celula, &topo);                
                break;

                case 'P': 
                    dado = remove_p(&topo);
                    printf("%d\n", dado);
                break;

                case 'D':
                    dado = remove_d(&topo);
                    printf("%d\n", dado);
                break;
            }
        }
    }

    return 0;
}

//***Implementação das funções***//


//***Implementação das funções***//
