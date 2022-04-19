#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct Arv23 Arv;
typedef struct calcados cal;
typedef struct lista Lis;

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

    	printf("Info 1 = %d pos = %dfilho = %d \n",Raiz->Info1.cod,Raiz->Info1.pos,in);
    	 if(Raiz->NInfos == 2)
        	printf("Info 2 = %d pos = %d\n",Raiz->Info2.cod,Raiz->Info2.pos);
        imprimir(Raiz->esq,1);
        imprimir(Raiz->cen,2);
        imprimir(Raiz->dir,3);

    }
}

int buscaValor(Arv **Raiz, int valor, Arv **Avo, Arv **Pai, int *filho, int *tio,
int m1,int m2, Arv ** auxAvo, Arv **auxPai, Arv **Aux){//BUSCAR O No DO NUMERO DADO

	int flag = 0;
    if(*Raiz != NULL){
        if((*Raiz)->Info1.cod == valor || (*Raiz)->Info2.cod == valor){
			*Aux = *Raiz;
			*filho = m1;
			*tio = m2;
			*Pai = *auxPai;
			*Avo = *auxAvo;
			flag = 1;
		}else{
        	flag = buscaValor(&(*Raiz)->esq,valor,&(*Avo),&(*Pai),filho,tio,1,m1,&(*auxPai),&(*Raiz),&(*Aux));
        	flag = buscaValor(&(*Raiz)->cen,valor,&(*Avo),&(*Pai),filho,tio,2, m1,&(*auxPai),&(*Raiz),&(*Aux));
           	flag = buscaValor(&(*Raiz)->dir,valor,&(*Avo),&(*Pai),filho,tio,3,m1,&(*auxPai),&(*Raiz),&(*Aux));
        }
    }

	return flag;
}

void InserirLista(Lis *LisEsp, int valor){

   Lis *nova = malloc (sizeof (Lis));
   nova->esp = valor;
   nova->prox = LisEsp->prox;
   LisEsp->prox = nova;
}

int atualizaTxt(cal Calcado, int esc, Lis *LisEsp){
	Lis *aux;
	FILE *pont;
	if(esc == 1){
		pont = fopen("arquivo_palavra.txt", "r");
		if(pont != NULL){
			fseek(pont, Calcado.pos, SEEK_SET);
			fprintf(pont,"%d %d %d %d %d %d",0,0,0,0,0,0);
			InserirLista(LisEsp,Calcado.pos);
		}
	}else{
		if(LisEsp != NULL){
			pont = fopen("arquivo_palavra.txt", "r+");

			if(pont != NULL){
				char s[200];
				int i = 0;
				while( (fgets(s, 200, pont)) && i < LisEsp->esp)
					i++;

				fprintf(pont, "%d %d %d %f %s %s",Calcado.cod,Calcado.tam,Calcado.qtd,Calcado.preco,Calcado.marca,Calcado.tipo );
				aux = LisEsp;
				LisEsp = LisEsp->prox;
				free(aux);
			}
			
		}else{
			pont = fopen("arquivo_palavra.txt", "a");
			fprintf(pont, "%d %d %d %f %s %s",Calcado.cod,Calcado.tam,Calcado.qtd,Calcado.preco,Calcado.marca,Calcado.tipo );
		}
	}

	fclose(pont);
}

int menu(){
	int esc;
	puts("1 - Gerar arvore");
	puts("2 - Inserir elemento");
	puts("2 - Excluir elemento");
	puts("4 - Buscar elemento unico");
	puts("5 - Busca varios elementos");
	scanf("%d",&esc);
	return esc;
}


int main() {
		
	Arv *Raiz, *Pai;
	cal Calcado, sobe;
	Raiz = NULL;
	Pai = NULL;

	//fazer a inserção de elementos
	FILE *pont = fopen("arquivo_palavra.txt", "r");
	if(pont == NULL)
		printf("Erro na abertura do arquivo!");
	int i = 1;
	while(fscanf(pont, "%d %d %d %f %s %s",&Calcado.cod,&Calcado.tam,&Calcado.qtd,&Calcado.preco,Calcado.marca,Calcado.tipo) != EOF){
		Calcado.pos = i;
		insereArv23(Pai,&Raiz,Calcado,&sobe);
		i++;
	}
	//usando fclose para fechar o arquivo
	fclose(pont);

	/*
	FILE *pont_arq = fopen("outrapalavra.txt", "w");
	//testando se o arquivo foi realmente criado
	if(pont_arq == NULL)
		printf("Erro na abertura do arquivo!");


	fprintf(pont_arq, "%d %d %d %f %s %s",Calcado.cod,Calcado.tam,Struc.qtd,Struc.preco,Struc.marca,Struc.tipo );
	fprintf(pont_arq, "%d %d %d %f %s %s",Struc.cod,Struc.tam,Struc.qtd,Struc.preco,Struc.marca,Struc.tipo );
	fprintf(pont_arq, "%d %d %d %f %s %s",Struc.cod,Struc.tam,Struc.qtd,Struc.preco,Struc.marca,Struc.tipo );
	fprintf(pont_arq, "%d %d %d %f %s %s",Struc.cod,Struc.tam,Struc.qtd,Struc.preco,"Nike",Struc.tipo );


	//usando fclose para fechar o arquivo
	fclose(pont_arq);*/

	//fscanf();

	//for (i = 0; v[i]; i++)
	//insereArv23(Pai,&Raiz,v[i],&sobe);

	printf(" impresos : \n");

	imprimir(Raiz,0);



	return 0;
}