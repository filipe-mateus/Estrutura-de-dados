#include <stdio.h>
#include <stdlib.h>

#define red 1
#define black 0

struct no{

    int valor;
    int cor;
    struct no *esq;
    struct no *dir;

};

typedef struct no No;


No* rotaciona_esquerda(No* raiz){

    No* aux = raiz->dir;

    raiz->dir  = aux->esq;
    aux->esq = raiz;
    aux->cor = raiz->cor;
    raiz->cor = red;
    return aux;
}

No* rotaciona_direita(No* raiz){

    No* aux = raiz->esq;

    raiz->esq = aux->dir;
    aux->dir = raiz;
    aux->cor = raiz->cor;
    raiz->dir = red; 
    return aux;

}

No* move_2_esq_red(No* raiz){

    troca_cor(raiz);
    if(cor(raiz->dir->esq) == red){
        raiz->dir = rotaciona_direita(raiz->dir);
        raiz = rotaciona_esquerda(raiz);
        troca_cor(raiz);
    }
    return raiz;

}

int cor(No *raiz){

    int aux;

    if(raiz->cor == red){
        aux = red;
    }else{
        aux = black;
    }

    return aux;
    
}

No* balancear(No* raiz){

    //nó vermelho é sempre filho à esquerda
    if(cor(raiz->dir->esq) == red){
        raiz = rotaciona_esquerda(raiz);
    }    
    //Filho da direita e neto da esquerda são vermelhos
    if(raiz->esq != NULL && cor(raiz->dir) == red && cor(raiz->esq->esq) == red){
        raiz = rotaciona_direita(raiz); 
    }
    //2 filhos vermelhos: troca cor:
    if(cor(raiz->esq) == red && cor(raiz->dir) == red){
        troca_cor(raiz);
        
    }

    return raiz;

}

No* remove_No(No* raiz, int valor){

    if(valor < raiz->valor){
        if(cor(raiz->esq) == black && cor(raiz->esq->esq) == black){
            raiz = move_2_esq_red(raiz);
        }
        raiz->esq = remove_No(raiz->esq, valor);
    }else{

        if(cor(raiz->esq) == red){
            raiz = rotaciona_direita(raiz);
        }

        if(valor == raiz->valor && (raiz->dir == NULL)){
            free(raiz);
            return NULL;
        }

        if(cor(raiz->dir) == black && cor(raiz->dir->esq == black)){
            raiz = move_2_dir_red(raiz);
        }

        if(valor == raiz->valor){
            No* aux = procura_Menor(raiz->dir);
            raiz->valor = aux->valor;
            raiz->dir = remover_menor(raiz->dir);
        }else{
            raiz->dir = remove_No(raiz->dir, valor);
        }


    }

    return balancear(raiz);


}

int remove_arv_llrb()



int main(){




}