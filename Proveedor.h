#pragma once
#include <iostream>
#include <cstring>

class Proveedor {
private:
    int  _idProveedor;
    char _nombre[50];
    char _telefono[20];
    char _email[50];
    char _direccion[50];
    bool _estado;

public:
    Proveedor(int id, const char* nombre, const char* telefono, const char* email, const char* direccion);

    Proveedor();

    void cargar(int id);
    void mostrar();

    // Getters
    int   getIdProveedor();
    char* getNombre();
    char* getTelefono();
    char* getEmail();
    char* getDireccion();
    bool  getEstado();
    std::string getEstadoStr();

    // Setters
    void setIdProveedor(int id);
    bool setNombre(const char* nombre);
    bool setTelefono(const char* telefono);
    bool setEmail(const char* email);
    bool setDireccion(const char* direccion);
    void setEstado(bool estado);
};
