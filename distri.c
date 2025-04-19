#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tarea {
    int TareaID;
    char *Descripcion;
    int Duracion;
};

struct Nodo {
    struct Tarea T;
    struct Nodo *Siguiente;
};

typedef struct Nodo Nodo;

Nodo* crearNodo(int id, char* descripcion, int duracion) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->T.TareaID = id;
    nuevo->T.Descripcion = strdup(descripcion);
    nuevo->T.Duracion = duracion;
    nuevo->Siguiente = NULL;
    return nuevo;
}

void agregarNodo(Nodo** lista, Nodo* nuevo) {
    nuevo->Siguiente = *lista;
    *lista = nuevo;
}

void mostrarLista(Nodo* lista, const char* nombreLista) {
    printf("\n%s:\n", nombreLista);
    while (lista != NULL) {
        printf("ID: %d - %s (Duracion: %d)\n", lista->T.TareaID, lista->T.Descripcion, lista->T.Duracion);
        lista = lista->Siguiente;
    }
}

void transferirTarea(Nodo** origen, Nodo** destino, int id) {
    Nodo *actual = *origen, *anterior = NULL;
    while (actual != NULL && actual->T.TareaID != id) {
        anterior = actual;
        actual = actual->Siguiente;
    }
    if (actual == NULL) {
        printf("Tarea con ID %d no encontrada en la lista de pendientes.\n", id);
        return;
    }
    if (anterior == NULL) {
        *origen = actual->Siguiente;
    } else {
        anterior->Siguiente = actual->Siguiente;
    }
    actual->Siguiente = NULL;
    agregarNodo(destino, actual);
    printf("Tarea ID %d transferida a realizadas.\n", id);
}

void buscarPorID(Nodo *pendientes, Nodo *realizadas, int idBuscado) {
    Nodo *actual = pendientes;
    while (actual != NULL) {
        if (actual->T.TareaID == idBuscado) {
            printf("\nTarea encontrada en PENDIENTES:\n");
            printf("ID: %d - %s (Duracion: %d)\n", actual->T.TareaID, actual->T.Descripcion, actual->T.Duracion);
            return;
        }
        actual = actual->Siguiente;
    }
    actual = realizadas;
    while (actual != NULL) {
        if (actual->T.TareaID == idBuscado) {
            printf("\nTarea encontrada en REALIZADAS:\n");
            printf("ID: %d - %s (Duracion: %d)\n", actual->T.TareaID, actual->T.Descripcion, actual->T.Duracion);
            return;
        }
        actual = actual->Siguiente;
    }
    printf("No se encontro ninguna tarea con el ID %d.\n", idBuscado);
}

void buscarPorPalabraClave(Nodo *pendientes, Nodo *realizadas, char *clave) {
    int encontrada = 0;
    Nodo *actual = pendientes;
    printf("\nBuscando en tareas PENDIENTES:\n");
    while (actual != NULL) {
        if (strstr(actual->T.Descripcion, clave) != NULL) {
            printf("ID: %d - %s (Duracion: %d)\n", actual->T.TareaID, actual->T.Descripcion, actual->T.Duracion);
            encontrada = 1;
        }
        actual = actual->Siguiente;
    }
    actual = realizadas;
    printf("\nBuscando en tareas REALIZADAS:\n");
    while (actual != NULL) {
        if (strstr(actual->T.Descripcion, clave) != NULL) {
            printf("ID: %d - %s (Duracion: %d)\n", actual->T.TareaID, actual->T.Descripcion, actual->T.Duracion);
            encontrada = 1;
        }
        actual = actual->Siguiente;
    }
    if (!encontrada) {
        printf("No se encontro ninguna tarea con la palabra clave \"%s\".\n", clave);
    }
}

int main() {
    Nodo *tareasPendientes = NULL;
    Nodo *tareasRealizadas = NULL;
    int idActual = 1000;
    char descripcion[200];
    int duracion;
    char respuesta;

    do {
        printf("\nIngrese descripcion de la tarea: ");
        fgets(descripcion, 200, stdin);
        descripcion[strcspn(descripcion, "\n")] = '\0';

        printf("Ingrese duracion de la tarea: ");
        scanf("%d", &duracion);
        getchar();

        Nodo* nueva = crearNodo(idActual++, descripcion, duracion);
        agregarNodo(&tareasPendientes, nueva);

        printf("Desea ingresar otra tarea? (s/n): ");
        scanf(" %c", &respuesta);
        getchar();

    } while (respuesta == 's' );

    mostrarLista(tareasPendientes, "Tareas Pendientes");

    do {
        printf("\nDesea marcar una tarea como realizada? (s/n): ");
        scanf(" %c", &respuesta);
        getchar();
        if (respuesta == 's' ) {
            int idTransferir;
            printf("Ingrese ID de la tarea a transferir: ");
            scanf("%d", &idTransferir);
            getchar();
            transferirTarea(&tareasPendientes, &tareasRealizadas, idTransferir);
        }
    } while (respuesta == 's' );

    mostrarLista(tareasPendientes, "Tareas Pendientes Actualizadas");
    mostrarLista(tareasRealizadas, "Tareas Realizadas");

    do {
        printf("\nDesea buscar una tarea? (s/n): ");
        scanf(" %c", &respuesta);
        getchar();
        if (respuesta == 's' ) {
            int opcion;
            printf("1. Buscar por ID\n2. Buscar por palabra clave\nSeleccione opcion: ");
            scanf("%d", &opcion);
            getchar();

            if (opcion == 1) {
                int id;
                printf("Ingrese el ID a bucar: ");
                scanf("%d", &id);
                getchar();
                buscarPorID(tareasPendientes, tareasRealizadas, id);
            } else if (opcion == 2) {
                char clave[100];
                printf("Ingrese palabra clave a buscar: ");
                fgets(clave, 100, stdin);
                clave[strcspn(clave, "\n")] = '\0';
                buscarPorPalabraClave(tareasPendientes, tareasRealizadas, clave);
            } else {
                printf("Opcion invalida.\n");
            }
        }
    } while (respuesta == 's');

    return 0;
}
