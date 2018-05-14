#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct elemento Elem;
typedef struct elemento* pilha;

struct elemento{
    double num;
    Elem *prox;
};

pilha* cria_Pilha(){
    pilha* pi = (pilha*) malloc(sizeof(pilha));
    if(pi != NULL)
        *pi = NULL;
    return pi;
}

int push(pilha* pi, double n){
    if(pi == NULL)
        return 0;
    Elem* no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->num = n;
    no->prox = (*pi);
    *pi = no;
    return 1;
}

int pop(pilha* pi, double *x){
    if(pi == NULL)
        return 0;
    if((*pi) == NULL)
        return 0;
    Elem *no = *pi;
    *x=no->num;
    *pi = no->prox;
    free(no);
    return 1;
}

int Pilha_vazia(pilha* pi){
    if(pi == NULL)
        return 1;
    if(*pi == NULL)
        return 1;
    return 0;
}

int main(int argc, char** argv) {
    int i=0;
    char p[1001];
    double n1,n2,n3;
    int erro=0;

    pilha *pi=cria_Pilha();

    scanf("%s", p);


    for(i = 0; p[i]!='\0' && !erro; i++){

        if(p[i]>=48 && p[i]<=57 ){

            n1 = p[i]-48;

            push(pi,n1);

        }else {
            switch(p[i]){
                case 'h':
                    if(pop(pi,&n1)){;
                        push(pi,n1*3);
                    }else  erro=1;
                break;

                case '+':
                    if(pop(pi, &n2) && pop(pi, &n1))
                       push(pi, n1+n2);
                    else erro=1;
                break;

                case '-':
                    if(pop(pi, &n2) && pop(pi, &n1))
                        push(pi, n1-n2);
                    else erro=1;
                break;

                case 'f':
                    if(pop(pi, &n3) && pop(pi, &n2) && pop(pi, &n1))
                        push(pi, (n1*n1) - (n2/2) + n3);
                    else erro=1;
                break;

                case 'g':
                    if(pop(pi, &n3) && pop(pi, &n2) && pop(pi, &n1))
                        push(pi, (n1*n2) + n3);
                    else erro=1;
                break;


            }
            
        }
    }
    if(pop(pi, &n1) && Pilha_vazia(pi) && !erro)
        printf("%.2lf\n", n1);
    else
        printf("ERRO");


    return (EXIT_SUCCESS);
}



