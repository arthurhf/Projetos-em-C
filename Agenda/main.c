#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
typedef struct Contato{
    char nome[MAX];
    int telefone;
    char email[MAX];
    //int id;
    struct Contato *prox;
}CONTATO;
typedef struct Contato node;
node *criaNo();
void MostrarAgenda(node *LISTA){
    //struct Agenda contato;
    //printf("ID do contato: %d\n",contato.id);
    //printf("Nome: %s\n",contato.nome);
    //printf("Telefone: %d\n",contato.telefone);
    //printf("Email: %s\n",contato.email);
    
    if(vazia(LISTA)){
		printf("Lista vazia!\n\n");
		return ;
	}
	
	node *tmp;
	tmp = LISTA->prox;
	
	while( tmp != NULL){
		//printf("%ID do contato %d\n", tmp->id);
                printf("\nNome: %s\n",tmp->nome);
                printf("Telefone: %d\n",tmp->telefone);
                printf("Email: %s\n",tmp->email);
		tmp = tmp->prox;
	}
	printf("\n\n");
}

void inicia(node *LISTA)
{
    LISTA->prox=NULL;
}
void libera(node *LISTA)
{
	if(!vazia(LISTA)){
		node *proxNode,
			  *atual;
		
		atual = LISTA->prox;
		while(atual != NULL){
			proxNode = atual->prox;
			free(atual);
			atual = proxNode;
		}
	}
}
int vazia(node *LISTA)
{
	if(LISTA->prox == NULL)
		return 1;
	else
		return 0;
}

void InserirContato (node *LISTA)
{   
        //struct Contato pessoa;
        //char nome[MAX], email[MAX];
        //int tel,qtd=1;
        //printf("Write the contact name: \n");
        //scanf("%s",&nome);
        //printf("Write the contact phone: \n");
        //scanf("%d",&tel);
        //printf("Write the contact email: \n");
        //scanf("%s",&email);
        //strcpy(pessoa.nome, nome);
        //pessoa.telefone=12345678;
        //strcpy(pessoa.email,"arthur@gmail.com");
        //pessoa.id=qtd;
        //qtd++;
        
        node *novo=(node *) malloc(sizeof(node));
	if(!novo){
		printf("Sem memoria disponivel!\n");
		exit(1);
	}
	printf("\nWrite the contact name: \n"); scanf("%s", &novo->nome);
        printf("Write the contact phone: \n");scanf("%d", &novo->telefone);
        printf("Write the contact email: \n");scanf("%s", &novo->email);
        //novo->id=novo->id+1;
	novo->prox = NULL;
	
	if(vazia(LISTA))
		LISTA->prox=novo;
	else{
		node *tmp = LISTA->prox;
		
		while(tmp->prox != NULL)
			tmp = tmp->prox;
		
		tmp->prox = novo;
	}
    printf("\n\n");        
}

void BuscaNome(node *LISTA){
    node *tmp;
	tmp = LISTA->prox;
	char entrada[MAX];
        printf("\nDigite o nome que quer buscar: \n");
        scanf("%s", &entrada);
        printf("\nNome procurado: %s\n", entrada);
        //char *p=&entrada[0];
	while( tmp != NULL){
            if(strcmp(tmp->nome,entrada)==0){
		//printf("ID do contato %d\n", tmp->id);
                printf("Nome: %s\n",tmp->nome);
                printf("Telefone: %d\n",tmp->telefone);
                printf("Email: %s\n",tmp->email);
            }
            tmp = tmp->prox;
	}
	printf("\n\n");
}
void BuscaTel(node *LISTA){
    node *tmp;
	tmp = LISTA->prox;
	int entrada;
        printf("\nDigite o telefone que quer buscar: \n");
        scanf("%d", &entrada);
	while( tmp != NULL){
            if(tmp->telefone==entrada){
		//printf("\n%ID do contato %d\n", tmp->id);
                printf("Nome: %s\n",tmp->nome);
                printf("Telefone: %d\n",tmp->telefone);
                printf("Email: %s\n",tmp->email);
            }
            tmp = tmp->prox;
	}
	printf("\n\n");
}
int main(int argc, char** argv) {
    
    struct Contato person;
    node *LISTA=(node *)malloc (sizeof(node));
    if(!LISTA){
        printf("Sem memoria disponivel!\n");
        exit(1);
    }
    inicia(LISTA);
    int opcao=1;
    while(opcao!=0){
        printf("Escolha a opção:\n0- Sair\n1-Mostrar Agenda\n2-Inserir um contato\n3-"
                " Buscar um contato por nome\n4-Buscar um contato por telefone\n");
        scanf("%d",&opcao);
    
        /*printf("Write the contact name: \n");
        //scanf("%s",&nome);
        //printf("Write the contact phone: \n");
        //scanf("%d",&tel);
        //printf("Write the contact email: \n");
        //scanf("%s",&email);
        //strcpy(contato.nome, nome);
        //contato.telefone=12345678;
        //strcpy(contato.email,"arthur@gmail.com");
        */
        if(opcao==2)  {
              InserirContato(LISTA);  
            }          
        if(opcao==1){
            MostrarAgenda(LISTA);
            }
        if(opcao==3){
            BuscaNome(LISTA);
        }
        if(opcao==4){
            BuscaTel(LISTA);
        }
        //printf("ID do contato: %d\n",contato.id);
        //printf("Nome: %s\n",contato.nome);
        //printf("Telefone: %d\n",contato.telefone);
        //printf("Email: %s\n",contato.email);
        if(opcao==0){
            libera(LISTA);
        }
    }
    free(LISTA);
    return (EXIT_SUCCESS);
}

