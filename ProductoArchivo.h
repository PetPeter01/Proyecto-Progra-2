#pragma once
#include <iostream>
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
    int getProximoId();

    int agregarRegistro(Producto reg);
    std::string getTipoEquipoStr(Producto& p);
    bool listarRegistros();
    Producto leerRegistro(int pos);
    int contarRegistros();
    bool existeProducto(const char* descripcion, const char* marca);
    bool bajaLogica();
    int modificarRegistro(Producto reg, int pos);
    int buscarPorId(int idProducto);
};
