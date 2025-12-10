#pragma once
#include <iostream>

class Cliente {
private:
    int _tipoCliente;
    long long _documento;
    char _nombre[30];
    char _apellido[30];
    char _numeroTelefono[20];
    char _correoElectronico[50];
    char _direccion[50];
    bool _estado;

public:
    Cliente();
    void cargar(long long documento, int tipo);
    void mostrar();
    /// getters
    int getTipoCliente();
    long long getDocumento();
    char *getNombre();
    char *getApellido();
    char *getNumeroTelefono();
    char *getCorreoElectronico();
    char *getDireccion();
    bool getEstado();
    std::string getTipoClienteStr() const;
    std::string getEstadoStr();
    //setters
    bool setTipoCliente(int tipoCliente);
    bool setDni(int dni);
    bool setCuit(long long cuit);
    bool setNombre(char *nombre);
    bool setApellido(char *apellido);
    bool setNumeroTelefono(char *numeroTelefono);
    bool setCorreoElectronico(char *correoElectronico);
    bool setDireccion(char *direccion);
    bool setEstado(bool estado);
};
