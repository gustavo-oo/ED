    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>
    #include <ctype.h>


    typedef struct Elemento{
        const char * valor;
        struct Elemento * proximo;
    }Elemento;

    Elemento * aloca_elemento(const char * simbolo){

        Elemento * celula = (Elemento*) malloc (sizeof(Elemento));
        celula -> proximo = NULL;
        celula -> valor = simbolo;

        return celula;
    }

    void empilhar(Elemento ** topo, const char * simbolo){

        Elemento * celula = aloca_elemento(simbolo);

        if(celula != NULL){
            if (*topo == NULL){
                *topo = celula;
            }else{
                celula -> proximo = *topo;
                *topo = celula;
            }
        }

    }

    void desempilhar(Elemento ** topo){
        Elemento * aux = *topo;

        *topo = (*topo) -> proximo;
        free(aux);
    }
/*
    char * removerEspacos(const char expressao[101]){
        int i = 0, j = 0;
        char * expressao_ws = (char*) malloc (sizeof(char)*101);

        for(i = 0; expressao[i] != '\0'; i++){
            if (!(expressao[i] == ' ')){
                expressao_ws[j] = expressao[i];
                j++;
            }
        }
        expressao_ws[j] = '\0';

        return expressao_ws;
    }
*/
    _Bool verifica_e_desempilha(Elemento ** topo, char * simbolo){
        if(strcmp(simbolo, "isNumber\0") != 0){
            if( *topo != NULL && strcmp((*topo) -> valor, simbolo) == 0) {
                desempilhar(topo);
                return true;
            }else{
                return false;
            }
        }else{
            if( *topo != NULL ){
                desempilhar(topo);
                return true;
            }else{
                return false;
            }
        }
        return false;
    }


    _Bool valida(const char* expressao) {
        int tamanho = strlen(expressao), i = 0, j = 1;
        //char * expressao_ws = removerEspacos(expressao, &tamanho);
        Elemento * topo_delimitadores = NULL, *topo_operadores = NULL;

        for(i = 0; i < tamanho; i++){
            j = 1;
            switch(expressao[i]){
                case '(':
                    empilhar(&topo_delimitadores, "(");
                break;

                case ')':
                    if (!verifica_e_desempilha(&topo_delimitadores, "(")){
                        return false;
                    }
                break;

                case '[':
                    empilhar(&topo_delimitadores, "[");
                break;
                
                case ']':
                    if (!verifica_e_desempilha(&topo_delimitadores, "[")){
                        return false;
                    }
                break;

                case '{':
                    empilhar(&topo_delimitadores, "{");
                break;

                case '}':
                    if (!verifica_e_desempilha(&topo_delimitadores, "{")){
                        return false;
                    }
                break;

                case ' ':
                break;

                case '+':
                case '-':
                case '*':
                case '/':
                case '^':
                    if (!verifica_e_desempilha(&topo_operadores, "isNumber\0")){
                        return false;
                    }

                    while(expressao[i+j] == ' '){
                        j++;
                    }
                    
                    if(expressao[i+j] ==  ']' || expressao[i+j] == '}' || expressao[i+j] == ')'){
                        return false;
                    }

                    j = 1;

                    while(expressao[i-j] == ' '){
                        j++;
                    }
                    
                    if(expressao[i-j] ==  '[' || expressao[i-j] == '{' || expressao[i-j] == '('){
                        return false;
                    }
                    j = 1;
                break;

                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    while(isdigit(expressao[i+1])){
                        i++;
                    }if(expressao[i+1] == '.'){
                        if(isdigit(expressao[i+2])){
                            i += 2;
                            while(isdigit(expressao[i+1])){
                                i++;
                            }
                            empilhar(&topo_operadores, &expressao[i]);
                        }else{
                            return false;
                        }
                    }else{
                        empilhar(&topo_operadores, &expressao[i]);
                    }
                break;

            }
        }

        if(topo_delimitadores == NULL && topo_operadores != NULL && topo_operadores -> proximo == NULL){
            //free(expressao_ws);
            //expressao_ws = NULL;

            free(topo_operadores);
            topo_operadores = NULL;

            return true;
            
        }else{
            //free(expressao_ws);
            //expressao_ws = NULL;

            free(topo_operadores);
            topo_operadores = NULL;

            return false;
        }
    }

    int main() {
        char expressao[101];
        
        scanf("%100[^\n]", expressao);

        if (valida(expressao))
            printf("VALIDA\n");
        else
            printf("INVALIDA\n");

        return 0;
    }