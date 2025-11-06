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
