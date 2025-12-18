#pragma once
#include <iostream>
#include <cstring>
#include <string>

class Producto {
private:
    int _idProducto;
    int _idTipoEquipo;
    float _precio;
    char _descripcion[50];
    char _marca[30];
    bool _estado;

    static int ultimoId;

public:
    Producto();
    void cargar(int idTipoEquipo, float precio);

    void mostrar();


    int getIdProducto();
    int getIdTipoEquipo();
    int getStock();
    float getPrecio();
    char* getDescripcion();
    char* getMarca();
    bool getEstado();

    std::string getTipoEquipoStr();
    std::string getEstadoStr();


    void setIdProducto(int id);
    bool setIdTipoEquipo(int idTipo);
    bool setStock(int s);
    bool setPrecio(float precio);
    bool setDescripcion(char* desc);
    bool setMarca(char* marca);
    void setEstado(bool estado);
};
