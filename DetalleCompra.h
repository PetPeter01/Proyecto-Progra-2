#pragma once

class DetalleCompra {
private:
    int   _idDetalleCompra;
    int   _idCompra;
    int   _idProducto;
    int   _cantidad;
    float _costoUnitario;
    float _subtotal;

public:
    DetalleCompra();

    void cargar(int idDetalle, int idCompra, int idProducto);
    void mostrar();

    // Setters
    void setIdDetalleCompra(int id);
    void setIdCompra(int id);
    void setIdProducto(int id);
    bool setCantidad(int cant);
    bool setCostoUnitario(float costo);
    bool setSubtotal(float subtotal);

    // Getters
    int   getIdDetalleCompra();
    int   getIdCompra();
    int   getIdProducto();
    int   getCantidad();
    float getCostoUnitario();
    float getSubtotal();
};
