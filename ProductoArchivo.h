#pragma once
#include "Producto.h"

class ProductoArchivo {
private:
    char _nombreArchivo[30];
    int tamanioRegistro;

public:
    ProductoArchivo(const char* nombreArchivo = "productos.dat") {
        strcpy(_nombreArchivo, nombreArchivo);
        tamanioRegistro = sizeof(Producto);
    }

    int altaProducto();
    int agregarRegistro(Producto reg);
    bool listarRegistros();
    Producto leerRegistro(int pos);
    bool bajaLogica();
    int modificarRegistro(Producto reg, int pos);
        int buscarPorId(int idProducto);
};
