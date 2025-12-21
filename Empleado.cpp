#include <iostream>
#include "Empleado.h"
#include "FuncionesGenerales.h"
#include <cstring>
using namespace std;

Empleado::Empleado(){
    _IdEmpleado=0;
    strcpy(_Nombre, "");
    strcpy(_Apellido,"");
    _Dni = 0;
    strcpy(_Telefono,"");
    strcpy(_Cargo,"");
    _Estado=true;
}

void Empleado::Cargar(int id, int dni){
    char nombre[30], apellido[30], telefono[20], cargo[30];
    int tipoCargo;

    setIdEmpleado(id);

    cout << "INGRESE EL TIPO DE CARGO DEL EMPLEADO" << endl;
    cout << "1) RESPONSABLE DE COMPRAS" << endl;
    cout << "2) RESPONSABLE DE VENTAS" << endl;
    cout << "3) OTRO TIPO" << endl;

    while (true) {
        cout << "SELECCIONE UNA OPCION: ";
        cin >> tipoCargo;
        cin.ignore();

        if (setTipoCargo(tipoCargo)) break;

        cout << "OPCION INVALIDA INTENTE NUEVAMENTE" << endl;;
        system("pause");
    }

    while (true) {
        cout << "INGRESE EL CARGO DEL EMPLEADO: ";
        cin.getline(cargo,30);

        if (setCargo(cargo)) break;

        cout << "Cargo invalido, solo letras" << endl;
        system("pause");
    }

    while (true) {
        cout << "INGRESE EL NOMBRE DEL EMPLEADO: ";
        cin.getline(nombre,30);

        if (SetNombre(nombre)) break;

        cout << "Nombre invalido, solo letras" << endl;
        system("pause");
    }

    while (true) {
        cout << "INGRESE EL APELLIDO O LOS APELLIDOS DEL EMPLEADO: ";
        cin.getline(apellido,30);

        if (setApellido(apellido)) break;

        cout << "Apellido invalido, solo letras" << endl;
        system("pause");
    }

    while (true) {
        cout << "INGRESE EL TELEFONO DEL EMPLEADO:";
        cin.getline(telefono,20);

        if (setTelefono(telefono)) break;

        cout << "Numero de telefono invalido" << endl;
        system("pause");
    }
}



void Empleado::Mostrar(){
    cout << "ID Empleado: " << _IdEmpleado << "\n";
    cout << "Tipo de cargo: " << GetTipoCargoeStr() << "\n";
    cout << "Cargo: " << _Cargo << "\n";
    cout << "Nombre: " << _Nombre << "\n";
    cout << "Apellido: " << _Apellido << "\n";
    cout << "DNI: " << _Dni << "\n";
    cout << "Telefono: " << _Telefono << "\n";
    cout << "Estado: " << (_Estado ? "Activo" : "Eliminado") << "\n";
    cout << "--------------------------------\n";

}

void Empleado::setIdEmpleado(int IdEmpleado){ _IdEmpleado = IdEmpleado; }

bool Empleado::setTipoCargo(int tipoCargo){
    if(tipoCargo <= 3 && tipoCargo >= 1){
        _TipoCargo = tipoCargo;
        return true;
    }
    return false;
}

bool Empleado::setCargo(const char *Cargo){
    if(!esTextoValido(Cargo)){
        return false;
    }
    strcpy(_Cargo, Cargo);
    return true;
}

bool Empleado::SetNombre(char *Nombre){
    if(!esTextoValido(Nombre)){
        return false;
    }
    strcpy(_Nombre, Nombre);
    return true;
}

bool Empleado::setApellido( char *Apellido){
    if(!esTextoValido(Apellido)){
        return false;
    }
    strcpy(_Apellido, Apellido);
    return true;
}

bool Empleado::setDni(int Dni){
    if (Dni < 10000000 || Dni > 99999999) {
        return false;
    }
    _Dni = Dni;
    return true;
}

bool Empleado::setTelefono( char *telefono){
    int len = strlen(telefono);
    int numero;

    if (!esEnteroValido(telefono, numero)) {
        std::cout << "El numero de telefono debe contener solo numeros." << std::endl;
        return false;
    }

    if (len != 10) {
        std::cout << "El numero de telefono debe tener exactamente 10 digitos." << std::endl;
        return false;
    }

    strcpy(_Telefono, telefono);
    return true;
}

void Empleado::SetEstado(bool Estado){ _Estado = Estado; }

std::string Empleado::GetTipoCargoeStr(){
    switch(_TipoCargo){
        case 1: return "Responsable de compras";
        case 2: return "Responsable de ventas";
        case 3: return "Otro";
        default: return "Desconocido";
    }
}

int Empleado::GetIdEmpleado(){ return _IdEmpleado; }
int Empleado::GetTipoCargo(){ return _TipoCargo; }
const char* Empleado::GetCargo(){ return _Cargo; }
char* Empleado::GetNombre(){ return _Nombre; }
char* Empleado::GetApellido(){ return _Apellido; }
int Empleado::GetDni(){ return _Dni; }
char* Empleado::GetTelefono(){ return _Telefono; }
bool Empleado::GetEstado(){ return _Estado; }
