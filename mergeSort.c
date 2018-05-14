#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct linkedNode linkedNode;
struct linkedNode{
  int RA;
  int grade;
  int index;
  linkedNode *next, *last;
};

void printList(linkedNode *tmp){
  if(!tmp) return;
  printf("[%d %d]\n", tmp->RA, tmp->grade);
  printList(tmp->next);
}

void deleteList(linkedNode *tmp){
  if(!tmp) return;
  deleteList(tmp->next);
  free(tmp);
}

linkedNode* midNode (linkedNode *first, linkedNode *last){
  int i, mid_index = first->index + (last->index - first->index)/ 2;

  for(i = first->index; i < mid_index; i++)
    first = first->next;

  return first;
}

void insertNode(linkedNode **linkedList, int RA, int grade){
  linkedNode *tmp = *linkedList, *last = NULL;
  int index = 0;

  while(tmp ? tmp->RA != RA : 0){
    last = tmp;
    tmp = tmp->next;
    index++;
  }

  if(!tmp){
    // caso RA nao esteja na lista, ele eh adicionado
    linkedNode *newNode = malloc(sizeof(linkedNode));
    if(newNode == NULL) return;

    newNode->RA = RA;
    newNode->grade = grade;
    newNode->next = newNode->last = NULL;
    newNode->index = index;

    if(!last)
      // primeiro nodo (quando a lista esta vazia)
      *linkedList = newNode;
    else{
      // quando a lista jah possui algum elemento
      last->next = newNode;
      newNode->last = last;
    }
  }
  else
    // caso contrario, atualiza a nota
    tmp->grade = grade;
}

void swapLinkedList(linkedNode *node1, linkedNode *node2){
  while(node2){
    node1->RA = node2->RA;
    node1->grade = node2->grade;
    node2 = node2->next;
    node1 = node1->next;
  }
}

// modo 6 - ordme crescente, modo 9 - ordem decrescente
void merge(linkedNode *low, linkedNode *mid, linkedNode *high, int mode){
  /// salvamos o mid para usar como referencia nos lacos
  linkedNode *tmp1 = low, *tmp2 = mid, *aux = NULL;

  while(tmp1 != mid->next && tmp2 != high->next){
    if( (mode == 6) ? tmp1->RA < tmp2->RA :  tmp1->RA > tmp2->RA){
      insertNode(&aux, tmp1->RA, tmp1->grade);
      tmp1 = tmp1->next;
    }
    else{
      insertNode(&aux, tmp2->RA, tmp2->grade);
      tmp2 = tmp2->next;
    }
  }

  while(tmp1 != mid->next){
    insertNode(&aux, tmp1->RA, tmp1->grade);
    tmp1= tmp1->next;
  }
  while(tmp2 != high->next){
    insertNode(&aux, tmp2->RA, tmp2->grade);
    tmp2 = tmp2->next;
  }
  //printList(low);
    //printList(aux);
    //printf("swap\n");
  swapLinkedList(low, aux);
 // printList(low);
 // printList(aux);
  deleteList(aux);
}

// modo 6 - ordme crescente, modo 9 - ordem decrescente
void mergeSort(linkedNode *low, linkedNode *high, int mode){
  int a;
    if((low && high) ? low->index < high->index : 0){
      linkedNode *mid = midNode(low, high);
      mergeSort(low, mid, mode);
      mergeSort(mid->next, high, mode);
      merge(low, mid->next, high, mode);
    }
//    printList(low);
}

int main(){
  int input = 1, RA, grade, mode;
  linkedNode *linkedList = NULL, *high = NULL;

  while(input != 0){
    scanf("\n%d", &input);
    switch (input) {
        case 1:   // Insere novo nodo
          scanf("%d %d", &RA, &grade);
          insertNode(&linkedList, RA, grade);
        break;

        case 2:   // Imprime a lista
          printf("[LISTA]\n");
          printList(linkedList);
        break;

        case 6:   // Lista em ordem crescente de RA
          high=linkedList;
          while(high->next!=NULL){
            high=high->next;
          }
          mergeSort(linkedList, high, 6);
          printList(linkedList);
        break;

        case 9:   // Lista em ordem descrescente de RA
          //for(high = linkedList; high; high = high->next);
          high=linkedList;
          while(high->next!=NULL){
            high=high->next;
          }
          mergeSort(linkedList, high, 9);
          printList(linkedList);
        break;
    }
  }
  deleteList(linkedList);
  return 0;
}
