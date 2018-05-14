#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct NO* ArvAVL;
struct NO{
    int info;
    int nota;
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
    //printf("No desbalanceado: %d",no->info);
    (*raiz)->esq=no->dir;
    no->dir=*raiz;
    (*raiz)->alt=maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir))+1;
    no->alt=maior(altura_NO(no->esq),(*raiz)->alt)+1;
    *raiz=no;
}

void RotacaoRR(ArvAVL *raiz){
    struct NO* no;
    no=(*raiz)->dir;
    //printf("[x=%d y=%d z=%d]",(*raiz)->info,no->dir->info,no->info);
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

int balanceou(){
    return 1;
}

int insere_ArvAVL(ArvAVL* raiz, int valor,int nota, int *bal){
    int res,b=0;
    if(*raiz == NULL){        
        struct NO* novo;
        novo = (struct NO*) malloc(sizeof(struct NO));
        if(novo == NULL)
            return 0;
        novo->info = valor;
        novo->nota=nota;
        novo->alt=0;
        novo->dir = NULL;
        novo->esq = NULL;
        *raiz=novo;
        //printf("[Ja esta balanceado]\n");
        *bal=0;
        return 1;
    }
    struct NO *atual=*raiz;
    if(valor<atual->info){
        if((res=insere_ArvAVL(&(atual->esq),valor,nota,bal))==1){               
                if(fatorBalanceamento_NO(atual)>=2){
                    *bal=1;
                    if(valor<(*raiz)->esq->info){
                        printf("[No desbalanceado: %d]\n",atual->info);
                        printf("[Rotacao SD]");
                        printf("[x=%d y=%d z=%d]",atual->info,(*raiz)->esq->esq->info,(*raiz)->esq->info);
                        RotacaoLL(raiz);

                    }else {
                        printf("[No desbalanceado: %d]\n",atual->info);
                        printf("[Rotacao DD]");
                        printf("[x=%d y=%d z=%d]",(*raiz)->esq->info,(*raiz)->esq->esq->info,atual->info);
                        RotacaoLR(raiz);
                    }
                }

            }
        }else{
            if(valor>atual->info){
                if((res=insere_ArvAVL(&(atual->dir),valor,nota,bal))==1){

                    if(fatorBalanceamento_NO(atual)>=2){
                        *bal=1;
                        if((*raiz)->dir->info<valor){
                            printf("[No desbalanceado: %d]\n",atual->info);
                            printf("[Rotacao SE]\n");
                            printf("[x=%d y=%d z=%d]\n",atual->info,(*raiz)->dir->info,(*raiz)->dir->dir->info);
                            RotacaoRR(raiz);
                        }else{
                            printf("[No desbalanceado: %d]\n",atual->info);
                            printf("[Rotacao DE]\n");
                            printf("[x=%d y=%d z=%d]\n",(*raiz)->dir->info,atual->info,(*raiz)->dir->dir->info);
                            RotacaoRL(raiz);
                        }
                    }//printf("[Ja esta balanceado]\n");
                }

            }else{
                atual->nota=nota;            
                *bal=0;
                printf("Valor duplicado!!\n");
                //printf("[Ja esta balanceado]");
                return 0;
            }
            
        }
    atual->alt=maior(altura_NO(atual->esq),altura_NO(atual->dir))+1;
    return res;    
}

int consulta_ArvAVL(ArvAVL *raiz, int valor){
    int contA=0;
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info){
            printf("C=%d Nota=%d\n",(contA+1),atual->nota);
            return (contA+1);
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
    printf("C=%d Nota=-1\n",(contA));
    return (contA-1);
}
void posOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL){
        printf("[]");
        return;}
    
    if(*raiz != NULL){
        posOrdem_ArvAVL(&((*raiz)->esq));
        //printf("%d\n",(*raiz)->info);
        posOrdem_ArvAVL(&((*raiz)->dir));
        //printf("%d ",(*raiz)->info);
        printf("%d ",(*raiz)->info);
        
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
    char opcao='I';
    int ra,valorA,grade,altura,remov;
    int res,i;    
    int b;
    
    avl = cria_ArvAVL();
    
    while( opcao != 'P')
        {
            
            scanf("\n%c",&opcao);
            
            if(opcao=='I'){
                scanf(" %d %d",&ra,&grade);
            
                res=insere_ArvAVL(avl,ra,grade,&b);
                if(b==0){
                    printf("[Ja esta balanceado]\n");
                }
            }
            
           if(opcao=='B'){
                scanf(" %d",&ra);
                valorA=consulta_ArvAVL(avl,ra);

            }

            if(opcao=='A'){
                
                altura=altura_ArvAVL(avl);
                printf("A=%d\n", (altura-1));
            }

            if(opcao=='R'){
                scanf(" %d",&ra);
                remov=remove_ArvAVL(avl,ra);
            }

            if(opcao=='P'){
            
                printf("[");
                posOrdem_ArvAVL(avl);
                printf("]");
                libera_ArvAVL(avl);
               
                return 0;

            }


        }

    
    return 0;
}