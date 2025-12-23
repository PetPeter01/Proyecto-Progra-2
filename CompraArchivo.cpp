#include "CompraArchivo.h"
#include "ProveedorArchivo.h"
#include "EmpleadoArchivo.h"
#include "DetalleCompraArchivo.h"
#include "StockArchivo.h"
#include "MovimientoStockArchivo.h"
#include "FuncionesGenerales.h"
#include "Fecha.h"
#include <iostream>
#include <cstdio>

using namespace std;

int CompraArchivo::altaCompra() {
    ProveedorArchivo archProv;
    DetalleCompraArchivo archDet;
    EmpleadoArchivo archEmp;

    cout << "ALTA DE COMPRA\n";
    cout << "-------------------------\n";


    int idEmpleado = PedirEnteroValido("ID EMPLEADO: ");
    int posEmp = archEmp.BuscarPorId(idEmpleado);
    if(posEmp < 0) return -3;
    Empleado e = archEmp.leerRegistro(posEmp);
    if(!e.GetEstado()) return -4;
    if(e.GetTipoCargo() != 1) return -5;

    int idProveedor = PedirEnteroValido("ID PROVEEDOR: ");
    int posProv = archProv.buscarPorId(idProveedor);
    if (posProv < 0) return -1;
    Proveedor p = archProv.leerRegistro(posProv);
    if (!p.getEstado()) return -2;

    int idCompra = getProximoId();

    Compra c;
    c.cargar(idCompra, idProveedor, idEmpleado, 0.0f);

    if (!agregarRegistro(c)) return -6;

    int posCompra = contarRegistros() - 1;

    float total = archDet.altaDetalle(idCompra, c.getFechaCompra());
    if (total <= 0) return -7;

    c.setImporte(total);
    modificarRegistro(c, posCompra);

    return 1;
}

int CompraArchivo::modificarRegistro(Compra reg, int pos) {
    FILE* pCompra = fopen(_nombreArchivo, "rb+");

    if (pCompra == nullptr) {
        return -1;
    }

    fseek(pCompra, pos * tamanioRegistro, 0);
    int escribio = fwrite(&reg, tamanioRegistro, 1, pCompra);
    fclose(pCompra);

    if (escribio != 1) {
        return -2;
    }

    return 1;
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
    ProveedorArchivo archiProv;
    EmpleadoArchivo archiEmple;
    DetalleCompraArchivo detArch;

    int cant = contarRegistros();
    if (cant == 0) {
        std::cout << "No hay compras registradas.\n";
        return false;
    }

    for(int i = 0; i < cant; i++){
        Compra c = leerRegistro(i);

        if(c.getEstado()){

            int posProv = archiProv.buscarPorId(c.getIdProveedor());
            Proveedor prov = archiProv.leerRegistro(posProv);

            int posEmple = archiEmple.BuscarPorId(c.getIdEmpleado());
            Empleado emple = archiEmple.leerRegistro(posEmple);

            std::cout << "ID: " << c.getIdCompra() << std::endl;
            std::cout << "Proveedor: " << prov.getNombre() << std::endl;
            std::cout << "id proveedor " << c.getIdProveedor() << std::endl;
            std::cout << "Empleado: " << emple.GetNombre() << " " << emple.GetApellido() << endl;
            std::cout << "id empleado: " << c.getIdEmpleado() << std::endl;
            std::cout << "Importe: $" << c.getImporte() << std::endl;
            std::cout << "Detalles:\n";

            int cantDetalles = detArch.listarPorCompra(c.getIdCompra());
            if (cantDetalles == 0) {
                std::cout << "   (Sin ítems)\n";
            }
            std::cout << "------------------------------\n\n";
        }
    }
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

int CompraArchivo::bajaLogica(int id) {
    int pos = buscarPorId(id);
    if (pos < 0) return -1;

    Compra compra = leerRegistro(pos);
    if (!compra.getEstado()) return -2;

    Fecha fecha;
    fecha.cargar();

    DetalleCompraArchivo detArch;

    int puede = detArch.puedeAnularCompra(id);
    if (puede == -1) return -4;
    if (puede == 0) return -3;

    int res = detArch.revertirCompra(id, fecha);
    if(res !=1) return -5;
    compra.setEstado(false);
    modificarRegistro(compra, pos);

    return 1;
}

float CompraArchivo::gastoPorEmpleado(int idEmpleado){
    Compra reg;
    float total = 0.0f;

    FILE* p = fopen(_nombreArchivo, "rb");
    if(p == nullptr) return -1;

    while(fread(&reg, tamanioRegistro, 1, p) == 1){
        if(reg.getIdEmpleado() == idEmpleado && reg.getEstado()){
            total += reg.getImporte();
        }
    }

    fclose(p);
    return total;
}

float CompraArchivo::gastoAnual(int anio) {
    Compra compra;
    float total = 0.0f;
    FILE* p = fopen(_nombreArchivo, "rb");
    if (p == nullptr) return -1;

    while (fread(&compra, tamanioRegistro, 1, p) == 1) {
        if (compra.getEstado() && compra.getFechaCompra().getAnio() == anio) {
            total += compra.getImporte();
        }
    }

    fclose(p);
    return total;
}

int CompraArchivo::listarComprasPorEmpleado(int idEmpleado) {
    FILE* p = fopen(_nombreArchivo, "rb");
    if (!p) {
        return -1;
    }

    Compra compra;
    bool encontro = false;

    cout << "COMPRAS DEL EMPLEADO " << idEmpleado << ":\n";
    cout << "==========================================\n";

    while (fread(&compra, tamanioRegistro, 1, p) == 1) {
        if (compra.getIdEmpleado() == idEmpleado && compra.getEstado()) {
            encontro = true;
            compra.mostrar();
            cout << "------------------------------\n";
        }
    }

    fclose(p);

    if (!encontro) {
        return -2;
    }

    return 1;
}



