#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lista {
	int ra;
	int CodTopico;
	struct Lista *prox;
        
} Lista;
typedef struct Lista node;
node *criaNo();

void inicia(node *LISTA) {
	LISTA->prox = NULL;
}
int vazia(node *LISTA) {
	if (LISTA->prox == NULL)
		return 1;
	else
		return 0;
}

void Mostrar(node *LISTA) {
	if (vazia(LISTA)) {
		printf("Lista vazia!\n\n");
		return;
	}
	node *tmp;
	tmp = LISTA->prox;

	while (tmp != NULL) {
		

		printf("%d ", tmp->ra);
		printf("%d\n", tmp->CodTopico);
		tmp = tmp->prox;
	}
	
}



void inserirDado(node * LISTA, int ra, int CodTop) {
    int aux=0;
                node *p, *q;
    		node *novo = (node *)malloc(sizeof(node));
		if (!novo) {
			printf("Sem memoria disponivel!\n");
			exit(1);
		}	
  		novo->prox=NULL;
  		novo->ra = ra;
  		novo->CodTopico = CodTop;
                p=LISTA;
                
                
                if (vazia(LISTA)){
  			LISTA->prox = novo;
  		}else{
                    q=LISTA->prox;
                    while(q->prox!=NULL ){
                        
                        if(aux==0){
                            if(novo->ra==q->ra){
                                novo->prox=q->prox;
                                q->prox=novo;                             
                                
                                aux=1;
                            }
                        }      

                       q=q->prox; 

                    }
                    if(aux==0){
                        q->prox=novo; 
                    }

                }                  		
		
	}

void libera(node *LISTA) {
	if (!vazia(LISTA)) {
		node *proxNode, *atual;

		atual = LISTA->prox;
		while (atual != NULL) {
			proxNode = atual->prox;
			free(atual);
			atual = proxNode;
		}
	}
}

int main(int argc, char **argv) {
	struct Lista dado;
        int ra=1, CodTop=1;
	node *LISTA = (node *)malloc(sizeof(node));
	if (!LISTA) {
		printf("Sem memória disponivel!\n");
	}
	inicia(LISTA);
        while(ra>0 && CodTop>0){
            
            scanf("%d %d", &ra, &CodTop);
            if(ra!=-1 && CodTop!=-1)
            inserirDado(LISTA,ra,CodTop);
        }
        Mostrar(LISTA);
	libera(LISTA);

	return (EXIT_SUCCESS);
}

