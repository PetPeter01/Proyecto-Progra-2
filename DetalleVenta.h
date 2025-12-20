#pragma once
#include "Producto.h"

class DetalleVenta {
private:
    int _idDetalleVenta;
    int _idVenta;
    int _idProducto;
    int _cantidad;
    float _precioUnitario;
    float _subtotal;

public:
    DetalleVenta();

    int cargar(int idDetalle, int idVenta, int idProducto);
    void mostrar();
    void calcularSubtotal();

    // getters
    int getIdDetalle();
    int getIdVenta();
    int getIdProducto();
    int getCantidad();
    float getPrecioUnitario();
    float getSubtotal();

    // setters
    void setIdDetalle(int idDetalle);
    void setIdVenta(int idVenta);
    void setIdProducto(int idProducto);
    bool setCantidad(int cantidad);
    void setPrecioUnitario(float precioUnitario);

};
