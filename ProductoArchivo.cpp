#include <iostream>
#include <cstdio>
#include <cstring>
#include "ProductoArchivo.h"
#include "FuncionesGenerales.h"
using namespace std;

int ProductoArchivo::altaProducto() {
    Producto reg;

    int id = PedirEnteroValido("ID PRODUCTO: ");

    int pos = buscarPorId(id);
    if (pos < 0) {
        reg.cargar(id);
        reg.setIdProducto(id);
        reg.setEstado(true);
        if (agregarRegistro(reg) == 1) {
            return 1;
        } else {
            return -1;
        }
    }

    Producto existente = leerRegistro(pos);
    if (!existente.getEstado()) {
        return -2;
    }

    return 0;
}

int ProductoArchivo::agregarRegistro(Producto reg) {
    FILE* pProd = fopen(_nombreArchivo, "ab");
    if (pProd == nullptr) {
        cout << "ERROR DE ARCHIVO";
        return -1;
    }

    int escribio = fwrite(&reg, tamanioRegistro, 1, pProd);
    fclose(pProd);

    return escribio;
}

bool ProductoArchivo::listarRegistros() {
    Producto prod;
    FILE* pProd = fopen(_nombreArchivo, "rb");

    if (pProd == nullptr) {
        return false;
    }

    while (fread(&prod, tamanioRegistro, 1, pProd) == 1) {
        if (prod.getEstado()) {
            prod.mostrar();
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
