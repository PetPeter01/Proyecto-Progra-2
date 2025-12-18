#pragma once
#include "Proveedor.h"
#include <cstring>

class ProveedorArchivo {
private:
    char _nombreArchivo[30];
    int  tamanioRegistro;

public:
    ProveedorArchivo(const char* nombreArchivo = "proveedores.dat") {
        strcpy(_nombreArchivo, nombreArchivo);
        tamanioRegistro = sizeof(Proveedor);
    }

    int  altaProveedor();
    int getProximoId();

    int  agregarRegistro(Proveedor reg);
    bool listarRegistros();
    Proveedor leerRegistro(int pos);
    bool bajaLogica();
    int  modificarRegistro(Proveedor reg, int pos);
    int  buscarPorId(int idProveedor);
    int  buscarPorNombre(const char* nombreBuscado);
    int  reactivarProveedor(int idProveedor);
};
