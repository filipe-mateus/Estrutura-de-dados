#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

struct no{

    int valor;
    int cor; 
    struct no *esq;
    struct no *dir;

};

typedef struct no No;


No* alocar(){
    No *aux = (No*) malloc(sizeof(No));

    if ( aux != NULL)
        aux = NULL;

    return aux;
}


No* rotaciona_esquerda(No* raiz){

    No* aux = raiz->dir;

    raiz->dir  = aux->esq;
    aux->esq = raiz;
    aux->cor = raiz->cor;
    raiz->cor = RED;
    return aux;
}

No* rotaciona_direita(No* raiz){

    No* aux = raiz->esq;

    raiz->esq = aux->dir;
    aux->dir = raiz;
    aux->cor = raiz->cor;
    raiz->cor = RED; 
    return aux;

}
/*
No* move_2_esq_red(No* raiz){

    troca_cor(raiz);
    if(cor(raiz->dir->esq) == red){
        raiz->dir = rotaciona_direita(raiz->dir);
        raiz = rotaciona_esquerda(raiz);
        troca_cor(raiz);
    }
    return raiz;

}

No* move_2_dir_red(No* raiz){

    troca_cor(raiz);
    if(cor(raiz->dir->esq) == red){
        raiz->dir = rotaciona_direita(raiz->dir);
        raiz = rotaciona_esquerda(raiz);
        troca_cor(raiz);
    }
    return raiz;

}
*/

int cor(No *raiz){

    int aux;

 
    if(raiz == NULL || raiz->cor == BLACK){
        aux = BLACK;
    }else{
        aux = RED;
    }

    return aux;
    
}

/*
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
            No* aux = procura_menor(raiz->dir);
            raiz->valor = aux->valor;
            raiz->dir = remove_menor(raiz->dir);
        }else{
            raiz->dir = remove_No(raiz->dir, valor);
        }


    }

    return balancear(raiz);


}

int consulta_arvore(No* raiz, int valor){

    int flag = 0;

    if(raiz != NULL){

        if(raiz->valor == valor){
            flag = 1;
        }

        if(raiz->valor > valor){
            flag = consulta_arvore(raiz->esq,valor);
        }else{
            flag = consulta_arvore(raiz->dir, valor);
        }
    }

    return flag;
}

int remove(No* raiz, int valor){

    int flag = 0;

    if(consulta_arvore(raiz,valor)){
        No* aux = raiz;
        raiz = remove_No(aux,valor);
        if(raiz != NULL){
            raiz->cor = black;
            flag = 1;
        }
    }

    return flag;
}
*/
void troca_cor(No* raiz){

    raiz->cor = !raiz->cor;
    if(raiz->esq != NULL){
        raiz->esq->cor = !raiz->esq->cor;
    }
    if(raiz->dir != NULL){
        raiz->dir->cor = !raiz->dir->cor;
    }

}
/*
No* remove_menor(No* raiz){

    int flag = 0;

    if(raiz->esq == NULL){
        free(raiz);
        flag = 1;
    }

    if(!flag){

        if(cor(raiz->esq) == black && cor(raiz->esq->esq) == black){
            raiz = move_2_esq_red(raiz);
        }
    
        raiz->esq = remove_menor(raiz->esq);
    

        return balancear(raiz);
    }

    

}

No* procura_menor(No* raiz){

    No* aux1 = raiz;
    No* aux2 = raiz->esq;

    while(aux2 != NULL){
        aux1 = aux2;
        aux2 = aux2->esq;
    }

    return aux1;

}
*/
No* insere_no(No* no, int valor, int *flag){

    if(no == NULL){
        
        No* novo;
        novo = (No*)malloc(sizeof(No));
        novo->valor = valor;
        novo->cor = RED;
        novo->dir = NULL;
        novo->esq = NULL;
        no = novo;
        *flag = 1;
        
        
    }else{

        if(valor == no->valor){
            *flag = 0;
        }else{
            
            if(valor < no->valor){
                no->esq = insere_no(no->esq, valor, flag);
            }else{
                no->dir = insere_no(no->dir, valor, flag);
            }
        }

        if(cor(no->dir) == RED && cor(no->esq) == BLACK){
            no = rotaciona_esquerda(no);
            
        }
        if(cor(no->esq) == RED && cor(no->esq->esq) == RED){
            no = rotaciona_direita(no);
            
        }
        if(cor(no->esq) == RED && cor(no->dir) == RED){
            troca_cor(no);
           
        }

    }

    
      

    return no;

}

int insere_arv(No **raiz, int valor){

    int flag;

    *raiz = insere_no(*raiz,valor,&flag);
    if((*raiz) != NULL){
        (*raiz)->cor = BLACK;
    }

    return flag;

}

void imprimir(No* arvore){//IMPRIMIR ARVORE

    if( arvore != NULL){

        imprimir(arvore->esq);
        printf("%d ",arvore->valor);
        imprimir(arvore->dir);

    }

}


    


int main(){

    No* arvore = alocar();

    insere_arv(&arvore,200);
    insere_arv(&arvore,100);
    insere_arv(&arvore,300);
    insere_arv(&arvore,50);
    insere_arv(&arvore,150);
    insere_arv(&arvore,120);


    printf("inserido\n");
    
    imprimir(arvore);

    return 0;


}