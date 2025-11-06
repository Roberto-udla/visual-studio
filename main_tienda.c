#include <stdio.h>
#include <string.h>
#include "tienda.h"

int main(void) {
    int cantidad = 0;
    printf("Ingrese la cantidad de productos (max %d): ", MAX_PRODUCTOS);
    if (scanf("%d", &cantidad) != 1 || cantidad <= 0 || cantidad > MAX_PRODUCTOS) {
        printf("Cantidad inválida. Debe ser entre 1 y %d.\n", MAX_PRODUCTOS);
        return 1;
    }
    int ch; while ((ch = getchar()) != '\n' && ch != EOF) {}

    char nombres[MAX_PRODUCTOS][NOMBRE_SIZE];
    float precios[MAX_PRODUCTOS] = {0};

    ingresar_datos(nombres, precios, cantidad);

    imprimir_resumen(nombres, precios, cantidad);

    char buscado[NOMBRE_SIZE];
    while (1) {
        printf("\nBuscar producto por nombre (deje vacío para salir): ");
        if (!fgets(buscado, sizeof buscado, stdin)) break;
        size_t len = strlen(buscado);
        if (len > 0 && buscado[len-1] == '\n') buscado[len-1] = '\0';
        if (buscado[0] == '\0') break;
        int pos = buscar_producto(nombres, cantidad, buscado);
        if (pos >= 0) printf("Producto '%s' encontrado en posición %d con precio $%.2f\n", buscado, pos+1, precios[pos]);
        else printf("Producto '%s' no encontrado.\n", buscado);
    }

    return 0;
}
