#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "heap.h"

typedef struct Nodo{
   void* data;
   int priority;
} heapElem;

typedef struct Heap{
  heapElem* heapArray;
  int size;
  int capac;
} Heap;

void* heap_top(Heap* pq){
  if (pq == NULL || pq->size == 0){
    return NULL;
  }
  return pq->heapArray[0].data;
}

void recorrerHeap(Heap* pq, int current){
  if (current == 0){
    return; // El elemento está en la raíz, no hay padre
  }

  int parent=(current-1)/2;
  if (pq->heapArray[current].priority<pq->heapArray[parent].priority){
    heapElem aux=pq->heapArray[current];
    pq->heapArray[current]=pq->heapArray[parent];
    pq->heapArray[parent]=aux;
    recorrerHeap(pq,parent);
  }
}

void heap_push(Heap* pq, void* data, int p){
  if (pq->size==pq->capac){
    pq->capac=(pq->capac*2)+1;
    pq->heapArray=realloc(pq->heapArray,sizeof(heapElem)*pq->capac); 
  }
  pq->heapArray[pq->size].data=data;
  pq->heapArray[pq->size].priority=p;
  recorrerHeap(pq, pq->size);
  pq->size++;
}

void heap_pop(Heap* pq){ 
  pq->heapArray[0]=pq->heapArray[--pq->size];
  int pos=0;
  int left, right, father;
  heapElem aux=pq->heapArray[pos];
  while ((left=(pos*2) + 1) < pq->size) { 
    right=left+1;
    father=left;
    if (right<pq->size && pq->heapArray[right].priority > pq->heapArray[left].priority) {
      father=right;
    }
    if(pq->heapArray[pos].priority >= pq->heapArray[father].priority){
      break;
    }
    pq->heapArray[pos]=pq->heapArray[father];
    pos=father;
  }
  pq->heapArray[pos]=aux;
}

Heap* createHeap(){ 
  Heap* heap = malloc(sizeof(Heap));
  heap->heapArray = malloc(sizeof(heapElem) * 3);
  heap->size = 0;
  heap->capac = 3;
  return heap;
}
