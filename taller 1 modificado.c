#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nombre[50];
    int stock;
    float precio;
    float ganancias;
} Producto;

int main() {
    const int N = 5;
    Producto *productos = malloc(N * sizeof *productos);
    if (!productos) {
        fprintf(stderr, "Error: no se pudo reservar memoria.\n");
        return 1;
    }

    printf("\n\t=== REGISTRO DE %d PRODUCTOS ===\n", N);
    for (int i = 0; i < N; ++i) {
        printf("\nProducto %d de %d:\n", i + 1, N);
        printf("Ingrese ID del producto: ");
        scanf("%d", &productos[i].id);
        getchar();

        printf("Ingrese nombre del producto: ");
        fgets(productos[i].nombre, sizeof(productos[i].nombre), stdin);
        productos[i].nombre[strcspn(productos[i].nombre, "\n")] = 0;

        printf("Ingrese cantidad inicial en stock: ");
        scanf("%d", &productos[i].stock);

        printf("Ingrese precio unitario: ");
        scanf("%f", &productos[i].precio);
        productos[i].ganancias = 0.0f;
        getchar();
    }

    int opcion = 0;
    int actual = 0; // índice del producto seleccionado

    do {
        printf("\n\t==============================\n");
        printf("\t       MENU PRINCIPAL        \n");
        printf("\t==============================\n");
        printf("\tProducto actual: %d - %s\n", productos[actual].id, productos[actual].nombre);
        printf("\t1. Vender producto\n");
        printf("\t2. Reabastecer producto\n");
        printf("\t3. Consultar informacion del producto actual\n");
        printf("\t4. Mostrar ganancias del producto actual\n");
        printf("\t5. Mostrar todos los productos\n");
        printf("\t6. Cambiar producto\n");
        printf("\t7. Salir\n");
        printf("\tSeleccione una opcion: ");
        if (scanf("%d", &opcion) != 1) {
            printf("Entrada invalida.\n");
            int c; while ((c = getchar()) != '\n' && c != EOF) ;
            opcion = 0;
            continue;
        }

        printf("\n---------------------------------\n");

        switch(opcion) {
            case 1: {
                int cantidad;
                float descuento;
                printf("Ingrese cantidad a vender: ");
                scanf("%d", &cantidad);

                if (cantidad <= 0) {
                    printf("⚠ Error: cantidad invalida.\n");
                    break;
                }

                if (cantidad > productos[actual].stock) {
                    printf("⚠ Error: stock insuficiente.\n");
                    break;
                }

                printf("Ingrese descuento (%%), 0 si no hay: ");
                scanf("%f", &descuento);
                if (descuento < 0 || descuento > 100) {
                    printf("⚠ Error: descuento invalido.\n");
                    break;
                }

                float precioFinal = (productos[actual].precio - (productos[actual].precio * descuento / 100.0f)) * cantidad;
                productos[actual].stock -= cantidad;
                productos[actual].ganancias += precioFinal;
                printf("✅ Venta realizada.\n");
                printf("Total de esta venta: $%.2f\n", precioFinal);
                break;
            }

            case 2: {
                int cantidad;
                printf("Ingrese cantidad a agregar al stock: ");
                scanf("%d", &cantidad);
                if (cantidad > 0) {
                    productos[actual].stock += cantidad;
                    printf("✅ Stock actualizado: %d\n", productos[actual].stock);
                } else {
                    printf("⚠ Error: cantidad invalida.\n");
                }
                break;
            }

            case 3:
                printf("\n📦 INFORMACION DEL PRODUCTO\n");
                printf("ID: %d\n", productos[actual].id);
                printf("Nombre: %s\n", productos[actual].nombre);
                printf("Stock disponible: %d\n", productos[actual].stock);
                printf("Precio unitario: $%.2f\n", productos[actual].precio);
                break;

            case 4:
                printf("💰 Ganancias acumuladas del producto %d: $%.2f\n", productos[actual].id, productos[actual].ganancias);
                break;

            case 5:
                printf("\n📋 LISTA DE PRODUCTOS\n");
                for (int i = 0; i < N; ++i) {
                    printf("%d) ID:%d Nombre:%s Stock:%d Precio:$%.2f Ganancias:$%.2f\n", i+1, productos[i].id, productos[i].nombre, productos[i].stock, productos[i].precio, productos[i].ganancias);
                }
                break;

            case 6: {
                int sel;
                printf("Seleccione producto (1-%d): ", N);
                scanf("%d", &sel);
                if (sel >= 1 && sel <= N) {
                    actual = sel - 1;
                    printf("Producto cambiado a: %d - %s\n", productos[actual].id, productos[actual].nombre);
                } else {
                    printf("⚠ Seleccion invalida.\n");
                }
                break;
            }

            case 7:
                printf("👋 Saliendo del programa...\n");
                break;

            default:
                printf("⚠ Opcion invalida.\n");
        }

        int c; while ((c = getchar()) != '\n' && c != EOF) ;

    } while(opcion != 7);

    free(productos);
    return 0;
}