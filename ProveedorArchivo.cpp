#include "ProveedorArchivo.h"
#include "FuncionesGenerales.h"
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int ProveedorArchivo::altaProveedor() {
    Proveedor p;

    int id = getProximoId();
    p.cargar(id);
    if(!p.getEstado()){
        return -1; // error al cargar
    }

    ProveedorArchivo archivo;
    archivo.agregarRegistro(p);

    cout << "Proveedor creado con ID: " << p.getIdProveedor() << endl;
    return 1; // ok
}

int ProveedorArchivo::getProximoId() {
    FILE* p = fopen(_nombreArchivo, "rb");
    if (p == nullptr) return 1;

    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Proveedor);
    fclose(p);

    return cant + 1;
}


int ProveedorArchivo::agregarRegistro(Proveedor reg) {
    FILE* p = fopen(_nombreArchivo, "ab");
    if (p == nullptr) {
        cout << "ERROR DE ARCHIVO\n";
        return -1;
    }

    int escribio = fwrite(&reg, tamanioRegistro, 1, p);
    fclose(p);
    return escribio;
}

bool ProveedorArchivo::listarRegistros() {
    Proveedor reg;
    FILE* p = fopen(_nombreArchivo, "rb");
    if (p == nullptr) return false;

    while (fread(&reg, tamanioRegistro, 1, p) == 1) {
        if (reg.getEstado()) {
            reg.mostrar();
        }
    }

    fclose(p);
    return true;
}

Proveedor ProveedorArchivo::leerRegistro(int pos) {
    Proveedor reg;
    FILE* p = fopen(_nombreArchivo, "rb");
    if (p == nullptr) return reg;

    fseek(p, pos * tamanioRegistro, SEEK_SET);
    fread(&reg, tamanioRegistro, 1, p);
    fclose(p);
    return reg;
}

bool ProveedorArchivo::bajaLogica() {
    cout << "INGRESE ID DEL PROVEEDOR A ELIMINAR: ";
    int id;
    cin >> id;
    cin.ignore();

    int pos = buscarPorId(id);
    if (pos < 0) {
        cout << "Proveedor no encontrado.\n";
        return false;
    }

    Proveedor reg = leerRegistro(pos);
    if (!reg.getEstado()) {
        cout << "El proveedor ya esta dado de baja.\n";
        return false;
    }

    reg.setEstado(false);
    int ok = modificarRegistro(reg, pos);
    if (ok == 1) {
        cout << "Proveedor dado de baja correctamente.\n";
        return true;
    }
    cout << "No se pudo modificar el registro.\n";
    return false;
}

int ProveedorArchivo::modificarRegistro(Proveedor reg, int pos) {
    FILE* p = fopen(_nombreArchivo, "rb+");
    if (p == nullptr) return -1;

    fseek(p, pos * tamanioRegistro, SEEK_SET);
    int escribio = fwrite(&reg, tamanioRegistro, 1, p);
    fclose(p);

    if (escribio != 1) return -2;
    return 1;
}

int ProveedorArchivo::buscarPorId(int idBuscado) {
    Proveedor reg;
    FILE* p = fopen(_nombreArchivo, "rb");
    if (p == nullptr) return -2;

    int pos = 0;
    while (fread(&reg, tamanioRegistro, 1, p) == 1) {
        if (reg.getIdProveedor() == idBuscado) {
            fclose(p);
            return pos;
        }
        pos++;
    }

    fclose(p);
    return -1;
}

int ProveedorArchivo::buscarPorNombre(const char* nombreBuscado) {
    Proveedor reg;
    FILE* p = fopen(_nombreArchivo, "rb");
    if (p == nullptr) return -2;

    int pos = 0;
    while (fread(&reg, tamanioRegistro, 1, p) == 1) {
        if (reg.getEstado() && std::strcmp(reg.getNombre(), nombreBuscado) == 0) {
            fclose(p);
            return pos;
        }
        pos++;
    }

    fclose(p);
    return -1;
}

int ProveedorArchivo::reactivarProveedor(int idProveedor) {
    int pos = buscarPorId(idProveedor);
    if (pos < 0) return -1;

    Proveedor reg = leerRegistro(pos);
    if (reg.getEstado()) return 0;

    reg.setEstado(true);
    int ok = modificarRegistro(reg, pos);
    if (ok == 1) return 1;
    return -2;
}
