#include "MovimientoStockArchivo.h"
#include <iostream>

int MovimientoStockArchivo::agregarRegistro(MovimientoStock reg){
    reg.setIdMovimiento(getProximoId());

    FILE* p = fopen(_nombreArchivo, "ab");
    if (p == nullptr) {
        return -1;
    }

    int escribio = fwrite(&reg, tamanioRegistro, 1, p);
    fclose(p);

    return escribio;
}


int MovimientoStockArchivo::getProximoId() {
    return contarRegistros() + 1;
}

int MovimientoStockArchivo::contarRegistros() {
    MovimientoStock m;
    FILE* pMov = fopen(_nombreArchivo, "rb");
    if (pMov == nullptr) {
        return 0;
    }

    int contador = 0;
    while (fread(&m, tamanioRegistro, 1, pMov) == 1) {
        contador++;
    }

    fclose(pMov);
    return contador;
}

bool MovimientoStockArchivo::listarRegistros() {
    FILE* p = fopen(_nombreArchivo, "rb");
    if (p == nullptr) return false;

    MovimientoStock reg;
    while (fread(&reg, tamanioRegistro, 1, p) == 1) {
        if (reg.getEstado()) reg.mostrar();
    }
    fclose(p);
    return true;
}

MovimientoStock MovimientoStockArchivo::leerRegistro(int pos) {
    MovimientoStock obj;
    FILE* pProd = fopen(_nombreArchivo, "rb");

    if (pProd == nullptr) {
        return obj;
    }

    fseek(pProd, pos * tamanioRegistro, 0);
    fread(&obj, tamanioRegistro, 1, pProd);
    fclose(pProd);

    return obj;
}

bool MovimientoStockArchivo::bajaLogica() {
    std::cout << "INGRESE ID DEL MOVIMIENTO: ";
    int id;
    std::cin >> id;
    std::cin.ignore();

    int pos = buscarPorId(id);
    if (pos < 0) {
        std::cout << "Movimiento de Stock no encontrado.\n";
        return false;
    }

    MovimientoStock reg = leerRegistro(pos);
    if (!reg.getEstado()) {
        std::cout << "El Movimiento de Stock ya esta dado de baja.\n";
        return false;
    }

    reg.setEstado(false);
    int ok = modificarRegistro(reg, pos);
    if (ok == 1) {
        std::cout << "Movimiento de Stock dado de baja correctamente.\n";
        return true;
    }
    std::cout << "No se pudo modificar el registro.\n";
    return false;
}

int MovimientoStockArchivo::modificarRegistro(MovimientoStock reg, int pos) {
    FILE* p = fopen(_nombreArchivo, "rb+");
    if (p == nullptr) return -1;

    fseek(p, pos * tamanioRegistro, SEEK_SET);
    int escribio = fwrite(&reg, tamanioRegistro, 1, p);
    fclose(p);

    if (escribio != 1) return -2;
    return 1;
}

int MovimientoStockArchivo::buscarPorId(int idBuscado) {
    MovimientoStock reg;
    FILE* p = fopen(_nombreArchivo, "rb");
    if (p == nullptr) return -2;

    int pos = 0;
    while (fread(&reg, tamanioRegistro, 1, p) == 1) {
        if (reg.getIdMovimiento() == idBuscado) {
            fclose(p);
            return pos;
        }
        pos++;
    }

    fclose(p);
    return -1;
}
