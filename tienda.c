#include "tienda.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>

/* Lee una línea y elimina el '\n' final si existe */
static void leer_linea_strip(char *buf, int size) {
    if (!fgets(buf, size, stdin)) {
        buf[0] = '\0';
        return;
    }
    size_t len = strlen(buf);
    if (len > 0 && buf[len-1] == '\n') buf[len-1] = '\0';
}

void ingresar_datos(char nombres[][NOMBRE_SIZE], float precios[], int cantidad) {
    for (int i = 0; i < cantidad; ++i) {
        printf("\nProducto %d de %d\n", i+1, cantidad);
        printf("Ingrese nombre: ");
        leer_linea_strip(nombres[i], NOMBRE_SIZE);

        char buf[128];
        while (1) {
            printf("Ingrese precio: ");
            leer_linea_strip(buf, sizeof buf);
            if (buf[0] == '\0') {
                printf("  Entrada inválida. Ingrese un número real (ej: 12.50).\n");
                continue;
            }
            errno = 0;
            char *endptr = NULL;
            float val = strtof(buf, &endptr);
            if (endptr == buf || *endptr != '\0' || errno == ERANGE) {
                printf("  Entrada inválida. Ingrese solo números (ej: 12.50).\n");
                continue;
            }
            if (val < 0.0f) {
                printf("  El precio debe ser mayor o igual a 0.\n");
                continue;
            }
            precios[i] = val;
            break;
        }
    }
}

float calcular_total(const float precios[], int cantidad) {
    float total = 0.0f;
    for (int i = 0; i < cantidad; ++i) total += precios[i];
    return total;
}

float calcular_promedio(const float precios[], int cantidad) {
    if (cantidad <= 0) return 0.0f;
    return calcular_total(precios, cantidad) / cantidad;
}

int producto_mas_caro(const float precios[], int cantidad) {
    if (cantidad <= 0) return -1;
    int idx = 0;
    for (int i = 1; i < cantidad; ++i) if (precios[i] > precios[idx]) idx = i;
    return idx;
}

int producto_mas_barato(const float precios[], int cantidad) {
    if (cantidad <= 0) return -1;
    int idx = 0;
    for (int i = 1; i < cantidad; ++i) if (precios[i] < precios[idx]) idx = i;
    return idx;
}

int buscar_producto(char nombres[][NOMBRE_SIZE], int cantidad, const char buscado[]) {
    for (int i = 0; i < cantidad; ++i) {
        if (strcmp(nombres[i], buscado) == 0) return i;
    }
    return -1;
}

void imprimir_resumen(char nombres[][NOMBRE_SIZE], const float precios[], int cantidad) {
    printf("\n--- Resumen del inventario (%d productos) ---\n", cantidad);
    for (int i = 0; i < cantidad; ++i) {
        printf("%d) %s - $%.2f\n", i+1, nombres[i], precios[i]);
    }
    float total = calcular_total(precios, cantidad);
    float promedio = calcular_promedio(precios, cantidad);
    int idxCaro = producto_mas_caro(precios, cantidad);
    int idxBarato = producto_mas_barato(precios, cantidad);
    printf("\nTotal inventario: $%.2f\n", total);
    printf("Precio promedio: $%.2f\n", promedio);
    if (idxCaro >= 0) printf("Producto más caro: %s ($%.2f)\n", nombres[idxCaro], precios[idxCaro]);
    if (idxBarato >= 0) printf("Producto más barato: %s ($%.2f)\n", nombres[idxBarato], precios[idxBarato]);
}
