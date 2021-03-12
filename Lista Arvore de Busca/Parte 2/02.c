void comprime(ab_int **p_raiz, int rotacoes) {
    int i;
    ab_int * node, * leaf, * aux = *p_raiz;

    for(i = 0; i < rotacoes; i++){
        if(i == 0){
            node = aux;
            leaf = (aux) -> esq -> dir;

            aux = (aux) -> esq;
            *p_raiz = aux;
            (aux) -> dir = node;
            (aux) -> dir -> esq = leaf;
        }else{
            node = (aux) -> esq;
            (aux) -> esq = (aux) -> esq -> esq;
            node -> esq = (aux) -> esq -> dir;
            (aux) -> esq -> dir = node;

            (aux) = (aux) -> esq;
        }
    }
}