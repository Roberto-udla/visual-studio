//Examen Progreso 1
//Roberto Cordero
//24-10-2025


#include <stdio.h>
#include <stdlib.h>
// aqui todo lo que controla las variables y la logica del programa
int main(void) {
    //la cantidad de libros a registrar
    const int N = 5;
    int id[N];
    int stock[N];
    double precio[N];
    int vendidos[N];
    //para los valores de subtotal
    double subtotal[N];

     printf("Control de ventas - Libreria (registrar %d libros)\n\n", N);

    for (int i = 0; i < N; ++i) {
        // para leer el ID del libro
        printf("Libro %d - Ingrese ID: ", i + 1);
        while (scanf("%d", &id[i]) != 1 || id[i] < 0) {
            printf("  Entrada invalida. Ingrese un ID valido: ");
            int c; while ((c = getchar()) != '\n' && c != EOF) { }

            }

        // para leer el Stock 
        printf("  Ingrese cantidad disponible en stock (>= 0): ");
        while (scanf("%d", &stock[i]) != 1 || stock[i] < 0) {
            printf("  Entrada invalida. Ingrese un numero entero >= 0 para stock: ");
            int c; while ((c = getchar()) != '\n' && c != EOF) { }
        }
        //getchar es para registrar el numero ingresado
        // para leer el Precio del libro
        printf("  Ingrese precio unitario (>= 0): ");
        while (scanf("%lf", &precio[i]) != 1 || precio[i] < 0.0) {
            printf("  Entrada invalida. Ingrese un numero >= 0 para el precio: ");
            int c; while ((c = getchar()) != '\n' && c != EOF) { }
        }

        // para leer la cantidad vendida
        printf("  Ingrese cantidad vendida (>= 0): ");
        while (scanf("%d", &vendidos[i]) != 1 || vendidos[i] < 0) {
            printf("  Entrada invalida. Ingrese un numero entero >= 0 para vendidos: ");
            int c; while ((c = getchar()) != '\n' && c != EOF) { }
        }

        // comprueba la cantidad de stock y lo que se vendió y si no se aplican los valores correctos se finaliza el programa
        if (vendidos[i] > stock[i]) {
            printf("\nError: la cantidad vendida (%d) supera el stock disponible (%d) para el libro ID %d.\n",
                   vendidos[i], stock[i], id[i]);
            printf("Hasta luego.\n");
            return 1;
        }

        subtotal[i] = precio[i] * (double)vendidos[i];
    }
// aqui muestro la cantidad total vendida y el subtotal por libro
 double total = 0.0;
    printf("\n--- Resumen de ventas ---\n");
    for (int i = 0; i < N; ++i) {
        printf("Libro ID %d: %d vendidos, subtotal: %.2f\n",
               id[i], vendidos[i], subtotal[i]);
        total += subtotal[i];
    }
    printf("Total de ventas: %.2f\n", total);
    return 0;
}
