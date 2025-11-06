#ifndef LIBRERIA_H
#define LIBRERIA_H

#include <stdio.h>

#define LIBROS_CANTIDAD 5

typedef struct {
    int id;
    int stock;
    double precio;
    int vendidos;
    double subtotal;
} Libro;

/* Lectura y validación de entradas. Devuelven 1 si se leyó correctamente, 0 en EOF/error. */
int leer_entero(const char *prompt, int *out);
int leer_entero_no_neg(const char *prompt, int *out);
int leer_double_no_neg(const char *prompt, double *out);

/* Operaciones principales */
void registrar_libros(Libro libros[], int n);
double calcular_subtotales_y_total(Libro libros[], int n);
void imprimir_resultados(const Libro libros[], int n, double total);

#endif /* LIBRERIA_H */
