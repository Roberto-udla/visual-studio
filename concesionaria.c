#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARCHIVO_VEHICULOS "vehiculos.dat"
#define ARCHIVO_VENTAS "ventas.dat"
#define PRESUPUESTO_RUBEN 14000

typedef struct {
    int id;
    char tipo[20];
    char marca[20];
    char modelo[20];
    int anio;
    float precio;
    int estado;        // 1 = nuevo, 0 = usado
    int disponible;    // 1 = disponible, 0 = vendido
} Vehiculo;

typedef struct {
    char cliente[50];
    int edad;
    int idVehiculo;
    float precioVenta;
} Venta;

/*--------------------------------------------------*/
/* VALIDACIÓN 1: Entrada de datos */
void agregarVehiculo() {
    FILE *f = fopen(ARCHIVO_VEHICULOS, "ab");
    Vehiculo v;

    if (f == NULL) {
        printf("Error al abrir archivo de vehiculos.\n");
        return;
    }

    printf("ID del vehiculo: ");
    scanf("%d", &v.id);

    printf("Tipo (camioneta/auto): ");
    scanf("%19s", v.tipo);

    printf("Marca: ");
    scanf("%19s", v.marca);

    printf("Modelo: ");
    scanf("%19s", v.modelo);

    printf("Anio: ");
    scanf("%d", &v.anio);

    printf("Precio: ");
    scanf("%f", &v.precio);

    printf("Estado:\n1. Nuevo\n0. Usado\nSeleccione: ");
    scanf("%d", &v.estado);

    v.disponible = 1;

    fwrite(&v, sizeof(Vehiculo), 1, f);
    fclose(f);

    printf("Vehiculo registrado correctamente.\n");
}

/*--------------------------------------------------*/
/* VALIDACIÓN 2 y 3: Búsqueda de preferencias */
int buscarVehiculosPreferencia() {
    FILE *f = fopen(ARCHIVO_VEHICULOS, "rb");
    Vehiculo v;
    int encontrado = 0;

    if (f == NULL) {
        printf("No existe inventario.\n");
        return 0;
    }

    printf("\n--- RESULTADOS PARA RUBEN ---\n");
    printf("Camionetas Chevrolet usadas bajo $%.2f\n\n", (float)PRESUPUESTO_RUBEN);

    while (fread(&v, sizeof(Vehiculo), 1, f)) {
        if (strcmp(v.tipo, "camioneta") == 0 &&
            strcmp(v.marca, "Chevrolet") == 0 &&
            v.estado == 0 &&
            v.precio <= PRESUPUESTO_RUBEN &&
            v.disponible == 1) {

            printf("ID: %d | Modelo: %s | Anio: %d | Precio: %.2f\n",
                   v.id, v.modelo, v.anio, v.precio);
            encontrado = 1;
        }
    }

    if (!encontrado)
        printf("No se encontraron vehiculos que cumplan las preferencias.\n");

    fclose(f);
    return encontrado;
}

/*--------------------------------------------------*/
/* VALIDACIÓN 4: Registro de venta */
void registrarVenta() {
    FILE *fv = fopen(ARCHIVO_VENTAS, "ab");
    FILE *fi = fopen(ARCHIVO_VEHICULOS, "rb+");

    Venta venta;
    Vehiculo v;
    int encontrado = 0;

    if (fv == NULL || fi == NULL) {
        printf("Error al abrir archivos.\n");
        return;
    }

    strcpy(venta.cliente, "Ruben");
    venta.edad = 56;

    printf("Ingrese ID del vehiculo seleccionado por Ruben: ");
    scanf("%d", &venta.idVehiculo);

    while (fread(&v, sizeof(Vehiculo), 1, fi)) {
        if (v.id == venta.idVehiculo &&
            v.disponible == 1 &&
            v.precio <= PRESUPUESTO_RUBEN) {

            v.disponible = 0;
            venta.precioVenta = v.precio;

            fseek(fi, -sizeof(Vehiculo), SEEK_CUR);
            fwrite(&v, sizeof(Vehiculo), 1, fi);

            fwrite(&venta, sizeof(Venta), 1, fv);

            printf("Venta registrada con exito.\n");
            printf("Vehiculo marcado como NO DISPONIBLE.\n");

            encontrado = 1;
            break;
        }
    }

    if (!encontrado)
        printf("No se pudo registrar la venta (verifique ID o presupuesto).\n");

    fclose(fi);
    fclose(fv);
}

/*--------------------------------------------------*/
int main() {
    int opcion;
    int hayResultados;

    do {
        printf("\n===== SGIC - Ruedas de Oro =====\n");
        printf("1. Registrar vehiculo\n");
        printf("2. Buscar preferencias de Ruben\n");
        printf("3. Registrar venta de Ruben\n");
        printf("0. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarVehiculo();
                break;

            case 2:
                hayResultados = buscarVehiculosPreferencia();
                break;

            case 3:
                registrarVenta();
                break;

            case 0:
                printf("Saliendo del sistema...\n");
                break;

            default:
                printf("Opcion invalida.\n");
        }

    } while (opcion != 0);

    return 0;
}
