#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "heap.h"
#include "list.h"
#include "Map.h"
//La struct tarea se encarga de guardar el nombre de la tarea y su prioridad.
typedef struct{
  char taskname[100];
  int prioridad; 
  List* prevTask;//Lista de tareas previas.
}tarea;

typedef struct{
  bool taskflag;//Si es True, la tarea se encuentra activa, de lo contrario es False.
  tarea* task;//La tarea en si.
}tipoTareas;

typedef struct{
  int accion;//Si es 0, se agregó una tarea; Si es 1, cambio una tarea y por último, si es 2, se marca como completada la tarea en cuestión.
  tipoTareas* PrimeTask;//Tarea sin ningún cambio
}pilaAcciones;

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
//Función que ordena tareas
void ordenarTareas(Map* tareas) {  
  //Convierte el mapa en un arreglo para facilitar mi vida
  tipoTareas **tareas_array = (tipoTareas **) mapToArray(tareas);
  int tareas_count = sizeMap(tareas);

  //Ordenamiento del arreglo basado en prioridad
  for (int i = 0; i < tareas_count - 1; i++) {
    for (int j = 0; j < tareas_count - i - 1; j++) {
      int prioridad1 = tareas_array[j]->task->prioridad;
      int prioridad2 = tareas_array[j+1]->task->prioridad;

        // PRUEBA: Cambio basado en tareas previas
        if (!is_empty(tareas_array[j]->task->prevTask) &&
          hasKey(tareas, front(tareas_array[j]->task->prevTask)) &&
          ((tipoTareas *)searchMap(tareas, (char *)front(tareas_array[j]->task->prevTask)))->task->prioridad > prioridad1) {
          tipoTareas *temp = tareas_array[j];
          tareas_array[j] = tareas_array[j + 1];
          tareas_array[j + 1] = temp;
        } else if (prioridad1 > prioridad2) {
          tipoTareas *temp = tareas_array[j];
          tareas_array[j] = tareas_array[j+1];
          tareas_array[j+1] = temp;
        }
    }
  }

  for (int i = 0; i < tareas_count; i++) {
    insertMap(tareas, tareas_array[i]->task->taskname, tareas_array[i]);
  }

  //Libera la memoria del arreglo
  free(tareas_array);
}
//Función 1 
void ingresarTarea(Map* tareas, Stack* pila) {
  tipoTareas* trashTask = malloc(sizeof(tipoTareas));
  trashTask->task = malloc(sizeof(tarea));
  trashTask->task->prevTask = createList();
  printf("Ingrese la tarea que desea guardar:\n");
  scanf("%[^\n]s", trashTask->task->taskname);
  getchar();
  confirmarCaracteres(trashTask->task->taskname);
  printf("Ingrese la prioridad de su tarea:\n");
  scanf("%i", &trashTask->task->prioridad);
  getchar();
  trashTask->taskflag = true;
 

  pilaAcciones* auxpila = malloc(sizeof(pilaAcciones));
  auxpila->PrimeTask=malloc(sizeof(tipoTareas));
  auxpila->accion = 0;
  auxpila->PrimeTask = trashTask;
  push(pila, auxpila);
  insertMap(tareas, trashTask->task->taskname, trashTask);

  // Reorndena tareas basadas en prioridad
  ordenarTareas(tareas);
}

void agregarTareaPrevia(List* prevTask, char* tareaPrevia) {
  char *newTarea = malloc(sizeof(char) * (strlen(tareaPrevia) + 1));
  strcpy(newTarea, tareaPrevia);

  // Ingresa la nueva cadena a la siguiente posición en la lista
  pushBack(prevTask, newTarea);
}

//Función 2
void cambioDePreferencia(Map* tareas, Stack* pila){
  //Se crean dos variables basuras una tarea para guardar la prioridad en un futuro swap y una cadena para usar como key de la tarea 2
  if(firstMap(tareas)==NULL){
    printf("No hay tareas ingresadas.\n"); 
    return;
  }
  tarea* trash1=malloc(sizeof(tarea));
  char trash2[100];
  printf("Ingrese el nombre de la tarea precedente:\n");
  scanf("%[^\n]s", trash1->taskname);
  getchar();
  printf("Ingrese el nombre donde agregará la tarea precedente:\n");
  scanf("%[^\n]s", trash2);
  getchar();
  //Se usan las variables basura para encontrar las tareas que se quieren cambiar
  tipoTareas* aux =searchMap(tareas, trash2);
  //se guarda la tarea antes del cambio
  pilaAcciones* auxpila = malloc(sizeof(pilaAcciones));
  auxpila->PrimeTask=malloc(sizeof(tipoTareas));// Allocate memory for the pilaAcciones struct
  auxpila->accion = 1;
  strcpy(auxpila->PrimeTask->task->taskname, trash2);
  auxpila->PrimeTask->taskflag=true;
  auxpila->PrimeTask->task->prioridad= aux->task->prioridad;
  push(pila, auxpila);
//una vez terminado el guardado
  printf("Se estableció correctamente la precedencia.\n");
  pushBack(aux->task->prevTask, trash1->taskname);//colloca la tarea 2 en la lista de tareas prev 1
}
//Función 3
void mostrarTareas(Map* tareas) {
  if(firstMap(tareas)==NULL){
    printf("No hay tareas ingresadas.\n"); 
    return;
  }
  ordenarTareas(tareas);
  printf("Tareas por hacer, ordenadas por prioridad:\n\n");
  // Convert the map to an array and sort it based on priority and previous tasks
  tipoTareas **tareas_array = (tipoTareas **)mapToArray(tareas);
  int tareas_count = sizeMap(tareas);

  for (int i = 0; i < tareas_count - 1; i++) {
    for (int j = 0; j < tareas_count - i - 1; j++) {
      int prioridad1 = tareas_array[j]->task->prioridad;
      int prioridad2 = tareas_array[j + 1]->task->prioridad;

      // Swap the positions of the tasks if the previous task of the first task has a lower priority
      if (!is_empty(tareas_array[j]->task->prevTask) &&
          hasKey(tareas, front(tareas_array[j]->task->prevTask)) &&
          ((tipoTareas *)searchMap(tareas, (char *)front(tareas_array[j]->task->prevTask)))->task->prioridad > prioridad1) {
        tipoTareas *temp = tareas_array[j];
        tareas_array[j] = tareas_array[j + 1];
        tareas_array[j + 1] = temp;
      } else if (prioridad1 > prioridad2) {
        tipoTareas *temp = tareas_array[j];
        tareas_array[j] = tareas_array[j + 1];
        tareas_array[j + 1] = temp;
      }
    }
  }
  int cont=1;
  // Iterate over all the tasks in the sorted array
  for (int i = 0; i < tareas_count; i++) {
    tipoTareas *tarea = tareas_array[i];
    printf(" ");
    printf("%d.", cont);
    printf(" Tarea %s (Prioridad: %d) -", tarea->task->taskname, tarea->task->prioridad);

    // Print the names of the previous tasks, if any
    if (is_empty(tarea->task->prevTask)) {
      printf(" Sin tareas previas\n");
    } else {
      printf(" Tarea: ");
      char *iter = first(tarea->task->prevTask);
      while (iter){
        printf("%s ", iter);
        iter = next(tarea->task->prevTask);
      }
      printf("\n");
    }
    printf("\n");
    cont++;
  }
  free(tareas_array);
}
//Función 4
void EliminarTarea(Map* tareas, Stack* pila){
  
  if(firstMap(tareas)==NULL){
    printf("No hay tareas ingresadas.\n"); 
    return;
  }
  char basura[100];
  printf("Ingrese el nombre de la tarea:\n");
  scanf("%99[^\n]", basura);
  
  tipoTareas* auxTask = malloc(sizeof(tipoTareas));
  auxTask->task = malloc(sizeof(tarea));
  
  auxTask = searchMap(tareas, basura);
  pilaAcciones* auxpila = malloc(sizeof(pilaAcciones));
  auxpila->PrimeTask=malloc(sizeof(tipoTareas));// Allocate memory for the pilaAcciones struct
  auxpila->accion = 2;
  auxpila->PrimeTask = auxTask;
  push(pila, auxpila);
  char aux;
  if(first(auxTask->task->prevTask)!=NULL){
    printf("Esta tarea tiene tareas previas. ¿Estás seguro de marcarla como hecha? s|n\n");
    scanf("%c", &aux);
    if(aux=='n'){
      printf("Está bien, no se marcó ninguna tarea.\n");
    }
    else if(aux=='s'){
      auxTask->taskflag=false;
      eraseMap(tareas, basura);
    }
  }
  else{
    auxTask->taskflag=false;
    eraseMap(tareas, basura);
    printf("La tarea fue completada con éxito.\n");
  }
}

void deletTaskpila(Map* tareas, pilaAcciones* ultAccion){
  eraseMap(tareas, ultAccion->PrimeTask->task->taskname);
}

void deletPrev(Map* tareas, pilaAcciones* ultAccion){
  eraseMap(tareas, ultAccion->PrimeTask->task->taskname);
  insertMap(tareas, ultAccion->PrimeTask->task->taskname, ultAccion->PrimeTask);
}

void deletMarc(Map* tareas, pilaAcciones* ultAccion){
  insertMap(tareas, ultAccion->PrimeTask->task->taskname, ultAccion->PrimeTask);
}


//funcion 5
void EliminarAccion(Map* tareas, Stack* pila){
  if(firstMap(tareas)==NULL){
    printf("No hay tareas ingresadas.\n"); 
    return;
  }
  
  pilaAcciones* ultAccion = ( pilaAcciones*) top(pila);
  printf("Eliminando ultima acción...\n");
  if(ultAccion==NULL){
    printf("Ya no quedan acciones disponibles.\n");
    return;
  }
  switch(ultAccion->accion){
    case 0: deletTaskpila(tareas, ultAccion);
    break; 
          
    case 1: deletPrev(tareas, ultAccion);
    break;
        
    case 2: deletMarc(tareas, ultAccion);
    break;
  }
  pop(pila);
  return;
}


const char *get_csv_field(char *tmp, int k, char separator1, char separator2) {
    static char *line = NULL;
    static int line_size = 0;
    int open_mark = 0;
    char *ret = (char *) malloc(100 * sizeof(char));
    int ini_i = 0, i = 0;
    int j = 0;
    char separator = separator1;
    if (line == NULL) {
        line_size = strlen(tmp);
        line = (char *) malloc((line_size + 1) * sizeof(char));
        strcpy(line, tmp);
    } else if (strcmp(line, tmp) != 0) {
        line_size = strlen(tmp);
        line = (char *) realloc(line, (line_size + 1) * sizeof(char));
        strcpy(line, tmp);
    }
    while (line[i + 1] != '\0') {
        if (line[i] == '\"') {
            open_mark = 1 - open_mark;
            if (open_mark) ini_i = i + 1;
            i++;
            continue;
        }
        if (open_mark || (line[i] != separator1 && line[i] != separator2)) {
            if (k == j) ret[i - ini_i] = line[i];
            i++;
            continue;
        }
        if (line[i] == separator1 || line[i] == separator2) {
            if (k == j) {
                ret[i - ini_i] = 0;
                return ret;
            }
            j++;
            ini_i = i + 1;
            if (line[i] == separator1) {
                separator = separator1;
            } else {
                separator = separator2;
            }
        }
        i++;
    }
    if (k == j) {
        ret[i - ini_i] = 0;
        return ret;
    }
    return NULL;
}
void importarArchivo(Map *tareas, Stack* acciones){
  char archivo[100];
  printf("Ingrese el nombre del archivo que quiere ingresar:\n");
  fflush(stdin);
  scanf("%[^\n]s",archivo);
  getchar();
  FILE *fp=fopen(archivo, "r");
  if(fp==NULL){
    printf("===============================================================\n");
    printf("                   Error al importar archivo...\n");
    printf("     Asegúrese de importar al programa con el mismo nombre\n");
    printf("===============================================================\n");
    return;
  }
  char linea[801];
  fgets(linea,800,fp);
  while(fgets(linea,800,fp)!=NULL){
    tipoTareas *auxTarea=malloc(sizeof(tipoTareas));
    auxTarea->task=malloc(sizeof(tarea));
    int j=0;
    while(get_csv_field(linea, j, ',', '\n')!=NULL){
      char *aux =(char *) get_csv_field(linea, j, ',', '\n');
      if(aux==NULL) break;
      
      if(j==0){
        strcpy(auxTarea->task->taskname,aux);

      }
      if(j==1){
        //Se guardan la prioriidad de la tarea
        auxTarea->task->prioridad=atoi(aux);
      }
      if(j==2){
        //Se le asigna la cantidad de prevtask a la tarea
        auxTarea->task->prevTask=createList();
        if (aux[0] == ' ') pushBack(auxTarea->task->prevTask, aux);
      }
      j++;
      pilaAcciones*auxAccion=malloc(sizeof(pilaAcciones));
      auxAccion->PrimeTask=malloc(sizeof(tarea));
      auxAccion->accion=0;
      auxAccion->PrimeTask=auxTarea;
      //Se guarda la acción en la pila de acciones y se inserta
      push(acciones,auxAccion);
      insertMap(tareas, auxTarea->task->taskname, auxTarea);
    }
  }
  printf("===============================================================\n");
  printf("        La importación de tareaes fue hecha con éxito\n");  
  printf("===============================================================\n");
  fclose(fp);
}

void menu(Map *tareas, Stack* acciones){

  int opcion = 1;
  while(opcion != 0){
    printf("╔════════════════════════════•°🜧°•════════════════════════════╗\n");
    printf("║ Para agregar una tarea, presione 1                          ║\n");
    printf("║ Para establecer precedencia entre dos tareas, presione 2    ║\n");
    printf("║ Si desea ver las tareas activas, presione 3                 ║\n");
    printf("║ Si desea marcar una tarea como completada, presione 4       ║\n");
    printf("║ Para deshacer una acción, presione 5                        ║\n");
    printf("║ Para importar desde un archivo, presione 6                  ║\n");
    printf("║ Si no desea hacer nada más presione 0                       ║\n");
    printf("╚════════════════════════════•°🜥°•════════════════════════════╝\n\n");
    scanf("%d", &opcion);
    getchar();

    switch(opcion){
      case 1: ingresarTarea(tareas, acciones);
      break; 
            
      case 2: cambioDePreferencia(tareas, acciones);
      break;
          
      case 3: mostrarTareas(tareas);
      break;

      case 4: EliminarTarea(tareas, acciones);
      break;
      
      case 5: EliminarAccion(tareas, acciones);
      break;
        
      case 6: importarArchivo(tareas, acciones);
      break;

      case 0:
        break;
    }
  }
}

int main(void) {
  Map* tareas= createMap(is_equal_string);
  Stack* acciones= createStack();
  menu(tareas, acciones);
  return 0;  
}