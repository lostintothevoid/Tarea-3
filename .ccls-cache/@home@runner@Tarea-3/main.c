#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "heap.h"
#include "list.h"

typedef struct{
  char taskname[100];
  int prioridad;
}tarea;

typedef struct{
  int accion;//si la accion es 1 se elimina la ultima
  tarea* tareaAnterior;//
  bool iterruptor;//guarda si de desactiva la tarea o se activa
}pilaAcciones;

typedef struct{
  Stack* actions;
  bool taskflag;
  tarea* Task; 
}tipoTareas;

void ingresarTarea(List* tarea){
  
}

void menu(List *tareas){

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
  List* tareas= createList();
  menu(tareas);
  return 0;  
}