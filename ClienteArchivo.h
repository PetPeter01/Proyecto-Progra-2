#pragma once
#include <cstring>
#include "Cliente.h"

class ClienteArchivo {
private:
    char _nombreArchivo[30];
    const int tamanioRegistro;

public:
    ClienteArchivo(const char* nombreArchivo = "cliente.dat")
        : tamanioRegistro(sizeof(Cliente)) {
        strcpy(_nombreArchivo, nombreArchivo);
    }

    // ALTAS
    int altaCliente(long long dni, int tipo);
    int agregarRegistro(Cliente cliente);
    bool listarRegistros();
    Cliente leerRegistro(int pos);
    int reactivarCliente(long long documento);

    // BAJAS
    bool bajaLogica();
    void listarDocumentosDadosDeBaja();

    // UTILIDADES
    int generarIdCliente();
    int contarRegistros();
    int modificarRegistro(Cliente reg, int pos);
    int BuscarPorDocumento(long long documentoBuscado);
    void BuscarPorNombre(const char* nombreBuscado);
    void BuscarPorApellido(const char* apellidoBuscado);
    int BuscarPorId(int idBuscado);
};
