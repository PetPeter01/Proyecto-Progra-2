#include "MovimientoStock.h"
#include "Fecha.h"
#include <iostream>
#include <cstring>

using namespace std;

MovimientoStock::MovimientoStock() {
    _idMovimiento = 0;
    _idProducto = 0;
    _cantidad = 0;
    strcpy(_tipoMovimiento, "");
    _estado = true;
}

void MovimientoStock::cargar(int idProducto, int cantidad, const char* tipo, Fecha fecha) {
    setIdProducto(idProducto);
    setCantidad(cantidad);
    setTipoMovimiento(tipo);

    setFecha(fecha);

    _estado = true;
}

void MovimientoStock::mostrar() {
    cout << "ID Movimiento: " << _idMovimiento << endl;
    cout << "ID Producto: " << _idProducto << endl;
    cout << "Cantidad: " << _cantidad << endl;
    cout << "Tipo: " << getTipoMovimiento() << endl;
    cout << "Fecha: " << _fecha.toString() << endl;
    cout << "--------------------------\n";
}

// Getters
int MovimientoStock::getIdMovimiento() { return _idMovimiento; }
int MovimientoStock::getIdProducto() { return _idProducto; }
int MovimientoStock::getCantidad() { return _cantidad; }
Fecha MovimientoStock::getFecha() { return _fecha; }
char* MovimientoStock::getTipoMovimiento() { return _tipoMovimiento; }
bool MovimientoStock::getEstado() { return _estado; }

// Setters
void MovimientoStock::setIdMovimiento(int id) { _idMovimiento = id; }
void MovimientoStock::setIdProducto(int idProducto) { _idProducto = idProducto; }

bool MovimientoStock::setCantidad(int cantidad) {
    if (cantidad > 0) {
        _cantidad = cantidad;
        return true;
    }
    return false;
}

void MovimientoStock::setFecha(Fecha fecha) { _fecha = fecha; }

void MovimientoStock::setTipoMovimiento(const char* tipo) {
    if (strcmp(tipo, "INGRESO") == 0 || strcmp(tipo, "EGRESO") == 0) {
        strcpy(_tipoMovimiento, tipo);
    }
}

void MovimientoStock::setEstado(bool estado) { _estado = estado; }

int MovimientoStock::getFactorMovimiento() {
    if (strcmp(_tipoMovimiento, "INGRESO") == 0) {
        return 1; // Aumenta stock
    } else if (strcmp(_tipoMovimiento, "EGRESO") == 0) {
        return -1; // Disminuye stock
    }
    return 0;
}
