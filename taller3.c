#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int id, stock = 0, opcion, cantidad;
float precio, ganancias = 0, descuento;
char nombre[50];
void Registro();
void Menu();
void Vender();
void Reabastecer();
void Consultar();
void Ganancias();
void Salir();
 
int main()
{
    Registro();
    do
    {
        Menu();
        switch (opcion)
        {
        case 1:
            Vender();
            break;
        case 2:
            Reabastecer();
            break;
        case 3:
            Consultar();
            break;
        case 4:
            Ganancias();
            break;
        case 5:
            Salir();
            break;    
        default:
            break;
        }
    } while (opcion != 5);

    return 0;
}
 
void Registro()
{
    printf("\n\t=== REGISTRO DE PRODUCTO ===\n");
 
    printf("Ingrese ID del producto: ");
 
    scanf("%d", &id);
 
    getchar();
 
    printf("Ingrese nombre del producto: ");
 
    fgets(nombre, sizeof(nombre), stdin);
 
    nombre[strcspn(nombre, "\n")] = 0;
 
    printf("Ingrese cantidad inicial en stock: ");
 
    scanf("%d", &stock);
 
    printf("Ingrese precio unitario: ");
 
    scanf("%f", &precio);
}
 
void Menu()
{
    printf("\n\t==============================\n");
 
    printf("\t         MENU PRINCIPAL       \n");
 
    printf("\t==============================\n");
 
    printf("\t1. Vender producto\n");
 
    printf("\t2. Reabastecer producto\n");
 
    printf("\t3. Consultar informacion\n");
 
    printf("\t4. Mostrar ganancias\n");
 
    printf("\t5. Salir\n");
 
    printf("\tSeleccione una opcion: ");
    
    scanf("%d", &opcion);

}
 
void Vender()
{
    printf("Ingrese cantidad a vender: ");
    scanf("%d", &cantidad);
 
    if (cantidad <= 0)
    {
        printf("⚠ Error: cantidad invalida.\n");
    }
    else if (cantidad > stock)
    {
        printf("⚠ Error: stock insuficiente.\n");
    }
    else
    {
        printf("Ingrese descuento (%%), 0 si no hay: ");
        scanf("%f", &descuento);
 
        if (descuento < 0 || descuento > 100)
        {
            printf("⚠ Error: descuento invalido.\n");
        }
 
        float precioFinal = (precio - (precio * descuento / 100)) * cantidad;
        stock -= cantidad;
        ganancias += precioFinal;
        printf("✅ Venta realizada.\n");
        printf("Total de esta venta: $%.2f\n", precioFinal);
    }
}
 
void Reabastecer()
{
    printf("Ingrese cantidad a agregar al stock: ");
    scanf("%d", &cantidad);
    if (cantidad > 0)
    {
        stock += cantidad;
        printf("✅ Stock actualizado: %d\n", stock);
    }
    else
    {
        printf("⚠ Error: cantidad invalida.\n");
    }
}
 
void Consultar()
{
    printf("\n📦 INFORMACION DEL PRODUCTO\n");
    printf("ID: %d\n", id);
    printf("Nombre: %s\n", nombre);
    printf("Stock disponible: %d\n", stock);
    printf("Precio unitario: $%.2f\n", precio);
}
 
void Ganancias()
{
    printf("💰 Ganancias acumuladas: $%.2f\n", ganancias);
}

void Salir(){
    printf("👋 Saliendo del programa...\n");
}