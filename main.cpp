#include <iostream>
#include "Menu.h"
#include "rlutil.h"
#include "TiposDeEquipoArchivo.h"
using namespace std;

int main() {
    TiposDeEquipoArchivo archTipos;
    archTipos.inicializarSiNoExiste();

    int opcion = 0;
    rlutil::setBackgroundColor(rlutil::BLUE);
    rlutil::hidecursor();

    do {
        opcion = mostrarMenuPrincipal();

        switch (opcion) {
            case 0:
                menuLogicoCliente();
                system("pause");
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
                menuLogicoTiposEquipo();
                system("pause");
                break;
            case 5:
                menuLogicoEmpleados();
                break;
            case 6:
                menuLogicoCompras();
                break;
            case 7:
                cout << endl << "Saliendo...\n";
                return 0;

            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
                system("pause");
                break;
        }

    } while (opcion != 5);

    return 0;
}
