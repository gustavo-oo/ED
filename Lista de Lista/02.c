#include <stdio.h>
#include <stdlib.h>

//implementar uma lista de chaves

//I - inserir o numero no inicio da lista
//F - inserir o numero no final da lista
//P - remove o ultimo numero e imprime o valor removido
//D - remove o primeiro numero e imprime o valor removido
//X - indica o final e imprime a lista resultante
//V - Remove por valor e retorna a quantidade de itens removidos.
//E - Remove por posição e retorna o valor removido.
//T - Troca o valor da primeira ocorrencia do item pelo valor novo.
//C - Retorna ocorrencias de valor.

typedef struct Elemento{
    int dado;
    struct Elemento * prox;
}Elemento;

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

int remove_v(int dado, Elemento ** topo){
    Elemento *aux  = *topo;
    Elemento * aux2 = aux;
    int ocorrencias = 0, j = 0;

    if(*topo != NULL){
        if ( (*topo) -> prox != NULL){
            while(aux2 != NULL){

                if(aux2 -> dado == dado){
                    aux -> prox = aux2 -> prox;
                    free(aux2);
                    ocorrencias++;
                    j--;
                }else{
                    j++;
                    if(j/2 == 1){
                        aux = aux -> prox;
                    }
                }
                aux2 = aux2 -> prox;

            }
            return ocorrencias;
        }else{
            if((*topo) -> dado == dado){
                free((*topo));
                return 1;
            }
        }
    }else{
        return 0;
    }
    return -1;
}

int remove_e(int dado, Elemento ** topo){
    Elemento * aux = *topo, *aux2;
    int i = 2, valor;
    

    if ((*topo) != NULL){
        if((*topo) -> prox != NULL){
            while(aux -> prox -> prox != NULL || i != dado){
                aux = aux -> prox;
                i++;
            }
            if(i == dado){
                valor = aux -> prox -> dado;
                aux2 = aux -> prox;
                aux -> prox = aux-> prox ->prox;
                free(aux2);
                return valor;
            }
        }else{
            if (dado == 1){
            valor = (*topo) -> dado;
            free(*topo);
            return valor;
            }else{
                return -1;
            }
        }
    }else{
        return -1;
    }
    return -1;
}

void troca(int antigo, int dado, Elemento ** topo){
    Elemento * aux = *topo;

    while( (aux -> dado != antigo) || aux == NULL){
        aux = aux -> prox;
    }
    if (aux != NULL){
        aux -> dado = dado;
    }
}

int ocorrencias(int dado, Elemento ** topo){
    Elemento * aux = *topo;
    int ocorrencias = 0;

    while(aux != NULL){
        if (aux -> dado == dado){
            ocorrencias++;
        }
        aux = aux -> prox;
    }
    return ocorrencias;
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


int main(){
    char operacao;
    Elemento * celula, *topo = NULL; 
    int dado, antigo;
    
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

                case 'V':
                    scanf("%d", &dado);
                    dado = remove_v(dado, &topo);
                    printf("%d\n", dado);
                break;

                case 'E':
                    scanf("%d", &dado);
                    dado = remove_e(dado, &topo);
                    printf("%d\n", dado);
                break;

                case 'T':
                    scanf("%d %d", &antigo, &dado);
                    troca(antigo, dado, &topo);
                break;

                case 'C':
                    scanf("%d", &dado);
                    dado = ocorrencias(dado, &topo);
                    printf("%d\n", dado);
                break;
            }
        }
    }

    return 0;
}
