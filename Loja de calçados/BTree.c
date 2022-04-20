#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct calcados cal;
typedef struct Arv23 Arv;
typedef struct lista Lis;

struct calcados{
	int tam, cod, qtd, pos;
	float preco;
	char marca[20],tipo[30];
};

struct Arv23{
	int  NInfos;
	struct calcados Info1, Info2;
	struct Arv23 *esq, *cen,*dir;
};

struct lista{
	int esp; 
	struct lista *prox;
};

Arv *criaNo(cal Calcado,Arv *FEsq,Arv *FCen,Arv *FDir)
{
	Arv *No;
	
	No = (Arv *) malloc(sizeof(Arv));
	(*No).Info1 = Calcado;
	(*No).Info2.cod = 0;
	(*No).NInfos = 1;
	(*No).esq = FEsq;
	(*No).cen = FCen;
	(*No).dir = FDir;
	
return No;	
}

int ehFolha(Arv *R)
{ int folha = 0; // não é folha
	
	if(R->dir == NULL && R->cen == NULL && R->esq == NULL)
		folha = 1;
		return folha;
}

void adiciona(Arv **Raiz, cal Calcado, Arv *MaiorNo)
{
	if(Calcado.cod > (*Raiz)->Info1.cod)
		{ (*Raiz)->Info2 =Calcado;
		  (*Raiz)->dir = MaiorNo;
		}	
	else {
		(*Raiz)->Info2 = (*Raiz)->Info1;
		(*Raiz)->Info1 =Calcado;
		(*Raiz)->dir = (*Raiz)->cen;
		(*Raiz)->cen = MaiorNo;
	}
	
	(*Raiz)->NInfos = 2;
}

Arv *quebraNo(Arv **Raiz,cal Calcado,cal *sobe, Arv *MaiorNo)
{ Arv *Novo;
	
 if(Calcado.cod < (*Raiz)->Info1.cod)
  {
	*sobe = (*Raiz)->Info1;
	Novo = criaNo((*Raiz)->Info2,(*Raiz)->cen,(*Raiz)->dir,NULL);
	(*Raiz)->Info1 = Calcado;
	(*Raiz)->cen = MaiorNo;
	
   }
 else if (Calcado.cod < (*Raiz)->Info2.cod) 	
        {
       *sobe = Calcado;
	 	Novo = criaNo((*Raiz)->Info2,MaiorNo,(*Raiz)->dir,NULL);
        }
   else{
	*sobe = (*Raiz)->Info2;
	Novo = criaNo(Calcado,(*Raiz)->dir,MaiorNo,NULL);
	}
(*Raiz)->Info2.cod = 0;
(*Raiz)->NInfos = 1;
(*Raiz)->dir = NULL;

return(Novo);	
}

Arv *insereArv23(Arv *Pai, Arv **Raiz, cal Calcado, cal *sobe)
	{ Arv *maiorNo;
	maiorNo = NULL;
	if(*Raiz == NULL)
		*Raiz = criaNo(Calcado,NULL,NULL,NULL);	
	else{ if(ehFolha(*Raiz)){ 
		if((*Raiz)->NInfos == 1){
			adiciona(Raiz,Calcado,maiorNo);
		}// quando não tem espaço
		else { 
			Arv *novo = quebraNo(Raiz,Calcado,sobe,maiorNo);
			if(Pai == NULL){	
				Arv *no  = criaNo(*sobe,*Raiz,novo,NULL);
				*Raiz = no;
			}else maiorNo = novo;	
		}
		}
		else{//quando não é folha
			if(Calcado.cod < (*Raiz)->Info1.cod)
				maiorNo = insereArv23(*Raiz, &((*Raiz)->esq),Calcado,sobe);
			else if((*Raiz)->NInfos == 1 || Calcado.cod < (*Raiz)->Info2.cod)
				maiorNo = insereArv23(*Raiz, &((*Raiz)->cen),Calcado,sobe);
			else maiorNo = insereArv23(*Raiz, &((*Raiz)->dir),Calcado,sobe);	

			if(maiorNo != NULL){

				if((*Raiz)->NInfos == 1){
					adiciona(Raiz,*sobe,maiorNo);
					maiorNo = NULL;
				}
				else{ // quando não tem espaço{  
					cal sobe1;
					//printf("mei %d\n",*sobe);
					Arv *novo = quebraNo(Raiz,*sobe,&sobe1,maiorNo);
					if(Pai == NULL){	
						Arv *no = criaNo(sobe1,*Raiz,novo,NULL);
						*Raiz = no;
						maiorNo = NULL;
					}
					else {
						maiorNo = novo;
						*sobe = sobe1;
					}

				}
			}  

		}

	}

	return maiorNo;	
}

void imprimir(Arv *Raiz, int in){
  
    if( Raiz != NULL){

    	printf("Info 1 = %d pos = %d filho = %d \n",Raiz->Info1.cod,Raiz->Info1.pos,in);
    	 if(Raiz->NInfos == 2)
        	printf("Info 2 = %d pos = %d\n",Raiz->Info2.cod,Raiz->Info2.pos);
        imprimir(Raiz->esq,1);
        imprimir(Raiz->cen,2);
        imprimir(Raiz->dir,3);
    }
}
void imprimirInfo(cal Calcado){
  
   printf("Informacoes do calcado com cod : %d\n",Calcado.cod);
   printf("Tamanho = %d\nQuantidade = %d\nPreco = %f\nMarca = %s\nTipo = %s\n",
   Calcado.tam,Calcado.qtd,Calcado.preco,Calcado.marca,Calcado.tipo );
}
void InserirLista(Lis *LisEsp, int valor){

   Lis *nova = malloc (sizeof (Lis));
   nova->esp = valor;
   nova->prox = LisEsp->prox;
   LisEsp->prox = nova;
   
}

int buscaValor(Arv **Raiz, int valor, int m1, Arv **Aux, Lis *caminho, int esc){//BUSCAR O No DO NUMERO DADO

	int flag = 0;
    if(*Raiz != NULL){

		if(esc)
			InserirLista(caminho,m1);

        if((*Raiz)->Info1.cod == valor || (*Raiz)->Info2.cod == valor){
			*Aux = *Raiz;
			flag = 1;	
		}else{
			if(valor < (*Raiz)->Info1.cod )
        		flag = buscaValor(&(*Raiz)->esq,valor,1,&(*Aux),caminho,esc);
			else{
				if((*Raiz)->NInfos == 2 && valor > (*Raiz)->Info2.cod && (*Raiz)->Info2.cod != 0)
        			flag = buscaValor(&(*Raiz)->dir,valor,3,&(*Aux),caminho,esc);
				else 
					flag = buscaValor(&(*Raiz)->cen,valor,2,&(*Aux),caminho,esc);
				} 
        }
    }

	return flag;
}

int atualizaTxt(cal Calcado, int esc){
	Lis *aux;
	FILE *pont;
	char s[200];
	int i = 1;
	if(esc == 1){
		pont = fopen("arquivo_palavra.txt", "r+");
		if(pont != NULL){
			i = 1;
			puts("q");
			while(  i < Calcado.pos){
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
		fprintf(pont, "%d %d %d %f %s %s\n",Calcado.cod,Calcado.tam,Calcado.qtd,Calcado.preco,Calcado.marca,Calcado.tipo );
	}
	fclose(pont);
}
Lis* Alocar(){
	Lis* caminho = malloc (sizeof (Lis));
   	caminho->prox = NULL;
	return caminho;
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

void imprimirCaminho(Lis *Lista,int valor){
	Lis *p;
	printf("Caminho pecorrido: \n");
	printf("%d ->",valor);
	for(p = Lista->prox; p != NULL; ){
			
		if(p->esp == 1)
			printf("Esquerda -> ");
		else if(p->esp ==2)
			printf("Centro -> ");
		else if(p->esp == 3)
			printf("Direita -> ");
		else
			printf("Raiz\n\n");
		//Lis *aux = p;
		p = p->prox;
		//free(aux);
	}
	
}
int menu(){
	int esc;
	puts("1 - Inserir elemento");
	puts("2 - Vender elemento");
	puts("3 - Atualizar elemento");
	puts("4 - Busca varios elementos");
	puts("5 - Imprimir Infos");
	puts("6 - Imprimir elementos");
	puts("0 - Sair");
	scanf("%d",&esc);
	return esc;
}




void liberaArv(Arv* Raiz){
	if (Raiz != NULL){
		liberaArv(Raiz->esq); /* libera sae */
		liberaArv(Raiz->cen);
		liberaArv(Raiz->dir); /* libera sad */
		free(Raiz); /* libera raiz */
	}
}


int main() {
		
	Arv *Raiz, *Pai,*Aux;
	cal Calcado, sobe;
	Raiz = NULL;
	Pai = NULL;
	int n, i = 1, valor, vlr, j = 0,v[100]; 
	double t,t_1;
	Lis *caminho = Alocar();
	FILE *pont;		

	n = menu();

	pont = fopen("arquivo_palavra.txt", "r");
	if(pont == NULL)
		printf("Erro na abertura do arquivo!");
	
	while(fscanf(pont, "%d %d %d %f %s %s",&Calcado.cod,&Calcado.tam,&Calcado.qtd,&Calcado.preco,Calcado.marca,Calcado.tipo) != EOF){
		Calcado.pos = i;
		insereArv23(Pai,&Raiz,Calcado,&sobe);
		i++;
		if(i % 2 == 0){
			v[j] = Calcado.cod;
			j++;
		}

	}
	fclose(pont);

	while(n){
		Aux = NULL;
		switch (n){
		
		case 1:
			printf("Para inserir calcado Digite (Apenas caracteres e numeros):\n");
			printf("Codigo : ");
			scanf("%d",&Calcado.cod);
			printf("Tamanho : ");
			scanf("%d",&Calcado.tam);
			printf("Quantidade : ");
			scanf("%d",&Calcado.qtd);
			printf("Preco : ");
			scanf("%f",&Calcado.preco);
			printf("Marca : ");
			scanf("%s",Calcado.marca);
			printf("Tipo : ");
			scanf("%s",Calcado.tipo);
			/*Calcado.cod = 57480;
			Calcado.tam = 40;
			Calcado.qtd = 10;
			Calcado.preco = 4.56;
			strcpy(Calcado.marca,"UOL");
			strcpy(Calcado.tipo,"Kid");*/
			Calcado.pos = i;
			i++;
			insereArv23(Pai,&Raiz,Calcado,&sobe);
			atualizaTxt(Calcado,2);
			break;
		case 2:
			printf("Digite codigo que deseja vender :");
			scanf("%d",&valor);
			buscaValor((&Raiz),valor,0,&Aux,caminho,0);
			if(Aux != NULL){
				printf("Quantos calcados deseja vender :");
				scanf("%d",&vlr);
				if (vlr <= Aux->Info1.qtd){
				
					if((Aux)->Info1.cod == valor){
						Aux->Info1.qtd -= vlr;
						atualizaTxt((Aux)->Info1,1);
					}else{
						Aux->Info2.qtd -= vlr;
						atualizaTxt((Aux)->Info2,1);
					}	
				}else
					printf("Produto sem estoque\n");
			}else
				printf("Calçado não cadastrado\n");
		
			break;
		case 3:
			caminho = Alocar();
			printf("Para atualizar calcado Digite (Apenas caracteres e numeros):\n");
			printf("Codigo : ");
			scanf("%d",&Calcado.cod);
			printf("Tamanho : ");
			scanf("%d",&Calcado.tam);
			printf("Quantidade : ");
			scanf("%d",&Calcado.qtd);
			printf("Preco : ");
			scanf("%f",&Calcado.preco);
			printf("Marca : ");
			scanf("%s",Calcado.marca);
			printf("Tipo : ");
			scanf("%s",Calcado.tipo);
			buscaValor((&Raiz),Calcado.cod,0,&Aux,caminho,0);
			if(Aux != NULL){
				if((Aux)->Info1.cod == valor){
					atualizaTxt((Aux)->Info1,1);
				}else{
					atualizaTxt((Aux)->Info2,1);
				}
			}

			break;
		case 4:
			printf("Quantas numeros deseja pesquisa (1 - 60):\n");
			scanf("%d",&valor);
			t_1 = clock();
			for(j = 0; j < valor; j ++){
				buscaValor((&Raiz),v[j],0,&Aux,caminho,1);
				imprimirCaminho(caminho,v[j]);

				libera(caminho);
				caminho = Alocar();
			}
			t_1 = clock() - t_1;
			 printf("Tempo de busca na arvore: %lf\n", ((double)t_1)/((CLOCKS_PER_SEC/1000)));
			break;
		case 5:
			caminho = Alocar();
			printf("Digite codigo que deseja imprimir infos :");
			scanf("%d",&valor);
			buscaValor((&Raiz),valor,0,&Aux,caminho,1);
			if(Aux != NULL){
			
				if((Aux)->Info1.cod == valor){
					imprimirInfo((Aux)->Info1);
				}else{
					imprimirInfo((Aux)->Info2);
				}
				imprimirCaminho(caminho,valor);
			}
			libera(caminho);
			caminho = Alocar();		
			break;
		case 6:
			printf(" impresos : \n");
			imprimir(Raiz,0);
			break;
		default:
			break;
		}
		n = menu();
	}
	liberaArv(Raiz);

	return 0;
}