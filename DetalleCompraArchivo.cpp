#include "DetalleCompraArchivo.h"
#include "ProductoArchivo.h"
#include "FuncionesGenerales.h"
#include "StockArchivo.h"
#include <iostream>
#include <cstdio>

using namespace std;

float DetalleCompraArchivo::altaDetalle(int idCompra) {
    ProductoArchivo archProducto;
    StockArchivo stockArch;
    DetalleCompra   det;
    float total = 0.0f;
    int   continuar = 1;

    int id = getProximoId();

    while (continuar == 1) {
        int idProducto = PedirEnteroValido("ID PRODUCTO: ");
        int posProd = archProducto.buscarPorId(idProducto);

        if (posProd < 0) {
            cout << "Producto no encontrado.\n";
            system("pause");
            continue;
        }

        Producto prod = archProducto.leerRegistro(posProd);
        if (!prod.getEstado()) {
            cout << "Producto inactivo.\n";
            system("pause");
            continue;
        }

        det.cargar(id, idCompra, idProducto);

        int guardo = agregarRegistro(det);
        if (guardo == 1) {
            cout << "Detalle de compra guardado con exito.\n";
            total += det.getCantidad() * det.getCostoUnitario();
            stockArch.sumarStock(idProducto, det.getCantidad());
        } else {
            cout << "Error al guardar el detalle de compra.\n";
        }

        cout << "¿Agregar otro producto a la compra? 1. Si / 2. No: ";
        cin >> continuar;
        cin.ignore();
    }

    return total;
}

int DetalleCompraArchivo::getProximoId() {
    FILE* p = fopen(_nombreArchivo, "rb");
    if (p == nullptr) return 1;

    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(DetalleCompra);
    fclose(p);

    return cant + 1;
}

int DetalleCompraArchivo::agregarRegistro(DetalleCompra reg) {
    FILE* p = fopen(_nombreArchivo, "ab");
    if (p == nullptr) {
        cout << "ERROR DE ARCHIVO\n";
        return -1;
    }

    int escribio = fwrite(&reg, tamanioRegistro, 1, p);
    fclose(p);

    return escribio;
}

int DetalleCompraArchivo::listarPorCompra(int idCompra) {
    FILE* p = fopen(_nombreArchivo, "rb");
    if (!p) {
        cout << "ERROR DE ARCHIVO\n";
        return 0;
    }

    DetalleCompra d;
    int cant = 0;

    while (fread(&d, tamanioRegistro, 1, p) == 1) {
        if (d.getIdCompra() == idCompra) {
            d.mostrar();
            cant++;
        }
    }
    fclose(p);
    return cant;
}

float DetalleCompraArchivo::totalPorCompra(int idCompra) {
    FILE* p = fopen(_nombreArchivo, "rb");
    if (!p) return 0.0f;

    DetalleCompra d;
    float total = 0.0f;

    while (fread(&d, tamanioRegistro, 1, p) == 1) {
        if (d.getIdCompra() == idCompra) {
            total += d.getCantidad() * d.getCostoUnitario();
        }
    }

    fclose(p);
    return total;
}
