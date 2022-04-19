#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rubro.h"

#define RED 1
#define BLACK 0

struct calcados{

    int tam, cod, qtd, pos;
    float preco;
    char marca[20],tipo[40]; 

};

struct no{

    int cor;
    struct calcados valor; 
    struct no *esq, *dir;

};

struct lista{
	int esp; 
	struct lista *prox;
};



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
No* move_2_esq_red(No* raiz){

    troca_cor(raiz);
    if(cor(raiz->dir->esq) == RED){
        raiz->dir = rotaciona_direita(raiz->dir);
        raiz = rotaciona_esquerda(raiz);
        troca_cor(raiz);
    }
    return raiz;

}

No* move_2_dir_red(No* raiz){

    troca_cor(raiz);
    if(cor(raiz->esq->dir) == RED){
        raiz->esq = rotaciona_direita(raiz->esq);
        raiz = rotaciona_esquerda(raiz);
        troca_cor(raiz);
    }
    return raiz;

}


int cor(No *raiz){

    int aux;

 
    if(raiz == NULL || raiz->cor == BLACK){
        aux = BLACK;
    }else{
        aux = RED;
    }

    return aux;
    
}

void troca_cor(No* raiz){

    raiz->cor = !raiz->cor;
    if(raiz->esq != NULL){
        raiz->esq->cor = !raiz->esq->cor;
    }
    if(raiz->dir != NULL){
        raiz->dir->cor = !raiz->dir->cor;
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

No* remove_menor(No* raiz){


    if(raiz->esq == NULL){
        free(raiz);
        return NULL;
    }

    if(cor(raiz->esq) == BLACK && cor(raiz->esq->esq) == BLACK){
        raiz = move_2_esq_red(raiz);
    }

    raiz->esq = remove_menor(raiz->esq);


    return balancear(raiz);


}


No* balancear(No* raiz){

    //nó vermelho é sempre filho à esquerda
    if(cor(raiz->dir->esq) == RED){
        raiz = rotaciona_esquerda(raiz);
    }    
    //Filho da direita e neto da esquerda são vermelhos
    if(raiz->esq != NULL && cor(raiz->dir) == RED && cor(raiz->esq->esq) == RED){
        raiz = rotaciona_direita(raiz); 
    }
    //2 filhos vermelhos: troca cor:
    if(cor(raiz->esq) == RED && cor(raiz->dir) == RED){
        troca_cor(raiz);
        
    }

    return raiz;

}

int consulta_arvore(No* raiz, Cal calcado){

    int flag = 0;

    if(raiz != NULL){

        if(raiz->valor.cod == calcado.cod){
            flag = 1;
        }

        if(raiz->valor.cod > calcado.cod){
            flag = consulta_arvore(raiz->esq, calcado);
        }else{
            flag = consulta_arvore(raiz->dir, calcado);
        }
    }

    return flag;
}


No* remove_No(No* raiz, Cal calcado){

    if(calcado.cod < raiz->valor.cod){
        if(cor(raiz->esq) == BLACK && cor(raiz->esq->esq) == BLACK){
            raiz = move_2_esq_red(raiz);
        }
        raiz->esq = remove_No(raiz->esq, calcado);
    }else{

        if(cor(raiz->esq) == RED){
            raiz = rotaciona_direita(raiz);
        }

        if(calcado.cod == raiz->valor.cod && (raiz->dir == NULL)){
            free(raiz);
            return NULL;
        }

        if(cor(raiz->dir) == BLACK && cor(raiz->dir->esq) == BLACK){
            raiz = move_2_dir_red(raiz);
        }

        if(calcado.cod == raiz->valor.cod){
            No* aux = procura_menor(raiz->dir);
            raiz->valor = aux->valor;
            raiz->dir = remove_menor(raiz->dir);
        }else{
            raiz->dir = remove_No(raiz->dir, calcado);
        }


    }

    return balancear(raiz);
}



int RemoveRubro(No **raiz, Cal calcado){

    if(consulta_arvore(*raiz,calcado)){
        No* aux = *raiz;
        *raiz = remove_No(aux,calcado);
        if(*raiz != NULL){
            (*raiz)->cor = BLACK;
        }

        return 1;

    }else{

        return 0;
    }
}


No* insere_no(No* no, Cal calcado, int *flag){

    if(no == NULL){
        
        No* novo;
        novo = (No*)malloc(sizeof(No));
        novo->valor = calcado;
        novo->cor = RED;
        novo->dir = NULL;
        novo->esq = NULL;
        no = novo;
        *flag = 1;

    }else{

        if(calcado.cod == no->valor.cod){
            *flag = 0;
        }else{
            
            if(calcado.cod < no->valor.cod){
                no->esq = insere_no(no->esq, calcado, flag);
            }else{
                no->dir = insere_no(no->dir, calcado, flag);
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

int insere_arv(No **raiz, Cal calcado){

    int flag;

    *raiz = insere_no(*raiz,calcado,&flag);
    if((*raiz) != NULL){
        (*raiz)->cor = BLACK;
    }

    return flag;

}

int atualizaTxt(Cal Calcado, int esc, Lis *LisEsp){

	Lis *aux;
	FILE *pont;
	char s[200];
	int i = 0;
	if(esc == 1){
        /*
		pont = fopen("arquivo_palavra.txt", "r");
		if(pont != NULL){
			i = 0;
			while( (fgets(s, 200, pont)) && i < Calcado.pos)
					i++;
			fprintf(pont,"%d %d %d %d %d %d",0,0,0,0,0,0);
			InserirLista(LisEsp,Calcado.pos);
		}
        */
	}else{
		if(LisEsp != NULL){
			pont = fopen("arquivo_palavra.txt", "r+");

			if(pont != NULL){
				i = 0;
				while( (fgets(s, 200, pont)) && i < LisEsp->esp)
					i++;

				fprintf(pont, "%d %d %d %f %s %s",Calcado.cod,Calcado.tam,Calcado.qtd,Calcado.preco,Calcado.marca,Calcado.tipo );
				aux = LisEsp;
				LisEsp = LisEsp->prox;
				free(aux);
			}
			
		}else{
            
			pont = fopen("arquivo_palavra.txt", "a");
			fprintf(pont, "%d %d %d %f %s %s\n\n",Calcado.cod,Calcado.tam,Calcado.qtd,Calcado.preco,Calcado.marca,Calcado.tipo);
		}
	}

	fclose(pont);
}






void imprimir(No* arvore){//IMPRIMIR ARVORE

    if( arvore != NULL){

        imprimir(arvore->esq);
        printf("%d ",arvore->valor.cod);
        imprimir(arvore->dir);

    }

}

int vender_sapato(No* raiz, int cod, int flag){

    if(raiz != NULL){
        
        if(raiz->valor.cod == cod){
            raiz->valor.qtd = raiz->valor.qtd - 1;
            flag = 1;
        }else{
            flag = vender_sapato(raiz->esq,cod,flag);
            flag = vender_sapato(raiz->dir,cod,flag);
        }

    }

    return flag;

}


int buscar(No* raiz, int cod, int flag){

    if(raiz != NULL){
        
        if(raiz->valor.cod == cod){
            flag = 1;
            printf("quantidade de sapatos = %d \n",raiz->valor.qtd);

        }else if(flag == 0){

            printf("esquerda ");
            flag = buscar(raiz->esq,cod,flag);
            printf("direita ");
            flag = buscar(raiz->dir,cod,flag);
        }

    }

    return flag;



}
    

int menu(){
	int esc;
	puts("\n1 - Gerar arvore");
	puts("2 - Inserir elemento");
	puts("3 - vender sapato");
	puts("4 - Buscar elemento unico");
	puts("5 - Para excluir");
	scanf("%d",&esc);
	return esc;
}

int main() {
		
	No* arvore = alocar();
	Cal calcado;
    Lis* lista;

    int escolha;

    

    do{
        escolha = menu();

        if(escolha == 1){
            FILE *pont = fopen("arquivo_palavra.txt", "r");
            int i = 1;
            while(fscanf(pont, "%d %d %d %f %s %s",&calcado.cod,&calcado.tam,&calcado.qtd,&calcado.preco,calcado.marca,calcado.tipo) != EOF){
                calcado.pos = i;
                insere_arv(&arvore,calcado);
                i++;
            }

            fclose(pont);

        }if(escolha == 3){
            int codigo;
            printf("codigo do sapato: ");
            scanf("%d",&codigo);

            if(vender_sapato(arvore,codigo,0)){
                printf("Sapato vendido!\n");
            }else{
                printf("sapato nao encontrasse no estoque!\n");
            }
            
            fseek(pont,0,SEEK_CUR);
            atualizaTxt(calcado,2,lista);

        }if(escolha == 4){
            int codigo;
            printf("codigo do sapato que deseja buscar: ");
            scanf("%d",&codigo);

            buscar(arvore,codigo,0);
                
         
        }if(escolha == 5){

            int codigo;
            printf("codigo do sapato que deseja buscar: ");
            scanf("%d",&codigo);

            if(RemoveRubro(&arvore,calcado)){
                printf("removido!\n");
            }
        }

    }while(1);

      
	return 0;
}
    