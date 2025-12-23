#pragma once
#include <string>
#include "Fecha.h"

class Venta {
private:
    int        _idVenta;
    int  _idCliente;
    int _idEmpleado;
    Fecha      _fechaVenta;
    float      _importeTotal;
    int        _formaPago;
    bool       _estado;

public:
    Venta();


    void cargar(int idEmpleado, int idVenta, int idCliente, float importeTotal);
    void mostrar();

    int        getIdVenta();
    int getIdEmpleado();
    int  getIdCliente();
    Fecha      getFechaVenta();
    float      getImporteTotal();
    std::string getFormaPago();
    bool       getEstado();


    void setIdVenta(int v);
    void setIdEmpleado(int v);
    void setIdCliente(int v);
    void setFechaVenta(Fecha v);
    void setImporteTotal(float v);
    bool setFormaPago(int v);
    void setEstado(bool v);
};
