#include <iostream>
#include <cstdio>
#include <cstring>
#include "ProductoArchivo.h"
#include "TiposDeEquipoArchivo.h"
#include "StockArchivo.h"
#include "FuncionesGenerales.h"
using namespace std;

int ProductoArchivo::altaProducto() {
    Producto reg;

    TiposDeEquipoArchivo archTipos;

    int codTipo;
    while (true) {
        cout << "TIPOS DE EQUIPO ACTIVOS:\n";
        archTipos.listarActivos();

        codTipo = PedirEnteroValido("CODIGO TIPO DE EQUIPO: ");
        int pos = archTipos.buscarPorId(codTipo);

        if (pos < 0) {
            cout << "No existe ese tipo.\n";
            system("pause");
            continue;
        }

        if (!archTipos.leerRegistro(pos).getEstado()) {
            cout << "Ese tipo esta INACTIVO.\n";
            system("pause");
            continue;
        }
        break;
    }

    float precio = pedirFloatValido("PRECIO: ");
    int id = getProximoId();
    reg.cargar(id, codTipo, precio);

    if (!reg.getEstado()){
        return -1; // error al cargar
    }

    if (existeProducto(reg.getDescripcion(), reg.getMarca())) {
        return -2; // producto duplicado
    }

    if (agregarRegistro(reg)) {
        return 1; // producto guardado
    }
    return -3; // error al guardar
}

int ProductoArchivo::getProximoId() {
    FILE* p = fopen(_nombreArchivo, "rb");
    if (p == nullptr) return 1;

    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Producto);
    fclose(p);

    return cant + 1;
}


int ProductoArchivo::agregarRegistro(Producto reg) {
    FILE* pProd = fopen(_nombreArchivo, "ab");
    if (pProd == nullptr) {
        return -1; // error de archivo
    }

    int escribio = fwrite(&reg, tamanioRegistro, 1, pProd);
    fclose(pProd);

    return escribio;
}

string ProductoArchivo::getTipoEquipoStr(Producto& p) {
    TiposDeEquipoArchivo arch;

    int pos = arch.buscarPorId(p.getIdTipoEquipo());
    if (pos < 0) return "DESCONOCIDO";

    return arch.leerRegistro(pos).getDescripcion();
} // esto debería ir en TipoEquipoProducto, tho.

bool ProductoArchivo::listarRegistros() {
    StockArchivo s;
    Producto prod;
    FILE* pProd = fopen(_nombreArchivo, "rb");
    if (pProd == nullptr) return false;

    while (fread(&prod, tamanioRegistro, 1, pProd) == 1) {
        if (prod.getEstado()) {
            int id = prod.getIdProducto();
            prod.mostrar();
            cout << "Tipo de equipo: ";
            cout << getTipoEquipoStr(prod) << endl;
            int stock = s.getStock(id);
            if(stock==-1){
                cout << "STOCK: No hay stock cargado" << endl;
            } else if (stock==0){
                cout << "STOCK: Sin stock" << endl;
                } else if (stock>0){
                    cout << "STOCK: " << stock << endl;
                }
            cout << "--------------------------------" << endl;
        }
    }

    fclose(pProd);
    return true;
}


Producto ProductoArchivo::leerRegistro(int pos) {
    Producto obj;
    FILE* pProd = fopen(_nombreArchivo, "rb");

    if (pProd == nullptr) {
        return obj;
    }

    fseek(pProd, pos * tamanioRegistro, 0);
    fread(&obj, tamanioRegistro, 1, pProd);
    fclose(pProd);

    return obj;
}

bool ProductoArchivo::existeProducto(const char* descripcion, const char* marca) {
    FILE* p = fopen(_nombreArchivo, "rb");
    if (p == nullptr) return false;

    Producto reg;
    while (fread(&reg, sizeof(Producto), 1, p)) {
        if (reg.getEstado()) {
            if (strcmp(reg.getDescripcion(), descripcion) == 0 &&
                strcmp(reg.getMarca(), marca) == 0) {
                fclose(p);
                return true;
            }
        }
    }

    fclose(p);
    return false;
}


bool ProductoArchivo::bajaLogica() {
    Producto reg;
    cout << "Ingrese el ID del producto: ";
    int id;
    cin >> id;
    cin.ignore();

    int pos = buscarPorId(id);
    if (pos < 0) {
        return false;
    }

    reg = leerRegistro(pos);
    reg.setEstado(false);

    if (modificarRegistro(reg, pos) == 1) {
        return true;
    }

    return false;
}

int ProductoArchivo::modificarRegistro(Producto reg, int pos) {
    FILE* pProd = fopen(_nombreArchivo, "rb+");

    if (pProd == nullptr) {
        return -1;
    }

    fseek(pProd, pos * tamanioRegistro, 0);
    int escribio = fwrite(&reg, tamanioRegistro, 1, pProd);
    fclose(pProd);

    if (escribio != 1) {
        return -2;
    }

    return 1;
}

int ProductoArchivo::buscarPorId(int idBuscado) {
    Producto prod;
    FILE* pProd = fopen(_nombreArchivo, "rb");

    if (pProd == nullptr) {
        return -2;
    }

    int pos = 0;
    while (fread(&prod, tamanioRegistro, 1, pProd) == 1) {
        if (prod.getIdProducto() == idBuscado) {
            fclose(pProd);
            return pos;
        }
        pos++;
    }

    fclose(pProd);
    return -1;
}
