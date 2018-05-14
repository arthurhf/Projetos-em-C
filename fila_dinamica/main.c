#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct fila Fila;
struct fila{
    struct elemento *inicio;
    struct elemento *final;
    int qtd;
};

struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
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

int Fila_vazia(Fila *fi){
    if(fi==NULL)return 1;
    if(fi->inicio==NULL)return 1;
    return 0;
}

int Fila_cheia(Fila *fi){
    return 0;
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

int remove_Fila(Fila *fi){
    if(fi==NULL)return 0;
    if(fi->inicio==NULL)return 0;
    Elem *no=fi->inicio;
    fi->inicio=fi->inicio->prox;
    if(fi->inicio==NULL)fi->final=NULL;
    free(no);
    fi->qtd--;
    return 1;
}
void mostra_Fila(Fila *fi){ 
    Elem *no=fi->inicio;
    if(fi!=NULL){
        printf("FILA ");
        if(no!=NULL){
            printf("ATUAL\n");
            while (no!=NULL){
                printf("%d\t%s\t%.2f\t%.2f\t%.2f\n",no->dados.matricula,no->dados.nome,no->dados.n1,no->dados.n2,no->dados.n3);
                no=no->prox;
            }
        }else{
            printf("VAZIA!!\n");
        }
    }
    printf("\n");
}

int main(int argc, char** argv) {
    Fila *fi;
    fi=cria_Fila();
    struct aluno al;
    int x;
    
    al.matricula=100;
    strcpy( al.nome, "arthur");   
    al.n1=10;
    al.n2=10;
    al.n3=10;
    x=insere_Fila(fi,al);
    printf("\nElementos na Fila: %d\n",fi->qtd);
    mostra_Fila(fi);
    al.matricula=101;
    strcpy( al.nome, "carol");   
    al.n1=11;
    al.n2=11;
    al.n3=11;
    x=insere_Fila(fi,al);
    printf("\nElementos na Fila: %d\n",fi->qtd);
    mostra_Fila(fi);
    remove_Fila(fi);
    printf("\nElementos na Fila: %d\n",fi->qtd);
    mostra_Fila(fi);    
    remove_Fila(fi);
    printf("\nElementos na Fila: %d\n",fi->qtd);
    mostra_Fila(fi);    
    
    
    libera_Fila(fi);

    return (EXIT_SUCCESS);
}

