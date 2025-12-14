#include "Proveedor.h"
#include "FuncionesGenerales.h"

#include <iostream>
#include <cstring>

using namespace std;

int Proveedor::_ultimoId = 0;

Proveedor::Proveedor(const char* nombre, const char* telefono, const char* email, const char* direccion) {

    _idProveedor = ++_ultimoId;

    std::strcpy(_nombre, nombre);
    std::strcpy(_telefono, telefono);
    std::strcpy(_email, email);
    std::strcpy(_direccion, direccion);

    _estado = true;
}

Proveedor::Proveedor() {
    _idProveedor = 0;
    std::strcpy(_nombre, "");
    std::strcpy(_telefono, "");
    std::strcpy(_email, "");
    std::strcpy(_direccion, "");
    _estado = false;
}

void Proveedor::cargar() {
    char nombre[50];
    char telefono[20];
    char email[50];
    char direccion[50];

    setIdProveedor(++_ultimoId);

    while (true) {
        cout << "NOMBRE DEL PROVEEDOR: ";
        cin.getline(nombre, 50);
        if (setNombre(nombre)) break;
        cout << "Nombre invalido. Solo letras y espacios.\n";
    }

    while (true) {
        cout << "TELEFONO: ";
        cin.getline(telefono, 20);
        int num;
        if (esEnteroValido(telefono, num)) {
            if (setTelefono(telefono)) break;
        }
        cout << "Telefono invalido. Debe contener solo numeros.\n";
    }

    while (true) {
        cout << "EMAIL: ";
        cin.getline(email, 50);
        if (setEmail(email)) break;
        cout << "Email invalido. Debe contener '@' y no estar vacio.\n";
    }

    while (true) {
        cout << "DIRECCION: ";
        cin.getline(direccion, 50);
        if (setDireccion(direccion)) break;
        cout << "Direccion invalida. No puede ser vacia.\n";
    }

    setEstado(true);
}

void Proveedor::mostrar() {
    cout << "ID Proveedor: " << _idProveedor << endl;
    cout << "Nombre: "      << _nombre      << endl;
    cout << "Telefono: "    << _telefono    << endl;
    cout << "Email: "       << _email       << endl;
    cout << "Direccion: "   << _direccion   << endl;
    cout << "Estado: "      << getEstadoStr() << endl;
    cout << "--------------------------------\n";
}

// Getters
int   Proveedor::getIdProveedor() { return _idProveedor; }
char* Proveedor::getNombre()      { return _nombre; }
char* Proveedor::getTelefono()    { return _telefono; }
char* Proveedor::getEmail()       { return _email; }
char* Proveedor::getDireccion()   { return _direccion; }
bool  Proveedor::getEstado()      { return _estado; }

std::string Proveedor::getEstadoStr() {
    if (_estado==1){
        return "activo";
    }
    return "eliminado";
}

// Setters
void Proveedor::setIdProveedor(int id) { _idProveedor = id; }

bool Proveedor::setNombre(const char* nombre) {
    if (nombre == nullptr || !esTextoValido(nombre)) return false;
    std::strcpy(_nombre, nombre);
    return true;
}

bool Proveedor::setTelefono(const char* telefono) {
    if (telefono == nullptr || std::strlen(telefono) == 0) return false;
    std::strcpy(_telefono, telefono);
    return true;
}

bool Proveedor::setEmail(const char* email) {
    if (email == nullptr) return false;
    if (std::strlen(email) == 0 || std::strchr(email, '@') == nullptr) {
        return false;
    }
    std::strcpy(_email, email);
    return true;
}

bool Proveedor::setDireccion(const char* direccion) {
    if (direccion == nullptr || std::strlen(direccion) == 0) return false;
    std::strcpy(_direccion, direccion);
    return true;
}

void Proveedor::setEstado(bool estado) {
    _estado = estado;
}
