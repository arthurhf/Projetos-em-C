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
        novo->proxColuna=NULL;
        novo->proxLinha=NULL;
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

int inserir(t_Matriz *matriz, /*t_LinhaCol *lin,t_LinhaCol *col,*/int linha,int coluna,t_celula *elem){
    printf("\ncomeço inserir\n");
    t_LinhaCol* novoLin,*novoCol,*atual;
    t_celula *ultimoCelLin,*aux,*ant;
    t_LinhaCol *tmp = matriz->linhas;

    novoLin = (t_LinhaCol*) malloc(sizeof(t_LinhaCol));
    if(novoLin == NULL)
        return 0;
    novoCol = (t_LinhaCol*) malloc(sizeof(t_LinhaCol));
    if(novoCol == NULL)
        return 0;



    novoLin->linOucol=linha;
    printf("\n novoLin %d \n",novoLin->linOucol);
    novoLin->prox=NULL;
    printf("\n novoLin prox %p \n",novoLin->prox);
    novoCol->linOucol=coluna;
    printf("\n novoCol  %d \n",novoCol->linOucol);

    novoCol->prox=NULL;
    //printf("\n lin %d \n",lin->linOucol);
    if (vazia(tmp)){
  			matriz->linhas = novoLin;

                        printf("\n Lin linha%d \n",matriz->linhas->linOucol);
  		}else {

            atual=tmp;
            printf("\n atual linha %d \n",atual->linOucol);
  			while (tmp->linOucol < novoLin->linOucol){
                atual=tmp;
                printf("\n atual linha %d \n",atual->linOucol);
  				tmp = tmp->prox;
            }

  			if(atual->prox->linOucol==novoLin->linOucol){
                    ultimoCelLin=atual->prox->cel;
                    printf("\n ultimoCelLin %d \n",ultimoCelLin->lin);
                    aux=ultimoCelLin;
                    while(ultimoCelLin!=NULL){
                        ultimoCelLin=ultimoCelLin->proxLinha;
                    }
                    ant=aux;
                    while(aux->col!=ultimoCelLin->col){

                        if(novoCol->linOucol<aux->col){
                            elem->proxLinha=aux;
                            ant->proxLinha=elem;
                            aux->col=ultimoCelLin->col;
                        }
                        ant=aux;
                        aux=aux->proxLinha;
                    }



//arrumar aqui condição no caderno e fazer o mesmo na coluna OK?
  			}else{
  			    elem->proxLinha=NULL;
                atual->prox = novoLin;
                novoLin->prox=tmp;
                novoLin->cel=elem;

  			}


  		}


    if (vazia(matriz->cols)){
  			matriz->cols = novoCol;
  		}else {
  			tmp = matriz->cols;
            atual=tmp;
  			while (tmp->linOucol <=novoCol->linOucol){
                atual=tmp;
  				tmp = tmp->prox;
            }

            if(atual->prox->linOucol==novoCol->linOucol){
                    ultimoCelLin=atual->prox->cel;
                    aux=ultimoCelLin;
                    while(ultimoCelLin!=NULL){
                        ultimoCelLin=ultimoCelLin->proxColuna;
                    }
                    ant=aux;
                    while(aux->lin!=ultimoCelLin->lin){

                        if(novoLin->linOucol<aux->lin){
                            elem->proxColuna=aux;
                            ant->proxColuna=elem;
                            aux->lin=ultimoCelLin->lin;
                        }
                        ant=aux;
                        aux=aux->proxColuna;
                    }



//arrumar aqui condição no caderno e fazer o mesmo na coluna OK?
  			}else{
            elem->proxColuna=NULL;
  			atual->prox = novoCol;
  			novoCol->prox=tmp;
  			novoCol->cel=elem;

            }
  		}


    return 1;
}


void salvaMatriz(t_Matriz *Y, t_LinhaCol *linhas, t_LinhaCol *colunas){


    Y->cols=colunas;
    Y->linhas=linhas;


}

void imprimeMatriz(t_Matriz *X){

    t_LinhaCol *correLinha=X->linhas;
    t_LinhaCol *correColuna=X->cols;
    t_celula *correCel,*inicio;
    correCel= correLinha->cel;
    inicio=correCel;
    while(correCel->lin<=X->numLin){
        printf("[");
        correCel->col=0;
        while(correCel->col<=X->numCols){

                    if(correCel->lin==correLinha->linOucol && correCel->col==correColuna->linOucol){
                        printf(" %d ",correCel->valor);

                    }else{
                        printf(" 0 ");
                    }
            correCel=correCel->proxColuna;
            correColuna=correColuna->prox;
        }
        printf("]");
        inicio=inicio->proxLinha;
        correCel=inicio;
        correLinha=correLinha->prox;
    }

}

int main(int argc, char * argv[])
{
    t_Matriz a,b,c;
	t_Matriz *A=&a, *B=&b, *C=&c;


        t_LinhaCol *linA=NULL;//lin e col sao sempre as raízes das árvores
        t_LinhaCol* colA=NULL;
        t_LinhaCol* linB=NULL;
        t_LinhaCol* colB=NULL;
        t_celula *cel;
        int i=0,valor,linha,coluna,o;
        char opcao,x;

	scanf("%d %d %d %d %d %d", &A->numLin, &A->numCols, &A->numElems,&B->numLin, &B->numCols, &B->numElems );
    //inicia(linA);
    //inicia(colA);
    //inicia(linB);
    //inicia(colB);


	for(i=0;i<A->numElems;i++){
        scanf("%d %d %d", &linha, &coluna, &valor  );
        printf("\nleu: %d %d %d\n",linha,coluna,valor);
        cel=criar_celula(linha,coluna,valor);
        printf("\ncriou: %d %d %d\n",cel->lin,cel->col,cel->valor);
        //salvaMatriz(A,linA,colA);
        o=inserir(A,linha,coluna,cel);
        salvaMatriz(A,linA,colA);
        printf("matriz a ok");
    }
    for(i=0;i<B->numElems;i++){
        B->linhas=NULL;
        B->cols=NULL;
        scanf("%d %d %d", &linha, &coluna, &valor  );
        cel=criar_celula(linha,coluna,valor);
        //salvaMatriz(B,linB,colB);
        o=inserir(B,linha,coluna,cel);
        salvaMatriz(B,linB,colB);
        printf("matriz b ok");
    }
    scanf("\n%c",&opcao);
    while(opcao!='S'||opcao!='s'){
            if(opcao=='A'){
                imprimeMatriz(A);
            }
            if(opcao=='B'){
                imprimeMatriz(B);
            }
            //if(opcao=='M'){
                //C = multiplicaMatriz(A,B);
                //imprimeMatriz(C);
            //}
            scanf("\n%c",&opcao);
    }

    libera(linA);
    libera(colA);
    libera(linB);
    libera(colB);

	return 0;
}
