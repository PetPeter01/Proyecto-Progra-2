#pragma once
#include <iostream>

class Stock {
private:
    int _idProducto;
    int _cantidad;
public:
    Stock();
    int getIdProducto();
    int getCantidad();

    void setIdProducto(int id);
    void setCantidad(int cant);

};
