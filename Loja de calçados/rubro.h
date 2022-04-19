
typedef struct no No;
typedef struct calcados Cal;
typedef struct lista Lis;


No* alocar();

int cor(No *raiz);

No* rotaciona_esquerda(No* raiz);

No* rotaciona_direita(No* raiz);

No* move_2_esq_red(No* raiz);

No* move_2_dir_red(No* raiz);
No* balancear(No* raiz);

No* remove_No(No* raiz, Cal calcado);

int consulta_arvore(No* raiz, Cal calcado);

int RemoveRubro(No **raiz, Cal calcado);

void troca_cor(No* raiz);

No* remove_menor(No* raiz);

No* procura_menor(No* raiz);

No* insere_no(No* no, Cal calcado, int *flag);
int insere_arv(No **raiz, Cal calcado);

void imprimir(No* arvore);

int atualizaTxt(Cal Calcado, int esc, Lis *LisEsp);

