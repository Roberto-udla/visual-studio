#include <stdio.h>
#include <string.h>
#include "funciones.h"

void ingresarProductos(char nombres[MAX][50], float precios[MAX], int cantidad) {
    int i;
    for (i = 0; i < cantidad; i++) {
        printf("Ingrese el nombre del producto %d: ", i + 1);
        fflush(stdin);
        fgets(nombres[i], 50, stdin);

        // Elimina salto de línea
        nombres[i][strcspn(nombres[i], "\n")] = '\0';

        printf("Ingrese el precio del producto %d: ", i + 1);
        scanf("%f", &precios[i]);
        fflush(stdin);
    }
}

float precioTotal(float precios[MAX], int cantidad) {
    float total = 0;
    int i;
    for (i = 0; i < cantidad; i++)
        total += precios[i];
    return total;
}

float precioPromedio(float precios[MAX], int cantidad) {
    if(cantidad == 0) return 0;
    return precioTotal(precios, cantidad) / cantidad;
}

int productoMasCaro(float precios[MAX], int cantidad) {
    int i, pos = 0;
    for (i = 1; i < cantidad; i++)
        if(precios[i] > precios[pos])
            pos = i;
    return pos;
}

int productoMasBarato(float precios[MAX], int cantidad) {
    int i, pos = 0;
    for (i = 1; i < cantidad; i++)
        if(precios[i] < precios[pos])
            pos = i;
    return pos;
}

int buscarProducto(char nombres[MAX][50], float precios[MAX], int cantidad, char buscado[50]) {
    int i;
    for (i = 0; i < cantidad; i++)
        if (strcmp(nombres[i], buscado) == 0)
            return i;
    return -1;
}
#include <stdio.h>
#include <string.h>
#include "funciones.h"

int main() {
    char nombres[MAX][50];
    float precios[MAX];
    int cantidad, opcion;

    printf("¿Cuántos productos desea ingresar? (máx 10): ");
    scanf("%d", &cantidad);
    fflush(stdin);

    if (cantidad > MAX || cantidad <= 0) {
        printf("Cantidad inválida.\n");
        return 0;
    }

    ingresarProductos(nombres, precios, cantidad);

    do {
        printf("\n----- MENU -----\n");
        printf("1. Mostrar precio total del inventario\n");
        printf("2. Mostrar precio promedio\n");
        printf("3. Producto más caro\n");
        printf("4. Producto más barato\n");
        printf("5. Buscar producto por nombre\n");
        printf("6. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        fflush(stdin);

        switch(opcion) {
            case 1:
                printf("Precio total del inventario: $%.2f\n",
                       precioTotal(precios, cantidad));
                break;

            case 2:
                printf("Precio promedio: $%.2f\n",
                       precioPromedio(precios, cantidad));
                break;

            case 3: {
                int pos = productoMasCaro(precios, cantidad);
                printf("Producto más caro: %s - $%.2f\n",
                       nombres[pos], precios[pos]);
            } break;

            case 4: {
                int pos = productoMasBarato(precios, cantidad);
                printf("Producto más barato: %s - $%.2f\n",
                       nombres[pos], precios[pos]);
            } break;

            case 5: {
                char buscar[50];
                printf("Ingrese el nombre a buscar: ");
                fgets(buscar, 50, stdin);
                buscar[strcspn(buscar, "\n")] = '\0';

                int pos = buscarProducto(nombres, precios, cantidad, buscar);
                if (pos >= 0)
                    printf("%s cuesta $%.2f\n", nombres[pos], precios[pos]);
                else
                    printf("Producto no encontrado.\n");
            } break;

            case 6:
                printf("Saliendo...\n");
                break;

            default:
                printf("Opción inválida.\n");
        }

    } while (opcion != 6);

    return 0;
}
