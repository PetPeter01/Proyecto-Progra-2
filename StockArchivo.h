#pragma once
#include "Stock.h"
#include "Fecha.h"

class StockArchivo {
private:
    char _nombreArchivo[30];
    int tamanioRegistro;

public:
    StockArchivo(const char* nombre = "Stock.dat");

    int buscarPorIdProducto(int idProducto);
    Stock leerRegistro(int pos);
    int agregarRegistro(Stock reg);
    int modificarRegistro(Stock reg, int pos);

    int getStock(int idProducto);
    bool sumarStock(int idProducto, int cantidad, Fecha fecha);
    bool restarStock(int idProducto, int cantidad, Fecha fecha);
};


