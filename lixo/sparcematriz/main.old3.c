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

int vazia(t_LinhaCol *LISTA){
    if(LISTA==NULL){
        return 1;
    }else return 0;
}

int vaziaMatriz(t_Matriz *LISTA) {
	if (LISTA->linhas== NULL && LISTA->cols==NULL)
		return 1;
	else
		return 0;
}
void libera(t_Matriz *LISTA) {
	if (!vazia(LISTA->linhas)) {
		t_LinhaCol *proxNode, *atual;

		atual = LISTA->linhas;
		while (atual != NULL) {
			proxNode = atual->prox;
			free(atual);
			atual = proxNode;
		}
	}

		if (!vazia(LISTA->cols)) {
		t_LinhaCol *proxNode, *atual;

		atual = LISTA->cols;
		while (atual != NULL) {
			proxNode = atual->prox;
			free(atual);
			atual = proxNode;
		}
	}

	free(LISTA);
}

int inserir(t_Matriz *matriz, /*t_LinhaCol *lin,t_LinhaCol *col,*/int linha,int coluna,t_celula *elem){
    printf("\ncomeço inserir\n");
    t_LinhaCol* novoLin,*novoCol,*atual;
    t_celula *aux,*ant;
    t_LinhaCol *tmp = matriz->linhas;

    novoLin = (t_LinhaCol*) malloc(sizeof(t_LinhaCol));
    if(novoLin == NULL)
        return 0;
    novoCol = (t_LinhaCol*) malloc(sizeof(t_LinhaCol));
    if(novoCol == NULL)
        return 0;


    novoLin->cel=elem;
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

            tmp = matriz->linhas;
            atual = NULL;
            //printf("\n atual linha %d \n",atual->linOucol);
            if(tmp->prox==NULL&&tmp->linOucol!=novoLin->linOucol){
                tmp->prox=novoLin;
                novoLin=NULL;

            }else{
                while (tmp->prox != NULL && tmp->linOucol < novoLin->linOucol){
                    atual=tmp;
                    printf("\n atual linha %d \n",atual->linOucol);
                    tmp = tmp->prox;
                }

  			//if(atual->prox->linOucol==novoLin->linOucol){
                if(tmp->linOucol==novoLin->linOucol){
                        //ultimoCelLin=tmp->cel;
                        //printf("\n ultimoCelLin %d \n",ultimoCelLin->lin);
                        aux=tmp->cel;
                        /*while(ultimoCelLin->proxLinha!=NULL){
                            ultimoCelLin=ultimoCelLin->proxLinha;
                        }*/
                        ant=NULL;
                        while(aux->proxLinha!=NULL){
                        //while(aux->proxLinha != NULL) {

                            if(novoCol->linOucol<aux->col){
                                elem->proxLinha=aux;
                                ant->proxLinha=elem;
                                //aux->col=ultimoCelLin->col;/// ALTEROU COLUNA !!!!!
                                break;
                            }
                            ant=aux;
                            aux=aux->proxLinha;
                        }


                    aux->proxLinha=elem;
                    elem->proxLinha=NULL;

    //arrumar aqui condição no caderno e fazer o mesmo na coluna OK?
                }else{
                    elem->proxLinha=NULL;
                    if (atual != NULL)
                        atual->prox = novoLin;
                    else
                        matriz->linhas = novoLin;
                    novoLin->prox=tmp;
                    novoLin->cel=elem;

                }



            }


  		}


    if (vazia(matriz->cols)){
  			matriz->cols = novoCol;
  			return 1;
  		}

  	tmp = matriz->cols;
    atual=NULL;
    if(tmp->prox==NULL && tmp->linOucol!=novoCol->linOucol){
        tmp->prox=novoCol;
        novoCol->prox=NULL;
        return 1;
    }

  	while (tmp->prox != NULL && tmp->linOucol < novoCol->linOucol){
         atual=tmp;
  		 tmp = tmp->prox;
    }

    if(tmp->linOucol==novoCol->linOucol){
                    //ultimoCelLin=atual->prox->cel;
       aux=tmp->cel;
                    /*while(ultimoCelLin!=NULL){
                        ultimoCelLin=ultimoCelLin->proxColuna;
                    }*/
       ant=NULL;
       while(aux->proxColuna!=NULL){

         if(novoLin->linOucol<aux->lin){
            elem->proxColuna=aux;
            ant->proxColuna=elem;
                            /////aux->lin=ultimoCelLin->lin;  ALTEROU MATRIZ!!!!
            break;
          }
          ant=aux;
          aux=aux->proxColuna;
        }
        aux->proxColuna=elem;
        elem->proxColuna=NULL;

//arrumar aqui condição no caderno e fazer o mesmo na coluna OK?
  			}else{
            elem->proxColuna=NULL;
            if(atual==NULL)
                matriz->cols=novoCol;

            else
                atual->prox = novoCol;

  			novoCol->prox=tmp;
  			novoCol->cel=elem;

            }



    return 1;
}


void imprimeMatriz(t_Matriz *X){

    t_LinhaCol *correLinha=X->linhas;
    t_LinhaCol *correColuna=X->cols;
    t_celula *correCel,*inicio;
    int i=0,j=0;
    if(!vaziaMatriz(X)){
        correCel= correLinha->cel; /// matriz pode estar vazia!
        inicio=correCel;

        for(i=0;i<X->numLin;i++){
            printf("[");
            //correCel->col=0;
            if(correLinha!=NULL && i==correLinha->linOucol){
                while(correCel!=NULL && correCel->col<=X->numCols){

                            if(correCel->lin==correLinha->linOucol && correCel->col==correColuna->linOucol){
                                printf("%d",correCel->valor);
                                printf(" ");

                            }else{
                                printf("0");
                                printf(" ");
                            }
                    correCel=correCel->proxColuna;
                    correColuna=correColuna->prox;
                }
                printf("]");
                inicio=inicio->proxLinha;
                correCel=inicio;
                correLinha=correLinha->prox;
        }else{
                for(j=0;j<X->numCols;j++){
                    printf("0");
                    printf(" ");
                }
                printf("]\n");
            }

        }
    }else{
        for(i=0;i<X->numLin;i++){
                printf("[");
            for(j=0;j<X->numCols;j++){
                printf("0");
                printf(" ");
            }
            printf("]\n");
        }
    }

}

t_Matriz *criaMatrizEmBranco(int nLin, int nCol,int nElem) {
    t_Matriz * novo;
	// aloca espaço em memória
	novo = (t_Matriz*)malloc(sizeof(t_Matriz));

	// testa se houve falha na alocação
	if(!novo)
	{
		printf("Erro ao alocar memoria!!\n");
		exit(1);
	}

	// atribuição de variáveis
	novo->cols=NULL;
	novo->linhas=NULL;
	novo->numCols=nCol;
	novo->numLin=nLin;
	novo->numElems=nElem;
	return novo;
}


int main(int argc, char * argv[])
{

	t_Matriz *A, *B, *C;
    t_celula *cel;
    int i=0,valor,linha,coluna,o,nLinA,nColA,nElemA,nLinB,nColB,nElemB;
    char opcao,x;

	scanf("%d %d %d %d %d %d", &nLinA, &nColA, &nElemA,&nLinB, &nColB, &nElemB );
	A=criaMatrizEmBranco(nLinA,nColA,nElemA);
	B=criaMatrizEmBranco(nLinB,nColB,nElemB);

    for(i=0;i<A->numElems;i++){
        scanf("%d %d %d", &linha, &coluna, &valor  );
        printf("\nleu: %d %d %d\n",linha,coluna,valor);
        cel=criar_celula(linha,coluna,valor);
        printf("\ncriou: %d %d %d\n",cel->lin,cel->col,cel->valor);

        o=inserir(A,linha,coluna,cel);

        printf("elemento inserido na matriz A : linha=%d coluna=%d valor=%d\n",A->linhas->linOucol,A->cols->linOucol,A->linhas->cel->valor);
    }
    for(i=0;i<B->numElems;i++){
        scanf("%d %d %d", &linha, &coluna, &valor  );
        cel=criar_celula(linha,coluna,valor);
        o=inserir(B,linha,coluna,cel);
        printf("elemento inserido na matriz B : linha=%d coluna=%d valor=%d\n",B->linhas->linOucol,B->cols->linOucol,B->linhas->cel->valor);

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
            if(opcao=='S'||opcao=='s')
                break;
            scanf("\n%c",&opcao);
    }

    /*
    pensar em outra maneira de liberar
    */

    libera(A);
    libera(B);

	return 0;
}
