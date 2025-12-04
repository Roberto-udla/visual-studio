#include <stdio.h>
#include <string.h>

#define MAX_LIBROS 10
#define TITULO_MAX 100
#define AUTOR_MAX 50

typedef struct {
    int id;
    char titulo[TITULO_MAX];
    char autor[AUTOR_MAX];
    int anio_publicacion;
    char estado[10]; // "Disponible" o "Prestado"
} Libro;

Libro biblioteca[MAX_LIBROS];
int contador_libros = 0;

void registrar_libro() {
    if (contador_libros >= MAX_LIBROS) {
        printf("No se pueden agregar más libros.\n");
        return;
    }
    
    Libro nuevo_libro;
    printf("Ingrese ID del libro: ");
    scanf("%d", &nuevo_libro.id);
    printf("Ingrese título: ");
    getchar(); // Limpiar el buffer
    fgets(nuevo_libro.titulo, TITULO_MAX, stdin);
    nuevo_libro.titulo[strcspn(nuevo_libro.titulo, "\n")] = 0; // Eliminar el salto de línea
    printf("Ingrese autor: ");
    fgets(nuevo_libro.autor, AUTOR_MAX, stdin);
    nuevo_libro.autor[strcspn(nuevo_libro.autor, "\n")] = 0; // Eliminar el salto de línea
    printf("Ingrese año de publicación: ");
    scanf("%d", &nuevo_libro.anio_publicacion);
    strcpy(nuevo_libro.estado, "Disponible");

    biblioteca[contador_libros++] = nuevo_libro;
    printf("Libro registrado con éxito.\n");
}

void mostrar_libros() {
    printf("ID\tTítulo\t\tAutor\t\tAño\tEstado\n");
    for (int i = 0; i < contador_libros; i++) {
        printf("%d\t%s\t%s\t%d\t%s\n", biblioteca[i].id, biblioteca[i].titulo, biblioteca[i].autor, biblioteca[i].anio_publicacion, biblioteca[i].estado);
    }
}

Libro* buscar_libro(int id) {
    for (int i = 0; i < contador_libros; i++) {
        if (biblioteca[i].id == id) {
            return &biblioteca[i];
        }
    }
    return NULL;
}

void actualizar_estado(int id) {
    Libro* libro = buscar_libro(id);
    if (libro != NULL) {
        if (strcmp(libro->estado, "Disponible") == 0) {
            strcpy(libro->estado, "Prestado");
        } else {
            strcpy(libro->estado, "Disponible");
        }
        printf("Estado actualizado.\n");
    } else {
        printf("Libro no encontrado.\n");
    }
}

void eliminar_libro(int id) {
    for (int i = 0; i < contador_libros; i++) {
        if (biblioteca[i].id == id) {
            for (int j = i; j < contador_libros - 1; j++) {
                biblioteca[j] = biblioteca[j + 1];
            }
            contador_libros--;
            printf("Libro eliminado.\n");
            return;
        }
    }
    printf("Libro no encontrado.\n");
}

int main() {
    int opcion, id;

    do {
        printf("1. Registrar libro\n");
        printf("2. Mostrar libros\n");
        printf("3. Buscar libro\n");
        printf("4. Actualizar estado\n");
        printf("5. Eliminar libro\n");
        printf("6. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                registrar_libro();
                break;
            case 2:
                mostrar_libros();
                break;
            case 3:
                printf("Ingrese ID del libro a buscar: ");
                scanf("%d", &id);
                Libro* libro = buscar_libro(id);
                if (libro) {
                    printf("ID: %d, Título: %s, Autor: %s, Año: %d, Estado: %s\n", libro->id, libro->titulo, libro->autor, libro->anio_publicacion, libro->estado);
                } else {
                    printf("Libro no encontrado.\n");
                }
                break;
            case 4:
                printf("Ingrese ID del libro a actualizar: ");
                scanf("%d", &id);
                actualizar_estado(id);
                break;
            case 5:
                printf("Ingrese ID del libro a eliminar: ");
                scanf("%d", &id);
                eliminar_libro(id);
                break;
            case 6:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida.\n");
        }
    } while (opcion != 6);

    return 0;
}