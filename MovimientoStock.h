#pragma once
#include "Fecha.h"
#include <cstring>

class MovimientoStock {
private:
    int _idMovimiento;
    int _idProducto;
    int _cantidad;
    Fecha _fecha;
    char _tipoMovimiento[20];
    bool _estado;

public:
    MovimientoStock();

    void cargar(int idProducto, int cantidad, const char* tipo, Fecha fecha);
    void mostrar();

    int getIdMovimiento();
    int getIdProducto();
    int getCantidad();
    Fecha getFecha();
    char* getTipoMovimiento();
    bool getEstado();

    void setIdMovimiento(int id);
    void setIdProducto(int idProducto);
    bool setCantidad(int cantidad);
    void setFecha(Fecha fecha);
    void setTipoMovimiento(const char* tipo);
    void setEstado(bool estado);

    int getFactorMovimiento();
};
