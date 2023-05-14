
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "heap.h"
#include "list.h"
#include "Map.h"
//struct tarea se encarga de guardar el nombre de la tarea y su prioridad
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
//la estructura tipo tarea guardatodo lo relacionado a la tarea
typedef struct{
  Stack* actions;//guarda las accioes para la fucion 5
  bool taskflag;//si es true la tarea esta activa en false lo cotrario
  tarea* task;// la tarea en si
  List* prevTasks; //lista de las tareas previas por prio
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
//fucion 1 
void ingresarTarea(Map* tareas){
  tipoTareas* trashTask = malloc(sizeof(tipoTareas));
  trashTask->task = malloc(sizeof(tarea));
  printf("ingrese la tarea que desea guardar\n");
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
  
}

//funcion 2
void cambioDeOrden(Map* tareas){
  //se crean dos variables basuras una tarea para guardar la prioridad en un futuro swap y una cadena para usar como key de la tarea 2
  tarea* trash1=malloc(sizeof(tarea));
  char trash2[100];
  printf("ingrese el nombre de la tarea 1 \n");
  scanf("%s", trash1->taskname);
  getchar();
  printf("ingrese el nombre de la tarea 2\n");
  scanf("%s", trash2);
  getchar();
  // se usan las variables basura para encontrar las tareas que se quieren cambiar
  tipoTareas* aux =searchMap(tareas, trash1->taskname);
  tipoTareas* aux2 =searchMap(tareas, trash2);
  //se verifica si la tarea 1 va antes en ese caso no se realiza swap debido a que la tarea 1 va antes de la tarea 2 caso contrario se hace swap para que asi sea.
  if(aux->task->prioridad<aux2->task->prioridad){
    printf("la tarea *%s* va antes que la tarea *%s* dos por lo que no se realizo cambio\n", trash1->taskname, trash2);
  }
  else{
    trash1->prioridad=aux2->task->prioridad;
    aux2->task->prioridad=aux->task->prioridad;
    aux->task->prioridad=trash1->prioridad;
    insertMap(tareas, aux->task->taskname, aux);
    insertMap(tareas, aux2->task->taskname, aux2);
    printf("se cambio de orden de la tarea %s por la tarea de %s \n", trash1->taskname, trash2);
  }
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
      case 1: ingresarTarea(tareas);
      break; 
            
      case 2: cambioDeOrden(tareas);
      break;
          
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