#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUCTS 5
#define NAME_LEN 40

/* Prototipos */
int findIndexByName(char names[][NAME_LEN], int count, const char *target);
void addProduct(char names[][NAME_LEN], int qty[], double timePU[], double resPU[], int *pcount);
void editProduct(char names[][NAME_LEN], int qty[], double timePU[], double resPU[], int count);
void deleteProduct(char names[][NAME_LEN], int qty[], double timePU[], double resPU[], int *pcount);
void listProducts(char names[][NAME_LEN], int qty[], double timePU[], double resPU[], int count);
void calculateTotals(int qty[], double timePU[], double resPU[], int count, double *totalTime, double *totalResources);
void clearInputBuffer(void);
void toLowerStr(char *s);

int main(void) {
    char names[MAX_PRODUCTS][NAME_LEN];
    int qty[MAX_PRODUCTS];
    double timePerUnit[MAX_PRODUCTS];
    double resourcesPerUnit[MAX_PRODUCTS];
    int count = 0;
    int option;
    double totalTimeNeeded, totalResourcesNeeded;
    double availableTime, availableResources;

    for (int i = 0; i < MAX_PRODUCTS; ++i) {
        names[i][0] = '\0';
        qty[i] = 0;
        timePerUnit[i] = 0.0;
        resourcesPerUnit[i] = 0.0;
    }

    do {
        printf("\n--- Sistema de Optimización de Producción ---\n");
        printf("1) Agregar producto\n");
        printf("2) Editar producto\n");
        printf("3) Eliminar producto\n");
        printf("4) Listar productos\n");
        printf("5) Calcular tiempo y recursos totales\n");
        printf("6) Verificar cumplimiento (con limites disponibles)\n");
        printf("0) Salir\n");
        printf("Seleccione una opcion: ");

        if (scanf("%d", &option) != 1) {
            printf("Entrada invalida.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (option) {
            case 1:
                addProduct(names, qty, timePerUnit, resourcesPerUnit, &count);
                break;
            case 2:
                editProduct(names, qty, timePerUnit, resourcesPerUnit, count);
                break;
            case 3:
                deleteProduct(names, qty, timePerUnit, resourcesPerUnit, &count);
                break;
            case 4:
                listProducts(names, qty, timePerUnit, resourcesPerUnit, count);
                break;
            case 5:
                calculateTotals(qty, timePerUnit, resourcesPerUnit, count, &totalTimeNeeded, &totalResourcesNeeded);
                printf("Tiempo total requerido: %.3f\n", totalTimeNeeded);
                printf("Recursos totales requeridos: %.3f\n", totalResourcesNeeded);
                break;
            case 6:
                printf("Ingrese tiempo total disponible: ");
                if (scanf("%lf", &availableTime) != 1) { clearInputBuffer(); printf("Entrada invalida.\n"); break; }
                printf("Ingrese recursos totales disponibles: ");
                if (scanf("%lf", &availableResources) != 1) { clearInputBuffer(); printf("Entrada invalida.\n"); break; }
                clearInputBuffer();

                calculateTotals(qty, timePerUnit, resourcesPerUnit, count, &totalTimeNeeded, &totalResourcesNeeded);

                printf("Tiempo requerido: %.3f  vs  Disponible: %.3f\n", totalTimeNeeded, availableTime);
                printf("Recursos requeridos: %.3f vs Disponible: %.3f\n", totalResourcesNeeded, availableResources);

                if (totalTimeNeeded <= availableTime && totalResourcesNeeded <= availableResources) {
                    printf("La fabrica PUEDE cumplir con la demanda.\n");
                } else {
                    printf("La fabrica NO PUEDE cumplir con la demanda. Faltan:\n");
                    if (totalTimeNeeded > availableTime)
                        printf("  Tiempo faltante: %.3f\n", totalTimeNeeded - availableTime);
                    if (totalResourcesNeeded > availableResources)
                        printf("  Recursos faltantes: %.3f\n", totalResourcesNeeded - availableResources);
                }
                break;

            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while (option != 0);

    return 0;
}

/* Limpia buffer */
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/* Convertir cadena a minúscula para búsquedas */
void toLowerStr(char *s) {
    for (; *s; ++s) *s = (char)tolower((unsigned char)*s);
}

/* Buscar por nombre */
int findIndexByName(char names[][NAME_LEN], int count, const char *target) {
    char tempTarget[NAME_LEN];
    strncpy(tempTarget, target, NAME_LEN-1);
    tempTarget[NAME_LEN-1] = '\0';
    toLowerStr(tempTarget);

    for (int i = 0; i < count; ++i) {
        char tempName[NAME_LEN];
        strncpy(tempName, names[i], NAME_LEN-1);
        tempName[NAME_LEN-1] = '\0';
        toLowerStr(tempName);

        if (strcmp(tempName, tempTarget) == 0)
            return i;
    }
    return -1;
}

/* Agregar producto */
void addProduct(char names[][NAME_LEN], int qty[], double timePU[], double resPU[], int *pcount) {
    if (*pcount >= MAX_PRODUCTS) {
        printf("Capacidad maxima alcanzada.\n");
        return;
    }

    char buffer[NAME_LEN];
    int q;
    double t, r;

    printf("Nombre del producto: ");
    if (!fgets(buffer, NAME_LEN, stdin)) { clearInputBuffer(); return; }
    buffer[strcspn(buffer, "\n")] = '\0';

    if (strlen(buffer) == 0) {
        printf("Nombre vacio.\n");
        return;
    }

    if (findIndexByName(names, *pcount, buffer) != -1) {
        printf("Producto ya existe.\n");
        return;
    }

    printf("Cantidad demandada: ");
    if (scanf("%d", &q) != 1) { clearInputBuffer(); printf("Entrada invalida.\n"); return; }

    printf("Tiempo por unidad: ");
    if (scanf("%lf", &t) != 1) { clearInputBuffer(); printf("Entrada invalida.\n"); return; }

    printf("Recursos por unidad: ");
    if (scanf("%lf", &r) != 1) { clearInputBuffer(); printf("Entrada invalida.\n"); return; }

    clearInputBuffer();

    int idx = *pcount;
    strncpy(names[idx], buffer, NAME_LEN-1);
    names[idx][NAME_LEN-1] = '\0';

    qty[idx] = q;
    timePU[idx] = t;
    resPU[idx] = r;

    (*pcount)++;

    printf("Producto agregado.\n");
}

/* Editar producto */
void editProduct(char names[][NAME_LEN], int qty[], double timePU[], double resPU[], int count) {
    if (count == 0) {
        printf("No hay productos.\n");
        return;
    }

    char buffer[NAME_LEN];
    printf("Ingrese el nombre del producto a editar: ");
    if (!fgets(buffer, NAME_LEN, stdin)) { clearInputBuffer(); return; }
    buffer[strcspn(buffer, "\n")] = '\0';

    int idx = findIndexByName(names, count, buffer);
    if (idx == -1) {
        printf("Producto no encontrado.\n");
        return;
    }

    printf("Producto encontrado: %s\n", names[idx]);

    /* Editar nombre */
    printf("Nuevo nombre (enter para mantener): ");
    char nuevo[NAME_LEN];
    if (!fgets(nuevo, NAME_LEN, stdin)) { clearInputBuffer(); return; }
    nuevo[strcspn(nuevo, "\n")] = '\0';

    if (strlen(nuevo) > 0) {
        int existe = findIndexByName(names, count, nuevo);
        if (existe != -1 && existe != idx) {
            printf("Ese nombre ya existe.\n");
        } else {
            strncpy(names[idx], nuevo, NAME_LEN-1);
            names[idx][NAME_LEN-1] = '\0';
        }
    }

    /* Editar cantidad */
    printf("Nueva cantidad (actual %d, -1 para mantener): ", qty[idx]);
    int q;
    if (scanf("%d", &q) == 1 && q >= 0) qty[idx] = q;

    /* Editar tiempo */
    printf("Nuevo tiempo por unidad (actual %.3f, -1 para mantener): ", timePU[idx]);
    double t;
    if (scanf("%lf", &t) == 1 && t >= 0.0) timePU[idx] = t;

    /* Editar recursos */
    printf("Nuevos recursos por unidad (actual %.3f, -1 para mantener): ", resPU[idx]);
    double r;
    if (scanf("%lf", &r) == 1 && r >= 0.0) resPU[idx] = r;

    clearInputBuffer();
    printf("Edicion finalizada.\n");
}

/* Eliminar producto */
void deleteProduct(char names[][NAME_LEN], int qty[], double timePU[], double resPU[], int *pcount) {
    if (*pcount == 0) {
        printf("No hay productos para eliminar.\n");
        return;
    }

    char buffer[NAME_LEN];
    printf("Ingrese el nombre del producto a eliminar: ");
    if (!fgets(buffer, NAME_LEN, stdin)) { clearInputBuffer(); return; }
    buffer[strcspn(buffer, "\n")] = '\0';

    int idx = findIndexByName(names, *pcount, buffer);
    if (idx == -1) {
        printf("Producto no encontrado.\n");
        return;
    }

    for (int i = idx; i < (*pcount) - 1; ++i) {
        strncpy(names[i], names[i+1], NAME_LEN);
        qty[i] = qty[i+1];
        timePU[i] = timePU[i+1];
        resPU[i] = resPU[i+1];
    }

    (*pcount)--;
    printf("Producto eliminado.\n");
}

/* Listar productos */
void listProducts(char names[][NAME_LEN], int qty[], double timePU[], double resPU[], int count) {
    if (count == 0) {
        printf("No hay productos registrados.\n");
        return;
    }

    printf("\nListado de productos (%d):\n", count);
    for (int i = 0; i < count; ++i) {
        printf("%d) %s | Cant: %d | Tiempo/u: %.3f | Recursos/u: %.3f\n",
               i + 1, names[i], qty[i], timePU[i], resPU[i]);
    }
}

/* Calcular totales */
void calculateTotals(int qty[], double timePU[], double resPU[], int count, double *totalTime, double *totalResources) {
    double tt = 0.0, tr = 0.0;

    for (int i = 0; i < count; ++i) {
        tt += qty[i] * timePU[i];
        tr += qty[i] * resPU[i];
    }

    *totalTime = tt;
    *totalResources = tr;
}
