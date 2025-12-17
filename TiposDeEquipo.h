#pragma once
#include <cstring>
#include <string>

class TiposDeEquipo {
private:
    int  _idTiposDeEquipo;
    char _descripcion[30];
    bool _estado;

public:
    TiposDeEquipo();

    void mostrar() const;

    int getIdTiposDeEquipo() const;
    const char* getDescripcion() const;
    bool getEstado() const;
    std::string getEstadoStr() const;

    void setIdTiposDeEquipo(int id);
    void setDescripcion(const char* desc);
    void setEstado(bool estado);
};
