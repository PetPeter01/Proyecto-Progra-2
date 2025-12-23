#pragma once
#include <cstring>
#include "DetalleCompra.h"
#include "Fecha.h"

class DetalleCompraArchivo {
private:
    char _nombreArchivo[30];
    int  tamanioRegistro;

public:
    DetalleCompraArchivo(const char* nombreArchivo = "detallesCompras.dat") {
        std::strcpy(_nombreArchivo, nombreArchivo);
        tamanioRegistro = sizeof(DetalleCompra);
    }

    float altaDetalle(int idCompra, Fecha fecha);
    int getProximoId();
    int   agregarRegistro(DetalleCompra reg);
    int   listarPorCompra(int idCompra);
    float totalPorCompra(int idCompra);
    int puedeAnularCompra(int idCompra);
    int revertirCompra(int idCompra, Fecha fecha);


};
