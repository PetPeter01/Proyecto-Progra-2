#include "Producto.h"
#include "FuncionesGenerales.h"
#include <iostream>
#include <string.h>

using namespace std;


Producto::Producto() {
    _idProducto = 0;
    _idTipoEquipo = 0;
    _precio = 0;
    strcpy(_descripcion, "");
    strcpy(_marca, "");
    _estado = false;
}

void Producto::cargar(int idProducto, int idTipoEquipo, float precio){
    setIdProducto(idProducto);
    setIdTipoEquipo(idTipoEquipo);
    setPrecio(precio);
    char marca[30], desc[50];

    while (true){
        cout << "DESCRIPCION: ";
        cin.getline(desc, 50);

        if (setDescripcion(desc)) {
            break;
        }
        cout << "Descripcion invalida.\n";
    }

    while (true){
        cout << "MARCA: ";
        cin.getline(marca, 30);

        if (setMarca(marca)) {
            break;
        }
        cout << "Marca invalida.\n";
    }

    setEstado(true);
}

void Producto::mostrar() {
    cout << "ID Producto: " << _idProducto << endl;
    cout << "Estado: " << getEstadoStr() << endl;
    cout << "Precio: " << _precio << endl;
    cout << "Descripcion: " << _descripcion << endl;
    cout << "Marca: " << _marca << endl;
}


int Producto::getIdProducto() { return _idProducto; }
int Producto::getIdTipoEquipo() { return _idTipoEquipo; }
float Producto::getPrecio() { return _precio; }
char* Producto::getDescripcion() { return _descripcion; }
char* Producto::getMarca() { return _marca; }
bool Producto::getEstado() { return _estado; }

std::string Producto::getEstadoStr() {
    return _estado ? "Activo" : "Desactivado";
}


void Producto::setIdProducto(int idProducto) { _idProducto = idProducto; }

bool Producto::setIdTipoEquipo(int idTipo) {
    if (idTipo > 0) {
        _idTipoEquipo = idTipo;
        return true;
    }
    return false;
}

bool Producto::setStock(int s) {
    if (s < 0) return false;
    return true;
}

bool Producto::setPrecio(float precio) {
    if (precio <= 0) return false;
    _precio = precio;
    return true;
}

bool Producto::setDescripcion(char* desc) {
    if (desc == nullptr || strlen(desc) == 0) return false;

    strncpy(_descripcion, desc, sizeof(_descripcion) - 1);
    _descripcion[sizeof(_descripcion) - 1] = '\0';
    return true;
}


bool Producto::setMarca(char* marca) {
    if (marca == nullptr || strlen(marca) == 0) {
        return false;
    }

    for (int i = 0; marca[i] != '\0'; i++) {
        if (!isalnum(marca[i]) && marca[i] != ' ') {
            return false;
        }
    }

    strncpy(_marca, marca, sizeof(_marca) - 1);
    _marca[sizeof(_marca) - 1] = '\0';

    return true;
}


void Producto::setEstado(bool estado) { _estado = estado; }
