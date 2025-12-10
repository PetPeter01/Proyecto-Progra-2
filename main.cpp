#include <iostream>
#include "Menu.h"
#include "rlutil.h"
using namespace std;

int main() {

    int opcion = 0;
    rlutil::setBackgroundColor(rlutil::BLUE);
    rlutil::hidecursor();
    do {
        opcion = mostrarMenuPrincipal();

        switch (opcion) {
            case 0: {
                menuLogicoCliente();
                system("pause");
            }
                break;
            case 1:
                menuLogicoProductos();
                system("pause");
                break;
            case 2:
                menuLogicoVentas();
                break;
           case 3:
                menuLogicoProveedores();
                break;
            case 4:
                cout << endl <<  "Saliendo...\n";
                return 0;
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
                system("pause");
        }
    } while (opcion != 50);

    return 0;
}
