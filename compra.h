#pragma once
#include "Fecha.h"
#include <string>

class Compra {
private:
    int   _idCompra;
    int   _idProveedor;
    int   _idEmpleado;
    Fecha _fechaCompra;
    float _importe;
    bool  _estado;

    static int ultimoId;

public:
    Compra();

    void cargar(int idProveedor, int idEmpleado, float importe);
    void mostrar();

    // Getters
    int getIdCompra();
    int getIdProveedor();
    int getIdEmpleado();
    Fecha getFechaCompra();
    float getImporte();
    bool getEstado();
    std::string getEstadoStr();

    // Setters
    void setIdCompra(int v);
    void setIdProveedor(int v);
    void setIdEmpleado(int v);
    void setFechaCompra(Fecha f);
    void setImporte(float v);
    void setEstado(bool v);
};


