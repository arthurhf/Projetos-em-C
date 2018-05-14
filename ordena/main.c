#include <stdio.h>
#include <stdlib.h>

struct aluno{
    int ra;
    char nome[50];
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
    
    if(fi->final==NULL)fi->inicio=no;
    
    else fi->final->prox=no;
    
    fi->final=no;
    fi->qtd++;
    return 1;
}

void mostra_Fila(Fila *fi){ 
    Elem *no=fi->inicio;
    if(fi!=NULL){
        printf("FILA ");
        if(no!=NULL){
            printf("ATUAL\n");
            while (no!=NULL){
                printf("%d\t%s\t%.2d",no->dados.ra,no->dados.nome,no->dados.nota);
                no=no->prox;
            }
        }else{
            printf("VAZIA!!\n");
        }
    }
    printf("\n");
}

void buscaRA_Fila(Fila *fi,int ra){
    Elem *no=fi->inicio;
    int pos=0;
    if(fi!=NULL){
        if(no!=NULL){
            while(no!=NULL){
                if(no->dados.ra==ra){
                    printf("Pos=%d",pos);
                }
                no=no->prox;
                pos=pos+1;
            }
            printf("Pos=-1");
        }
    }
}

/*void buscaNOME_Fila(Fila *fi,char nome[]){
    Elem *no=fi->inicio;
    int pos=0;
    if(!=NULL){
        if(no!=NULL){
            while(no!=NULL){
                if(no->dados.nome==nome){
                    printf("Pos=%d",pos);
                }
                pos=pos+1;
            }
            printf("Pos=-1");
        }
    }
}*/

int selectionSort(Fila *fi, int n,int opcao) {
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
            aux=no->prox;
            min=no;
            while(aux!=NULL){
                
                if(opcao==1 && min->dados.ra>aux->dados.ra){
                   min=aux; 
                }else if(opcao==2 && ret = strcmp(min->dados.nome, aux->dados.nota)>0){
                    min=aux;
                }
                comp++;
                aux=aux->prox;
            }
            if(min!=no){
                //aux=min;
                aux2->dados.nome=min->dados.nome;
                aux2->dados.nota=min->dados.nota;
                aux2->dados.ra=min->dados.ra;
                //min=no;
                min->dados.nome=no->dados.nome;
                min->dados.nota=no->dados.nota;
                min->dados.ra=no->dados.ra;
                //no=aux;
                no->dados.nome=aux2->dados.nome;
                no->dados.nota=aux2->dados.nota;
                no->dados.ra=aux2->dados.ra;
            }
            no=no->prox;
        }
    return comp;
}


int insertionSort(int v[], int n,Fila *fi, int n,int opcao) {
    /*ordenar as cartas do baralho
     * melhor caso array ordenada
     * pior caso quando a array está na ordem reversa
     * é estável
     * usa memória constante
     * é adaptativo,demora mais no pior caso
     */
    int i, j, key;
    long int comp=0;
     
    for (i=1; i<n; i++) {
        key = v[i];
        j = i-1; 
        while(j>=0  && ++comp && v[j]>key) {
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = key;
    }
    
    return comp;
}

int main(int argc, char** argv) {

    return (EXIT_SUCCESS);
}

