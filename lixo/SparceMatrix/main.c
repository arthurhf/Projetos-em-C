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

typedef struct LinhaCol* ArvBin;
typedef struct LinhaCol{
	int linOucol;
	struct LinhaCol *dir;
        struct LinhaCol *esq;
	t_celula *elem;
} t_LinhaCol;

ArvBin* cria_ArvBin(){
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

typedef struct Matriz{
	t_LinhaCol * linhas, * cols;
	int numLin, numCols, numElems;
} t_Matriz;

void inicia(t_LinhaCol *arr)
{
    arr=NULL;
    
}

int consulta(ArvBin *raiz, int valor){
    int contA=0;
    if(raiz == NULL)
        return 0;
    t_LinhaCol* atual = *raiz;
    while(atual != NULL){
       
        if(valor == atual->linOucol){
            //printf("C=%d Nota=%d\n",(contA+1),atual->nota);
            return (contA+1);
        }
        if(valor > atual->linOucol){
            atual = atual->dir;
            contA=contA+1;
        }
        else{
            atual = atual->esq;
            contA=contA+1;
        }
        
        
    }
    //printf("C=%d Nota=-1\n",(contA));
    return -1;
}
t_celula* criar_celula(ArvBin *lin, ArvBin *col,int linha, int coluna, int valor)
{
	t_celula * novo;
        ArvBin *p1=lin; 
        ArvBin *p2=col;
        int pos,n1,n2;
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
        
        
        
        if(pos=consulta(lin,linha)!=-1){
                if(lin[pos]->elem==NULL){
                    lin[pos]->elem=novo;
                } else {
                    lin[pos]->elem->proxLinha=novo;
                }
        }
        
        
        
        if(pos=consulta(col,coluna)!=-1){
            if(col[pos]->elem==NULL){
                    col[pos]->elem=novo;
            } else {
                    col[pos]->elem->proxColuna=novo;
            }
        }
        
	return novo;
}


int inserir(ArvBin *raiz,int x){
    if(raiz == NULL)
        return 0;
    t_LinhaCol* novo;
    novo = (t_LinhaCol*) malloc(sizeof(t_LinhaCol));
    if(novo == NULL)
        return 0;
    novo->linOucol=x;    
    novo->dir = NULL;
    novo->esq = NULL;

    if(*raiz == NULL)
        *raiz = novo;
    else{
         t_LinhaCol* atual = *raiz;
         t_LinhaCol* ant = NULL;
        while(atual != NULL){
            ant = atual;           

            if(x > atual->linOucol)
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        if(x > ant->linOucol)
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    return 1;   
}


void libera_NO(t_LinhaCol* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera(ArvBin* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada nó
    free(raiz);//libera a raiz
}
/*
void exibirEmOrdem(ArvBin **pRaiz){
    if(pRaiz != NULL){
        exibirEmOrdem((**pRaiz)->esq);
        printf(" %d ", (**pRaiz)->elem->valor);
        exibirEmOrdem((**pRaiz)->dir);
    }
}*/
void imprimeMatriz(t_Matriz X, ArvBin *linhas, ArvBin *colunas){
    
    t_LinhaCol* atual = *linhas;
    t_LinhaCol* atual2= *colunas;
    int i=0,j=0;
    while(atual!=NULL){
        printf(" %d ",atual->elem->valor);
    }
    //exibirEmOrdem(&linhas);
    //exibirEmOrdem(&colunas);    
}

int main(int argc, char * argv[])
{
	
	t_Matriz A, B, C;
       
        ArvBin* linA = cria_ArvBin();//lin e col sao sempre as raízes das árvores
        ArvBin* colA = cria_ArvBin();
        ArvBin* linB = cria_ArvBin();
        ArvBin* colB = cria_ArvBin();
        t_celula *cel;
        int i=0,valor,linha,coluna;
        char opcao,x;
	
	scanf("%d %d %d %d %d %d", &A.numLin, &A.numCols, &A.numElems,&B.numLin, &B.numCols, &B.numElems );
        for(i=0;i<=A.numLin;i++){
            x=inserir(linA,i);           
        }
        for(i=0;i<=A.numCols;i++){
            x=inserir(colA,i);           
        }          
	      
        for(i=0;i<=B.numLin;i++){
            x=inserir(linB,i);           
        }
        for(i=0;i<=B.numCols;i++){
            x=inserir(colB,i);           
        } 
        
        
        
	for(i=0;i<=A.numElems;i++){
            scanf("%d %d %d", linha, coluna, valor  );
            cel=criar_celula(linA,colA,linha,coluna,valor);
        }
        for(i=0;i<=B.numElems;i++){
            scanf("%d %d %d", linha, coluna, valor  );
            cel=criar_celula(linB,colB,linha,coluna,valor);
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