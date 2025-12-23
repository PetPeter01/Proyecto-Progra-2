#pragma once
#include <cstring>
#include "Venta.h"

class VentaArchivo {
private:
    char _nombreArchivo[30];
    int tamanioRegistro;

public:
    VentaArchivo(const char *nombreArchivo = "ventas.dat") {
         std::strcpy(_nombreArchivo, nombreArchivo);
        tamanioRegistro=sizeof(Venta);
    };

    int altaVenta();
    bool agregarRegistro(Venta reg);
    Venta leerRegistro(int pos);
    int modificarRegistro(Venta reg, int pos);
    int  contarRegistros();
    bool listarRegistros();
    int generarIdVenta();
    int ModificarRegistro(Venta reg, int pos);
    int  reactivarVenta(int idVenta);
    int bajaLogica(int id);

    int buscarPorId(int idVenta);
    void BuscarMayorImportePorAnio();
    float recaudacionAnual(int anio);
    float recaudacionPorCliente(long long idCliente);
    float recaudacionPorEmpleado(int idEmpleado);
};
