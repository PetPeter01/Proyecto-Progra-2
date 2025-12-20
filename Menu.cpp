#include <iostream>
#include "Menu.h"
#include "rlutil.h"
#include "FuncionesGenerales.h"
#include "cliente.h"
#include "Venta.h"
#include "Producto.h"
#include "ClienteArchivo.h"
#include "ProductoArchivo.h"
#include "VentaArchivo.h"
#include "ProveedorArchivo.h"
#include "TiposDeEquipoArchivo.h"
#include "Empleado.h"
#include "EmpleadoArchivo.h"
#include "CompraArchivo.h"
#include "MovimientoStock.h"
#include "MovimientoStockArchivo.h"

using namespace std;


int flechaSeleccion(int y, int cantidadOpciones, bool &seleccionar) {
    int tecla = rlutil::getkey();

    switch (tecla) {
        case rlutil::KEY_UP:
            y--;
            if (y < 0) y = cantidadOpciones - 1;
            break;
        case rlutil::KEY_DOWN:
            y++;
            if (y >= cantidadOpciones) y = 0;
            break;
        case rlutil::KEY_ENTER:
            seleccionar = true;
            break;
        default:
            break;
    }
    return y;
}

// MENUS VISUALES
int mostrarMenuPrincipal() {
    int y = 0;
    const int cantidadOpciones = 3;
    bool seleccionar = false;
    int yAnterior = -1;

    rlutil::cls();
    rlutil::locate(50, 10); cout << "--- MENU PRINCIPAL ---";
    rlutil::locate(55, 11); cout << "DATOS BASE";
    rlutil::locate(55, 12); cout << "OPERACIONES";
    rlutil::locate(55, 13); cout << "SALIR";

    while (!seleccionar) {
        if (y != yAnterior) {

            if (yAnterior != -1) {
                rlutil::locate(53, 11 + yAnterior);
                cout << " ";
            }

            rlutil::locate(53, 11 + y);
            cout << (char)175;
            yAnterior = y;
        }
        y = flechaSeleccion(y, cantidadOpciones, seleccionar);
    }

    return y;
}

int mostrarDatosBase(){
    int y = 0;
    const int cantidadOpciones = 6;
    bool seleccionar = false;
    int yAnterior = -1;

    rlutil::cls();
    rlutil::locate(50, 10); cout << "--- DATOS BASE ---";
    rlutil::locate(55, 11); cout << "CLIENTES";
    rlutil::locate(55, 12); cout << "PRODUCTOS";
    rlutil::locate(55, 13); cout << "PROVEEDORES";
    rlutil::locate(55, 14); cout << "EMPLEADOS";
    rlutil::locate(55, 15); cout << "TIPOS DE EQUIPO";
    rlutil::locate(55, 16); cout << "ATRAS";

    while (!seleccionar) {
        if (y != yAnterior) {

            if (yAnterior != -1) {
                rlutil::locate(53, 11 + yAnterior);
                cout << " ";
            }

            rlutil::locate(53, 11 + y);
            cout << (char)175;
            yAnterior = y;
        }
        y = flechaSeleccion(y, cantidadOpciones, seleccionar);
    }

    return y;
}

int mostrarOperaciones(){
    int y = 0;
    const int cantidadOpciones = 4;
    bool seleccionar = false;
    int yAnterior = -1;

    rlutil::cls();
    rlutil::locate(50, 10); cout << "--- OPERACIONES ---";
    rlutil::locate(55, 11); cout << "VENTAS";
    rlutil::locate(55, 12); cout << "COMPRAS";
    rlutil::locate(55, 13); cout << "MOVIMIENTO DE STOCK";
    rlutil::locate(55, 14); cout << "ATRAS";

    while (!seleccionar) {
        if (y != yAnterior) {

            if (yAnterior != -1) {
                rlutil::locate(53, 11 + yAnterior);
                cout << " ";
            }

            rlutil::locate(53, 11 + y);
            cout << (char)175;
            yAnterior = y;
        }
        y = flechaSeleccion(y, cantidadOpciones, seleccionar);
    }

    return y;
}

int mostrarMenuCliente() {
    int y = 0;
    const int cantidadOpciones = 6;
    bool seleccionar = false;
    int yAnterior = -1;

    rlutil::cls();
    rlutil::locate(50, 10); cout << "--- MENU CLIENTE ---";
    rlutil::locate(55, 11); cout << " AGREGAR CLIENTE";
    rlutil::locate(55, 12); cout << " BORRAR CLIENTE";
    rlutil::locate(55, 13); cout << " REACTIVAR CLIENTE";
    rlutil::locate(55, 14); cout << " VER CLIENTES";
    rlutil::locate(55, 15); cout << " BUSCAR CLIENTE";
    rlutil::locate(55, 16); cout << " ATRAS";

    while (!seleccionar) {
        if (y != yAnterior) {

            if (yAnterior != -1) {
                rlutil::locate(53, 11 + yAnterior);
                cout << " ";
            }

            rlutil::locate(53, 11 + y);
            cout << (char)175;
            yAnterior = y;
        }
        y = flechaSeleccion(y, cantidadOpciones, seleccionar);
    }

    return y;
}

int mostrarMenuProductos() {
    int y = 0;
    const int cantidadOpciones = 4;
    bool seleccionar = false;
    int yAnterior = -1;

    rlutil::cls();
    rlutil::locate(50, 10); cout << "--- MENU PRODUCTOS ---";
    rlutil::locate(55, 11); cout << " AGREGAR PRODUCTO";
    rlutil::locate(55, 12); cout << " BORRAR PRODUCTO";
    rlutil::locate(55, 13); cout << " VER PRODUCTOS";
    rlutil::locate(55, 14); cout << " ATRAS";

    while (!seleccionar) {
        if (y != yAnterior) {

            if (yAnterior != -1) {
                rlutil::locate(53, 11 + yAnterior);
                cout << " ";
            }

            rlutil::locate(53, 11 + y);
            cout << (char)175;
            yAnterior = y;
        }
        y = flechaSeleccion(y, cantidadOpciones, seleccionar);
    }

    return y;
}

int mostrarMenuVentas() {
    int y = 0;
    const int cantidadOpciones = 8;
    bool seleccionar = false;
    int yAnterior = -1;

    rlutil::cls();
    rlutil::locate(50, 10); cout << "--- MENU VENTAS ---";
    rlutil::locate(55, 11); cout << " NUEVA VENTA";
    rlutil::locate(55, 12); cout << " BORRAR VENTA";
    rlutil::locate(55, 13); cout << " LISTAR VENTAS";
    rlutil::locate(55, 14); cout << " REACTIVAR VENTA";
    rlutil::locate(55, 15); cout << " MAYOR IMPORTE POR ANIO";
    rlutil::locate(55, 16); cout << " RECAUDACION ANUAL";
    rlutil::locate(55, 17); cout << " RECAUDACION POR CLIENTE";
    rlutil::locate(55, 18); cout << " ATRAS";

    while (!seleccionar) {
        if (y != yAnterior) {
            if (yAnterior != -1) {
                rlutil::locate(53, 11 + yAnterior);
                cout << " ";
            }
            rlutil::locate(53, 11 + y);
            cout << (char)175;
            yAnterior = y;
        }
        y = flechaSeleccion(y, cantidadOpciones, seleccionar);
    }

    return y;
}

int mostrarMenuProveedores() {
    int y = 0;
    const int cantidadOpciones = 6;
    bool seleccionar = false;
    int yAnterior = -1;

    rlutil::cls();
    rlutil::locate(50, 10); cout << "--- MENU PROVEEDORES ---";
    rlutil::locate(55, 11); cout << " ALTA PROVEEDOR";
    rlutil::locate(55, 12); cout << " LISTAR PROVEEDORES";
    rlutil::locate(55, 13); cout << " BAJA LOGICA";
    rlutil::locate(55, 14); cout << " REACTIVAR PROVEEDOR";
    rlutil::locate(55, 15); cout << " BUSCAR POR NOMBRE";
    rlutil::locate(55, 16); cout << " ATRAS";

    while (!seleccionar) {
        if (y != yAnterior) {

            if (yAnterior != -1) {
                rlutil::locate(53, 11 + yAnterior);
                cout << " ";
            }

            rlutil::locate(53, 11 + y);
            cout << (char)175;
            yAnterior = y;
        }
        y = flechaSeleccion(y, cantidadOpciones, seleccionar);
    }

    return y;
}

int mostrarMenuTiposEquipo() {
    int y = 0;
    const int cantidadOpciones = 4;
    bool seleccionar = false;
    int yAnterior = -1;

    rlutil::cls();
    rlutil::locate(50, 10); cout << "--- MENU TIPOS DE EQUIPO ---";
    rlutil::locate(55, 11); cout << " VER TODOS";
    rlutil::locate(55, 12); cout << " VER SOLO ACTIVOS";
    rlutil::locate(55, 13); cout << " ACTIVAR / DESACTIVAR";
    rlutil::locate(55, 14); cout << " ATRAS";

    while (!seleccionar) {
        if (y != yAnterior) {
            if (yAnterior != -1) {
                rlutil::locate(53, 11 + yAnterior);
                cout << " ";
            }
            rlutil::locate(53, 11 + y);
            cout << (char)175;
            yAnterior = y;
        }
        y = flechaSeleccion(y, cantidadOpciones, seleccionar);
    }

    return y;
}

int mostrarMenuEmpleados() {
    int y = 0;
    const int cantidadOpciones = 6;
    bool seleccionar = false;
    int yAnterior = -1;

    rlutil::cls();
    rlutil::locate(50, 10); cout << "--- MENU EMPLEADOS ---";
    rlutil::locate(55, 11); cout << " ALTA EMPLEADO";
    rlutil::locate(55, 12); cout << " BAJA LOGICA EMPLEADO";
    rlutil::locate(55, 13); cout << " REACTIVAR EMPLEADO";
    rlutil::locate(55, 14); cout << " LISTAR EMPLEADOS ACTIVOS";
    rlutil::locate(55, 15); cout << " LISTAR TODOS LOS EMPLEADOS";
    rlutil::locate(55, 16); cout << " VOLVER AL MENU PRINCIPAL";

    while (!seleccionar) {
        if (y != yAnterior) {

            if (yAnterior != -1) {
                rlutil::locate(53, 11 + yAnterior);
                cout << " ";
            }

            rlutil::locate(53, 11 + y);
            cout << (char)175;
            yAnterior = y;
        }
        y = flechaSeleccion(y, cantidadOpciones, seleccionar);
    }

    return y;
}

int mostrarMenuCompras() {
    int y = 0;
    const int cantidadOpciones = 6;
    bool seleccionar = false;
    int yAnterior = -1;

    rlutil::cls();
    rlutil::locate(50, 10); cout << "--- MENU COMPRAS ---";
    rlutil::locate(55, 11); cout << " NUEVA COMPRA";
    rlutil::locate(55, 12); cout << " BORRAR COMPRA";
    rlutil::locate(55, 13); cout << " LISTAR COMPRAS";
    rlutil::locate(55, 14); cout << " GASTO ANUAL";
    rlutil::locate(55, 15); cout << " LISTAR COMPRAS POR EMPLEADO";
    rlutil::locate(55, 16); cout << " ATRAS";

    while (!seleccionar) {
        if (y != yAnterior) {
            if (yAnterior != -1) {
                rlutil::locate(53, 11 + yAnterior);
                cout << " ";
            }
            rlutil::locate(53, 11 + y);
            cout << (char)175;
            yAnterior = y;
        }
        y = flechaSeleccion(y, cantidadOpciones, seleccionar);
    }

    return y;
}

int mostrarMenuMovimientoStock(){
    int y = 0;
    const int cantidadOpciones = 5;
    bool seleccionar = false;
    int yAnterior = -1;

    rlutil::cls();
    rlutil::locate(50, 10); cout << "--- MENU MOVIMIENTO STOCK ---";
    rlutil::locate(55, 11); cout << " HISTORIAL";
    rlutil::locate(55, 12); cout << " ELIMINAR MOVIMIENTO";
    rlutil::locate(55, 13); cout << " BUSCAR POR ID";
    rlutil::locate(55, 14); cout << " ATRAS";

    while (!seleccionar) {
        if (y != yAnterior) {
            if (yAnterior != -1) {
                rlutil::locate(53, 11 + yAnterior);
                cout << " ";
            }
            rlutil::locate(53, 11 + y);
            cout << (char)175;
            yAnterior = y;
        }
        y = flechaSeleccion(y, cantidadOpciones, seleccionar);
    }

    return y;
}

long long ValidarDocumentoSegunTipo(int tipo) {
   rlutil::showcursor();
    Cliente c;
    int documento;
    long long documentoLargo;

    switch(tipo) {
        case 1:
            while(true) {
                documento = PedirEnteroValido("DNI: ");
                if(c.setDni(documento)) break;
                std::cout << "DNI invalido\n";
            }
            return documento;
            break;
        case 2:
            while(true) {
                documentoLargo = PedirEnteroValidoLargo("CUIT: ");
                if(c.setCuit(documentoLargo)) break;
                std::cout << "CUIT invalido\n";
            }
            return documentoLargo;
            break;
        default:
            std::cout << "Tipo invalido.\n";
            system("pause");
            return -1;
    }

    return documento;
}

// MENUS LOGICOS

int menuLogicoDatosBase(){
    rlutil::showcursor();
    int opcion;

    do {
        opcion = mostrarDatosBase();

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
                menuLogicoProveedores();
                system("pause");
                break;

            case 3:
                menuLogicoEmpleados();
                break;
            case 4:
                menuLogicoTiposEquipo();
                break;
            case 5:
                cout << endl << "Volviendo...\n";
                return 0;

            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
                system("pause");
                break;
        }

    } while (opcion != 5);
    return 0;
}

int menuLogicoOperaciones(){
    rlutil::showcursor();
    int opcion;

    do {
        opcion = mostrarOperaciones();

        switch (opcion) {
            case 0:
                menuLogicoVentas();
                system("pause");
                break;

            case 1:
                menuLogicoCompras();
                system("pause");
                break;

            case 2:
                menuLogicoMovimientoStock();
                system("pause");
                break;
            case 3:
                cout << endl << " Volviendo...\n";
                return 0;

            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
                system("pause");
                break;
        }

    } while (opcion != 3);
    return 0;
}

int menuLogicoMovimientoStock(){
    rlutil::showcursor();
    int opcion;
    MovimientoStockArchivo msA;
    MovimientoStock ms;
    do {
        opcion = mostrarMenuMovimientoStock();
        switch(opcion){
            case 0: {
                system("cls");
                cout << "HISTORIAL: MOVIMIENTO DE STOCK \n";
                cout << "--------------------------\n";
                msA.listarRegistros();
                system("pause");
                break;
            }
            case 1: {
                system("cls");
                cout << "ELIMINAR MOVIMIENTO \n";
                cout << "--------------------------\n";
                msA.bajaLogica();
            }
            case 2:
                system("cls");
                cout << "BUSCAR POR ID \n";
                cout << "--------------------------\n";
                int id = PedirEnteroValido("ID: ");
                int pos = msA.buscarPorId(id);
                if(pos>=0){
                    MovimientoStock encontrado = msA.leerRegistro(pos);
                    encontrado.mostrar();
                    system("pause");
                }
        }
    } while(opcion!=3);
    return 0;
}

int menuLogicoCliente() {
    rlutil::showcursor();
    int opcion;
    ClienteArchivo cA;
    Cliente c;
    do {
        opcion = mostrarMenuCliente();

        switch (opcion) {
            case 0: {
                system("cls");
                cout << "Agregar cliente...\n";
                cout << "--------------------------\n";

                int tipo = PedirEnteroValido("Tipo cliente: 1. Particular / 2. Empresa: ");
                long long documento = ValidarDocumentoSegunTipo(tipo);
                if(documento > 0) {
                    cA.altaCliente(documento, tipo);
                }
                break;
            }
            case 1: {
                system("cls");
                cout << "Borrar cliente...\n";
                cout << "--------------------------\n";
                cA.bajaLogica();
                system("pause");
                break;
            }
            case 2: {
                system("cls");
                cout << "Reactivar cliente...\n";
                cout << "--------------------------\n";
                cA.listarDocumentosDadosDeBaja();
                int tipo = PedirEnteroValido("Tipo cliente: 1. Particular / 2. Empresa: ");
                long long documento = ValidarDocumentoSegunTipo(tipo);
                if(documento > 0) {
                    int exito = cA.reactivarCliente(documento);
                    switch(exito){
                        case 0:
                            cout << "Ya esta activo"<<endl;
                            break;
                        case 1:
                            cout << "Reactivado"<<endl;
                            break;
                        case -1:
                            cout << "Error al guardar"<<endl;
                            break;
                        case -2:
                            cout << "Cliente no encontrado"<<endl;
                            break;
                    }

                    system("pause");
                }
                break;
            }
            case 3: {
                system("cls");
                cout << "CLIENTES\n";
                cout << "---------------------------------\n";
                cA.listarRegistros();
                system("pause");
                break;
            }
            case 4: {
                system("cls");
                cout << "BUSCAR CLIENTE..." << endl;

                int opcion = PedirEnteroValido("1. POR DOCUMENTO / 2. POR NOMBRE / 3. POR APELLIDO: ");

                switch(opcion) {
                    case 1: {
                        cout << "BUSCANDO POR DOCUMENTO..." << endl;
                        int tipo = PedirEnteroValido("TIPO DE CLIENTE: 1. Particular / 2. Empresa: ");
                        long long documento = ValidarDocumentoSegunTipo(tipo);
                        if (documento > 0) {
                            int pos = cA.BuscarPorDocumento(documento);
                            if (pos >= 0){
                                Cliente encontrado = cA.leerRegistro(pos);
                                encontrado.mostrar();
                                system("pause");
                            } else { cout << "Cliente no encontrado." << endl; }
                        }
                        break;
                    }
                    case 2: {
                        char nombre[30];
                        cout << "BUSCANDO POR NOMBRE..." << endl;
                        cout << "Nombre: ";
                        cin.getline(nombre, 30);

                        if (strlen(nombre) > 0) {
                            cA.BuscarPorNombre(nombre);
                        } else {
                            cout << "Entrada vacía. Intente nuevamente." << endl;
                        }

                        system("pause");
                        break;
                    }

                    case 3: {
                        char apellido[30];
                        cout << "BUSCANDO POR APELLIDO..." << endl;
                        cout << "Apellido: ";
                        cin.getline(apellido, 30);

                        if (strlen(apellido) > 0) {
                            cA.BuscarPorApellido(apellido);
                        } else {
                            cout << "Entrada vacía. Intente nuevamente." << endl;
                        }

                        system("pause");
                        break;
                    }

                    default:
                        cout << "Opción inválida." << endl;
                        break;
                }

            }
            case 5:
                cout << "Volviendo...\n";
                break;
            default:
                cout << "Opcion invalida\n";
                system("pause");
        }
    } while (opcion != 5);

    return 0;
}

int menuLogicoProductos(){
    rlutil::showcursor();
    int opcion;
    ProductoArchivo pA;
    Producto p;

    do {
        opcion = mostrarMenuProductos();

        switch (opcion) {
            case 0: {
                system("cls");
                cout << "Agregar Producto...\n";
                cout << "--------------------------\n";
                pA.altaProducto();
                break;
            }
            case 1: {
                system("cls");
                cout << "Borrar producto...\n";
                pA.bajaLogica();
                system("pause");
                break;
            }
            case 2: {
                system("cls");
                cout << "PRODUCTOS\n";
                cout << "---------------------------------\n";
                pA.listarRegistros();
                system("pause");
                break;
            }
            case 3:  // VOLVER
                cout << "Volviendo...\n";
                break;
            default:
                cout << "Opcion invalida\n";
                system("pause");
        }
    } while (opcion != 3);

    return 0;
}

int menuLogicoVentas() {
    int opcion;
    VentaArchivo pV;

    do {
        opcion = mostrarMenuVentas();

        switch (opcion) {
            case 0: {
                system("cls");
                cout << "Agregar Venta...\n";
                cout << "--------------------------\n";
                int resultado = pV.altaVenta();
                switch(resultado){
                    case 1:  cout << "Compra registrada correctamente"; break;
                    case 0:  cout << "ERROR AL GUARDAR VENTA"; break;
                    case -1: cout << "ERROR: OPCION INVALIDA"; break;
                    case -2: cout << "ERROR: CLIENTE NO ENCONTRADO."; break;
                    case -3: cout << "ERROR: CLIENTE DADO DE BAJA"; break;
                    case -4: cout << "ERROR: NO SE PUDO REGISTRAR EL DETALLE O VENTA VACIA"; break;
                }
                system("pause");
                break;
            }
            case 1: {
                system("cls");
                cout << "Borrar venta...\n";
                int idVenta = PedirEnteroValido("INGRESE EL ID DE LA VENTA A BORRAR: ");
                bool ok = pV.bajaLogica(idVenta);
                cout << (ok ? "Baja realizada correctamente.\n" : "No se pudo dar de baja.\n");
                system("pause");
                break;
            }
            case 2: {
                system("cls");
                cout << "VENTAS REGISTRADAS\n";
                cout << "---------------------------------\n";
                pV.listarRegistros();
                system("pause");
                break;
            }
            case 3: {
                system("cls");
                cout << "Reactivar venta...\n";
                int id = PedirEnteroValido("INGRESE EL ID DE LA VENTA A REACTIVAR: ");
                int r = pV.reactivarVenta(id);
                switch (r) {
                    case 1:  cout << "Venta reactivada correctamente.\n"; break;
                    case 0:  cout << "La venta ya estaba activa.\n"; break;
                    case -1: cout << "Venta no encontrada.\n"; break;
                    case -2: cout << "Error al guardar la modificación.\n"; break;
                }
                system("pause");
                break;
            }
            case 4: {
                system("cls");
                cout << "Buscar venta con mayor importe por anio\n";
                cout << "--------------------------------------\n";
                VentaArchivo Varch;
                Varch.BuscarMayorImportePorAnio();
                system("pause");
                break;
            }
            case 5:{
                system("cls");
                cout << "Buscar recaudacion anual\n";
                cout << "--------------------------------------\n";
                VentaArchivo Varch;
                int anio = PedirEnteroValido("Anio: ");
                if (anio > 2000 && anio < 2999) {
                    float total = Varch.recaudacionAnual(anio);
                    if (total >= 0) {
                        cout << "Recaudacion del anio " << anio << ": $" << total << endl;
                    } else {
                        cout << "Error al abrir el archivo de ventas.\n";
                    }
                } else {
                    cout << "Anio invalido.\n";
                }
                system("pause");
                break;
            }
            case 6: {
                system("cls");
                cout << "BUSCAR RECAUDACION POR CLIENTE\n";
                cout << "--------------------------------------\n";
                VentaArchivo Varch;
                int tipo = PedirEnteroValido("Tipo cliente: 1. Particular / 2. Empresa: ");
                long long documento = ValidarDocumentoSegunTipo(tipo);
                if(documento>0){
                    float total = Varch.recaudacionPorCliente(documento);
                    if (total >= 0) {
                        cout << "Recaudacion total del cliente con ID " << documento << ": $" << total << endl;
                    } else {
                        cout << "Error al abrir el archivo de ventas.\n";
                    }
                } else {
                    cout << "ID de cliente invalido.\n";
                }
                system("pause");
                break;
            }
            case 7:
                cout << "Volviendo...\n";
                break;
            default:
                cout << "Opcion invalida\n";
                system("pause");
        }
    } while (opcion != 7);

    return 0;
}

int menuLogicoCompras() {
    int opcion;
    CompraArchivo cArch;

    do {
        opcion = mostrarMenuCompras();

        switch (opcion) {
            case 0: {
                system("cls");
                cout << "Agregar compra...\n";
                cout << "--------------------------\n";
                int resultado = cArch.altaCompra();
                switch(resultado){
                    case 0: cout << "ERROR DESCONOCIDO"; break;
                    case 1: cout << "Compra registrada correctamente"; break;
                    case -1: cout << "ERROR: PROVEEDOR NO REGISTRADO"; break;
                    case -2: cout << "ERROR: PROVEEDOR INACTIVO"; break;
                    case -3: cout << "ERROR: ERROR AL CARGAR DETALLE"; break;
                }
                system("pause");
                break;
            }
            case 1: {
                system("cls");
                cout << "Borrar compra...\n";
                int idCompra = PedirEnteroValido(
                    "INGRESE EL ID DE LA COMPRA A BORRAR: "
                );
                bool ok = cArch.bajaLogica(idCompra);
                cout << (ok ? "Baja realizada correctamente.\n"
                            : "No se pudo dar de baja.\n");
                system("pause");
                break;
            }
            case 2: {
                system("cls");
                cout << "COMPRAS REGISTRADAS\n";
                cout << "---------------------------------\n";
                cArch.listarRegistros();
                system("pause");
                break;
            }
            case 3: {
                system("cls");
                cout << "GASTO ANUAL\n";
                cout << "---------------------------------\n";
                /*int anio = PedirEnteroValido("Anio: ");
                if (anio > 2000 && anio < 2999) {
                    float total = cArch.gastoAnual(anio);
                    if (total >= 0) {
                        cout << "Gasto total del anio "
                             << anio << ": $" << total << endl;
                    } else {
                        cout << "Error al abrir el archivo de compras.\n";
                    }
                } else {
                    cout << "Anio invalido.\n";
                }
                system("pause");*/
                break;
            }
            case 4: {
                system("cls");
                cout << "COMPRAS POR EMPLEADO\n";
                cout << "---------------------------------\n";
                /*int idEmpleado = PedirEnteroValido("ID del empleado: ");
                cArch.listarComprasPorEmpleado(idEmpleado);
                system("pause");*/
                break;
            }
            case 5:
                cout << "Volviendo...\n";
                break;
        }

    } while (opcion != 5);

    return 0;
}

int menuLogicoProveedores() {
    rlutil::showcursor();
    ProveedorArchivo pArch;
    int opcion;

    do {
        opcion = mostrarMenuProveedores();
        rlutil::cls();

        switch (opcion) {
        case 0: {
            std::cout << "--- ALTA PROVEEDOR ---\n";
            int res = pArch.altaProveedor();
            if (res == 1)       std::cout << "Proveedor cargado correctamente.\n";
            else if (res == 0)  std::cout << "El proveedor ya existe y esta activo.\n";
            else if (res == -2) std::cout << "El proveedor existia pero estaba dado de baja.\n";
            else                std::cout << "Error al guardar proveedor.\n";
            system("pause");
            break;
        }
        case 1: {
            std::cout << "--- LISTADO DE PROVEEDORES ACTIVOS ---\n";
            if (!pArch.listarRegistros()) {
                std::cout << "No se pudo abrir el archivo o no hay proveedores.\n";
            }
            system("pause");
            break;
        }
        case 2: {
            std::cout << "--- BAJA LOGICA DE PROVEEDOR ---\n";
            pArch.bajaLogica();
            system("pause");
            break;
        }
        case 3: {
            std::cout << "--- REACTIVAR PROVEEDOR ---\n";
            int id;
            std::cout << "INGRESE ID DE PROVEEDOR A REACTIVAR: ";
            std::cin >> id;
            std::cin.ignore();

            int res = pArch.reactivarProveedor(id);
            if (res == 1)       std::cout << "Proveedor reactivado correctamente.\n";
            else if (res == 0)  std::cout << "El proveedor ya estaba activo.\n";
            else if (res == -1) std::cout << "Proveedor no encontrado.\n";
            else                std::cout << "No se pudo reactivar el proveedor.\n";

            system("pause");
            break;
        }
        case 4: {
            std::cout << "--- BUSCAR PROVEEDOR POR NOMBRE ---\n";
            char nombre[50];
            std::cout << "NOMBRE: ";

            std::cin.getline(nombre, 50);

            int pos = pArch.buscarPorNombre(nombre);
            if (pos >= 0) {
                Proveedor prov = pArch.leerRegistro(pos);
                prov.mostrar();
            } else if (pos == -1) {
                std::cout << "No se encontro un proveedor activo con ese nombre.\n";
            } else {
                std::cout << "Error al abrir archivo de proveedores.\n";
            }

            system("pause");
            break;
        }
        case 5:
            cout << "Volviendo...\n";
            break;
        }
    } while (opcion != 5);

    return 0;
}

int menuLogicoTiposEquipo() {
    rlutil::showcursor();
    TiposDeEquipoArchivo archTipos;

    int opcion;
    do {
        opcion = mostrarMenuTiposEquipo();
        rlutil::cls();

        switch (opcion) {
            case 0: {
                cout << "TIPOS DE EQUIPO;" << endl;
                cout << "------------------------------\n";
                archTipos.listarTodos();
                system("pause");
                break;
            }
            case 1: {
                cout << "TIPOS DE EQUIPO (ACTIVOS)\n";
                cout << "------------------------------\n";
                archTipos.listarActivos();
                system("pause");
                break;
            }
            case 2: {
                cout << "CAMBIAR ESTADO DE TIPO DE EQUIPO\n";
                cout << "--------------------------------\n";
                archTipos.listarTodos();

                int id = PedirEnteroValido("CODIGO DEL TIPO A CAMBIAR: ");

                int pos = archTipos.buscarPorId(id);
                if (pos < 0) {
                    cout << "No existe ese codigo.\n";
                    system("pause");
                    break;
                }

                TiposDeEquipo te = archTipos.leerRegistro(pos);

                cout << "\nSeleccionado: " << te.getDescripcion()
                     << " | Estado actual: " << (te.getEstado() ? "ACTIVO" : "INACTIVO") << "\n";

                int op = PedirEnteroValido("1) Activar  2) Desactivar: ");
                if (op == 1) te.setEstado(true);
                else if (op == 2) te.setEstado(false);
                else {
                    cout << "Opcion invalida.\n";
                    system("pause");
                    break;
                }

                int ok = archTipos.modificarRegistro(te, pos);
                if (ok == 1) cout << "Estado actualizado.\n";
                else cout << "No se pudo guardar.\n";

                system("pause");
                break;
            }
            case 3:
                cout << "Volviendo...\n";
                break;
        }

    } while (opcion != 3);

    return 0;
}

int menuLogicoEmpleados() {
    rlutil::showcursor();
    EmpleadoArchivo arch;
    int opcion;

    do {
        opcion = mostrarMenuEmpleados();
        rlutil::cls();

        switch (opcion) {
            case 0: {
                cout << "--- ALTA EMPLEADO ---\n";
                arch.altaEmpleado();
                cout << "CLIENTE CARGADO CORRECTAMENTE" << endl;
                system("pause");
                break;
            }
            case 1: {
                cout << "--- BAJA LOGICA EMPLEADO ---\n";
                int id = PedirEnteroValido("ID EMPLEADO: ");
                arch.bajaLogica(id);
                system("pause");
                break;
            }
            case 2: {
                cout << "--- REACTIVAR EMPLEADO ---\n";
                int id = PedirEnteroValido("ID EMPLEADO: ");
                arch.reactivarEmpleado(id);
                system("pause");
                break;
            }
            case 3: {
                cout << "--- EMPLEADOS ACTIVOS ---\n";
                arch.listarEmpleados();
                system("pause");
                break;
            }
            case 4: {
                cout << "--- TODOS LOS EMPLEADOS ---\n";
                arch.listarEmpleados();
                system("pause");
                break;
            }
            case 5:
                cout << "Volviendo...\n";
                break;
            default:
                cout << "Opcion invalida\n";
                system("pause");
        }

    } while (opcion != 5);

    return 0;
}
