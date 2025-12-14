#pragma once

class TipoEquipo {
private:
    int _idTipoEquipo;
    char detalle[50];
    bool estado;

public:

    // setters
    void setId(int id);
    void setDetalle(char* detalle);
    void setEstado(bool detalle);

    // getters

    int getId();
    char* getDetalle();
    bool getEstado();


};
