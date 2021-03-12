void em_lista(ab_char **p_raiz) {
    if(p_raiz != NULL && *p_raiz != NULL){
        while((*p_raiz) -> dir != NULL){
            rotaciona_esquerda(p_raiz);
        }
        em_lista(&(*p_raiz) -> esq);
    }
}