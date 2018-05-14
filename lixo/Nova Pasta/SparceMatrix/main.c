#include <stdio.h>
#include <stdlib.h>
//colocar condição de erro (onde a multiplicação nao acontece)
//criar a segunda lista que vai guardar os elementos da segunda matriz

/*
	Estrutura célula contendo os seguintes campos:
		- valor
		- linha e coluna (posição da célula)
		- ponteiro para o próximo elemento na mesma linha
		- ponteiro para o proximo elemento na mesma coluna
*/
typedef struct celula
{
	int valor;
	int lin, col;
	struct celula *proxLinha;
	struct celula *proxColuna;
} t_celula;


typedef struct LinhaCol{
	int linOucol;
    struct LinhaCol *prox;
	t_celula *cel;
} t_LinhaCol;



typedef struct Matriz{
	t_LinhaCol * linhas, * cols;
	int numLin, numCols, numElems;
} t_Matriz;

t_celula* criar_celula(int linha, int coluna, int valor)
{
	t_celula * novo;
	// aloca espaço em memória
	novo = (t_celula*)malloc(sizeof(t_celula));

	// testa se houve falha na alocação
	if(!novo)
	{
		printf("Erro ao alocar memoria!!\n");
		exit(1);
	}

	// atribuição de variáveis
	novo->valor = valor;
	novo->lin=linha;
    novo->col=coluna;
	return novo;
}

void inicia(t_LinhaCol *LISTA) {
	LISTA= NULL;
}
int vazia(t_LinhaCol *LISTA) {
	if (LISTA== NULL)
		return 1;
	else
		return 0;
}
void libera(t_LinhaCol *LISTA) {
	if (!vazia(LISTA)) {
		t_LinhaCol *proxNode, *atual;

		atual = LISTA;
		while (atual != NULL) {
			proxNode = atual->prox;
			free(atual);
			atual = proxNode;
		}
	}
}

int inserir(t_LinhaCol *lin,t_LinhaCol *col,int linha,int coluna,t_celula *elem){

    t_LinhaCol* novoLin,*novoCol,*atual;

    novoLin = (t_LinhaCol*) malloc(sizeof(t_LinhaCol));
    if(novo == NULL)
        return 0;
    novoCol = (t_LinhaCol*) malloc(sizeof(t_LinhaCol));
    if(novo == NULL)
        return 0;



    novoLin.linOucol=linha;
    //novoLin->cel=elem;
    novoLin->prox=NULL;
    if (vazia(lin)){
  			lin = novoLin;
  		}else {
  			t_LinhaCol *tmp = lin;
            atual=tmp;
  			while (tmp.linOucol < novoLin.linOucol){
                atual=tmp;
  				tmp = tmp->prox;
            }

  			if(atual->prox.linOucol==novoLin.linOucol){

//arrumar aqui condição no caderno e fazer o mesmo na coluna
  			}else{
                atual->prox = novoLin;
                novoLin->prox=tmp;
  			}


  		}

    novoCol.linOucol=coluna;
    novoCol->cel=elem;
    novoCol->prox=NULL;
    if (vazia(col)){
  			col = novoCol;
  		}else {
  			t_LinhaCol *tmp = col;
            atual=tmp;
  			while (tmp.linOucol <novoCol.linOucol){
                atual=tmp;
  				tmp = tmp->prox;
            }

  			atual->prox = novoCol;
  			novoCol->prox=tmp;
  		}


    return 1;
}




void imprimeMatriz(t_Matriz X, ArvBin *linhas, ArvBin *colunas){


}

int main(int argc, char * argv[])
{

	t_Matriz A, B, C;

        t_LinhaCol *linA;//lin e col sao sempre as raízes das árvores
        t_LinhaCol* colA;
        t_LinhaCol* linB;
        t_LinhaCol* colB;
        t_celula *cel;
        int i=0,valor,linha,coluna,o;
        char opcao,x;

	scanf("%d %d %d %d %d %d", &A.numLin, &A.numCols, &A.numElems,&B.numLin, &B.numCols, &B.numElems );
    inicia(linA);
    inicia(colA);
    inicia(linB);
    inicia(colB);


	for(i=0;i<=A.numElems;i++){
            scanf("%d %d %d", linha, coluna, valor  );
            o=inserir(linA,colA,linha,coluna,valor);
        }
        for(i=0;i<=B.numElems;i++){
            scanf("%d %d %d", linha, coluna, valor  );
            cel=criar_celula(linha,coluna,valor);
            o=inserir(linB,colB,linha,coluna,cel);
        }
        scanf("%c",&opcao);
        while(opcao!='S'||opcao!='s'){
            if(opcao=='A'){
                imprimeMatriz(A,linA,colA);
            }
            if(opcao=='B'){
                imprimeMatriz(B,linB,colB);
            }

            if(opcao=='M'){
                //multiplicaMatriz(A,B);
            }
            scanf("%c",&opcao);
        }


        libera(linA);
        libera(colA);
        libera(linB);
        libera(colB);

	return 0;
}
