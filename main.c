#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "heap.h"
#include "list.h"
#include "Map.h"

typedef struct{
  char taskname[100];
  int prioridad; 
}tarea;

typedef struct{
  int accion;//si es 0 se agrego una tarea si es 1 cambio una tarea y si es 2 se marco como completa la tarea
  tarea* pilaTask;//se guarda la tarea
  tarea* pilaTask2;// tarea dos e caso de ser opcion 1
  bool iterruptor;//guarda si de desactiva la tarea o se activa
}pilaAcciones;

typedef struct{
  Stack* actions;
  bool taskflag;
  tarea* task;
  List* prevTasks; 
}tipoTareas;

int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

void confirmarCaracteres(char *cadena){
  if(strlen(cadena)>=30) 
  while(strlen(cadena)>=30){
    printf("Ingrese una tarea con una cantidad de caracteres menor a 30");
    scanf("%s", cadena);
    getchar();
  } 
}

void ingresarTarea(Map* tareas, Heap* ordenPrio){
  tipoTareas* trashTask = malloc(sizeof(tipoTareas));
  trashTask->task = malloc(sizeof(tarea));
  scanf("%s", trashTask->task->taskname);
  getchar();
  confirmarCaracteres(trashTask->task->taskname);
  printf("ingrese la prioridad de su tarea\n");
  scanf("%i", &trashTask->task->prioridad);
  trashTask->taskflag=true;
  
  trashTask->prevTasks=createList();

  trashTask->actions=createStack();
  // pilaAcciones* pila;
  // pila->accion=0;
  // pila->iterruptor=true;
  // pila->pilaTask=trashTask->task;
  // push(trashTask->actions, pila);
  
  insertMap(tareas, trashTask->task->taskname, trashTask);
  heap_push(ordenPrio, trashTask->task->taskname, trashTask->task->prioridad);

}

void menu(Map *tareas, Heap* ordenPrio){

  int opcion = 1;
  while(opcion != 0){
    printf("╔════════════════════════════•°🜧°•════════════════════════════╗\n");
    printf("║ Si desea agregar una alguna tarea presione 1                ║\n");
    printf("║ Si desea cambiar el orden de de dos tareas presione 2       ║\n");
    printf("║ Si desea ver las tareas activas presione 3                  ║\n");
    printf("║ Si desea marcar una tarea como completada presione 4        ║\n");
    printf("║ Si desea volver atras a su ultima accion presione 5         ║\n");
    printf("║ Si desea cargar las tareas a un archivo de texto presione 6 ║\n");
    printf("║ Si no desea hacer nada más presione 0                       ║\n");
    printf("╚════════════════════════════•°🜥°•════════════════════════════╝\n\n");
    
    scanf("%d", &opcion);
    getchar();

    switch(opcion){
      case 1: ingresarTarea(tareas, ordenPrio);
      break; 
            
      // case 2: mostrarJugador(jugadores);
      // break;
          
      // case 3: procesoInsertarItem(jugadores,mapaItems);
      // break;

      // case 4: EliminarItem(jugadores, mapaItems);
      // break;
      
      // case 5: agregarPh(jugadores);
      // break;
        
      // case 6: ItemEspecifico(jugadores,mapaItems);
      // break;

      case 0:
        break;
    }
  }
}

int main(void) {
  Map* tareas= createMap(is_equal_string);
  Heap* ordenPrio=createHeap();
  menu(tareas, ordenPrio);
  return 0;  
}