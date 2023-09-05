// bibliotecas 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

// Definiciones de constantes
#define MAX_TITULO 51
#define MAX_AUTOR 51
#define MAX_GENERO 21
#define MAX_UBICACION 4
#define MAX_ESTADO 21
#define MAX_NOMBRE_ARCHIVO 101

// Estructura de Nodo
typedef struct Node {
    void *data;
    struct Node *prev;
    struct Node *next;
} Node;

// Estructura de Lista
typedef struct List {
    Node *head;
    Node *tail;
    Node *current;
} List;

// Estructura de Reserva
typedef struct Reserva {
    char nombreUsuario[MAX_TITULO];
    struct Reserva *siguiente;
} Reserva;

// Estructura de Libro
typedef struct Libro {
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    char genero[MAX_GENERO];
    int isbn;
    char ubicacion[MAX_UBICACION];
    char estado[MAX_ESTADO];
    Reserva *reservas;
} Libro;

Node *crearNode(void *data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    assert(newNode != NULL);
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

Reserva *crearReserva(const char *nombreUsuario) {
    Reserva *newReserva = (Reserva *)malloc(sizeof(Reserva));
    assert(newReserva != NULL);
    strcpy(newReserva->nombreUsuario, nombreUsuario);
    newReserva->siguiente = NULL;
    return newReserva;
}

List *createList() {
    List *newList = (List *)malloc(sizeof(List));
    assert(newList != NULL);
    newList->head = newList->tail = newList->current = NULL;
    return newList;
}

void *firstList(List *list) {
    if (list == NULL || list->head == NULL) return NULL;
    list->current = list->head;
    return list->current->data;
}

void *nextList(List *list) {
    if (list == NULL || list->head == NULL || list->current == NULL || list->current->next == NULL) return NULL;
    list->current = list->current->next;
    return list->current->data;
}

void *lastList(List *list) {
    if (list == NULL || list->head == NULL) return NULL;
    list->current = list->tail;
    return list->current->data;
}

void *prevList(List *list) {
    if (list == NULL || list->head == NULL || list->current == NULL || list->current->prev == NULL) return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List *list, void *data) {
    assert(list != NULL);

    Node *newNode = crearNode(data);

    if (list->head == NULL) {
        list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head->prev = newNode;
    }

    list->head = newNode;
}

void pushCurrent(List *list, void *data) {
    assert(list != NULL && list->current != NULL);
    Node *newNode = crearNode(data);

    if (list->current->next != NULL) {
        newNode->next = list->current->next;
        list->current->next->prev = newNode;
    }

    newNode->prev = list->current;
    list->current->next = newNode;

    if (list->current == list->tail) {
        list->tail = newNode;
    }
}

void pushBack(List *list, void *data) {
    if (list->tail == NULL) {
        pushFront(list, data);
    } else {
        list->current = list->tail;
        pushCurrent(list, data);
    }
}

// Declaración de la función popCurrent
Libro *popCurrent(List *list);

void *popFront(List *list) {
    if (list == NULL || list->head == NULL) return NULL;
    list->current = list->head;
    return popCurrent(list);
}

void *popBack(List *list) {
    if (list == NULL || list->tail == NULL) return NULL;
    list->current = list->tail;
    return popCurrent(list);
}

Libro *popCurrent(List *list) {
    assert(list != NULL && list->current != NULL);

    Node *nodeToDelete = list->current;
    Libro *data = (Libro *)nodeToDelete->data;

    if (nodeToDelete->prev != NULL) {
        nodeToDelete->prev->next = nodeToDelete->next;
    } else {
        list->head = nodeToDelete->next;
    }

    if (nodeToDelete->next != NULL) {
        nodeToDelete->next->prev = nodeToDelete->prev;
    } else {
        list->tail = nodeToDelete->prev;
    }

    if (list->current == nodeToDelete) {
        list->current = nodeToDelete->prev;
    }
    free(nodeToDelete);

    return data;
}

void cleanList(List *list) {
    if (list == NULL || list->head == NULL) return;
    while (popFront(list) != NULL);
}

void mostrarReservas(Reserva *reservas) {
    printf("Reservas: ");
    while (reservas != NULL) {
        printf("%s ", reservas->nombreUsuario);
        reservas = reservas->siguiente;
    }
    printf("\n");
}

void registrarLibro(List *biblioteca) {
    assert(biblioteca != NULL);

    Libro *newLibro = (Libro *)malloc(sizeof(Libro));
    assert(newLibro != NULL);

    printf("Ingrese el título del libro: ");
    scanf("%s", newLibro->titulo);
    printf("Ingrese el autor del libro: ");
    scanf("%s", newLibro->autor);
    printf("Ingrese el género del libro: ");
    scanf("%s", newLibro->genero);
    printf("Ingrese el ISBN del libro: ");
    scanf("%d", &newLibro->isbn);
    printf("Ingrese la ubicación del libro: ");
    scanf("%s", newLibro->ubicacion);
  
    // Inicializar la lista de reservas del libro
    newLibro->reservas = NULL;

    //Utilizar pushBack para agregar el nuevo libro a la biblioteca
    pushBack(biblioteca, newLibro);
}

void mostrarDatosLibro(List *biblioteca, const char *titulo, const char *autor) {
    assert(biblioteca != NULL && titulo != NULL && autor != NULL);

    firstList(biblioteca);

    while (biblioteca->current != NULL) {
        Libro *libro = (Libro *)(biblioteca->current->data);
        if (strcmp(libro->titulo, titulo) == 0 && strcmp(libro->autor, autor) == 0) {
            printf("Título: %s\n", libro->titulo);
            printf("Autor: %s\n", libro->autor);
            printf("Género: %s\n", libro->genero);
            printf("ISBN: %d\n", libro->isbn);
            printf("Ubicación: %s\n", libro->ubicacion);
            printf("Estado: %s\n", libro->estado);
            mostrarReservas(libro->reservas);
            return;
        }
        nextList(biblioteca);
    }

    printf("Libro no encontrado.\n");
}

void mostrarAllLibros(List *biblioteca) {
    assert(biblioteca != NULL);

    // Inicializar current al principio de la lista
    firstList(biblioteca);

    while (biblioteca->current != NULL) {
        Libro *libro = (Libro *)(biblioteca->current->data);
        printf("Título: %s\n", libro->titulo);
        printf("Autor: %s\n", libro->autor);
        printf("Género: %s\n", libro->genero);
        printf("ISBN: %d\n", libro->isbn);
        printf("Ubicación: %s\n", libro->ubicacion);
        printf("Estado: %s\n", libro->estado);
        mostrarReservas(libro->reservas);
        printf("\n");

        // Avanzar al siguiente libro
        if (nextList(biblioteca) == NULL) {
            break;  // terminar bucle si no hay más libros
        }
    }
}

void reservarLibro(List *biblioteca, const char *titulo, const char *autor, const char *nombre_estudiante) {
    assert(biblioteca != NULL && titulo != NULL && autor != NULL && nombre_estudiante != NULL);

    firstList(biblioteca);

    while (biblioteca->current != NULL) {
        Libro *libro = (Libro *)(biblioteca->current->data);
        if (strcmp(libro->titulo, titulo) == 0 && strcmp(libro->autor, autor) == 0) {
            Reserva *newReserva = crearReserva(nombre_estudiante);

            // Agregar reserva a la lista de reservas del libro
            if (libro->reservas == NULL) {
                libro->reservas = newReserva;
            } else {
                Reserva *ultimaReserva = libro->reservas;
                while (ultimaReserva->siguiente != NULL) {
                    ultimaReserva = ultimaReserva->siguiente;
                }
                ultimaReserva->siguiente = newReserva;
            }

            printf("Libro \"%s\" reservado por %s\n", libro->titulo, nombre_estudiante);
            return;
        }
        nextList(biblioteca);
    }

    printf("Libro no encontrado o ya reservado.\n");
}

void cancelarReserva(List *biblioteca, const char *titulo, const char *autor, const char *nombre_estudiante) {
    assert(biblioteca != NULL && titulo != NULL && autor != NULL && nombre_estudiante != NULL);

    firstList(biblioteca);

    while (biblioteca->current != NULL) {
        Libro *libro = (Libro *)(biblioteca->current->data);
        if (strcmp(libro->titulo, titulo) == 0 && strcmp(libro->autor, autor) == 0) {
            Reserva *anterior = NULL;
            Reserva *actual = libro->reservas;

            while (actual != NULL) {
                if (strcmp(actual->nombreUsuario, nombre_estudiante) == 0) {
                    // Encontró la reserva del estudiante
                    if (anterior != NULL) {
                        anterior->siguiente = actual->siguiente;
                    } else {
                        libro->reservas = actual->siguiente;
                    }

                    free(actual);
                    printf("Reserva cancelada para \"%s\" por %s\n", libro->titulo, nombre_estudiante);
                    return;
                }

                anterior = actual;
                actual = actual->siguiente;
            }

            printf("Reserva no encontrada para %s\n", nombre_estudiante);
            return;
        }
        nextList(biblioteca);
    }

    printf("Libro no encontrado.\n");
}

void retirarLibro(List *biblioteca, const char *titulo, const char *autor, const char *nombre_estudiante) {
    assert(biblioteca != NULL && titulo != NULL && autor != NULL && nombre_estudiante != NULL);

    firstList(biblioteca);

    while (biblioteca->current != NULL) {
        Libro *libro = (Libro *)(biblioteca->current->data);
        if (strcmp(libro->titulo, titulo) == 0 && strcmp(libro->autor, autor) == 0) {
            // Verificar si el libro tiene reservas
            if (libro->reservas != NULL) {
                Reserva *reserva = libro->reservas;

                // Verificar si el estudiante tiene una reserva
                if (strcmp(reserva->nombreUsuario, nombre_estudiante) == 0) {
                    // El estudiante tiene reserva!, retirar el libro
                    free(reserva);
                    libro->reservas = NULL;
                    printf("Libro \"%s\" retirado por %s\n", libro->titulo, nombre_estudiante);
                    return;
                }
            }

            printf("Reserva no encontrada para %s o el libro no tiene reservas.\n", nombre_estudiante);
            return;
        }
        nextList(biblioteca);
    }

    printf("Libro no encontrado.\n");
}

void devolverLibro(List *biblioteca, const char *titulo, const char *autor) {
    assert(biblioteca != NULL && titulo != NULL && autor != NULL);

    firstList(biblioteca);

    while (biblioteca->current != NULL) {
        Libro *libro = (Libro *)(biblioteca->current->data);
        if (strcmp(libro->titulo, titulo) == 0 && strcmp(libro->autor, autor) == 0) {
            // Verificar si el libro tiene reservas
            if (libro->reservas != NULL) {
                // Eliminar la primera reserva (el estudiante que retiró el libro)
                Reserva *reserva = libro->reservas;
                libro->reservas = reserva->siguiente;
                free(reserva);
                printf("Libro \"%s\" devuelto con éxito.\n", libro->titulo);
                return;
            } else {
                printf("El libro \"%s\" no tiene reservas.\n", libro->titulo);
                return;
            }
        }
        nextList(biblioteca);
    }

    printf("Libro no encontrado.\n");
}

void mostrarPrestados(List *biblioteca) {
    assert(biblioteca != NULL);

    printf("Libros prestados:\n");

    firstList(biblioteca);

    while (biblioteca->current != NULL) {
        Libro *libro = (Libro *)(biblioteca->current->data);
        if (libro->reservas != NULL) {
            printf("Título: %s, Autor: %s\n", libro->titulo, libro->autor);
        }
        nextList(biblioteca);
    }
}

void subirCSV(List *biblioteca, const char *nombre_archivo_csv) {
    assert(biblioteca != NULL && nombre_archivo_csv != NULL);

    FILE *archivo = fopen(nombre_archivo_csv, "r"); // Abre el archivo CSV para lectura

    if (archivo == NULL) {
        printf("Error al abrir el archivo CSV.\n");
        return;
    }

    char linea[256];
    while (fgets(linea, sizeof(linea), archivo)) {
        // Divide la línea en campos usando la coma como delimitador
        char *titulo = strtok(linea, ",");
        char *autor = strtok(NULL, ",");
        char *genero = strtok(NULL, ",");
        char *isbn_str = strtok(NULL, ",");
        char *ubicacion = strtok(NULL, ",");
        char *estado = strtok(NULL, "\n");

        if (titulo && autor && genero && isbn_str && ubicacion && estado) {
            // Convierte el ISBN de cadena a entero
            int isbn = atoi(isbn_str);

            // Crea un nuevo libro con los datos del archivo CSV
            Libro *newLibro = (Libro *)malloc(sizeof(Libro));
            assert(newLibro != NULL);

            strcpy(newLibro->titulo, titulo);
            strcpy(newLibro->autor, autor);
            strcpy(newLibro->genero, genero);
            newLibro->isbn = isbn;
            strcpy(newLibro->ubicacion, ubicacion);
            strcpy(newLibro->estado, estado);
            newLibro->reservas = NULL;

            // Agrega el nuevo libro a la biblioteca
            pushBack(biblioteca, newLibro);
        }
    }

    fclose(archivo);
    printf("Datos cargados desde el archivo CSV con éxito.\n");
}

void exportarCSV(List *biblioteca, const char *nombre_archivo_exportar) {
    assert(biblioteca != NULL && nombre_archivo_exportar != NULL);

    FILE *archivo = fopen(nombre_archivo_exportar, "w"); // Abre el archivo CSV para escritura

    if (archivo == NULL) {
        printf("Error al abrir el archivo CSV para exportar.\n");
        return;
    }

    // Recorre la biblioteca y escribe los datos en el archivo CSV
    firstList(biblioteca);

    while (biblioteca->current != NULL) {
        Libro *libro = (Libro *)(biblioteca->current->data);

        fprintf(archivo, "%s,%s,%s,%d,%s,%s\n",
                libro->titulo, libro->autor, libro->genero, libro->isbn, libro->ubicacion, libro->estado);

        nextList(biblioteca);
    }

    fclose(archivo);
    printf("Datos exportados al archivo CSV con éxito.\n");
}

int main() {
    List *biblioteca = createList();

    int option;
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    char nombre_estudiante[MAX_TITULO];
    char nombre_archivo[MAX_NOMBRE_ARCHIVO];

    do {
        // Menu interactivo
        printf("\nMenú:\n");
        printf("** Seleccione una opción (1-10) **\n");
        printf("** Seleccione 0 para terminar el programa **\n");
        printf("1. Registrar libro\n");
        printf("2. Mostrar datos de un libro\n");
        printf("3. Mostrar todos los libros\n");
        printf("4. Reservar libro\n");
        printf("5. Cancelar reserva\n");
        printf("6. Retirar libro\n");
        printf("7. Devolver libro\n");
        printf("8. Mostrar libros prestados\n");
        printf("9. Subir datos desde archivo CSV\n");
        printf("10. Exportar datos a archivo CSV\n");
        printf("0. Salir\n");
        
        scanf("%d", &option);
        printf("Seleccionó la opción N°%d\n", option);

        switch (option) {
            case 1:
                registrarLibro(biblioteca);
                break;
            case 2:
                printf("Ingrese el título del libro: ");
                scanf("%s", titulo);
                printf("Ingrese el autor del libro: ");
                scanf("%s", autor);
                mostrarDatosLibro(biblioteca, titulo, autor);
                break;
            case 3:
                mostrarAllLibros(biblioteca);
                break;
            case 4:
                printf("Ingrese el título del libro: ");
                scanf("%s", titulo);
                printf("Ingrese el autor del libro: ");
                scanf("%s", autor);
                printf("Ingrese su nombre: ");
                scanf("%s", nombre_estudiante);
                reservarLibro(biblioteca, titulo, autor, nombre_estudiante);
                break;
            case 5:
                printf("Ingrese el título del libro: ");
                scanf("%s", titulo);
                printf("Ingrese el autor del libro: ");
                scanf("%s", autor);
                printf("Ingrese su nombre: ");
                scanf("%s", nombre_estudiante);
                cancelarReserva(biblioteca, titulo, autor, nombre_estudiante);
                break;
            case 6:
                printf("Ingrese el título del libro: ");
                scanf("%s", titulo);
                printf("Ingrese el autor del libro: ");
                scanf("%s", autor);
                printf("Ingrese su nombre: ");
                scanf("%s", nombre_estudiante);
                retirarLibro(biblioteca, titulo, autor, nombre_estudiante);
                break;
            case 7:
                printf("Ingrese el título del libro: ");
                scanf("%s", titulo);
                printf("Ingrese el autor del libro: ");
                scanf("%s", autor);
                devolverLibro(biblioteca, titulo, autor);
                break;
            case 8:
                mostrarPrestados(biblioteca);
                break;
            case 9:
                printf("Ingrese el nombre del archivo CSV: ");
                scanf("%s", nombre_archivo);
                subirCSV(biblioteca, nombre_archivo);
                break;
            case 10:
                printf("Ingrese el nombre del archivo para exportar: ");
                scanf("%s", nombre_archivo);
                exportarCSV(biblioteca, nombre_archivo);
                break;
            case 0:
                // Salir del programa
                break;
            default:
                printf("Opción no válida. Por favor, ingrese una opción válida.\n");
                break;
        }
    } while (option != 0);

    // limpiar lista y liberar memoria
    cleanList(biblioteca);
    free(biblioteca);

    return 0;
}
