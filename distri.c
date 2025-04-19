#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CLIENTES 5
#define MAX_PRODUCTOS 10
#define TIPOS_PRODUCTOS 5

char *TiposProductos[] = {"Galletas", "Snack", "Cigarrillos", "Caramelos", "Bebidas"};


struct Producto {
    int ProductoID;
    int Cantidad; 
    char *TipoProducto; 
    float PrecioUnitario; 
};

struct Cliente {
    int ClienteID; 
    char *NombreCliente; 
    int CantidadProductosAPedir; 
    struct Producto *Productos;
};


int generarNumeroAleatorio(int min, int max) {
    return min + rand() % (max - min + 1);
}


float calcularCostoTotalProducto(struct Producto p) {
    return p.Cantidad * p.PrecioUnitario;
}


void cargarClientes(struct Cliente *clientes, int cantidadClientes) {
    for (int i = 0; i < cantidadClientes; i++) {
        clientes[i].ClienteID = i + 1;

        clientes[i].NombreCliente = (char *)malloc(100 * sizeof(char));
        printf("\nIngrese el nombre del cliente %d: ", clientes[i].ClienteID);
        fgets(clientes[i].NombreCliente, 100, stdin);
        clientes[i].NombreCliente[strcspn(clientes[i].NombreCliente, "\n")] = '\0'; 

        clientes[i].CantidadProductosAPedir = generarNumeroAleatorio(1, 5);
        clientes[i].Productos = (struct Producto *)malloc(clientes[i].CantidadProductosAPedir * sizeof(struct Producto));

        for (int j = 0; j < clientes[i].CantidadProductosAPedir; j++) {
            clientes[i].Productos[j].ProductoID = j + 1;
            clientes[i].Productos[j].Cantidad = generarNumeroAleatorio(1, 10);
            clientes[i].Productos[j].TipoProducto = TiposProductos[generarNumeroAleatorio(0, TIPOS_PRODUCTOS - 1)];
            clientes[i].Productos[j].PrecioUnitario = (float)generarNumeroAleatorio(10, 100);
            printf("\nProducto cargado nro. %d\n", clientes[i].Productos[j].ProductoID);
            printf("ProductoID = %d\n", clientes[i].Productos[j].ProductoID);
            printf("Cantidad = %d\n", clientes[i].Productos[j].Cantidad);
            printf("TipoProducto = %s\n", clientes[i].Productos[j].TipoProducto);
            printf("PrecioUnitario = %.2f\n", clientes[i].Productos[j].PrecioUnitario);
        }
    }
}


void mostrarClientes(struct Cliente *clientes, int cantidadClientes) {
    float totalCliente;
    for (int i = 0; i < cantidadClientes; i++) {
        printf("\nCliente %d: %s\n", clientes[i].ClienteID, clientes[i].NombreCliente);
        totalCliente = 0;
        for (int j = 0; j < clientes[i].CantidadProductosAPedir; j++) {
            float costoProducto = calcularCostoTotalProducto(clientes[i].Productos[j]);
            totalCliente += costoProducto;
            printf("Producto %d: %s\n", clientes[i].Productos[j].ProductoID, clientes[i].Productos[j].TipoProducto);
            printf("Cantidad: %d\n", clientes[i].Productos[j].Cantidad);
            printf("Precio unitario: %.2f\n", clientes[i].Productos[j].PrecioUnitario);
            printf("Costo total: %.2f\n", costoProducto);
        }
        printf("Total a pagar por cliente %d: %.2f\n", clientes[i].ClienteID, totalCliente);
    }
}

int main() {
    srand(time(NULL)); 
    int cantidadClientes;

    printf("Ingrese la cantidad de clientes que desea registrar (máximo %d): ", MAX_CLIENTES);
    scanf("%d", &cantidadClientes);
    getchar();

    if (cantidadClientes > MAX_CLIENTES) {
        cantidadClientes = MAX_CLIENTES;
    }


    struct Cliente *clientes = (struct Cliente *)malloc(cantidadClientes * sizeof(struct Cliente));
    cargarClientes(clientes, cantidadClientes);
    mostrarClientes(clientes, cantidadClientes);


    for (int i = 0; i < cantidadClientes; i++) {
        free(clientes[i].Productos);
        free(clientes[i].NombreCliente);
    }
    free(clientes);

    return 0;
}
