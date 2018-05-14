#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct NO* ArvAVL;
struct NO{
    int info;
    int alt;
    struct NO *esq;
    struct NO *dir;
};

ArvAVL* cria_ArvAVL(){
    ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}
int altura_ArvAVL(ArvAVL *raiz){
    if(raiz==NULL)return 0;
    if(*raiz==NULL)return 0;
    int alt_esq=altura_ArvAVL(&((*raiz)->esq));
    int alt_dir=altura_ArvAVL(&((*raiz)->dir));
    if(alt_esq>alt_dir)return (alt_esq +1);
    else return(alt_dir+1);
}

void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvAVL(ArvAVL* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada nó
    free(raiz);//libera a raiz
}

int altura_NO(struct NO* no){
    if(no==NULL)return -1;
    else return no->alt;
}

int fatorBalanceamento_NO(struct NO* no){
    return labs(altura_NO(no->esq)-altura_NO(no->dir));
}

int maior(int x, int y){

    if(x>y)return x;
    else return y;
    
}

void RotacaoLL(ArvAVL *raiz){
    struct NO* no;
    no=(*raiz)->esq;
    (*raiz)->esq=no->dir;
    no->dir=*raiz;
    (*raiz)->alt=maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir))+1;
    no->alt=maior(altura_NO(no->esq),(*raiz)->alt)+1;
    *raiz=no;
}

void RotacaoRR(ArvAVL *raiz){
    struct NO* no;
    no=(*raiz)->dir;
    (*raiz)->dir=no->esq;
    no->esq=*raiz;
    (*raiz)->alt=maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir))+1;
    no->alt=maior(altura_NO(no->dir),(*raiz)->alt)+1;
    *raiz=no;
}

void RotacaoLR(ArvAVL *raiz){
    RotacaoRR(&(*raiz)->esq);
    RotacaoLL(raiz);
}

void RotacaoRL(ArvAVL *raiz){
    RotacaoLL(&(*raiz)->dir);
    RotacaoRR(raiz);
}

int insere_ArvAVL(ArvAVL* raiz, int valor){
    int res;
    if(*raiz == NULL){        
        struct NO* novo;
        novo = (struct NO*) malloc(sizeof(struct NO));
        if(novo == NULL)
            return 0;
        novo->info = valor;
        novo->alt=0;
        novo->dir = NULL;
        novo->esq = NULL;
        *raiz=novo;
        return 1;
    }
    struct NO *atual=*raiz;
    if(valor<atual->info){
        if((res=insere_ArvAVL(&(atual->esq),valor))==1){
            if(fatorBalanceamento_NO(atual)>=2){
                if(valor<(*raiz)->esq->info){
                    RotacaoLL(raiz);
                }else {
                    RotacaoLR(raiz);
                }
            }
        }
    }else{
        if(valor>atual->info){
            if((res=insere_ArvAVL(&(atual->dir),valor))==1){
                if(fatorBalanceamento_NO(atual)>=2){
                    if((*raiz)->dir->info<valor){
                        RotacaoRR(raiz);
                    }else{
                        RotacaoRL(raiz);
                    }
                }
            }
        }else{
            printf("Valor duplicado!!\n");
            return 0;
        }
    }
    atual->alt=maior(altura_NO(atual->esq),altura_NO(atual->dir))+1;
    return res;    
}

int consulta_ArvAVL(ArvAVL *raiz, int valor){
    int contA=1;
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info){
            return contA;
        }
        if(valor > atual->info){
            atual = atual->dir;
            contA=contA+1;
        }
        else{
            atual = atual->esq;
            contA=contA+1;
        }
        
        
    }
    return (contA-1);
}
void emOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvAVL(&((*raiz)->esq));
        //printf("%d\n",(*raiz)->info);
        printf("No %d: H(%d) fb(%d)\n",(*raiz)->info,altura_NO(*raiz),fatorBalanceamento_NO(*raiz));
        emOrdem_ArvAVL(&((*raiz)->dir));
    }
}

struct NO* procuraMenor(struct NO*atual){
    struct NO *no1=atual;
    struct NO *no2=atual->esq;
    while(no2!=NULL){
        no1=no2;
        no2=no2->esq;
    }
    return no1;
}

int remove_ArvAVL(ArvAVL *raiz, int valor){
	if(*raiz == NULL){// valor não existe
	    printf("valor não existe!!\n");
	    return 0;
	}

    int res;
	if(valor < (*raiz)->info){
	    if((res = remove_ArvAVL(&(*raiz)->esq,valor)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(altura_NO((*raiz)->dir->esq) <= altura_NO((*raiz)->dir->dir))
                    RotacaoRR(raiz);
                else
                    RotacaoRL(raiz);
            }
	    }
	}

	if((*raiz)->info < valor){
	    if((res = remove_ArvAVL(&(*raiz)->dir, valor)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq) )
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
	    }
	}

	if((*raiz)->info == valor){
	    if(((*raiz)->esq == NULL || (*raiz)->dir == NULL)){// nó tem 1 filho ou nenhum
			struct NO *oldNode = (*raiz);
			if((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
			free(oldNode);
		}else { // nó tem 2 filhos
			struct NO* temp = procuraMenor((*raiz)->dir);
			(*raiz)->info = temp->info;
			remove_ArvAVL(&(*raiz)->dir, (*raiz)->info);
            if(fatorBalanceamento_NO(*raiz) >= 2){
				if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
					RotacaoLL(raiz);
				else
					RotacaoLR(raiz);
			}
		}
		if (*raiz != NULL)
            (*raiz)->alt = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;
		return 1;
	}

	(*raiz)->alt = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;

	return res;
}

int main(void)
{
      ArvAVL* avl;
    int res,i;
    //int N = 10, dados[10] = {50,25,10,5,7,3,30,20,8,15};
    //int N = 11, dados[11] = {50,25,10,5,5,7,3,30,20,8,15};
    int N = 10, dados[10] = {1,2,3,10,4,5,9,7,8,6};

    avl = cria_ArvAVL();

    for(i=0;i<N;i++){
        //printf("========================\n");
        //printf("Inserindo: %d\n",dados[i]);
        res = insere_ArvAVL(avl,dados[i]);
        //printf("\n\nres = %d\n",res);
        //preOrdem_ArvAVL(avl);
        //printf("\n\n");
    }
//
    printf("\nAVL tree:\n");
    emOrdem_ArvAVL(avl);
    printf("\n\n");
//
//    int NR = 4, dadosR[4] = {7,51,3,5};
//    for(i=0;i<NR;i++){
//        printf("\nRemovendo: %d\n",dadosR[i]);
//        res = remove_ArvAVL(avl,dadosR[i]);
//        printf("\n\nres = %d\n",res);
//        preOrdem_ArvAVL(avl);
//        //printf("\n\n");
//    }
//
//    printf("\nAVL tree:\n");
//    preOrdem_ArvAVL(avl);
//    printf("\n\n");

    remove_ArvAVL(avl,6);
    printf("\nAVL tree:\n");
    emOrdem_ArvAVL(avl);
    printf("\n\n");

    remove_ArvAVL(avl,7);
    printf("\nAVL tree:\n");
    emOrdem_ArvAVL(avl);
    printf("\n\n");

    remove_ArvAVL(avl,4);
    printf("\nAVL tree:\n");
    emOrdem_ArvAVL(avl);
    printf("\n\n");

    libera_ArvAVL(avl);


    return 0;
    return 0;
}