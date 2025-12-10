#pragma once
#include "Producto.h"

class DetalleVenta {
private:
    int _idVenta;
    int _idProducto;
    int _cantidad;
    float _precioUnitario;
    float _subtotal;

public:
    DetalleVenta();

    void cargar(int idVenta, int idProducto);
    void mostrar();
    void calcularSubtotal();

    // getters
    int getIdVenta();
    int getIdProducto();
    int getCantidad();
    float getPrecioUnitario();
    float getSubtotal();

    // setters
    void setIdVenta(int idVenta);
    void setIdProducto(int idProducto);
    bool setCantidad(int cantidad);
    void setPrecioUnitario(float precioUnitario);

};
