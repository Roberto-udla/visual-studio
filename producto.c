#include "producto.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* --- Helpers de lectura validados (privados) --- */
static int leer_linea(char *buf, size_t size) {
    if (!fgets(buf, (int)size, stdin)) return 0;
    size_t len = strlen(buf);
    if (len > 0 && buf[len-1] == '\n') buf[len-1] = '\0';
    return 1;
}

static int leer_entero(const char *prompt, int *out) {
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

static int leer_entero_no_neg(const char *prompt, int *out) {
    if (!leer_entero(prompt, out)) return 0;
    while (*out < 0) {
        printf("  El valor debe ser mayor o igual a 0.\n");
        if (!leer_entero(prompt, out)) return 0;
    }
    return 1;
}

static int leer_float_no_neg(const char *prompt, float *out) {
    char buf[128];
    char *endptr;
    float val;
    while (1) {
        printf("%s", prompt);
        if (!leer_linea(buf, sizeof buf)) return 0;
        errno = 0;
        val = strtof(buf, &endptr);
        if (endptr == buf || *endptr != '\0' || errno == ERANGE) {
            printf("  Entrada inválida. Ingrese un número (ej: 12.50).\n");
            continue;
        }
        if (val < 0.0f) {
            printf("  El valor debe ser mayor o igual a 0.\n");
            continue;
        }
        *out = val;
        return 1;
    }
}

/* --- Implementación de la API pública --- */
void producto_registrar(Producto *p) {
    if (!p) return;
    printf("\n\t=== REGISTRO DE PRODUCTO ===\n");

    /* ID */
    if (!leer_entero("Ingrese ID del producto: ", &p->id)) {
        printf("Lectura cancelada.\n"); exit(1);
    }

    /* Nombre */
    printf("Ingrese nombre del producto: ");
    if (!leer_linea(p->nombre, sizeof p->nombre)) { printf("Lectura cancelada.\n"); exit(1); }

    /* Stock */
    if (!leer_entero_no_neg("Ingrese cantidad inicial en stock: ", &p->stock)) {
        printf("Lectura cancelada.\n"); exit(1);
    }

    /* Precio */
    if (!leer_float_no_neg("Ingrese precio unitario: ", &p->precio)) {
        printf("Lectura cancelada.\n"); exit(1);
    }

    p->ganancias_acumuladas = 0.0f;
}

int producto_menu_obtener_opcion(void) {
    int opcion;
    printf("\n\t==============================\n");
    printf("\t         MENU PRINCIPAL       \n");
    printf("\t==============================\n");
    printf("\t1. Vender producto\n");
    printf("\t2. Reabastecer producto\n");
    printf("\t3. Consultar informacion\n");
    printf("\t4. Mostrar ganancias\n");
    printf("\t5. Salir\n");
    if (!leer_entero("\tSeleccione una opcion: ", &opcion)) return 5; /* finalizar en EOF */
    return opcion;
}

void producto_vender(Producto *p) {
    if (!p) return;
    int cantidad;
    if (!leer_entero("Ingrese cantidad a vender: ", &cantidad)) { printf("Lectura cancelada.\n"); return; }

    if (cantidad <= 0) {
        printf("⚠ Error: cantidad invalida.\n");
        return;
    }
    if (cantidad > p->stock) {
        printf("⚠ Error: stock insuficiente.\n");
        return;
    }

    float descuento;
    if (!leer_float_no_neg("Ingrese descuento (%%), 0 si no hay: ", &descuento)) { printf("Lectura cancelada.\n"); return; }
    if (descuento < 0.0f || descuento > 100.0f) {
        printf("⚠ Error: descuento invalido.\n");
        return;
    }

    float precioFinal = (p->precio - (p->precio * descuento / 100.0f)) * (float)cantidad;
    p->stock -= cantidad;
    p->ganancias_acumuladas += precioFinal;
    printf("✅ Venta realizada.\n");
    printf("Total de esta venta: $%.2f\n", precioFinal);
}

void producto_reabastecer(Producto *p) {
    if (!p) return;
    int cantidad;
    if (!leer_entero("Ingrese cantidad a agregar al stock: ", &cantidad)) { printf("Lectura cancelada.\n"); return; }
    if (cantidad > 0) {
        p->stock += cantidad;
        printf("✅ Stock actualizado: %d\n", p->stock);
    } else {
        printf("⚠ Error: cantidad invalida.\n");
    }
}

void producto_consultar(const Producto *p) {
    if (!p) return;
    printf("\n📦 INFORMACION DEL PRODUCTO\n");
    printf("ID: %d\n", p->id);
    printf("Nombre: %s\n", p->nombre);
    printf("Stock disponible: %d\n", p->stock);
    printf("Precio unitario: $%.2f\n", p->precio);
}

void producto_mostrar_ganancias(const Producto *p) {
    if (!p) return;
    printf("💰 Ganancias acumuladas: $%.2f\n", p->ganancias_acumuladas);
}
