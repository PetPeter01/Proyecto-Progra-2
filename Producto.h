#pragma once
#include <iostream>
#include <cstring>

class Producto {
private:
    int _idProducto;
    int _tipoEquipo;
    float _precio;
    char _descripcion[50];
    char _marca[30];
    bool _estado;

public:
    Producto();
    void cargar(int id);
    void mostrar();
    //getters
    int getIdProducto();
    char* getDescripcion();
    char* getMarca();
    int getTipoEquipo();
    float getPrecio();
    bool getEstado();

    std::string getTipoEquipoStr();
    std::string getEstadoStr();

    // Setters
    void setIdProducto(int id);
    bool setPrecio(float precio);
    void setDescripcion(char* desc);
    void setMarca(char* marca);
    bool setTipoEquipo(int tipoEquipo);
    void setEstado(bool estado);
};
