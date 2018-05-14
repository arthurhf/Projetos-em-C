#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};


struct elemento {
    struct aluno dados;
    struct elemento *prox;    
};
typedef struct elemento Elem;
typedef struct elemento *Pilha;//ponteiro de ponteiro que guarda o 1 elem

Pilha *cria_Pilha(){
    Pilha *pi;
    pi=(Pilha*)malloc(sizeof(Pilha));
    if(pi!=NULL){
        *pi=NULL;//topo aponta para NULL
    }
    return pi;
}

void libera_Pilha(Pilha *pi){
    if(pi!=NULL){
        Elem *no;
        while((*pi)!=NULL){
            no=*pi;
            *pi=(*pi)->prox;
            free(no);
        }
        free(pi);
    }
}

int tamanho_Pilha(Pilha *pi){
    if(pi==NULL)return 0;
    int cont=0;
    Elem *no=*pi;
    while(no!=NULL){        
        cont++;
        no=no->prox;
    }
    return cont;
}

int insere_Pilha(Pilha *pi, struct aluno al){
    if(pi==NULL)return 0;
    Elem *no=(Elem *)malloc(sizeof(Elem));
    if(no==NULL)return 0;
    no->dados=al;
    no->prox=(*pi);
    *pi=no;
    return 1;
}

int remove_Pilha(Pilha *pi){
    if(pi==NULL)return 0;
    if((*pi)==NULL)return 0;
    Elem *no=(*pi);           
    *pi=no->prox;
    free(no);
    return 1;
    
}

void mostra_Pilha(Pilha *pi){
    //int t=tamanho_Pilha(pi);
    Elem *no=*pi;
    if(pi!=NULL){
        printf("Pilha ");
        if(no!=NULL){
            printf("atual:\n");
            while(no!=NULL){
                printf("%d\t%s\t%.2f\t%.2f\t%.2f\n",no->dados.matricula,no->dados.nome,no->dados.n1,no->dados.n2,no->dados.n3);
                no=no->prox;
            }
        }else{
            printf("VAZIA!!");
        }
    }
}

int main(int argc, char** argv) {

    Pilha *pi;
    struct aluno al;
    int x,tam;
    pi=cria_Pilha();
    al.matricula=100;
    strcpy( al.nome, "arthur");   
    al.n1=10;
    al.n2=10;
    al.n3=10;
    x=insere_Pilha(pi,al);
    tam=tamanho_Pilha(pi);
    printf("\nElementos na Pilha= %d\n",tam);
    mostra_Pilha(pi);
    al.matricula=101;
    strcpy( al.nome, "carol");   
    al.n1=11;
    al.n2=11;
    al.n3=11;
    
    x=insere_Pilha(pi,al);
    tam=tamanho_Pilha(pi);
    printf("\nElementos na Pilha = %d\n",tam);
    mostra_Pilha(pi);
    x=remove_Pilha(pi);
    tam=tamanho_Pilha(pi);
    printf("\nElementos na Pilha = %d\n",tam);
    mostra_Pilha(pi);
    x=remove_Pilha(pi);
    tam=tamanho_Pilha(pi);
    printf("\nElementos na Pilha = %d\n",tam);
    mostra_Pilha(pi);
    libera_Pilha(pi);
    
    return (EXIT_SUCCESS);
}

