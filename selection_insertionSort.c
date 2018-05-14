#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
struct aluno{
    int ra;
    char nome[MAX];
    int nota;
};
typedef struct fila Fila;

struct fila{
    struct elemento *inicio;
    struct elemento *final;
    int qtd;
};

struct elemento{
    struct aluno dados;
    struct elemento *prox;
    struct elemento *ant;
};
typedef struct elemento Elem;

Fila * cria_Fila(){
    Fila*fi=(Fila*)malloc(sizeof(Fila));
    if(fi!=NULL){
        fi->final=NULL;
        fi->inicio=NULL;
    }
    return fi;
}

void libera_Fila(Fila *fi){
    if(fi!=NULL){
        Elem *no;
        while(fi->inicio!=NULL){
            no=fi->inicio;
            fi->inicio=fi->inicio->prox;
            free(no);
        }
        free(fi);
    }
}

int insere_Fila(Fila *fi, struct aluno al){
    if(fi==NULL)return 0;

    Elem *no=(Elem*)malloc(sizeof(Elem));
    if(no==NULL)return 0;


    no->dados=al;
    no->prox=NULL;

    if(fi->final==NULL){
        fi->inicio=no;
        no->ant=NULL;
    }
    else {
        Elem *aux=fi->inicio;
        while(aux->prox!=NULL){
            aux=aux->prox;
        }
        no->ant=aux;
        fi->final->prox=no;
    }

    fi->final=no;
    fi->qtd++;
    return 1;
}

void mostra_Fila(Fila *fi){
    Elem *no=fi->inicio;
    if(fi!=NULL){
        //printf("FILA ");
        if(no!=NULL){
            //printf("ATUAL\n");
            while (no!=NULL){
                printf("[%d %s %d]\n",no->dados.ra,no->dados.nome,no->dados.nota);
                no=no->prox;
            }
        }else{
           // printf("VAZIA!!\n");
        }
    }
    //printf("\n");
}

void buscaRA_Fila(Fila *fi,int ra){
    Elem *no=fi->inicio;
    int pos=0;
    if(fi!=NULL){
        if(no!=NULL){
            while(no!=NULL){
                if(no->dados.ra==ra){
                    printf("Pos=%d\n",pos);
                    return;
                }
                no=no->prox;
                pos=pos+1;
            }
            printf("Pos=-1\n");
        }
    }
}
int selectionSort(Fila *fi,int opcao) {
    /*
     https://visualgo.net/pt/sorting
     * melhor caso quando a array está ordenada
     * pior caso quando o maior está sempre no começo ou o menor está
      sempre no final da array nao ordenada de cada troca
     * não é estável (pode mudar a posição relativa dos registros que possuem mesma chave)
     * usa memória constante
     * não é adaptativo pois para qualquer arranjo tem a mesmma complexidade
    */
    Elem *no=fi->inicio;
    Elem *min,*aux;
    Elem *aux2=(Elem*)malloc(sizeof(Elem));
    long int comp=0;
    int ret;

    //ordena por RA
        while(no!=NULL){
            if(no->prox==NULL){
                return comp;
            }
            aux=no->prox;
            min=no;
            while(aux!=NULL){

                if(opcao==1 && min->dados.ra>aux->dados.ra){
                   min=aux;
                }else if(opcao==2 && (ret = strcmp(min->dados.nome, aux->dados.nome))>0){
                    min=aux;
                }
                comp++;
                aux=aux->prox;
            }
            if(min!=no){
                //aux=min;
                strcpy(aux2->dados.nome,min->dados.nome);
                //aux2->dados.nome=min->dados.nome;
                aux2->dados.nota=min->dados.nota;
                aux2->dados.ra=min->dados.ra;
                //min=no;
                strcpy(min->dados.nome,no->dados.nome);
                //min->dados.nome=no->dados.nome;
                min->dados.nota=no->dados.nota;
                min->dados.ra=no->dados.ra;
                //no=aux;
                strcpy(no->dados.nome,aux2->dados.nome);
                //no->dados.nome=aux2->dados.nome;
                no->dados.nota=aux2->dados.nota;
                no->dados.ra=aux2->dados.ra;
            }
            no=no->prox;
        }
    return comp;
}


int insertionSort(Fila *fi,int opcao) {
    /*ordenar as cartas do baralho
     * melhor caso array ordenada
     * pior caso quando a array está na ordem reversa
     * é estável
     * usa memória constante
     * é adaptativo,demora mais no pior caso
     */

    long int comp=0;
    Elem *no=fi->inicio;
    Elem *ant,*atual;
    int ret,key1,key3;
    char key2[MAX];
    while(no!=NULL){
        if(no->prox==NULL){
            return comp;
        }
        atual=no->prox;
        key1=atual->dados.ra;
        strcpy (key2,atual->dados.nome);
        key3=atual->dados.nota;
        ant=no;
            while(ant!=NULL && ++comp && ((ant->dados.ra>key1&&opcao==1)||((ret = strcmp(ant->dados.nome, key2))>0&&opcao==2))){

                ant->prox->dados.ra=ant->dados.ra;
                ant->prox->dados.nota=ant->dados.nota;
                strcpy(ant->prox->dados.nome,ant->dados.nome);

                ant=ant->ant;
            }
            if(ant==NULL){
                    fi->inicio->dados.ra=key1;
                    strcpy (fi->inicio->dados.nome,key2);
                    fi->inicio->dados.nota=key3;
            }else  {
                ant->prox->dados.ra=key1;
                strcpy (ant->prox->dados.nome,key2);
                ant->prox->dados.nota=key3;
            }

        no=no->prox;
    }


    return comp;
}

int main(int argc, char** argv) {
    Fila *fi;
    fi=cria_Fila();
    struct aluno al;
    int x,ra,algoritmo,campo,comp;
    char opcao='A',nome[MAX];

    while(opcao!='P'){
        scanf("\n%c",&opcao);
        if(opcao=='I'){
            scanf(" %d %s %d",&al.ra,nome,&al.nota);
            strcpy(al.nome,nome);
            x=insere_Fila(fi,al);
            }

           if(opcao=='B'){
                scanf(" %d",&ra);
                buscaRA_Fila(fi,ra);

            }

            if(opcao=='O'){

                scanf(" %d",&algoritmo);
                if(algoritmo==1){
                    scanf(" %d",&campo);
                    comp=selectionSort(fi,campo);
                }else{
                    scanf(" %d",&campo);
                    comp=insertionSort(fi,campo);
                }
                printf("Comparacoes=%d\n",comp);
            }

            if(opcao=='M'){
                mostra_Fila(fi);
            }

            if(opcao=='P'){

                libera_Fila(fi);
                return 0;
            }
    }


    return (EXIT_SUCCESS);
}

