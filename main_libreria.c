#include "libreria.h"
#include <stdlib.h>

int main(void) {
    Libro libros[LIBROS_CANTIDAD];

    printf("Control de ventas - Librería (registro de %d libros)\n", LIBROS_CANTIDAD);
    registrar_libros(libros, LIBROS_CANTIDAD);

    double total = calcular_subtotales_y_total(libros, LIBROS_CANTIDAD);
    imprimir_resultados(libros, LIBROS_CANTIDAD, total);

    return 0;
}
