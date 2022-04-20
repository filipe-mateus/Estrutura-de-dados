#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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


typedef struct no No;
typedef struct calcados Cal;
typedef struct lista Lis;



No* alocar_arv(){

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
int atualizaTxt(Cal Calcado, int esc){
	FILE *pont;
	char s[200];
	int i = 1;
	if(esc == 1){
		pont = fopen("arquivo_palavra.txt", "r+");
		if(pont != NULL){
			i = 1;
			while( i < Calcado.pos){
				i++;
				fgets(s,200, pont);
				//printf("%d\n",l.cod);
			}
			printf("qtd = %d\n",Calcado.qtd);
			fseek(pont,0,SEEK_CUR);
			fprintf(pont, "%d %d %d %f %s %s",Calcado.cod,Calcado.tam,Calcado.qtd,Calcado.preco,Calcado.marca,Calcado.tipo );
			//fscanf(pont, "%d %d %d %f %s %s",&l.cod,&l.tam,&l.qtd,&l.preco,l.marca,l.tipo );
			
		}
	}else{
		pont = fopen("arquivo_palavra.txt", "a");
		fprintf(pont,"%d %d %d %2f %s %s\n",Calcado.cod,Calcado.tam,Calcado.qtd,Calcado.preco,Calcado.marca,Calcado.tipo );
	}

	fclose(pont);
}



Lis* alocar_lis(){
	Lis* caminho = malloc (sizeof (Lis));
   	caminho->prox = NULL;
	return caminho;
}

void InserirLista(Lis *LisEsp, int valor){

    Lis *nova = malloc (sizeof (Lis));
    nova->esp = valor;
    nova->prox = LisEsp->prox;
	LisEsp->prox = nova;
   
}

/*
int buscaValor(No **Raiz, int valor, int m1, No **Aux, Lis *caminho){//BUSCAR O No DO NUMERO DADO

	int flag = 0;
    if(*Raiz != NULL){
		InserirLista(caminho,m1);
        if((*Raiz)->valor.cod == valor){
			*Aux = *Raiz;
			flag = 1;
		}else{

			if(valor < (*Raiz)->valor.cod){
				flag = buscaValor(&(*Raiz)->esq,valor,1,&(*Aux),caminho);
			}else{
				flag = buscaValor(&(*Raiz)->dir,valor,2,&(*Aux),caminho);
			}
    	}
	}

	return flag;
}

*/
int buscaValor(No **Raiz, int valor, int m1, No **Aux, Lis *caminho, int esc){//BUSCAR O No DO NUMERO DADO

	int flag = 0;
    if(*Raiz != NULL){

		if(esc)
			InserirLista(caminho,m1);

        if((*Raiz)->valor.cod == valor || (*Raiz)->valor.cod == valor){
			*Aux = *Raiz;
			flag = 1;
		}else{

			if(valor < (*Raiz)->valor.cod){
				flag = buscaValor(&(*Raiz)->esq,valor,1,&(*Aux),caminho,esc);
			}else{
				flag = buscaValor(&(*Raiz)->dir,valor,2,&(*Aux),caminho,esc);
			}

        }
    }

	return flag;
}

void caminhoBusca(Lis *Lista,int valor){
	Lis *p;
	printf("Caminho pecorrido: \n");
	printf("%d ->",valor);
	for(p = Lista->prox; p != NULL; p = p->prox){
			
		if(p->esp == 1)
			printf("Esquerda -> ");
		else if(p->esp == 2)
			printf("Direita -> ");
		else
			printf("Zero");
	}
	
}

void imprimirInfo(Cal Calcado){
  
    printf("Informações do calcado com cod: %d\n",Calcado.cod);
    printf("Tamanho = %d\nQuantidade = %d\nPreco = %2.f\nMarca = %s\nTipo = %s\n",
    Calcado.tam,Calcado.qtd,Calcado.preco,Calcado.marca,Calcado.tipo );

}

void liberaArv(No* Raiz){
	if (Raiz != NULL){
		liberaArv(Raiz->esq); /* libera sae */
		liberaArv(Raiz->dir); /* libera sad */
		free(Raiz); /* libera raiz */
	}
}

void libera (Lis* lista)
{
	Lis* p = lista->prox, *aux;
	while (p != NULL) {
		aux = p->prox;
		free(p); 
		p = aux;
	}

}

int menu(){
	int esc;
	puts("\n1 - Inserir elemento");
	puts("2 - Vender elemento");
	puts("3 - Atualizar elemento");
	puts("4 - Busca varios elementos");
	puts("5 - Imprimir Infos");
	puts("0 - Sair");
	scanf("%d",&esc);
	return esc;
}

int main() {
		
	No* arvore = alocar_arv();
    No* aux = alocar_arv();
    Cal  calcado;
    int n, i = 1, valor, vlr, j = 0, v[100];
    double t,t_1;
    Lis *caminho = alocar_lis();
    FILE *pont;


    n = menu();

    pont = fopen("arquivo_palavra.txt","r");
    if(pont == NULL){
        printf("Erro na abertura do arquivo!");
    }

    while(fscanf(pont, "%d %d %d %f %s %s",&calcado.cod,&calcado.tam,&calcado.qtd,&calcado.preco,calcado.marca,calcado.tipo) != EOF){
        calcado.pos = i;
        insere_arv(&arvore,calcado);
        i++;
        if(i % 2 != 0){
            v[j] = calcado.cod;
            j++;
        }
    }
    fclose(pont);

    while(n){

        switch (n){
        case 1:
			printf("Para inserir calcado Digite (Apenas caracteres e numeros):\n");
			printf("Codigo : ");
			scanf("%d",&calcado.cod);
			printf("Tamanho : ");
			scanf("%d",&calcado.tam);
			printf("Quantidade : ");
			scanf("%d",&calcado.qtd);
			printf("Preco : ");
			scanf("%f",&calcado.preco);
			printf("Marca : ");
			scanf("%s",calcado.marca);
			printf("Tipo : ");
			scanf("%s",calcado.tipo);
			calcado.pos = i;
			i++;
			insere_arv(&arvore,calcado);
			atualizaTxt(calcado,2);
			break;

        case 2:

			printf("Digite codigo que deseja vender :");
			scanf("%d",&valor);
			buscaValor((&arvore),valor,0,&aux,caminho,0);
			if(aux != NULL){
				printf("Quantos calcados deseja vender :");
				scanf("%d",&vlr);
				if (vlr <= aux->valor.qtd){
				
					if((aux)->valor.cod == valor){
						aux->valor.qtd -= vlr;
						atualizaTxt((aux)->valor,1);
					}
				}else
					printf("Produto sem estoque\n");
			}else
				printf("Calçado não cadastrado\n");

			break;

        case 3:

			printf("Para inserir calcado Digite (Apenas caracteres e numeros):\n");
			printf("Codigo : ");
			scanf("%d",&calcado.cod);
			printf("Tamanho : ");
			scanf("%d",&calcado.tam);
			printf("Quantidade : ");
			scanf("%d",&calcado.qtd);
			printf("Preco : ");
			scanf("%f",&calcado.preco);
			printf("Marca : ");
			scanf("%s",calcado.marca);
			printf("Tipo : ");
			scanf("%s",calcado.tipo);
			buscaValor((&arvore),calcado.cod,0,&aux,caminho,0);
			if(aux != NULL){
				if((aux)->valor.cod == valor){
					atualizaTxt((aux)->valor,1);
				}
			}
			break;

        case 4:

			printf("Quantas numeros deseja pesquisa (1 - 60):\n");
			scanf("%d",&valor);
			t_1 = clock();
			for(j = 0; j < valor; j ++){
				buscaValor((&arvore),v[j],0,&aux,caminho,1);
				caminhoBusca(caminho,v[j]);

				libera(caminho);
				caminho = alocar_lis();
				
			}
			t_1 = clock() - t_1;
			printf("\nTempo de busca na arvore: %lf\n", ((double)t_1)/((CLOCKS_PER_SEC/1000)));
			break;
        
        case 5:

			printf("Digite codigo que deseja imprimir infos :");
			scanf("%d",&valor);
			buscaValor((&arvore),valor,0,&aux,caminho,1);
			if(aux != NULL){
				if((aux)->valor.cod == valor){
					imprimirInfo((aux)->valor);
				}else{
					imprimirInfo((aux)->valor);
				}
				caminhoBusca(caminho,valor);
			}
			libera(caminho);
			caminho = alocar_lis();	
						
			break;
        
        default:
            break;
        }

        n = menu();
    }

	liberaArv(arvore);

      
	return 0;
}
    