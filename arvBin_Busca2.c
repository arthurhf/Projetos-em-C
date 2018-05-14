#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct NO* ArvBin;
struct NO{
    int ra;
    int nota;
    struct NO *esq;
    struct NO *dir;
};

ArvBin* cria_ArvBin(){
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvBin(ArvBin* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada nó
    free(raiz);//libera a raiz
}

int insere_ArvBin(ArvBin* raiz, int valor, int grade){
    if(raiz == NULL)
        return 0;
    struct NO* novo;
    novo = (struct NO*) malloc(sizeof(struct NO));
    if(novo == NULL)
        return 0;
    novo->ra = valor;
    novo->nota=grade;
    novo->dir = NULL;
    novo->esq = NULL;

    if(*raiz == NULL)
        *raiz = novo;
    else{
        struct NO* atual = *raiz;
        struct NO* ant = NULL;
        while(atual != NULL){
            ant = atual;
            if(valor == atual->ra){
                atual->nota=novo->nota;
                free(novo);
                return 0;//elemento já existe
            }

            if(valor > atual->ra)
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        if(valor > ant->ra)
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    return 1;
}

int consulta_ArvBin(ArvBin *raiz, int valor){
    int contA=0;
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL){
        //printf(":::\n%d\n",atual->ra);
        if(valor == atual->ra){
            printf("C=%d Nota=%d\n",(contA+1),atual->nota);
            return (contA+1);
        }
        if(valor > atual->ra){
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

int altura_ArvBin(ArvBin *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvBin(&((*raiz)->esq));
    int alt_dir = altura_ArvBin(&((*raiz)->dir));
    if (alt_esq > alt_dir){
       // printf("\n 106\n");
        return (alt_esq + 1);}
    else{
        //printf("\n109\n");
        return(alt_dir + 1);}
}

int remove_ArvBin(ArvBin *raiz, int valor){
    //printf("\n INICIO REMOVE \n");
    if(raiz == NULL)
        return 0;
    struct NO* ant = NULL;
    struct NO* atual = *raiz;
    struct NO* aux=NULL;
    //aux->dir=NULL;
    //aux->esq=NULL;
    //printf("\n aux direita \n",aux->dir);
    //printf("\n aux esq \n",aux->esq);
    int i=0,c=0;
    while(atual!=NULL){
        if(valor==atual->ra){
            if(atual->dir==NULL && atual->esq==NULL){
                //REMOVE FOLHA
                //printf("\n REMOVE FOLHA \n");
                    if(atual==*raiz){
                      *raiz = NULL;
                    }
                    else if(ant->esq == atual)
                            ant->esq = NULL;
                          else
                            ant->dir = NULL;
                    free(atual);
                    atual=NULL;
                    return 1;
                }
            else

              // Considerar o caso em que atual tem um único filho!!!!
                if (atual->esq == NULL || atual->dir == NULL) {
                  if(atual==*raiz && atual->dir!=NULL){
                    aux=atual->dir;
                    while(aux->esq!=NULL){
                        aux=aux->esq;
                        //printf("\n ra do auxiliar %d \n",aux->ra);
                        c++;
                    }
                    atual->ra=aux->ra;
                    atual->nota=aux->nota;
                    remove_ArvBin(&atual->dir, atual->ra);
                    return 1;

                    }
                    if(atual==*raiz && atual->esq!=NULL){
                      aux=atual->esq;
                      atual->ra=aux->ra;
                      atual->nota=aux->nota;
                      remove_ArvBin(&atual->esq, atual->ra);
                      return 1;

                    }
                    if(ant->dir==atual){
                        //REMOVE elemento que tem apenas filho do lado dir
                        //printf("\n REMOVE elemento que tem apenas filho do lado dir \n");
                        if(atual->dir==NULL)
                            ant->dir=atual->esq;
                        if(atual->esq==NULL)
                            ant->dir=atual->dir;
                        //free(atual);
                        free(atual);
                        return 1;
                    } else if(ant->esq==atual){
                        //REMOVE elemento que tem apenas filho do lado esq
                        //printf("\n REMOVE elemento que tem apenas filho do lado esq \n");
                        if(atual->dir==NULL)
                            ant->esq=atual->esq;
                        if(atual->esq==NULL)
                            ant->esq=atual->dir;
                        //free(atual);
                        free(atual);
                        return 1;
                    }
                } else   if (atual->dir!=NULL && atual->esq!=NULL){
                  if(atual==*raiz){
                    aux=atual->dir;
                    while(aux->esq!=NULL){
                        aux=aux->esq;
                        //printf("\n ra do auxiliar %d \n",aux->ra);
                        c++;
                    }
                     atual->ra=aux->ra;
                    atual->nota=aux->nota;
                    remove_ArvBin(&atual->dir, atual->ra);
                    return 1;

                    }
                    //caso que tem dois filhos
                    //printf("\n REMOVE elemento que tem dois filhos \n");
                    aux=atual->dir;
                    //printf("\n ra do auxiliar %d \n",aux->ra);
                    while(aux->esq!=NULL){
                        aux=aux->esq;
                        //printf("\n ra do auxiliar %d \n",aux->ra);
                        c++;
                    }
                    // copiar o RA e nota do aux para o atual!!!!
                    atual->ra=aux->ra;
                    atual->nota=aux->nota;

                    remove_ArvBin(&atual->dir, atual->ra);
                    /*ant=atual->dir;
                    for(i=0;i<c;i++){
                        ant=ant->esq;
                        printf("\n ra do anterior %d \n",ant->ra);
                    }
                    ant->esq=aux->dir;
                    printf("\n ra do elemento à esquerda do anterior%d \n",ant->esq->ra);
                    free(aux);
                    //free(atual);
                    ant=NULL;*/
                    return 1;
                }
            }
        ant=atual;
        if(valor > atual->ra)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

int main(void)
{

    ArvBin* raiz = cria_ArvBin();
    char opcao='I';
    int ra,valorL,valorA,grade,altura,remov;

    //scanf("%c",&opcao);
    //scanf(" %d",&ra);
    //printf("\n%c\n",opcao);
   // printf("\n:%d\n",ra);

        while( opcao != 'P')
        {
            //ra=0;
            //fflush(stdin);
            //scanf("%c",&opcao);
            //fflush(stdin);
            //printf("\ndigite entrada:\n");
            scanf("\n%c",&opcao);
            //fflush(stdin);
            //printf("leu: %d\n",ra);
            if(opcao=='I'){
                scanf(" %d %d",&ra,&grade);
            //printf("\n::opcao %c ra =%d nota= %d\n",opcao,ra,grade);
               // inserir(&inicio,ra,grade);
                insere_ArvBin(raiz,ra,grade);
            }
            //printf("\n:::%d\n",ra);
            //printf("\nopcao = %c\n",opcao);
            //scanf("%c", &opcao);
            //printf("\nopcao == %c\n",opcao);

            //printf("\n%c",opcao);
           // printf("\n::::%d\n",ra);
           if(opcao=='B'){
                scanf(" %d",&ra);
                valorA=consulta_ArvBin(raiz,ra);

            }

            if(opcao=='A'){
                //printf("\nif altura\n");
                altura=altura_ArvBin(raiz);
                printf("A=%d\n", (altura-1));
            }

            if(opcao=='R'){
                scanf(" %d",&ra);
                remov=remove_ArvBin(raiz,ra);
            }

            if(opcao=='P'){
            //printf("\nopcao=== %c",opcao);

            libera_ArvBin(raiz);
           // printf("\naliberou\n");
            return 0;

            }


        }

    //printf("\nbliberou\n");

    libera_ArvBin(raiz);
    return 0;
}
