#include <iostream>
#include "DetalleVentaArchivo.h"
#include "ProductoArchivo.h"
#include "DetalleVenta.h"
#include "StockArchivo.h"
#include "FuncionesGenerales.h"
using namespace std;

float DetalleVentaArchivo::altaDetalle(int idVenta) {
    ProductoArchivo archProducto;
    DetalleVenta detalle;
    float total = 0.0f;
    int continuar = 1;

    while (continuar == 1) {
        int idProducto = PedirEnteroValido("ID PRODUCTO: ");
        int posProd = archProducto.buscarPorId(idProducto);

        if (posProd < 0) {
            cout << "Producto no encontrado.\n";
            system("pause");
            continue;
        }
        Producto prod = archProducto.leerRegistro(posProd);
        if(!prod.getEstado()){
            cout<< "Producto inactivo\n";
            system("pause");
            continue;
        }

        int cantidad = detalle.cargar(idVenta, idProducto);

        StockArchivo stockArch;
        int stockDisponible = stockArch.getStock(idProducto);

        if (stockDisponible < 0) {
            cout << "El producto no tiene stock cargado.\n";
            continue;
        }

        if (cantidad > stockDisponible) {
            cout << "Stock insuficiente.\n";
            continue;
        }


        detalle.setPrecioUnitario(prod.getPrecio());

        detalle.calcularSubtotal();

        int guardo = agregarRegistro(detalle);
        if (guardo == 1) {
            cout << "Guardado con exito.\n";
            total += detalle.getSubtotal();
        } else {
            cout << "Error al guardar el detalle.\n";
        }

        cout << "¿Agregar otro producto? 1. Si / 2. No: ";
        cin >> continuar;
        cin.ignore();
    }

    return total;
}

int DetalleVentaArchivo::agregarRegistro(DetalleVenta reg) {
    FILE* pDetalle = fopen(_nombreArchivo, "ab");
    if (pDetalle == nullptr) {
        cout << "ERROR DE ARCHIVO\n";
        return -1;
    }

    int escribio = fwrite(&reg, tamanioRegistro, 1, pDetalle);
    fclose(pDetalle);

    return escribio; // 1 si escribió correctamente, 0 o -1 si falló
}

int DetalleVentaArchivo::listarPorVenta(int idVenta) {
    FILE* p = fopen(_nombreArchivo, "rb");
    if (!p) { std::cout << "ERROR DE ARCHIVO\n"; return 0; }

    DetalleVenta d;
    int cant = 0;

    while (fread(&d, tamanioRegistro, 1, p) == 1) {
        if (d.getIdVenta() == idVenta) {
            std::cout << "   - Prod: "   << d.getIdProducto()
                      << " | Cant: "      << d.getCantidad()
                      << " | P.U.: "      << d.getPrecioUnitario()
                      << " | Subtotal: "  << d.getSubtotal() << '\n';
            cant++;
        }
    }
    fclose(p);
    return cant;
}

float DetalleVentaArchivo::totalPorVenta(int idVenta) {
    FILE* p = fopen(_nombreArchivo, "rb");
    if (!p) return 0.0f;

    DetalleVenta d; float total = 0.0f;
    while (fread(&d, tamanioRegistro, 1, p) == 1) {
        if (d.getIdVenta() == idVenta) total += d.getSubtotal();
    }
    fclose(p);
    return total;
}
