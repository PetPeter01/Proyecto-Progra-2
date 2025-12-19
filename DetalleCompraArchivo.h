#pragma once
#include <cstring>
#include "DetalleCompra.h"

class DetalleCompraArchivo {
private:
    char _nombreArchivo[30];
    int  tamanioRegistro;

public:
    DetalleCompraArchivo(const char* nombreArchivo = "detallesCompras.dat") {
        std::strcpy(_nombreArchivo, nombreArchivo);
        tamanioRegistro = sizeof(DetalleCompra);
    }

    float altaDetalle(int idCompra);
    int getProximoId();
    int   agregarRegistro(DetalleCompra reg);
    int   listarPorCompra(int idCompra);
    float totalPorCompra(int idCompra);
};
