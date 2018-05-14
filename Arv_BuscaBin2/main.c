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
        printf(":::\n%d\n",atual->ra);
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

/*struct NO* remove_atual(ArvBin *raiz,struct NO* atual) {
    struct NO *no1, *no2;

    if(atual->esq == NULL){
        no2 = atual->dir;
        free(atual);
        return no2;
    }
    no1 = atual;
    no2 = atual->esq;
    if(no1==*raiz){
        no1=no1->dir;
        while(no1!=NULL){
          no1=no1->esq;
        }
        atual->nota=no1->nota;
        atual->ra=atual->ra;
        return atual;
    }
    while(no2->dir != NULL){
        no1 = no2;
        no2 = no2->dir;
    }

    // no2 é o nó anterior a r na ordem e-r-d
    // no1 é o pai de no2
    if(no1 != atual){
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2 = atual->dir;
    no2->esq=no1->esq;
    free(atual);
    return no2;
}*/

int remove_ArvBin(ArvBin *raiz, int valor){
    if(raiz == NULL)
        return 0;

    struct NO* ant = NULL;
    struct NO* atual = *raiz;
    struct NO* aux=NULL;
    int i=0,c=0;

    while(atual!=NULL){
        if(valor==atual->ra){
            if(atual->dir==NULL && atual->esq==NULL){
                    atual=NULL;//REMOVE FOLHA
                }
            else   if(atual->dir!=NULL){
                                if(atual==*raiz){
                                aux=atual->dir;
                                while(aux->esq!=NULL){

                                    aux=aux->esq;
                                    c++;

                                }
                                *raiz=aux;
                                (*raiz)->dir=atual->dir;
                                (*raiz)->esq=atual->esq;

                                ant=atual->dir;

                                for(i=0;i<c;i++){
                                    ant=ant->esq;
                                }
                                ant=NULL;
                            } else {

                                    if(atual->dir!=NULL){
                                            c=0;
                                            aux=atual->dir;
                                            while(aux->esq!=NULL){
                                                aux=aux->esq;
                                                c++;
                                            }
                                            atual->ra=aux->ra;
                                            atual->nota=aux->nota;
                                            ant=atual->dir;
                                            for(i=0;i<c;i++){
                                                ant=ant->esq;
                                            }
                                            ant=NULL;
                                        }

                            }
            }  else{

                    aux=atual->esq;
                    ant->esq=aux;
                    atual=NULL;
                    }
            return 1;
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
                valorA=consulta_ArvBin(raiz,ra);                //valorL=buscaLista(inicio,ra);

            }

            if(opcao=='A'){
                //printf("\nif altura\n");
                altura=altura_ArvBin(raiz);
                printf("A= %d\n", (altura-1));
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
