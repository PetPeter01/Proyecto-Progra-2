#pragma once
#include "MovimientoStock.h"

class MovimientoStockArchivo{
private:
    char _nombreArchivo[30];
    int tamanioRegistro;

public:
    MovimientoStockArchivo(const char* nombreArchivo = "MovimientosStock.dat") {
        strcpy(_nombreArchivo, nombreArchivo);
        tamanioRegistro = sizeof(MovimientoStock);
    }

    int getProximoId();
    int contarRegistros();
    int agregarRegistro(MovimientoStock reg);
    bool listarRegistros();
    MovimientoStock leerRegistro(int pos);
    int buscarPorId(int idMovimientoStock);
    bool bajaLogica();
    int modificarRegistro(MovimientoStock reg, int pos);
};
