#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX 10

void ingresarProductos(char nombres[MAX][50], float precios[MAX], int cantidad);
float precioTotal(float precios[MAX], int cantidad);
float precioPromedio(float precios[MAX], int cantidad);
int productoMasCaro(float precios[MAX], int cantidad);
int productoMasBarato(float precios[MAX], int cantidad);
int buscarProducto(char nombres[MAX][50], float precios[MAX], int cantidad, char buscado[50]);

#endif
