#include "Venta.h"
#include "FuncionesGenerales.h"
#include <iostream>

using namespace std;

Venta::Venta() {
    _idVenta = 0;
    _idCliente = 0;
    _importeTotal = 0.0f;
    _formaPago = 0;
    _estado = false;
}

void Venta::cargar(int idVenta, long long idCliente, float importeTotal) {
    setIdVenta(idVenta);
    setIdCliente(idCliente);
    setImporteTotal(importeTotal);

    cout << "FECHA: ";
    Fecha f;
    f.cargar();
    setFechaVenta(f);

    while (true) {
        cout << "FORMA DE PAGO:\n"
             << "1) BILLETERA VIRTUAL\n"
             << "2) TARJETA DE CREDITO\n"
             << "3) TARJETA DE DEBITO\n";
        int fp = PedirEnteroValido("INGRESAR: ");
        if (setFormaPago(fp)) break;
        cout << "Opcion invalida.\n";
    }
    setEstado(true);
}

void Venta::mostrar() {
    cout << " ID Venta: "  << _idVenta            << '\n'
         << " Cliente: "   << _idCliente          << '\n'
         << " Fecha: "     << _fechaVenta.toString() << '\n'
         << " Importe: "   << _importeTotal       << '\n'
         << " Pago: "      << getFormaPago()      << '\n';
}


int Venta::getIdVenta(){ return _idVenta; }
long long Venta::getIdCliente() { return _idCliente; }
Fecha Venta::getFechaVenta(){ return _fechaVenta; }
float Venta::getImporteTotal(){ return _importeTotal; }
std::string Venta::getFormaPago() {
    switch (_formaPago) {
        case 1: return "Billetera virtual";
        case 2: return "Tarjeta de credito";
        case 3: return "Tarjeta de debito";
        default: return "Desconocido";
    }
}
bool      Venta::getEstado()         { return _estado; }


void  Venta::setIdVenta(int v)               { _idVenta = v; }
void  Venta::setIdCliente(long long v)       { _idCliente = v; }
void  Venta::setFechaVenta(Fecha v)          { _fechaVenta = v; }
void  Venta::setImporteTotal(float v)        { _importeTotal = v; }
bool  Venta::setFormaPago(int v) {
    if (v >= 1 && v <= 3) { _formaPago = v; return true; }
    return false;
}
void  Venta::setEstado(bool v)               { _estado = v; }
