#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

//salvar o inicio e o final da lista
typedef struct data data;
struct data{
    char modelo[MAX];
    int speed;
    double effi;
    int capacity;
    int days;
};

typedef struct LinkedNode LinkedNode;
struct LinkedNode{
    data dados;
    LinkedNode *prox;
};

int vazia(LinkedNode *first){
    if (first==NULL){
        return 1;
    }
    return 0;
}

int insere(LinkedNode **first,data dados){
    LinkedNode *new=(LinkedNode*)malloc(sizeof(LinkedNode));

    if (!new){
	printf("Sem memoria disponivel!\n");
	return 0;
    }

    new->dados=dados;
    new->prox=NULL;

    if(vazia(*first)){
        (*first)=new;
        return 1;
    }

    LinkedNode *tmp=*first;
    while (tmp->prox != NULL){
        tmp = tmp->prox;
    }


    tmp->prox = new;
    return 1;
}
void printList(LinkedNode *first){
    if(vazia(first)){
        return;
    }
    LinkedNode *tmp=first;
    if(tmp!=NULL){
        printf("[M=%s V=%d KM-L=%.2f C=%d E=%d]\n",tmp->dados.modelo,tmp->dados.speed,tmp->dados.effi,tmp->dados.capacity,tmp->dados.days);
        printList(tmp->prox);
    }
}
void libera(LinkedNode *tmp) {
    if(!tmp) return;
    libera(tmp->prox);
    free(tmp);
    printf("liberou");
}

int main(int argc, char** argv) {
    LinkedNode *node =NULL;
    int x,opcao=100;
    data d;
    char nome[MAX];

    while(opcao!=0){
        scanf("\n%d",&opcao);
        if(opcao==1){
            scanf(" %s %d %lf %d %d",nome,&d.speed,&d.effi,&d.capacity,&d.days);
            strcpy(d.modelo,nome);
            x=insere(&node,d);
        }

        if(opcao==2){
            printf("[DISCOS]\n");
            printList(node);
        }
        if(opcao==0){
            libera(node);
        }
    }


    return (EXIT_SUCCESS);
}

