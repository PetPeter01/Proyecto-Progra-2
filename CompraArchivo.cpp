#include "CompraArchivo.h"
#include "ProveedorArchivo.h"
#include "DetalleCompraArchivo.h"
#include "FuncionesGenerales.h"
#include <iostream>
#include <cstdio>

using namespace std;

int CompraArchivo::altaCompra() {
    ProveedorArchivo     archProv;
    DetalleCompraArchivo archDet;

    cout << "ALTA DE COMPRA\n";
    cout << "-------------------------\n";

    int idProveedor = PedirEnteroValido("ID PROVEEDOR: ");
    int posProv = archProv.buscarPorId(idProveedor);
    if (posProv < 0) return -1;

    Proveedor p = archProv.leerRegistro(posProv);
    if (!p.getEstado()) return -2;

    int idEmpleado = PedirEnteroValido("ID EMPLEADO: ");

    int idCompra = getProximoId();
    Compra c;
    c.cargar(idCompra, idProveedor, idEmpleado, 0);


    float total = archDet.altaDetalle(idCompra, c.getFechaCompra());
    if (total <= 0) return -3;

    c.setImporte(total);

    if (agregarRegistro(c)) {
        return 1;
    }

    return 0;
}

int CompraArchivo::getProximoId() {
    FILE* p = fopen(_nombreArchivo, "rb");
    if (p == nullptr) return 1;

    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Compra);
    fclose(p);

    return cant + 1;
}

bool CompraArchivo::agregarRegistro(Compra reg) {
    FILE* p = fopen(_nombreArchivo, "ab");
    if (p == nullptr) {
        cout << "ERROR DE ARCHIVO\n";
        return false;
    }

    int escribio = fwrite(&reg, tamanioRegistro, 1, p);
    fclose(p);

    return (escribio == 1);
}

Compra CompraArchivo::leerRegistro(int pos) {
    Compra obj;
    FILE* p = fopen(_nombreArchivo, "rb");

    if (p == nullptr) {
        return obj;
    }

    fseek(p, pos * tamanioRegistro, SEEK_SET);
    fread(&obj, tamanioRegistro, 1, p);
    fclose(p);

    return obj;
}

int CompraArchivo::contarRegistros() {
    FILE*  p   = fopen(_nombreArchivo, "rb");
    Compra aux;
    if (p == nullptr) return 0;

    int cont = 0;
    while (fread(&aux, tamanioRegistro, 1, p) == 1) {
        cont++;
    }
    fclose(p);
    return cont;
}

bool CompraArchivo::listarRegistros() {
    FILE*  p = fopen(_nombreArchivo, "rb");
    Compra c;

    if (p == nullptr) return false;

    while (fread(&c, tamanioRegistro, 1, p) == 1) {
        if (!c.getEstado()) continue;
        c.mostrar();
    }

    fclose(p);
    return true;
}

int CompraArchivo::ModificarRegistro(Compra reg, int pos) {
    FILE* p = fopen(_nombreArchivo, "rb+");
    if (p == nullptr) return -1;

    fseek(p, pos * tamanioRegistro, SEEK_SET);
    int escribio = fwrite(&reg, tamanioRegistro, 1, p);
    fclose(p);

    if (escribio != 1) return -2;
    return 1;
}

bool CompraArchivo::bajaLogica(int idCompra) {
    int pos = buscarPorId(idCompra);
    if (pos < 0) return false;

    Compra c = leerRegistro(pos);
    if (!c.getEstado()) return false;

    c.setEstado(false);
    return (ModificarRegistro(c, pos) == 1);
}

int CompraArchivo::buscarPorId(int idCompra) {
    FILE*  p = fopen(_nombreArchivo, "rb");
    Compra c;
    if (p == nullptr) return -2;

    int pos = 0;
    while (fread(&c, tamanioRegistro, 1, p) == 1) {
        if (c.getIdCompra() == idCompra) {
            fclose(p);
            return pos;
        }
        pos++;
    }

    fclose(p);
    return -1;
}

int CompraArchivo::reactivarCompra(int idCompra) {
    int pos = buscarPorId(idCompra);
    if (pos < 0) return -1;

    Compra c = leerRegistro(pos);
    if (c.getEstado()) return 0;

    c.setEstado(true);
    if (ModificarRegistro(c, pos) == 1) return 1;
    return -2;
}
