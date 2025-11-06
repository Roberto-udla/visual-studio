#include "libreria.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* Implementaciones de funciones de lectura con validación estricta */
static int leer_linea(char *buf, size_t size) {
    if (!fgets(buf, (int)size, stdin)) return 0;
    size_t len = strlen(buf);
    if (len > 0 && buf[len-1] == '\n') buf[len-1] = '\0';
    return 1;
}

int leer_entero(const char *prompt, int *out) {
    char buf[128];
    char *endptr;
    long val;
    while (1) {
        printf("%s", prompt);
        if (!leer_linea(buf, sizeof buf)) return 0;
        errno = 0;
        val = strtol(buf, &endptr, 10);
        if (endptr == buf || *endptr != '\0' || errno == ERANGE) {
            printf("  Entrada inválida. Ingrese un número entero válido.\n");
            continue;
        }
        *out = (int)val;
        return 1;
    }
}

int leer_entero_no_neg(const char *prompt, int *out) {
    if (!leer_entero(prompt, out)) return 0;
    while (*out < 0) {
        printf("  El valor debe ser mayor o igual a 0.\n");
        if (!leer_entero(prompt, out)) return 0;
    }
    return 1;
}

int leer_double_no_neg(const char *prompt, double *out) {
    char buf[128];
    char *endptr;
    double val;
    while (1) {
        printf("%s", prompt);
        if (!leer_linea(buf, sizeof buf)) return 0;
        errno = 0;
        val = strtod(buf, &endptr);
        if (endptr == buf || *endptr != '\0' || errno == ERANGE) {
            printf("  Entrada inválida. Ingrese un número (ej: 12.50).\n");
            continue;
        }
        if (val < 0.0) {
            printf("  El valor debe ser mayor o igual a 0.\n");
            continue;
        }
        *out = val;
        return 1;
    }
}

void registrar_libros(Libro libros[], int n) {
    for (int i = 0; i < n; ++i) {
        printf("\n--- Libro %d/%d ---\n", i+1, n);
        if (!leer_entero("ID del libro (entero): ", &libros[i].id)) {
            printf("Lectura cancelada.\n"); exit(1);
        }
        if (!leer_entero_no_neg("Cantidad disponible en stock: ", &libros[i].stock)) {
            printf("Lectura cancelada.\n"); exit(1);
        }
        if (!leer_double_no_neg("Precio unitario: ", &libros[i].precio)) {
            printf("Lectura cancelada.\n"); exit(1);
        }
        if (!leer_entero_no_neg("Cantidad vendida: ", &libros[i].vendidos)) {
            printf("Lectura cancelada.\n"); exit(1);
        }

        /* Validación: cantidad vendida no supere stock */
        if (libros[i].vendidos > libros[i].stock) {
            printf("\nERROR: La cantidad vendida (%d) supera el stock disponible (%d) para el libro ID %d.\n",
                   libros[i].vendidos, libros[i].stock, libros[i].id);
            /* Según requisito 3: finalizar inmediatamente */
            exit(1);
        }

        libros[i].subtotal = 0.0; /* se calculará después */
    }
}

double calcular_subtotales_y_total(Libro libros[], int n) {
    double total = 0.0;
    for (int i = 0; i < n; ++i) {
        libros[i].subtotal = libros[i].precio * (double)libros[i].vendidos;
        total += libros[i].subtotal;
    }
    return total;
}

void imprimir_resultados(const Libro libros[], int n, double total) {
    printf("\n--- Subtotales por libro ---\n");
    for (int i = 0; i < n; ++i) {
        printf("Libro ID %d: Vendidos: %d, Precio unitario: $%.2f, Subtotal: $%.2f\n",
               libros[i].id, libros[i].vendidos, libros[i].precio, libros[i].subtotal);
    }
    printf("\nTotal general recaudado: $%.2f\n", total);
}
/*
  Control de ventas - Librería (5 libros)
  - Para cada libro (5): ID (int), stock (int), precio unitario (double), cantidad vendida (int)
  - Validaciones:
    * Entradas numéricas (scanf devuelve 1)
    * Cantidades >= 0
    * Si cantidad vendida > stock -> mostrar error y finalizar inmediatamente
  - Calcular subtotal por libro (precio * cantidad vendida)
  - Mostrar subtotales y total general al finalizar
*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const int N = 5;
    int id[N];
    int stock[N];
    double precio[N];
    int vendidos[N];
    double subtotal[N];

    printf("Control de ventas - Librería (registrar %d libros)\n\n", N);

    for (int i = 0; i < N; ++i) {
        /* ID */
        printf("Libro %d - Ingrese ID (entero no negativo): ", i + 1);
        while (scanf("%d", &id[i]) != 1 || id[i] < 0) {
            printf("  Entrada inválida. Ingrese un ID entero no negativo: ");
            int c; while ((c = getchar()) != '\n' && c != EOF) { }
        }

        /* Stock */
        printf("  Ingrese cantidad disponible en stock (>= 0): ");
        while (scanf("%d", &stock[i]) != 1 || stock[i] < 0) {
            printf("  Entrada inválida. Ingrese un número entero >= 0 para stock: ");
            int c; while ((c = getchar()) != '\n' && c != EOF) { }
        }

        /* Precio */
        printf("  Ingrese precio unitario (>= 0): ");
        while (scanf("%lf", &precio[i]) != 1 || precio[i] < 0.0) {
            printf("  Entrada inválida. Ingrese un número >= 0 para el precio: ");
            int c; while ((c = getchar()) != '\n' && c != EOF) { }
        }

        /* Vendidos */
        printf("  Ingrese cantidad vendida (>= 0): ");
        while (scanf("%d", &vendidos[i]) != 1 || vendidos[i] < 0) {
            printf("  Entrada inválida. Ingrese un número entero >= 0 para vendidos: ");
            int c; while ((c = getchar()) != '\n' && c != EOF) { }
        }

        /* Validación de stock vs vendidos */
        if (vendidos[i] > stock[i]) {
            printf("\nError: la cantidad vendida (%d) supera el stock disponible (%d) para el libro ID %d.\n",
                   vendidos[i], stock[i], id[i]);
            printf("El programa finalizará inmediatamente.\n");
            return 1;
        }

        subtotal[i] = precio[i] * (double)vendidos[i];
    }

    double total = 0.0;
    printf("\n--- Resumen de ventas ---\n");
    for (int i = 0; i < N; ++i) {
        printf("Libro %d (ID %d): vendidos = %d, precio = $%.2f, subtotal = $%.2f\n",
               i + 1, id[i], vendidos[i], precio[i], subtotal[i]);
        total += subtotal[i];
    }

    printf("\nTotal general recaudado: $%.2f\n", total);

    return 0;
}
