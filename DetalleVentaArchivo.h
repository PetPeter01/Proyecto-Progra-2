#pragma once
#include <cstring>
#include "DetalleVenta.h"
#include "Fecha.h"

class DetalleVentaArchivo {
private:
    char _nombreArchivo[30];
    int tamanioRegistro;

public:
    DetalleVentaArchivo(const char *nombreArchivo = "detallesVentas.dat") {
        strcpy(_nombreArchivo, nombreArchivo);
        tamanioRegistro = sizeof(DetalleVenta);
    }

    float altaDetalle(int idVenta, Fecha fechaCompra);
    int agregarRegistro(DetalleVenta reg);
    int  listarPorVenta(int idVenta);
    float totalPorVenta(int idVenta);
};
