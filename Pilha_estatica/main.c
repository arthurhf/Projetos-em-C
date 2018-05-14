#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};

typedef struct pilha Pilha;

struct pilha{
    int qtd;
    struct aluno dados[MAX];
};

Pilha * cria_Pilha(){
    Pilha *pi;
    pi=(Pilha*)malloc(sizeof(struct pilha));
    if(pi!=NULL){
        pi->qtd=0;
    }
    return pi;
}

void libera_Pilha(Pilha *pi){
    free(pi);
}

int Pilha_vazia(Pilha *pi){
    if(pi==NULL)return -1;
    return (pi->qtd==0);
    
}

int Pilha_cheia(Pilha *pi){
    if(pi==NULL)return -1;
    return (pi->qtd==MAX);
}

int insere_Pilha(Pilha *pi, struct aluno al){
    if(pi==NULL)return 0;
    if(Pilha_cheia(pi))return 0;
    pi->dados[pi->qtd]=al;
    pi->qtd++;
    return 1;
}

int remove_Pilha(Pilha *pi){
    if(pi==NULL)return 0;
    if(Pilha_vazia(pi))return 0;    
    pi->qtd--;
    return 1;
}

void mostra_Pilha(Pilha *pi){
    int cont=pi->qtd-1;
    if(pi!=NULL){
        printf("Pilha ");
        if(pi->qtd>0){
            printf("atual:\n");
            while(cont>=0){
                printf("%d\t%s\t%.2f\t%.2f\t%.2f\n",pi->dados[cont].matricula,pi->dados[cont].nome,pi->dados[cont].n1,pi->dados[cont].n2,pi->dados[cont].n3);
                cont--;
            }
        }else{
            printf("VAZIA!!");
        }
    }
        
}

int main(int argc, char** argv) {
    Pilha *pi;
    struct aluno al;
    int x;
    pi=cria_Pilha();
    al.matricula=100;
    strcpy( al.nome, "arthur");   
    al.n1=10;
    al.n2=10;
    al.n3=10;
    x=insere_Pilha(pi,al);
    printf("\nElementos na Pilha= %d\n",pi->qtd);
    mostra_Pilha(pi);
    al.matricula=101;
    strcpy( al.nome, "carol");   
    al.n1=11;
    al.n2=11;
    al.n3=11;
    
    x=insere_Pilha(pi,al);
    printf("\nElementos na Pilha = %d\n",pi->qtd);
    mostra_Pilha(pi);
    x=remove_Pilha(pi);
    printf("\nElementos na Pilha = %d\n",pi->qtd);
    mostra_Pilha(pi);
    x=remove_Pilha(pi);
    printf("\nElementos na Pilha = %d\n",pi->qtd);
    mostra_Pilha(pi);
    libera_Pilha(pi);
    return (EXIT_SUCCESS);
}

