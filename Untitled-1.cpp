#include <iostream>
#include <string>
using namespace std;

int main() {
    int id, stock = 0, opcion, cantidad;
    float precio, ganancias = 0, descuento;
    string nombre;

    // Registro inicial del producto
    cout << "\n\t=== REGISTRO DE PRODUCTO ===\n";
    cout << "Ingrese ID del producto: ";
    cin >> id;
    cin.ignore(); // limpiar buffer

    cout << "Ingrese nombre del producto: ";
    getline(cin, nombre);

    cout << "Ingrese cantidad inicial en stock: ";
    cin >> stock;

    cout << "Ingrese precio unitario: ";
    cin >> precio;

    do {
        cout << "\n\t==============================\n";
        cout << "\t         MENU PRINCIPAL       \n";
        cout << "\t==============================\n";
        cout << "\t1. Vender producto\n";
        cout << "\t2. Reabastecer producto\n";
        cout << "\t3. Consultar informacion\n";
        cout << "\t4. Mostrar ganancias\n";
        cout << "\t5. Salir\n";
        cout << "\tSeleccione una opcion: ";
        cin >> opcion;

        cout << "\n---------------------------------\n";

        switch(opcion) {
            case 1:
                cout << "Ingrese cantidad a vender: ";
                cin >> cantidad;

                if (cantidad <= 0) {
                    cout << "⚠ Error: cantidad invalida.\n";
                } else if (cantidad > stock) {
                    cout << "⚠ Error: stock insuficiente.\n";
                } else {
                    cout << "Ingrese descuento (%), 0 si no hay: ";
                    cin >> descuento;

                    if (descuento < 0 || descuento > 100) {
                        cout << "⚠ Error: descuento invalido.\n";
                        break;
                    }

                    float precioFinal = (precio - (precio * descuento / 100)) * cantidad;
                    stock -= cantidad;
                    ganancias += precioFinal;
                    cout << "✅ Venta realizada.\n";
                    cout << "Total de esta venta: $" << precioFinal << "\n";
                }
                break;

            case 2:
                cout << "Ingrese cantidad a agregar al stock: ";
                cin >> cantidad;
                if (cantidad > 0) {
                    stock += cantidad;
                    cout << "✅ Stock actualizado: " << stock << "\n";
                } else {
                    cout << "⚠ Error: cantidad invalida.\n";
                }
                break;

            case 3:
                cout << "\n📦 INFORMACION DEL PRODUCTO\n";
                cout << "ID: " << id << "\n";
                cout << "Nombre: " << nombre << "\n";
                cout << "Stock disponible: " << stock << "\n";
                cout << "Precio unitario: $" << precio << "\n";
                break;

            case 4:
                cout << "💰 Ganancias acumuladas: $" << ganancias << "\n";
                break;

            case 5:
                cout << "👋 Saliendo del programa...\n";
                break;

            default:
                cout << "⚠ Opcion invalida.\n";
        }

    } while(opcion != 5);

    return 0;
}
