#include "DetalleVenta.h"
#include "FuncionesGenerales.h"
#include <iostream>

DetalleVenta::DetalleVenta() {
    _idVenta = 0;
    _idProducto = 0;
    _cantidad = 0;
    _subtotal = 0;
    _precioUnitario = 0;
}

void DetalleVenta::cargar(int idVenta, int idProducto){
    setIdVenta(idVenta);
    setIdProducto(idProducto);

    while(true){
        int cant = PedirEnteroValido("CANTIDAD: ");
        if(setCantidad(cant)){
            break;
        } else {
            std::cout << "Cantidad invalida" << std::endl;
        }
    }

}

void DetalleVenta::mostrar() {
    std::cout << "ID Producto: " << _idProducto << std::endl;
    std::cout << "Cantidad: " << _cantidad << std::endl;
    std::cout << "Precio Unitario: $" << _precioUnitario << std::endl;
    std::cout << "Subtotal: $" << getSubtotal() << std::endl;
}

void DetalleVenta::calcularSubtotal() {
    _subtotal = _cantidad * _precioUnitario;
}

/// getters
int DetalleVenta::getIdVenta() { return _idVenta; }
int DetalleVenta::getIdProducto() { return _idProducto; }
int DetalleVenta::getCantidad() { return _cantidad; }
float DetalleVenta::getPrecioUnitario() { return _precioUnitario; }
float DetalleVenta::getSubtotal() { return _subtotal; }

/// setters
void DetalleVenta::setIdVenta(int idVenta) { _idVenta = idVenta; }
void DetalleVenta::setIdProducto(int idProducto) { _idProducto = idProducto; }
bool DetalleVenta::setCantidad(int cantidad) {
    if(cantidad<0){
        return false;
    }
    _cantidad = cantidad;
    return true;
    }
void DetalleVenta::setPrecioUnitario(float precioUnitario) { _precioUnitario = precioUnitario; }
