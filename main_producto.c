#include "producto.h"

int main(void) {
    Producto p;
    producto_registrar(&p);

    int opcion;
    do {
        opcion = producto_menu_obtener_opcion();
        switch (opcion) {
            case 1: producto_vender(&p); break;
            case 2: producto_reabastecer(&p); break;
            case 3: producto_consultar(&p); break;
            case 4: producto_mostrar_ganancias(&p); break;
            case 5: printf("👋 Saliendo del programa...\n"); break;
            default: printf("Opción no válida. Intente de nuevo.\n"); break;
        }
    } while (opcion != 5);

    return 0;
}
