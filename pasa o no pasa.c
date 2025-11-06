#include <stdio.h>

// Definición de constantes
#define NUM_ESTUDIANTES 5
#define NUM_ASIGNATURAS 3

// Prototipos de funciones
void ingresar_calificaciones(float calificaciones[NUM_ESTUDIANTES][NUM_ASIGNATURAS]);
void calcular_promedio_estudiante(float calificaciones[NUM_ESTUDIANTES][NUM_ASIGNATURAS]);
void calcular_promedio_asignatura(float calificaciones[NUM_ESTUDIANTES][NUM_ASIGNATURAS]);
void encontrar_calificaciones_extremas(float calificaciones[NUM_ESTUDIANTES][NUM_ASIGNATURAS]);
void contar_aprobados_reprobados(float calificaciones[NUM_ESTUDIANTES][NUM_ASIGNATURAS]);

// ----------------------------------------------------------------------------------------------------------------------
int main() {
    // Matriz para almacenar las calificaciones: [estudiante][asignatura]
    float calificaciones[NUM_ESTUDIANTES][NUM_ASIGNATURAS];
    
    printf("Programa de Gestion de Calificaciones de Alumnos \n");
    printf("--------------------------------------------------\n");

    // Tarea 1: Ingreso y validación de calificaciones
    ingresar_calificaciones(calificaciones);
    
    printf("\n--- Resultados del Analisis de Calificaciones ---\n");
    
    // Tarea 2: Calcular el promedio de calificaciones por estudiante
    calcular_promedio_estudiante(calificaciones);
    
    // Tarea 3: Calcular el promedio por asignatura
    calcular_promedio_asignatura(calificaciones);
    
    // Tarea 4: Encontrar la calificación más alta y baja por estudiante y por asignatura
    encontrar_calificaciones_extremas(calificaciones);
    
    // Tarea 5: Determinar cuántos estudiantes aprobaron o reprobaron cada asignatura
    contar_aprobados_reprobados(calificaciones);

    printf("\n--- Fin del Programa ---\n");

    return 0;
}

/**
 * @brief Solicita al usuario las calificaciones y valida que estén en el rango de 0 a 10.
 * * @param calificaciones La matriz donde se almacenarán las notas.
 */
void ingresar_calificaciones(float calificaciones[NUM_ESTUDIANTES][NUM_ASIGNATURAS]) {
    printf("\nIngreso de Calificaciones (Rango: 0.0 - 10.0):\n");
    int i, j;
    float nota;

    for (i = 0; i < NUM_ESTUDIANTES; i++) {
        for (j = 0; j < NUM_ASIGNATURAS; j++) {
            do {
                printf("Ingrese la calificacion del Estudiante %d en la Asignatura %d: ", i + 1, j + 1);
                // Leer la nota
                if (scanf("%f", &nota) != 1) {
                    printf("Error: Entrada no valida. Por favor, ingrese un numero.\n");
                    // Limpiar el buffer de entrada en caso de error de lectura
                    while (getchar() != '\n');
                    nota = -1; // Forzar la repetición del bucle
                }
                
                // Validar el rango
                if (nota < 0.0 || nota > 10.0) {
                    printf("Error: La calificacion debe estar entre 0.0 y 10.0.\n");
                }
            } while (nota < 0.0 || nota > 10.0);
            
            calificaciones[i][j] = nota;
        }
        printf("----------------------------------\n");
    }
}

/**
 * @brief Calcula y muestra el promedio de calificaciones para cada estudiante.
 * * @param calificaciones La matriz con las notas.
 */
void calcular_promedio_estudiante(float calificaciones[NUM_ESTUDIANTES][NUM_ASIGNATURAS]) {
    printf("\n\nPromedio de Calificaciones por Estudiante:\n");
    int i, j;
    float suma_notas;
    float promedio;

    for (i = 0; i < NUM_ESTUDIANTES; i++) {
        suma_notas = 0.0;
        for (j = 0; j < NUM_ASIGNATURAS; j++) {
            suma_notas += calificaciones[i][j];
        }
        promedio = suma_notas / NUM_ASIGNATURAS;
        printf("Estudiante %d: %.2f\n", i + 1, promedio);
    }
}

/**
 * @brief Calcula y muestra el promedio de calificaciones por asignatura.
 * * @param calificaciones La matriz con las notas.
 */
void calcular_promedio_asignatura(float calificaciones[NUM_ESTUDIANTES][NUM_ASIGNATURAS]) {
    printf("\n\n Promedio de Calificaciones por Asignatura:\n");
    int i, j;
    float suma_notas;
    float promedio;

    for (j = 0; j < NUM_ASIGNATURAS; j++) {
        suma_notas = 0.0;
        for (i = 0; i < NUM_ESTUDIANTES; i++) {
            suma_notas += calificaciones[i][j];
        }
        promedio = suma_notas / NUM_ESTUDIANTES;
        printf("Asignatura %d: %.2f\n", j + 1, promedio);
    }
}

/**
 * @brief Encuentra y muestra la calificación más alta y más baja por estudiante y por asignatura.
 * * @param calificaciones La matriz con las notas.
 */
void encontrar_calificaciones_extremas(float calificaciones[NUM_ESTUDIANTES][NUM_ASIGNATURAS]) {
    int i, j;
    float max_estudiante, min_estudiante;
    float max_asignatura, min_asignatura;

    printf("\n\nCalificaciones Maximas y Minimas:\n");

    // Por Estudiante
    printf("\n--- Por Estudiante ---\n");
    for (i = 0; i < NUM_ESTUDIANTES; i++) {
        max_estudiante = calificaciones[i][0];
        min_estudiante = calificaciones[i][0];
        for (j = 1; j < NUM_ASIGNATURAS; j++) {
            if (calificaciones[i][j] > max_estudiante) {
                max_estudiante = calificaciones[i][j];
            }
            if (calificaciones[i][j] < min_estudiante) {
                min_estudiante = calificaciones[i][j];
            }
        }
        printf("Estudiante %d: Maxima = %.2f, Minima = %.2f\n", i + 1, max_estudiante, min_estudiante);
    }

    // Por Asignatura
    printf("\n--- Por Asignatura ---\n");
    for (j = 0; j < NUM_ASIGNATURAS; j++) {
        max_asignatura = calificaciones[0][j];
        min_asignatura = calificaciones[0][j];
        for (i = 1; i < NUM_ESTUDIANTES; i++) {
            if (calificaciones[i][j] > max_asignatura) {
                max_asignatura = calificaciones[i][j];
            }
            if (calificaciones[i][j] < min_asignatura) {
                min_asignatura = calificaciones[i][j];
            }
        }
        printf("Asignatura %d: Maxima = %.2f, Minima = %.2f\n", j + 1, max_asignatura, min_asignatura);
    }
}

/**
 * @brief Determina y muestra cuántos estudiantes aprobaron o reprobaron cada asignatura.
 * * @param calificaciones La matriz con las notas.
 */
void contar_aprobados_reprobados(float calificaciones[NUM_ESTUDIANTES][NUM_ASIGNATURAS]) {
    // Nota aprobatoria es >= 6.0
    const float NOTA_APROBATORIA = 6.0;
    
    printf("\n\nCuenta de Aprobados y Reprobados (Nota Aprobatoria %.1f):\n", NOTA_APROBATORIA);
    int i, j;
    int aprobados, reprobados;

    for (j = 0; j < NUM_ASIGNATURAS; j++) {
        aprobados = 0;
        reprobados = 0;
        for (i = 0; i < NUM_ESTUDIANTES; i++) {
            if (calificaciones[i][j] >= NOTA_APROBATORIA) {
                aprobados++;
            } else {
                reprobados++;
            }
        }
        printf("Asignatura %d: Aprobados = %d, Reprobados = %d\n", j + 1, aprobados, reprobados);
    }
}