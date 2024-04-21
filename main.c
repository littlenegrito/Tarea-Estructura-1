#include "tdas/list.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define MAX 1000 

// MAX = numero de caracteres maximo de la palabra, ajustar manualmente

typedef struct Paciente{
char nombre[MAX];
char sintoma[MAX];
char prioridad[MAX];
unsigned short edad;
int hora;
int min;
}Paciente;

// Función para limpiar la pantalla
void limpiarPantalla() { system("clear"); }

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  while(getchar() != '\n'); // Limpiar el buffer antes de esperar un input 
  getchar(); // Esperar a presionar tecla

}

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión Hospitalaria");
  puts("========================================");

  puts("1) Registrar paciente");
  puts("2) Asignar prioridad a paciente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente paciente");
  puts("5) Mostrar pacientes por prioridad");
  puts("6) Salir");
}

void registrar_paciente(List *colaBajo) {
  printf("Registrar nuevo paciente\n\n");
  Paciente *paciente = (Paciente *)malloc(sizeof(Paciente)); // reservar memoria para el paciente

  // Importar libreria time para obtener hora en tiempo real
  time_t currentTime; 
  struct tm *localTime; 
  currentTime = time(NULL);
  localTime = localtime(&currentTime);

  printf("Ingrese el nombre del paciente: \n");
  scanf(" %[^\n]", paciente->nombre);
  printf("Ingrese la edad del paciente: \n");
  scanf("%hu", &paciente->edad);
  printf("Ingrese el sintoma del paciente: \n");
  scanf(" %[^\n]", paciente->sintoma);

  paciente->hora = (localTime->tm_hour -4); // Ajustar hora a zona horaria 
  paciente->min = localTime->tm_min;
  strcpy(paciente->prioridad, "BAJO"); // Inicializar prioridad en bajo

  list_pushBack(colaBajo, paciente); // Agregar paciente al final de la cola de bajo prioridad
                                    // mantiene orden de llegada del paciente a medida que se agregan mas

}

void asignarPrioridad(List *colaAlto, List *colaMedio, List *colaBajo)
{
  Paciente *paciente = list_first(colaBajo); // crear auxiliar para recorrer la cola
  char prioridad;
  char auxnombre[MAX];

  printf("Ingrese el nombre del paciente: \n");
  scanf(" %[^\n]", auxnombre);
  
  while(paciente !=NULL){ // recorrer la cola hasta encontrar paciente nulo
    if(strcmp(auxnombre, paciente->nombre) == 0){
      printf("Ingrese la prioridad a asignar:\n 1) BAJO\n 2) MEDIO\n 3) ALTO\n");
      scanf(" %c", &prioridad);
      getchar();

      switch (prioridad) { // cambiar de cola a paciente y mostrar mensaje
        case '1':
          strcpy(paciente->prioridad, "BAJO"); // asignar prioridad BAJO
          printf("%s ya se encuentra con prioridad BAJO\n\n", paciente->nombre);
          break;
        case '2':
          strcpy(paciente->prioridad, "MEDIO"); // asignar prioridad MEDIO
          printf("Nueva Prioridad %s: MEDIO\n\n", paciente->nombre);
          break;
        case '3':
          strcpy(paciente->prioridad, "ALTO"); // asignar prioridad ALTO
          printf("Nueva Prioridad %s: ALTO\n\n", paciente->nombre);
          break;
        default:
          printf("Prioridad inválida. Intente nuevamente.\n"); // aviso prioridad invalida
          return;
        }
      if (strcmp(paciente->prioridad, "MEDIO") == 0) { // cambio a cola medio
        list_pushBack(colaMedio, paciente);
        list_popCurrent(colaBajo);
      } else if (strcmp(paciente->prioridad, "ALTO") == 0) { // cambio a cola alto
        list_pushBack(colaAlto, paciente);
        list_popCurrent(colaBajo);
      }
      return;
    }
    paciente = list_next(colaBajo); // seguir con siguiente paciente lista
  }
  printf("El paciente no se encuentra en la lista.\n\n"); // aviso de paciente no encontrado al terminar el ciclo
  return;
}

void mostrarDatos(Paciente *paciente) // funcion mostrar nombre, edad, sintoma, hora y prioridad
{
  printf("Nombre: %s\n", paciente->nombre);
  printf("Edad: %hu\n", paciente->edad);
  printf("Sintoma: %s\n", paciente->sintoma);
  printf("Hora: %02d:%02d\n", paciente->hora, paciente->min);
  printf("Prioridad: %s\n\n", paciente->prioridad);
}

void mostrar_lista_pacientes(List *colaAlto, List *colaMedio, List *colaBajo) {

  Paciente *paciente = list_first(colaAlto);
  if ((list_first(colaAlto) == NULL) && (list_first(colaMedio)== NULL) && (list_first(colaBajo)== NULL)) {
    printf("No hay pacientes en la lista de espera.\n"); // aviso de colas espera vacia
    return;
  }
  printf("Pacientes en espera: \n");
  int contA = 1; // llevar cuenta de pacientes (se empieza con cola Alto)
  int contB = 0; // contador pacientes cola Medio
  int contC = 0; // contador pacientes cola Bajo

  // RECORRER COLA ALTO 
  while(paciente != NULL) {
    printf("Paciente n°%d: %s\n Prioridad: ALTO\n Hora: %02d:%02d\n", contA, paciente->nombre, paciente->hora, paciente->min);
    contA++; 
    paciente = list_next(colaAlto);
  }
  // RECORRER COLA MEDIO 
  paciente = list_first(colaMedio);
  while(paciente != NULL) {
    printf("Paciente n°%d: %s\n Prioridad: MEDIO\n Hora: %02d:%02d\n", contA + contB, paciente->nombre, paciente->hora, paciente->min);
    contB++;
    paciente = list_next(colaMedio);
  }
  // RECORRER COLA BAJO
  paciente = list_first(colaBajo);
  while(paciente != NULL) {
    printf("Paciente n°%d: %s\n Prioridad: BAJO\n Hora: %02d:%02d\n", contA+contB+contC, paciente->nombre, paciente->hora, paciente->min);
    contC++;
    paciente = list_next(colaBajo);
  }
}
void atenderPaciente(List *colaAlto, List *colaMedio, List *colaBajo)
{
    if ((list_first(colaAlto) == NULL) && (list_first(colaMedio)== NULL) && (list_first(colaBajo)== NULL)) {
    printf("No hay pacientes en la lista de espera.\n"); // aviso de cola vacia
    return;
  }
  // MOSTRAR PACIENTE DE LA COLA ALTO MIENTRAS NO ESTÉ VACÍA
  if(list_first(colaAlto) != NULL) {
    Paciente *paciente = list_first(colaAlto);
    printf("Atendiendo a paciente :\n");
    mostrarDatos(paciente);
    list_popFront(colaAlto); // eliminar paciente de la cola para atender al siguiente
    return;
  }
  // MOSTRAR PACIENTE DE LA COLA MEDIO MIENTRAS ALTO ESTÉ VACÍA Y MEDIO NO VACÍA
  if((list_first(colaMedio) != NULL) && (list_first(colaAlto) == NULL)){
    Paciente *paciente = list_first(colaMedio);
    printf("Atendiendo a paciente :\n");
    mostrarDatos(paciente);
    list_popFront(colaMedio); // eliminar paciente de la cola para atender al siguiente
    return;
  }
  // MOSTRAR PACIENTE DE LA COLA BAJO MIENTRAS ALTO Y MEDIO ESTÉN VACÍA Y BAJO NO VACÍA
  if((list_first(colaBajo) != NULL) && (list_first(colaAlto) == NULL) && (list_first(colaMedio) == NULL)){
    Paciente *paciente = list_first(colaBajo);
    printf("Atendiendo a paciente :\n");
    mostrarDatos(paciente);
    list_popFront(colaBajo); // eliminar paciente de la cola para atender al siguiente
    return;
  }
}

void mostrarPrioridad(List *colaAlto, List *colaMedio, List *colaBajo)
{
  char prioridad;
  printf("Ingrese la prioridad a mostrar:\n 1) BAJO\n 2) MEDIO\n 3) ALTO\n");
  scanf(" %c", &prioridad);
  int cont = 1; // llevar cuenta de pacientes

  Paciente *paciente = list_first(colaAlto);
  switch (prioridad) { // para cada caso, mostrar pacientes de la cola correspondiente
    case '3':
      if(paciente ==NULL)printf("No hay pacientes con prioridad ALTO.\n"); // aviso de cola vacia
      while(paciente != NULL) { // mientras cola no esté vacía
        printf("Paciente n°%d: %s\n Hora: %02d:%02d\n", cont, paciente->nombre, paciente->hora, paciente->min);
        cont++;
        paciente = list_next(colaAlto); // avanzar cola
      }
      break;

    case '2':
      paciente = list_first(colaMedio);
      if(paciente ==NULL)printf("No hay pacientes con prioridad MEDIO.\n"); // aviso de cola vacia
      while(paciente != NULL) { // mientras cola no esté vacía
        printf("Paciente n°%d: %s\n Hora: %02d:%02d\n", cont, paciente->nombre, paciente->hora, paciente->min);
        cont++;
        paciente = list_next(colaMedio); // avanzar cola
      }
      break;

    case '1':
      paciente = list_first(colaBajo);
      if(paciente ==NULL)printf("No hay pacientes con prioridad Bajo.\n"); // aviso de cola vacia
      while(paciente != NULL) { // mientras cola no esté vacía
        printf("Paciente n°%d: %s\n Hora: %02d:%02d\n", cont, paciente->nombre, paciente->hora, paciente->min);
        cont++;
        paciente = list_next(colaBajo); // avanzar cola
      }
      break;
    default:
      printf("Prioridad inválida. Intente nuevamente.\n"); // cualquier otro caso
  }
  return;
}

int main() {

  char opcion;
  List *colaAlto = list_create();
  List *colaMedio = list_create();
  List *colaBajo = list_create(); // usar lista para simular cola de espera

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // consumir el newline anterior

    switch (opcion) {
    case '1':
      registrar_paciente(colaBajo);
      break;
    case '2':
      asignarPrioridad(colaAlto, colaMedio, colaBajo);
      break;
    case '3':
      mostrar_lista_pacientes(colaAlto, colaMedio, colaBajo);
      break;
    case '4':
      atenderPaciente(colaAlto, colaMedio, colaBajo);
      break;
    case '5':
      mostrarPrioridad(colaAlto, colaMedio, colaBajo);
      break;
    case '6':
      puts("Saliendo del sistema de gestión hospitalaria...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  // Liberar recursos, si es necesario
  list_clean(colaBajo);
  list_clean(colaMedio);
  list_clean(colaAlto);

  return 0;
}
