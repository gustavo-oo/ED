#include <stdio.h>
#include <string.h>

//Definição das Structs
typedef struct Elemento{
    char * mercadoria;
    float preco;
    struct Elemento * proximo;
}Elemento;

typedef struct{
    Elemento * topo;
    int quantidade;
}Lista;

//Funções
Lista * Inicializar_Lista(){
    Lista lista;

    lista.topo = NULL;
    lista.quantidade = 0;

    return &lista;
}

Elemento * Alocar_Elemento(char * mercadoria, float preco){
    Elemento * elemento = (Elemento*)malloc(sizeof(Elemento))

    return &elemento;
}

void Adicionar(Lista * lista, char * mercadoria, float preco){
    Elemento * elemento = Alocar_Elemento(mercadoria, preco);

    elemento.proximo = lista -> topo;

    lista -> topo = &elemento;
    lista -> quantidade++;
}

void Retirar(Lista * lista, char * mercadoria){
    Elemento * ptr_auxiliar;
    while(1){
        if (!strcmp((lista -> topo) -> mercadoria, mercadoria){
            ptr_auxiliar = (lista -> topo) -> proximo;
            free(lista -> topo);
            lista -> topo = ptr_auxiliar;
            lista -> quantidade--;
            break;
        }else{
            ptr_auxiliar = lista -> 
        }
    }
}


int main(){
    Lista * lista;
    char * nome;
    int preco;
    Elemento * ptr_auxiliar;

    lista = Inicializar_Lista();

    while(1){
        scanf("%s", nome);
        if (!strcmp(nome, "fim\0")){
            scanf("%d", &preco);
            Adicionar(lista, nome, preco);
        }else{
            break;
        }
    }



    return 0;
}