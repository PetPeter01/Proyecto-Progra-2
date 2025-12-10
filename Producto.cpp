#include "Producto.h"
#include "FuncionesGenerales.h"

#include <iostream>
#include <string.h>

Producto::Producto() {
    _idProducto = 0;
    _tipoEquipo = 0;
    _precio = 0;
    strcpy(_descripcion, "");
    strcpy(_marca, "");
    _estado = false;
}

void Producto::cargar(int id) {

    char descripcion[50], marca[30];
    int tipo;
    float precio;

    setIdProducto(id);

    while (true) {
        std::cout << "TIPO DE EQUIPO: " << std::endl;
        std::cout << "1. PC" << std::endl;
        std::cout << "2. PORTATIL" << std::endl;
        std::cout << "3. PERIFERICO" << std::endl;
        std::cout << "4. COMPONENTE" << std::endl;
        std::cout << "Seleccione una opcion: ";
        tipo = PedirEnteroValido("INGRESE UNA OPCION: ");

        if (setTipoEquipo(tipo)) {
            break;
        } else {
            std::cout << "Opcion invalida. Ingrese un valor entre 1 y 4.\n";
        }
    }

    while (true) {
    std::cout << "INGRESE EL PRECIO: ";
    std::cin >> precio;

    if (std::cin.fail() || !setPrecio(precio)){
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Precio invalido.\n";
    } else {
        break;
        }
    }
    while (true) {
        cin.ignore();
        std::cout << "INGRESE DESCRIPCION DEL PRODUCTO: ";
        std::cin.getline(descripcion, 50);
        if (strlen(descripcion) > 0) {
            setDescripcion(descripcion);
            break;
        } else {
            std::cout << "Descripcion invalida. Intente nuevamente.\n";
        }
    }

    while (true) {
        std::cout << "INGRESE MARCA: ";
        std::cin.getline(marca, 30);
        if (strlen(marca) > 0) {
            setMarca(marca);
            break;
        } else {
            std::cout << "Marca invalida. Intente nuevamente.\n";
        }
    }

    setEstado(true);
    std::cin.ignore();
}

void Producto::mostrar(){
    std::cout << "ID Producto: " << _idProducto << std::endl;
    std::cout << "Tipo Equipo: " << getTipoEquipoStr() << std::endl;
    std::cout << "Precio: " << _precio << std::endl;
    std::cout<< "Descripcion: " << _descripcion << std::endl;
    std::cout<< "Marca: " << _marca << std::endl;
    std::cout<< "Estado: " << getEstadoStr() << std::endl;

    std::cout << "--------------------------------"<< std::endl;
}

// --- Getters ---
int Producto::getIdProducto() { return _idProducto; }
float Producto::getPrecio() {return _precio; }
char* Producto::getDescripcion() { return _descripcion; }
int Producto::getTipoEquipo() { return _tipoEquipo; }
char* Producto::getMarca() { return _marca; }
bool Producto::getEstado() { return _estado; }

std::string Producto::getTipoEquipoStr(){
    switch(_tipoEquipo){
        case 1: return "PC";
        case 2: return "PORTATILES";
        case 3: return "PERIFERICOS";
        case 4: return "COMPONENTES";
        default: return "DESCONOCIDO";
    }
}
std::string Producto::getEstadoStr(){
    if(_estado==true){
        return "Activo";
    } else {
        return "Desactivado";
    }
}

// --- Setters ---
void Producto::setIdProducto(int idProducto) { _idProducto = idProducto; }

bool Producto::setPrecio(float precio){
    if(precio<=0){
        return false;
    }
    _precio = precio;
    return true;
}
void Producto::setDescripcion(char* desc) { std::strcpy(_descripcion, desc); }
void Producto::setMarca(char* marca) { std::strcpy(_marca, marca); }
bool Producto::setTipoEquipo(int tipoEquipo) {
    if(tipoEquipo>=1 && tipoEquipo<=4){
    _tipoEquipo = tipoEquipo;
    return true;
    }
    return false;
}
void Producto::setEstado(bool estado) { _estado = estado; }


