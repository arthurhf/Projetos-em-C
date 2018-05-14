#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10
double pilha[MAX];
int inicio,fim;

int pilhaVazia(){
    return(inicio==fim);
}
int pilhaCheia(){
    return (fim==MAX);
}

void push(double x){
    
    if(!pilhaCheia()){
       
        pilha[fim++]=x;
    }else{
        
    }
   

}
int pop (){
   
    double aux;
    if(!pilhaVazia()){
        
        
        aux=pilha[fim-1];
        fim--;
       
        
        
        return aux;
    }else{
               
    }
     
    
}


int main(int argc, char** argv) {
    inicio=0;
    fim=0;
    int i=0;
    char *p;
    double n1,n2,n3;
    int tamanho;
    
    scanf("%s", p);
    tamanho= strlen(p);
    
    for(i=0;i<tamanho;i++){
       
        if(pilhaVazia() && p[i]>=48 && p[i]<=57 ){
            
            n1 = p[i]-48;
            
            push(n1);
            n2=1;
        }
        if(n2==0 && !pilhaVazia() && p[i]>=48 && p[i]<=57){
            
            n1 = p[i]-48;
            
            push(n1);
        }else {            
            if(p[i]=='h'){
                n1=pilha[fim-1]*3;
                pop();
                push(n1);
                
            }
            
                       
            if(p[i]=='+'){
                if(fim-1==inicio){
                    printf("ERRO");
                    n3=1;
                }else{
                    n1= pilha[fim-1]+pilha[fim-2];
                    pilha[fim-1]=0;
                    pop();
                    pop();                
                    push(n1);
                }
            }
            if(p[i]=='-'){
                if(fim-1==inicio){
                    printf("ERRO");
                    n3=1;
                }else{
                    n1=pilha[fim-2]-pilha[fim-1];
                    
                    pilha[fim-1]=0;
                    pilha[fim-2]=0;
                    pop();
                    pop();                
                    push(n1);
                }
            }
            
            
            if(p[i]=='f'){
                if(fim-2==inicio){
                    printf("ERRO");
                    n3=1;
                }else{
                    n1=(pilha[fim-3]*pilha[fim-3])-(pilha[fim-2]/2)+pilha[fim-1];
                    pilha[fim-1]=0;
                    pilha[fim-2]=0;
                    pilha[fim-3]=0;
                    pop();
                    pop();
                    pop();
                    push(n1);
                }
            }
            if(p[i]=='g'){
                if(fim-2==inicio){
                    printf("ERRO");
                    n3=1;
                }else{
                    n1=(pilha[fim-3]*pilha[fim-2])+pilha[fim-1];
                    pilha[fim-1]=0;
                    pilha[fim-2]=0;
                    pilha[fim-3]=0;
                    pop();
                    pop();
                    pop();
                    push(n1);
                }
            }
        }
        n2=0;        
    }
    if(fim-1!=inicio){
        printf("ERRO");
        n3=1;
    }
    if(n3!=1){
        printf("%.2f",pilha[fim-1]);
    }
    
    
    return (EXIT_SUCCESS);
}

