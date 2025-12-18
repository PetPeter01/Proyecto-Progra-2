#pragma once
#include <cstring>
#include "Empleado.h"
class EmpleadoArchivo{
private:
    char _NombreArchivo[30];
    const int _TamanioRegistro;
public:
    EmpleadoArchivo(const char* NombreArchivo = "Empleado.dat")
        : _TamanioRegistro(sizeof(Empleado)) {
        strcpy(_NombreArchivo, NombreArchivo);
    }


    bool agregarRegistro(Empleado reg);
    Empleado leerRegistro(int pos);
    int contarRegistros();
   int BuscarPorDni(const char* dni);

    int GenerarProximoId();

   bool modificarRegistro(Empleado reg, int pos);
    bool altaEmpleado();
    void listarEmpleados();
    bool bajaLogica(int id);
    bool reactivarEmpleado(int id);
};



