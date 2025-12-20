#include "Compra.h"
#include "FuncionesGenerales.h"
#include <iostream>
#include <cstring>

using namespace std;

int Compra::ultimoId=0;

Compra::Compra() {
    _idCompra    = 0;
    _idProveedor = 0;
    _idEmpleado  = 0;
    _importe     = 0.0f;
    _estado      = false;
}

void Compra::cargar(int idCompra, int idProveedor, int idEmpleado, float importe) {
    setIdCompra(idCompra);
    setIdProveedor(idProveedor);
    setIdEmpleado(idEmpleado);
    setImporte(importe);

    cout << "FECHA DE COMPRA:\n";
    Fecha f;
    f.cargar();
    setFechaCompra(f);

    setEstado(true);
}

void Compra::mostrar() {
    cout << "ID Compra: "      << _idCompra               << '\n';
    cout << "ID Proveedor: "   << _idProveedor            << '\n';
    cout << "ID Empleado: "    << _idEmpleado             << '\n';
    cout << "Fecha: "          << _fechaCompra.toString() << '\n';
    cout << "Importe: $"       << _importe                << '\n';
    cout << "Estado: "<< getEstadoStr()         << "\n";
    cout << "--------------------------------\n";
}

// Getters
int         Compra::getIdCompra()      { return _idCompra; }
int         Compra::getIdProveedor()   { return _idProveedor; }
int         Compra::getIdEmpleado()    { return _idEmpleado; }
Fecha       Compra::getFechaCompra()   { return _fechaCompra; }
float       Compra::getImporte()       { return _importe; }
bool        Compra::getEstado()        { return _estado; }

std::string Compra::getEstadoStr() {
    return _estado ? "Activa" : "Eliminada";
}

// Setters
void Compra::setIdCompra(int v)      { _idCompra = v; }
void Compra::setIdProveedor(int v)   { _idProveedor = v; }
void Compra::setIdEmpleado(int v)    { _idEmpleado = v; }
void Compra::setFechaCompra(Fecha f) { _fechaCompra = f; }
void Compra::setImporte(float v)     { _importe = v; }


void Compra::setEstado(bool v) {
    _estado = v;
}

