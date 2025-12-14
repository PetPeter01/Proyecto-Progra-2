#include "DetalleCompraArchivo.h"
#include "ProductoArchivo.h"
#include "FuncionesGenerales.h"
#include <iostream>
#include <cstdio>

using namespace std;

float DetalleCompraArchivo::altaDetalle(int idCompra) {
    ProductoArchivo archProducto;
    DetalleCompra   det;
    float total = 0.0f;
    int   continuar = 1;

    // Calcula el  próximo idDetalleCompra
    int ultimoId = 0;
    FILE* p = fopen(_nombreArchivo, "rb");
    if (p != nullptr) {
        DetalleCompra aux;
        while (fread(&aux, tamanioRegistro, 1, p) == 1) {
            if (aux.getIdDetalleCompra() > ultimoId) {
                ultimoId = aux.getIdDetalleCompra();
            }
        }
        fclose(p);
    }
    int siguienteId = ultimoId + 1;

    while (continuar == 1) {
        int idProducto = PedirEnteroValido("ID PRODUCTO: ");
        int posProd    = archProducto.buscarPorId(idProducto);

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

        det.cargar(siguienteId, idCompra, idProducto);
        siguienteId++;

        int guardo = agregarRegistro(det);
        if (guardo == 1) {
            cout << "Detalle de compra guardado con exito.\n";
            total += det.getCantidad() * det.getCostoUnitario();
        } else {
            cout << "Error al guardar el detalle de compra.\n";
        }

        cout << "¿Agregar otro producto a la compra? 1. Si / 2. No: ";
        cin >> continuar;
        cin.ignore();
    }

    return total;
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
