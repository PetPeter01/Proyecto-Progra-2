#include <iostream>
#include "EmpleadoArchivo.h"
using namespace std;


bool EmpleadoArchivo::agregarRegistro(Empleado reg){
    FILE* p=fopen(_NombreArchivo,"ab");
    if(p==nullptr){
        return false;
}
    bool ok=fwrite(&reg,_TamanioRegistro,1,p);
    fclose(p);
    return ok;
}

Empleado EmpleadoArchivo::leerRegistro(int pos){
    FILE* p=fopen(_NombreArchivo,"rb");
    Empleado reg;
    if(p==nullptr){
      return reg;
    }
    fseek(p,pos*_TamanioRegistro,SEEK_SET);
    fread(&reg,_TamanioRegistro,1,p);
    fclose(p);
    return reg;
}


int EmpleadoArchivo::contarRegistros(){
     FILE* p=fopen(_NombreArchivo,"rb");
     if(p==nullptr){
      return 0;
        }
    fseek(p,0,SEEK_END);
    int cant=ftell(p)/_TamanioRegistro;
    fclose(p);
    return cant;
}

int EmpleadoArchivo::BuscarPorDni(int  dniBuscado) {
    int cantidad = contarRegistros();
    if (cantidad == 0) return -1;

    Empleado reg;

    for (int i = 0; i < cantidad; i++) {
        reg = leerRegistro(i);
        if (!reg.GetEstado()){
           cout << "EMPLEADO DADO DE BAJA" << endl;
        }

        if (reg.GetDni() == dniBuscado) {
            return i;
        }
    }

    return -1;
}

int EmpleadoArchivo::BuscarPorId(int idBuscado) {
    int cantidad = contarRegistros();
    if (cantidad == 0) return -1;

    Empleado reg;

    for (int i = 0; i < cantidad; i++) {
        reg = leerRegistro(i);
        if (!reg.GetEstado()){
           cout << "EMPLEADO DADO DE BAJA" << endl;
        }

        if (reg.GetIdEmpleado() == idBuscado) {
            return i;
        }
    }

    return -1;
}


int EmpleadoArchivo::GenerarProximoId(){
    return contarRegistros() + 1;
}

bool EmpleadoArchivo::altaEmpleado(){
    Empleado reg;
    int id = GenerarProximoId();
    reg.Cargar(id);
    reg.SetEstado(true);

    return agregarRegistro(reg);
}

void EmpleadoArchivo::listarEmpleados(){
    int CantidadRegistros=contarRegistros();
    Empleado reg;

    for(int i=0;i<CantidadRegistros;i++){
       reg=leerRegistro(i);
       if(reg.GetEstado()){
       reg.Mostrar();
       }
    }

}
bool EmpleadoArchivo::modificarRegistro(Empleado reg, int pos){
    FILE* p = fopen(_NombreArchivo, "rb+");
    if(p == nullptr){
        return false;
    }

    fseek(p, pos * sizeof(Empleado), SEEK_SET);

    bool ok = fwrite(&reg, sizeof(Empleado), 1, p);

    fclose(p);
    return ok;
}



bool EmpleadoArchivo::bajaLogica(int id){
    int CantidadRegistros = contarRegistros();
    Empleado reg;
    for(int i=0;i<CantidadRegistros;i++){
     reg=leerRegistro(i);
     if(!reg.GetEstado()){
       cout << "EMPLEADO YA DADO DE BAJA" << endl;
       return false;
     }
     if(reg.GetIdEmpleado() == id){
        reg.SetEstado(false);
        modificarRegistro(reg,i);
        cout << "EMPLEADO DADO DE BAJA CORRECTAMENTE" << endl;
        return true;
     }
    }
    cout << "EMPLEADO NO ENCONTRADO" << endl;
    return false;

}

bool EmpleadoArchivo::reactivarEmpleado(int id){
    int CantidadRegistros = contarRegistros();
    Empleado reg;

    for(int i = 0; i < CantidadRegistros; i++){
        reg = leerRegistro(i);

        if(reg.GetIdEmpleado() == id){

            if(reg.GetEstado()){
                cout << "EMPLEADO YA ACTIVO" << endl;
                return false;
            }

            reg.SetEstado(true);
            if(modificarRegistro(reg, i)){
                     cout << "EMPLEADO REACTIVADO CORRECTAMENTE" << endl;
                return true;
            } else {
                cout << "ERROR AL GUARDAR CAMBIO" << endl;
                return false;
            }
        }
    }

    cout << "EMPLEADO NO ENCONTRADO" << endl;
    return false;
}
