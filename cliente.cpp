#include "cliente.h"
#include "FuncionesGenerales.h"
#include <iostream>
#include <string.h>

Cliente::Cliente() {
    _idCliente = 0;
    _tipoCliente = 0;
    _documento = 0;
    strcpy(_nombre, "");
    strcpy(_apellido, "");
    strcpy(_numeroTelefono, "");
    strcpy(_correoElectronico, "");
    strcpy(_direccion, "");
    _estado = true;
}

 void Cliente::cargar(long long documento, int tipo, int id) {
     char nombre[30], apellido[30], numeroTelefono[11], correoElectronico[50], direccion [50];
     _tipoCliente = tipo;
     _documento = documento;

    setIdCliente(id);

     if(tipo==1){
        while(true){
            std::cout<< "Nombre: ";
            std::cin.getline(nombre, 30);
            if(setNombre(nombre)){
                break;
            }
        std::cout<< "Solo letras.\n";
        }

        while(true){
            std::cout<< "Apellido: ";
            std::cin.getline(apellido, 30);
            if(setApellido(apellido)){
                break;
            }
        std::cout<< "Solo letras.\n";
        }
     }

     if(tipo==2){
        while(true){
            std::cout<< "Razon social: ";
            std::cin.getline(nombre, 30);
            if(setNombre(nombre)){
                break;
            }
        std::cout<< "Solo letras.\n";
        }

        strcpy(_apellido, "");
     }

     while (true){
        std::cout<< "Ingrese el numero telefonico: ";
        std::cin.getline(numeroTelefono, 20);
        int resultado = setNumeroTelefono(numeroTelefono);
        if(resultado==1){ break; }
        if(resultado==-1){ std::cout << "Numero de telefono invalido, solo numeros\n"; }
        if(resultado==-2){ std::cout << "Numero de telefono invalido, debe tener 10 digitos\n"; }

    }
    while (true){
        std::cout<< "Ingrese el correo electronico: ";
        std::cin.getline(correoElectronico, 50);
        if(setCorreoElectronico(correoElectronico)){
                break;
        } else {
            std::cout << "Correo electronico invalido\n";

        }
    }

    while (true){
        std::cout<< "Ingrese la direccion: ";
        std::cin.getline(direccion, 30);
        if(setDireccion(direccion)){
            break;
        } else {
            std::cout<< "Direccion invalida\n";
        }
    }

     setEstado(true);
}

void Cliente::mostrar(){
    int tipo = getTipoCliente();
    std::cout << "ID: " << getIdCliente() << std::endl;
    std::cout << "Tipo Cliente: " << getTipoClienteStr() << std::endl;
    if(tipo==1){
        std::cout<< "DNI: " << getDocumento() << std::endl;
        std::cout<< "Nombre: " << getNombre() << std::endl;
        std::cout<< "Apellido: " << getApellido() << std::endl;
    }
    if(tipo==2){
        std::cout<< "CUIT: " << getDocumento() << std::endl;
        std::cout<< "Razon social: " << getNombre() << std::endl;
    }
    std::cout<< "Telefono: " << getNumeroTelefono() << std::endl;
    std::cout<< "Correo Electronico: " << getCorreoElectronico() << std::endl;
    std::cout<< "Direccion: " << getDireccion() << std::endl;
    std::cout << "Estado: " << getEstadoStr() << std::endl;

    std::cout << "--------------------------------"<< std::endl;
}
/// getters
int Cliente::getIdCliente(){ return _idCliente; }
int Cliente::getTipoCliente(){ return _tipoCliente; }
long long Cliente::getDocumento() { return _documento; }
char* Cliente::getNombre() { return _nombre; }
char* Cliente::getApellido() {return _apellido; }
char* Cliente::getNumeroTelefono() { return _numeroTelefono; }
char* Cliente::getCorreoElectronico() { return _correoElectronico; }
char* Cliente::getDireccion(){ return _direccion; }
bool Cliente::getEstado(){ return _estado; }

std::string Cliente::getTipoClienteStr() const {
    switch (_tipoCliente) {
        case 1:
            return "Particular";
        case 2:
            return "Empresa";
        default:
            return "Desconocido";
    }
}

std::string Cliente::getEstadoStr(){
    if(_estado==1){
        return "activo";
    } else { return "inactivo";}
}


//setters

void Cliente::setIdCliente(int id){
    _idCliente = id;
}
bool Cliente::setTipoCliente(int tipoCliente){
    if(tipoCliente == 1 || tipoCliente == 2 ){
        _tipoCliente = tipoCliente;
        return true;
    }
    return false;
}

bool Cliente::setDni(int dni) {
    if (dni < 10000000 || dni > 99999999) {
        return false;
    }
    _documento = dni;
    return true;
}
bool Cliente::setCuit(long long cuit){
    if (cuit < 10000000000LL || cuit > 99999999999LL) {
        return false;
    }
    _documento = cuit;
    return true;
}
bool Cliente::setNombre(char *nombre){
    if(!esTextoValido(nombre)){
        return false;
    }
    strcpy(_nombre, nombre);
    return true;
}

bool Cliente::setApellido(char *apellido){
    if(!esTextoValido(apellido)){
        return false;
    }
    strcpy(_apellido, apellido);
    return true;
}

int Cliente::setNumeroTelefono(char *numeroTelefono){
    int len = strlen(numeroTelefono);
    int numero;

    if (!esEnteroValido(numeroTelefono, numero)) {
        return -1;
    }

    if (len != 10) {
        return -2;
    }

    strcpy(_numeroTelefono, numeroTelefono);
    return 1;
}

bool Cliente::setCorreoElectronico(char *correoElectronico) {
    if (strlen(correoElectronico) == 0 || strchr(correoElectronico, '@') == nullptr) {
        std::cout << "Correo electronico invalido." << std::endl;
        return false;
    }
    strcpy(_correoElectronico, correoElectronico);
    return true;
}

bool Cliente::setDireccion(char *direccion) {
    if (strlen(direccion) == 0) {
        std::cout << "Direccion vacia no valida." << std::endl;
        return false;
    }
    strcpy(_direccion, direccion);
    return true;
}


bool Cliente::setEstado(bool estado){
    _estado = estado;
    return true;
}


