#pragma once
#include <cstring>
#include "Compra.h"

class CompraArchivo {
private:
    char _nombreArchivo[30];
    int  tamanioRegistro;

public:
    CompraArchivo(const char* nombreArchivo = "compras.dat") {
        std::strcpy(_nombreArchivo, nombreArchivo);
        tamanioRegistro = sizeof(Compra);
    }

    int   altaCompra();
    int getProximoId();
    bool  agregarRegistro(Compra reg);
    Compra leerRegistro(int pos);
    int   contarRegistros();
    bool  listarRegistros();
    int   generarIdCompra();
    int   ModificarRegistro(Compra reg, int pos);
    bool  bajaLogica(int idCompra);
    int   buscarPorId(int idCompra);
    int   reactivarCompra(int idCompra);
};
