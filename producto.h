#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <stdio.h>

#define NOMBRE_SIZE 50

typedef struct {
    int id;
    char nombre[NOMBRE_SIZE];
    int stock;
    float precio;
    float ganancias_acumuladas;
} Producto;

/* API pública */
void producto_registrar(Producto *p);
int producto_menu_obtener_opcion(void);
void producto_vender(Producto *p);
void producto_reabastecer(Producto *p);
void producto_consultar(const Producto *p);
void producto_mostrar_ganancias(const Producto *p);

#endif /* PRODUCTO_H */
