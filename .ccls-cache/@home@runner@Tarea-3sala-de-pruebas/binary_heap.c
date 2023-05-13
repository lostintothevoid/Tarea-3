#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
  void* data;
  int last_prio;
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

// void print_node(Node* n){
//     int i,j;
//     for(i=0;i<9;i++){
//        for(j=0;j<9;j++)
//           printf("%d ", n->sudo[i][j]);
//        printf("\n");
//     }
//     printf("\n");
// }

// int subMatriz(Node* n){
//   int k,p; 
//   for(k=0; k<9; k++){
//     int a[9]={0};
//     for(p=0;p<9;p++){
//       int i=3*(k/3) + (p/3) ;
//       int j=3*(k%3) + (p%3) ;
//       if(n->sudo[i][j]!=0){
//         if(a[(n->sudo[i][j]-1)]==0){
//           a[(n->sudo[i][j]-1)]=1;
//         }
//         else return 0;
//       }
//     }
//   }
//   return 1;
// }

// int numColum(Node* n){
//   int i, j;
//   for(j=0; j<9; j++){
//     int a[9]={0};
//     for(i=0; i<9; i++){
//       if(n->sudo[i][j]!=0){
//         if(a[(n->sudo[i][j]-1)]==0){
//           a[(n->sudo[i][j]-1)]=1;
//         }
//         else return 0;
//       }
//     }
//   }
//   return 1;
// }

// int numFila(Node* n){
//   int i, j;
//   for(i=0; i<9; i++){
//     int a[9]={0};
//     for(j=0; j<9; j++){
//       if(n->sudo[i][j]!=0){
//         if(a[(n->sudo[i][j]-1)]==0){
//           a[(n->sudo[i][j]-1)]=1;
//         }
//         else return 0;
//       }
//     }
//   }
//   return 1;
// }

// int is_valid(Node* n){
//   if(numFila(n)==1){
//     if(numColum(n)==1){
//       if(subMatriz(n)==1){
//         return 1;
//       }
//       else return 0; 
//     }
//     else return 0; 
//   }
//   else  return 0;

// }


List* get_adj_nodes(Node* n){
  List* list=createList();
  int i, j;
  for(i=0; i<9; i++){
    for(j=0; j<9; j++){
      if(n->sudo[i][j]==0){
        for(int k=1; k<10; k++){
          Node* novo = createNode();
          novo =copy(n);
          novo->sudo[i][j]=k;
          if(is_valid(novo)) pushBack(list, novo);    
        }
        return list;
      }
    }
  }
  return list;
}