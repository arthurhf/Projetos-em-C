#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};
typedef struct fila Fila;
struct fila{
    int inicio, final, qtd;
    struct aluno dados[MAX];
};

Fila* cria_Fila(){
    Fila *fi=(Fila*)malloc(sizeof(struct fila));
    if(fi!=NULL){
        fi->inicio=0;
        fi->final=0;
        fi->qtd=0;
    }
    return fi;
}

void libera_Fila(Fila *fi){
    free(fi);
}

int fila_cheia(Fila *fi){
    if(fi==NULL) return -1;
    if(fi->qtd==MAX)
        return 1;
    else
    return 0;
}

int fila_vazia(Fila *fi){
    if(fi==NULL) return -1;
    if(fi->qtd==0)
        return 1;
    else return 0;
}

int insere_Fila(Fila *fi, struct aluno al){
    if(fi==NULL)return 0;
    if(fila_cheia(fi))return 0;
    fi->dados[fi->final]=al;
    fi->final=(fi->final+1)%MAX;
    fi->qtd++;
    return 1;
}

int remove_Fila(Fila *fi){
    if(fi==NULL)return 0;
    if(fila_vazia(fi))return 0;    
    fi->inicio=(fi->inicio+1)%MAX;
    fi->qtd--;
    return 1;
}
void mostra_Fila(Fila *fi){ 
    int cont=fi->inicio;
    if(fi!=NULL){
        printf("FILA ");
        if(fi->qtd>0){
            printf("ATUAL\n");
            while (cont<fi->final){
                printf("%d\t%s\t%.2f\t%.2f\t%.2f\n",fi->dados[cont].matricula,fi->dados[cont].nome,fi->dados[cont].n1,fi->dados[cont].n2,fi->dados[cont].n3);
                cont++;
            }
        }else{
            printf("VAZIA!!\n");
        }
    }
    printf("\n");
}
int main(int argc, char** argv) {
    Fila *fi;
    struct aluno al;
    int x;
    fi=cria_Fila();
    al.matricula=100;
    strcpy( al.nome, "arthur");   
    al.n1=10;
    al.n2=10;
    al.n3=10;
    x=insere_Fila(fi,al);
    al.matricula=101;
    strcpy( al.nome, "carol");   
    al.n1=11;
    al.n2=11;
    al.n3=11;
    x=insere_Fila(fi,al);
    mostra_Fila(fi);
    
    //printf("\n%d\n",x);
    //printf("\n%d\n",fi->dados[fi->inicio].matricula);
    x=remove_Fila(fi);
    //printf("\n%d\n",fi->dados[fi->inicio].matricula);
    //printf("\n%d\n",x);
    mostra_Fila(fi);
    //printf("\n%d\n",x);
   // printf("\n%d\n",fi->dados[fi->inicio].matricula);
    x=remove_Fila(fi);   // printf("\n%d\n",x);
    
    mostra_Fila(fi);
    
    libera_Fila(fi);
    return (EXIT_SUCCESS);
}

