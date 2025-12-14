#include "DetalleCompra.h"
#include "FuncionesGenerales.h"
#include <iostream>

using namespace std;

DetalleCompra::DetalleCompra() {
    _idDetalleCompra = 0;
    _idCompra        = 0;
    _idProducto      = 0;
    _cantidad        = 0;
    _costoUnitario   = 0.0f;
}

void DetalleCompra::cargar(int idDetalle, int idCompra, int idProducto) {
    setIdDetalleCompra(idDetalle);
    setIdCompra(idCompra);
    setIdProducto(idProducto);

    while (true) {
        int cant = PedirEnteroValido("CANTIDAD COMPRADA: ");
        if (setCantidad(cant)) break;
        cout << "Cantidad invalida (debe ser > 0).\n";
    }

    while (true) {
        cout << "COSTO UNITARIO: ";
        float costo;
        cin >> costo;

        if (cin.fail() || !setCostoUnitario(costo)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Costo invalido.\n";
        } else {
            cin.ignore();
            break;
        }
    }
}

void DetalleCompra::mostrar() {
    cout << "ID Detalle Compra: " << _idDetalleCompra << endl;
    cout << "ID Compra: "        << _idCompra        << endl;
    cout << "ID Producto: "      << _idProducto      << endl;
    cout << "Cantidad: "         << _cantidad        << endl;
    cout << "Costo Unitario: $"  << _costoUnitario   << endl;
    cout << "Subtotal: $"        << (_cantidad * _costoUnitario) << endl;
    cout << "--------------------------------\n";
}

// Setters
void DetalleCompra::setIdDetalleCompra(int id) { _idDetalleCompra = id; }
void DetalleCompra::setIdCompra(int id)        { _idCompra = id; }
void DetalleCompra::setIdProducto(int id)      { _idProducto = id; }

bool DetalleCompra::setCantidad(int cant) {
    if (cant <= 0) return false;
    _cantidad = cant;
    return true;
}

bool DetalleCompra::setCostoUnitario(float costo) {
    if (costo <= 0) return false;
    _costoUnitario = costo;
    return true;
}

// Getters
int   DetalleCompra::getIdDetalleCompra() { return _idDetalleCompra; }
int   DetalleCompra::getIdCompra()        { return _idCompra; }
int   DetalleCompra::getIdProducto()      { return _idProducto; }
int   DetalleCompra::getCantidad()        { return _cantidad; }
float DetalleCompra::getCostoUnitario()   { return _costoUnitario; }
