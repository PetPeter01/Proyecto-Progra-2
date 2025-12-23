#include "DetalleCompraArchivo.h"
#include "ProductoArchivo.h"
#include "FuncionesGenerales.h"
#include "StockArchivo.h"
#include "MovimientoStockArchivo.h"
#include <time.h>
#include <iostream>
#include <cstdio>

using namespace std;

float DetalleCompraArchivo::altaDetalle(int idCompra, Fecha fechaCompra) {
    ProductoArchivo archProducto;
    StockArchivo stockArch;
    DetalleCompra   det;
    float total = 0.0f;
    int   continuar = 1;


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

        int idDetalle = getProximoId();

        det.cargar(idDetalle, idCompra, idProducto);

        int guardo = agregarRegistro(det);
        if (guardo == 1) {
            cout << "Detalle de compra guardado con exito.\n";
            total += det.getSubtotal();
            stockArch.sumarStock(idProducto, det.getCantidad(), fechaCompra);
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
    if (!p) { std::cout << "ERROR DE ARCHIVO\n"; return 0; }
    DetalleCompra d;
    ProductoArchivo archiProd;
    int cant = 0;
    while (fread(&d, tamanioRegistro, 1, p) == 1) {
        if (d.getIdCompra() == idCompra) {
            int pos = archiProd.buscarPorId(d.getIdProducto());
            Producto prod = archiProd.leerRegistro(pos);

            std::cout << "   - Prod: "   << d.getIdProducto() << " - " << prod.getDescripcion()
                      << " | Cant: "      << d.getCantidad()
                      << " | P.U.: "      << d.getCostoUnitario()
                      << " | Subtotal: "  << d.getSubtotal() << '\n';
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

int DetalleCompraArchivo::puedeAnularCompra(int idCompra) {
    FILE* p = fopen(_nombreArchivo, "rb");
    if (!p) return -1;

    DetalleCompra det;
    StockArchivo stockArch;

    while (fread(&det, sizeof(DetalleCompra), 1, p) == 1) {
        if (det.getIdCompra() == idCompra) {
            int stockActual = stockArch.getStock(det.getIdProducto());
            if (stockActual < det.getCantidad()) {
                fclose(p);
                return 0; // no se puede
            }
        }
    }

    fclose(p);
    return 1; // se puede
}

int DetalleCompraArchivo::revertirCompra(int idCompra, Fecha fecha) {
    FILE* p = fopen(_nombreArchivo, "rb");
    if (!p) return -1;

    DetalleCompra det;
    StockArchivo stockArch;
    MovimientoStockArchivo movArch;

    while (fread(&det, sizeof(DetalleCompra), 1, p) == 1) {
        if (det.getIdCompra() == idCompra) {
            stockArch.restarStock(det.getIdProducto(), det.getCantidad(), fecha);

            MovimientoStock mov;
            mov.cargar(det.getIdProducto(), det.getCantidad(),"EGRESO", fecha);
            movArch.agregarRegistro(mov);
        }
    }

    fclose(p);
    return 1;
}


