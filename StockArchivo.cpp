#include "StockArchivo.h"
#include "MovimientoStock.h"
#include "MovimientoStockArchivo.h"
#include <iostream>
#include <cstring>

StockArchivo::StockArchivo(const char* nombre) {
    strcpy(_nombreArchivo, nombre);
    tamanioRegistro = sizeof(Stock);
}

int StockArchivo::buscarPorIdProducto(int idBuscado){
    Stock reg;
    FILE* p = fopen(_nombreArchivo, "rb");
    if (p == nullptr) return -2;

    int pos = 0;
    while (fread(&reg, tamanioRegistro, 1, p) == 1) {
        if (reg.getIdProducto() == idBuscado) {
            fclose(p);
            return pos;
        }
        pos++;
    }

    fclose(p);
    return -1;
}

Stock StockArchivo::leerRegistro(int pos){
    Stock reg;
    FILE* p = fopen(_nombreArchivo, "rb");
    if (p == nullptr) return reg;

    fseek(p, pos * tamanioRegistro, SEEK_SET);
    fread(&reg, tamanioRegistro, 1, p);
    fclose(p);
    return reg;
}

int StockArchivo::agregarRegistro(Stock reg) {
    FILE* p = fopen(_nombreArchivo, "ab");
    if (p == nullptr) {
        std::cout << "ERROR DE ARCHIVO";
        return -1;
    }

    int escribio = fwrite(&reg, tamanioRegistro, 1, p);
    fclose(p);

    return escribio;
}

int StockArchivo::modificarRegistro(Stock reg, int pos) {
    FILE* p = fopen(_nombreArchivo, "rb+");
    if (p == nullptr) return -1;

    fseek(p, pos * tamanioRegistro, SEEK_SET);
    int escribio = fwrite(&reg, tamanioRegistro, 1, p);
    fclose(p);

    if (escribio != 1) return -2;
    return 1;
}

int StockArchivo::getStock(int id){
    int pos = buscarPorIdProducto(id);
    if(pos<0){
        return -1; // no existe ese producto
    }
    Stock reg = leerRegistro(pos);
    int stock = reg.getCantidad();
    return stock;
}

bool StockArchivo::hayStockSuficiente(int idProducto, int cantidad) {
    int pos = buscarPorIdProducto(idProducto);
    if (pos < 0) return false;

    Stock reg = leerRegistro(pos);
    return reg.getCantidad() >= cantidad;
}


bool StockArchivo::sumarStock(int idProducto, int cantidad, Fecha fecha) {
    int pos = buscarPorIdProducto(idProducto);

    if (pos >= 0) {
        Stock reg = leerRegistro(pos);
        reg.setCantidad(reg.getCantidad() + cantidad);
        modificarRegistro(reg, pos);
    }
    else {
        Stock nuevo;
        nuevo.setIdProducto(idProducto);
        nuevo.setCantidad(cantidad);
        agregarRegistro(nuevo);
    }

    MovimientoStock mov;
    MovimientoStockArchivo movArch;
    mov.cargar(idProducto, cantidad, "INGRESO", fecha);
    movArch.agregarRegistro(mov);
    return true;
}

bool StockArchivo::restarStock(int idProducto, int cantidad, Fecha fecha) {
    int pos = buscarPorIdProducto(idProducto);
    if (pos < 0){
        return false;
    }

    Stock reg = leerRegistro(pos);
    if (reg.getCantidad() < cantidad) return false;

    reg.setCantidad(reg.getCantidad() - cantidad);
    modificarRegistro(reg, pos);

    MovimientoStock mov;
    MovimientoStockArchivo movArch;
    mov.cargar(idProducto, cantidad, "EGRESO", fecha);
    movArch.agregarRegistro(mov);
    return true;
}


