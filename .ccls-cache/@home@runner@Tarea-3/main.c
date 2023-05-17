 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "heap.h"
#include "list.h"
#include "Map.h"
/*La struct tarea se encarga de guardar el nombre de la tarea y su prioridad.
typedef struct{
  char taskname[100];
  int prioridad; 
}tarea;

typedef struct{
  int accion;//Si es 0, se agregó una tarea; Si es 1, cambio una tarea y si es 2, se marca como completada la tarea en cuestión.
  tarea* pilaTask;//Guarda la Tarea
  tarea* pilaTask2;// tarea dos e caso de ser opcion 1
  bool iterruptor;//guarda si de desactiva la tarea o se activa
}pilaAcciones;

typedef struct{
  Stack* actions;//Guarda las funciones para una futura función.
  bool taskflag;//Si es True, la tarea se encuentra activa, de lo contrario es False.
  tarea* task;//La tarea en si.
  List* prevTasks; //Lista de tareas previas, por prioridad.
}tipoTareas;//La estructura tipoTareas guarda todo lo relacionado a la tarea.
*/
int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

void confirmarCaracteres(char *cadena){
  if(strlen(cadena)>=30) 
  while(strlen(cadena)>=30){
    printf("Ingrese una tarea con una cantidad de caracteres menor a 30");
    scanf("%[^\n]s", cadena);
    getchar();
  } 
}
typedef struct tarea {
  char taskname[100];
  int prioridad;
  struct tarea* precedente;
} tarea;

typedef struct Nodo {
  tarea* dato;
  struct Nodo* siguiente;
} Nodo;

typedef struct List {
  Nodo* inicio;
  int size;
} List;

typedef struct {
  int accion;
  tarea* pilaTask;
  tarea* pilaTask2;
  bool interruptor;
} pilaAcciones;

typedef struct {
  bool taskflag;
  tarea* task;
  List* prevTasks;
  pilaAcciones* actions; // Se agregó el miembro actions de tipo pilaAcciones
} tipoTareas;

//fucion 1 
void ingresarTarea(Map* tareas){
  tipoTareas* trashTask = malloc(sizeof(tipoTareas));
  trashTask->task = malloc(sizeof(tarea));
  printf("Ingrese la tarea que desea guardar:\n");
  scanf("%[^\n]s", trashTask->task->taskname);
  getchar();
  confirmarCaracteres(trashTask->task->taskname);
  printf("Ingrese la prioridad de su tarea:\n");
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
  scanf("%[^\n]s", trash1->taskname);
  getchar();
  printf("ingrese el nombre de la tarea 2\n");
  scanf("%[^\n]s", trash2);
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

//Función 3
// Función para mostrar las tareas pendientes ordenadas por prioridad y precedencia
void mostrarTareasPendientes(tipoTareas* tareas) {
  printf("Tareas por hacer, ordenadas por prioridad y precedencia:\n");

  if (tareas->prevTasks == NULL || tareas->prevTasks->inicio == NULL) {
    printf("No hay tareas pendientes.\n");
    return;
  }

  // Crear un arreglo de tareas pendientes
  tarea** tareasPendientes = malloc(sizeof(tarea*) * tareas->prevTasks->size);

  // Copiar las tareas pendientes a un arreglo
  Nodo* nodo = tareas->prevTasks->inicio;
  int i = 0;
  while (nodo != NULL) {
    tareasPendientes[i] = nodo->dato;
    nodo = nodo->siguiente;
    i++;
  }

  // Ordenar las tareas pendientes por prioridad (usando el algoritmo de selección)
  int j, min_idx;
  for (i = 0; i < tareas->prevTasks->size - 1; i++) {
    min_idx = i;
    for (j = i + 1; j < tareas->prevTasks->size; j++) {
      if (tareasPendientes[j]->prioridad < tareasPendientes[min_idx]->prioridad) {
        min_idx = j;
      }
    }
    tarea* temp = tareasPendientes[min_idx];
    tareasPendientes[min_idx] = tareasPendientes[i];
    tareasPendientes[i] = temp;
  }

  // Mostrar las tareas pendientes y sus precedentes (si los tienen)
  for (i = 0; i < tareas->prevTasks->size; i++) {
    printf("%d. %s (Prioridad: %d)", i + 1, tareasPendientes[i]->taskname, tareasPendientes[i]->prioridad);
    if (tareasPendientes[i]->precedente != NULL) {
      printf(" - Precedente: %s", tareasPendientes[i]->precedente->taskname);
    }
    printf("\n");
  }

  // Liberar memoria
  free(tareasPendientes);
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
          
      case 3: mostrarTareasPendientes(tareas);
      break;

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