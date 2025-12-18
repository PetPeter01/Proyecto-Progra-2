#include <iostream>
#include "Empleado.h"
#include <cstring>
using namespace std;

Empleado::Empleado(){
_IdEmpleado=0;
strcpy(_Nombre, "");
strcpy(_Apellido,"");
strcpy(_Dni,"");
strcpy(_Telefono,"");
strcpy(_Cargo,"");
_Estado=true;
}
    void Empleado::Cargar(int id){
    char nombre[30], apellido[30], dni[15], telefono[20], cargo[30];
    setIdEmpleado(id);
    cout << "INGRESE EL NOMBRE O LOS NOMBRES DEL EMPLEADO: " << endl;
    cin.getline(nombre,30);
    SetNombre(nombre);
    cout << "INGRESE EL APELLIDO O LOS APELLIDOS DEL EMPLEADO: " << endl;
    cin.getline(apellido,30);
    setApellido(apellido);

    int Opcion;
    while(true){
       cout << "INGRESE EL CARGO DEL EMPLEADO" << endl;
        cout << "1) RESPONSABLE DE COMPRAS" << endl;
        cout << "2) RESPONSABLE DE VENTAS" << endl;
        cout << "3) OTRO TIPO" << endl;
        cout << "SELECCIONE UNA OPCION" << endl;
        cin >> Opcion;
    if(Opcion==1){
      setCargo("RESPONSABLE DE COMPRAS");
      break;
    }
    else if(Opcion==2){
        setCargo("RESPONSABLE DE VENTAS");
        break;
    }
    else if(Opcion==3){
        setCargo("OTRO TIPO");
        break;
    }
    else{
        cout << "OPCION INVALIDA INTENTE NUEVAMENTE" << endl;
    }
    }
cin.ignore();
    cout << "INGRESE EL DNI DEL EMPLEADO: " << endl;
    cin.getline(dni,15);
    setDni(dni);
    cout << "INGRESE EL TELEFONO DEL EMPLEADO:" << endl;
    cin.getline(telefono,20);
    setTelefono(telefono);
    }
    void Empleado::Mostrar(){
    cout << "ID Empleado: " << _IdEmpleado << "\n";
    cout << "Nombre: " << _Nombre << "\n";
    cout << "Apellido: " << _Apellido << "\n";
    cout << "DNI: " << _Dni << "\n";
    cout << "Telefono: " << _Telefono << "\n";
    cout << "Cargo: " << _Cargo << "\n";
    cout << "Estado: " << (_Estado ? "Activo" : "Eliminado") << "\n";
    cout << "--------------------------------\n";

    }





void Empleado::setIdEmpleado(int IdEmpleado){ _IdEmpleado = IdEmpleado; }

void Empleado::SetNombre( char *Nombre){
    if(Nombre != nullptr) strcpy(_Nombre, Nombre);
}

void Empleado::setApellido( char *Apellido){
    if(Apellido != nullptr) strcpy(_Apellido, Apellido);
}

void Empleado::setDni( char *Dni){
    if(Dni != nullptr) strcpy(_Dni, Dni);
}

void Empleado::setTelefono( char *Telefono){
    if(Telefono != nullptr) strcpy(_Telefono, Telefono);
}

void Empleado::setCargo(const char *Cargo){
    if(Cargo != nullptr) strcpy(_Cargo, Cargo);
}

void Empleado::SetEstado(bool Estado){ _Estado = Estado; }


int Empleado::GetIdEmpleado(){ return _IdEmpleado; }
 char* Empleado::GetNombre(){ return _Nombre; }
 char* Empleado::GetApellido(){ return _Apellido; }
 char* Empleado::GetDni(){ return _Dni; }
 char* Empleado::GetTelefono(){ return _Telefono; }
const char* Empleado::GetCargo(){ return _Cargo; }
bool Empleado::GetEstado(){ return _Estado; }
