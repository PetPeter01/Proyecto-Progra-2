#include "VentaArchivo.h"
#include "Venta.h"
#include "cliente.h"
#include "ClienteArchivo.h"
#include "EmpleadoArchivo.h"
#include "DetalleVentaArchivo.h"
#include "FuncionesGenerales.h"
#include <iostream>

int VentaArchivo::altaVenta() {
    EmpleadoArchivo archEmp;
    ClienteArchivo archCliente;
    DetalleVentaArchivo archDetalle;

    int tipo = PedirEnteroValido("TIPO CLIENTE: 1. PARTICULAR / 2. EMPRESA ");
    long long documento;
    if (tipo == 1) {
        documento = PedirEnteroValido("DNI: ");
    }
    else if (tipo == 2) {
        documento = PedirEnteroValidoLargo("CUIT: ");
    }
    else {
        return -1;
    }
    int posCliente = archCliente.BuscarPorDocumento(documento);
    if (posCliente < 0) return -2;
    Cliente c = archCliente.leerRegistro(posCliente);
    if (!c.getEstado()) return -3;

    int idEmpleado = PedirEnteroValido("ID EMPLEADO: ");
    int posEmp = archEmp.BuscarPorId(idEmpleado);
    if (posEmp < 0) return -4;
    Empleado e = archEmp.leerRegistro(posEmp);
    if (!e.GetEstado()) return -5;
    if (e.GetTipoCargo() != 2) return -6;

    int idVenta = generarIdVenta();

    Venta v;
    v.cargar(idEmpleado, idVenta, documento, 0.0f);

    if (!agregarRegistro(v)) return -7;

    int posVenta = contarRegistros() - 1;

    float total = archDetalle.altaDetalle(idVenta, v.getFechaVenta());
    if (total <= 0) return -7;

    v.setImporteTotal(total);
    modificarRegistro(v, posVenta);

    return 1;
}


int VentaArchivo::modificarRegistro(Venta reg, int pos) {
    FILE* pVenta = fopen(_nombreArchivo, "rb+");

    if (pVenta == nullptr) {
        return -1;
    }

    fseek(pVenta, pos * tamanioRegistro, 0);
    int escribio = fwrite(&reg, tamanioRegistro, 1, pVenta);
    fclose(pVenta);

    if (escribio != 1) {
        return -2;
    }

    return 1;
}

bool VentaArchivo::agregarRegistro(Venta reg) {
    FILE* pVenta = fopen(_nombreArchivo, "ab");
    if (pVenta == nullptr) {
        std::cout << "ERROR DE ARCHIVO";
        return false;
    }

    int escribio = fwrite(&reg, tamanioRegistro, 1, pVenta);
    fclose(pVenta);

    return escribio == 1;
}

Venta VentaArchivo::leerRegistro(int pos) {
    Venta obj;
    FILE* pVenta = fopen(_nombreArchivo, "rb");

    obj.setIdVenta(-1);
    if (pVenta == nullptr) {
        return obj;
    }

    fseek(pVenta, pos * tamanioRegistro, 0);
    fread(&obj, tamanioRegistro, 1, pVenta);

    fclose(pVenta);
    return obj;
}

int VentaArchivo::ModificarRegistro(Venta reg, int pos) {
    FILE* pVenta = fopen(_nombreArchivo, "rb+");
    if (pVenta == nullptr) {
        return -1;
    }

    fseek(pVenta, pos * tamanioRegistro, 0);
    int escribio = fwrite(&reg, tamanioRegistro, 1, pVenta);

    fclose(pVenta);
    return escribio;
}

bool VentaArchivo::bajaLogica(int idVenta) {
    Venta reg;
    VentaArchivo archivo(_nombreArchivo);

    int pos = archivo.buscarPorId(idVenta);
    if (pos < 0) {
        return false;
    }

    reg = archivo.leerRegistro(pos);
    reg.setEstado(false);

    return archivo.ModificarRegistro(reg, pos) == 1;
}


int VentaArchivo::buscarPorId(int idVenta) {
    Venta venta;
    FILE* pVenta = fopen(_nombreArchivo, "rb");

    if (pVenta == nullptr) {
        return -2;
    }

    int pos = 0;
    while (fread(&venta, tamanioRegistro, 1, pVenta) == 1) {
        if (venta.getIdVenta() == idVenta) {
            fclose(pVenta);
            return pos;
        }
        pos++;
    }

    fclose(pVenta);
    return -3;
}

bool VentaArchivo::listarRegistros() {
    FILE* pVenta = fopen(_nombreArchivo, "rb");
    if (!pVenta) return false;
ClienteArchivo cliArch;
    Venta reg;
    DetalleVentaArchivo detArch;

    while (fread(&reg, tamanioRegistro, 1, pVenta) == 1) {
        if (!reg.getEstado()) continue;

        reg.mostrar();

        int pos = cliArch.BuscarPorDocumento(reg.getIdCliente());
        if (pos >= 0) {
            Cliente c = cliArch.leerRegistro(pos);
            std::cout << " Tipo Cliente: ";
            if (c.getTipoCliente() == 1)
                std::cout << "Particular\n";
            else if (c.getTipoCliente() == 2)
                std::cout << "Empresa\n";
        } else {
            std::cout << " Tipo Cliente: (No encontrado)\n";
        }


        std::cout << " Detalles:\n";
        int cant = detArch.listarPorVenta(reg.getIdVenta());
        if (cant == 0) std::cout << "   (Sin ítems)\n";

        std::cout << "------------------------------\n";
    }

    fclose(pVenta);
    return true;
}

int VentaArchivo::contarRegistros() {
    Venta venta;
    FILE* pVenta = fopen(_nombreArchivo, "rb");
    if (pVenta == nullptr) {
        return 0;
    }

    int contador = 0;
    while (fread(&venta, tamanioRegistro, 1, pVenta) == 1) {
        contador++;
    }

    fclose(pVenta);
    return contador;
}

int VentaArchivo::generarIdVenta() {
    return contarRegistros() + 1;
}

int VentaArchivo::reactivarVenta(int idVenta) {
    int pos = buscarPorId(idVenta);
    if (pos < 0) return -1;

    Venta reg = leerRegistro(pos);
    if (reg.getEstado()) return 0;

    reg.setEstado(true);

    if (ModificarRegistro(reg, pos) == 1) {
        return 1;
    } else {
        return -2;
    }
}


void VentaArchivo::BuscarMayorImportePorAnio() {
    int anio = PedirEnteroValido("INGRESE EL ANIO QUE QUIERE BUSCAR: ");
    int cantidad = contarRegistros();

    if (cantidad == 0) {
        cout << "No hay ventas registradas.\n";
        return;
    }

    float maxImporte = -1;
    int posMax = -1;

    for (int i = 0; i < cantidad; i++) {
        Venta v = leerRegistro(i);
        if (!v.getEstado()) continue;
        if (v.getFechaVenta().getAnio() != anio) continue;

        if (v.getImporteTotal() > maxImporte) {
            maxImporte = v.getImporteTotal();
            posMax = i;
        }
    }

    if (posMax == -1) {
        cout << "No hay ventas registradas en el anio " << anio << ".\n";
        return;
    }

    Venta maxVenta = leerRegistro(posMax);

    cout << "\nVENTA CON MAYOR IMPORTE EN " << anio << ":\n";
    cout << "---------------------------------------------\n";
    maxVenta.mostrar();


}

float VentaArchivo::recaudacionAnual(int anio) {
    Venta venta;
    float total = 0;
    FILE* p = fopen(_nombreArchivo, "rb");
    if (p == nullptr) return -1;

    while (fread(&venta, sizeof(Venta), 1, p) == 1) {
        if (venta.getEstado() && venta.getFechaVenta().getAnio() == anio) {
            total += venta.getImporteTotal();
        }
    }

    fclose(p);
    return total;
}

float VentaArchivo::recaudacionPorCliente(long long idCliente) {
    Venta venta;
    float total = 0;
    FILE* p = fopen(_nombreArchivo, "rb");
    if (p == nullptr) return -1;

    while (fread(&venta, sizeof(Venta), 1, p) == 1) {
        if (venta.getEstado() && venta.getIdCliente() == idCliente) {
            total += venta.getImporteTotal();
        }
    }

    fclose(p);
    return total;
}




