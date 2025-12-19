#pragma once
#include <string>
using namespace std;

int flechaSeleccion(int y, int cantidadOpciones, bool &seleccionar);

int mostrarMenuPrincipal();
int mostrarMenuCliente();
int mostrarMenuProductos();
int mostrarMenuTiposEquipo();
int mostrarMenuVentas();
int mostrarMenuProveedores();
int mostrarMenuCompras();
int mostrarMenuEmpleados();

int menuLogicoEmpleados();
int menuLogicoTiposEquipo();
int menuLogicoCliente();
int menuLogicoProductos();
int menuLogicoVentas();
int menuLogicoProveedores();
int menuLogicoCompras();

long long ValidarDocumentoSegunTipo(int tipo);


