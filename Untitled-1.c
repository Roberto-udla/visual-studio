#include <stdio.h>

int main() {
    int n; // número de cursos
    printf("Ingrese la cantidad de cursos que ofrece la academia: ");
    scanf("%d", &n);

    int cupos[n], inscritos[n];
    float costo[n], recaudado[n];
    float totalRecaudado = 0;

    // Registro de datos de cada curso
    for (int i = 0; i < n; i++) {
        printf("\n=== Curso %d ===\n", i + 1);
        printf("Ingrese el numero maximo de cupos: ");
        scanf("%d", &cupos[i]);
        printf("Ingrese el costo del curso: ");
        scanf("%f", &costo[i]);
        printf("Ingrese la cantidad de estudiantes inscritos: ");
        scanf("%d", &inscritos[i]);

        if (inscritos[i] <= cupos[i]) {
            int cuposDisponibles = cupos[i] - inscritos[i];
            recaudado[i] = inscritos[i] * costo[i];
            totalRecaudado += recaudado[i];

            printf("Cupos disponibles: %d\n", cuposDisponibles);
            printf("Dinero recaudado en este curso: $%.2f\n", recaudado[i]);
        } else {
            printf("❌ Error: Los inscritos (%d) superan los cupos (%d).\n", inscritos[i], cupos[i]);
            recaudado[i] = 0;
        }
    }

    printf("\n============================\n");
    printf("Recaudacion total de todos los cursos: $%.2f\n", totalRecaudado);
    printf("============================\n");

    return 0;
}
