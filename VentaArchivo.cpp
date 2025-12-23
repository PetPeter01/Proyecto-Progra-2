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

    int idEmpleado = PedirEnteroValido("ID EMPLEADO: ");
    int posEmp = archEmp.BuscarPorId(idEmpleado);
    if (posEmp < 0) return -4;
    Empleado e = archEmp.leerRegistro(posEmp);
    if (!e.GetEstado()) return -5;
    if (e.GetTipoCargo() != 2) return -6;

    int idCliente = PedirEnteroValido("ID CLIENTE: ");
    int posCli = archCliente.BuscarPorId(idCliente);
    if(posCli < 0) return -1;
    Cliente c = archCliente.leerRegistro(posCli);
    if(!c.getEstado()) return -2;

    int idVenta = generarIdVenta();

    Venta v;
    v.cargar(idEmpleado, idVenta, idCliente, 0.0f);

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
    ClienteArchivo cliArch;
    EmpleadoArchivo empArch;
    DetalleVentaArchivo detArch;

    int cant = contarRegistros();
    if (cant == 0) {
        std::cout << "No hay ventas registradas.\n";
        return false;
    }

    for (int i = 0; i < cant; i++) {
        Venta v = leerRegistro(i);

        if (v.getEstado()) {

            int posCli = cliArch.BuscarPorId(v.getIdCliente());
            Cliente cli;
            if (posCli >= 0) cli = cliArch.leerRegistro(posCli);

            std::cout << "ID Venta: " << v.getIdVenta() << std::endl;

            if (posCli >= 0) {
                std::cout << "Cliente: "
                          << cli.getNombre() << " " << cli.getApellido() << std::endl;
                std::cout << "Tipo cliente: " << cli.getTipoClienteStr() << std::endl;
            } else {
                std::cout << "Cliente: (no encontrado)\n";
            }

            int posEmp = empArch.BuscarPorId(v.getIdEmpleado());
            Empleado emp;
            if (posEmp >= 0) emp = empArch.leerRegistro(posEmp);
            std::cout << "Empleado: " << emp.GetNombre() << " " << emp.GetApellido() << std::endl;

            std::cout << "Fecha: ";
            std::cout << v.getFechaVenta().toString();
            std::cout << std::endl;
            std::cout << "Importe: $" << v.getImporteTotal() << std::endl;
            std::cout << "Pago: " << v.getFormaPago() << std::endl;

            std::cout << "Detalles:\n";
            int cantDetalles = detArch.listarPorVenta(v.getIdVenta());
            if (cantDetalles == 0) {
                std::cout << "   (Sin ítems)\n";
            }

            std::cout << "------------------------------\n\n";
        }
    }
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

float VentaArchivo::recaudacionPorEmpleado(int idEmpleado){
    Venta venta;
    float total = 0.0f;
    FILE* p = fopen(_nombreArchivo, "rb");
    if(p == nullptr) return -1;

    while(fread(&venta, sizeof(Venta), 1, p) == 1){
        if(venta.getIdEmpleado() == idEmpleado && venta.getEstado()){
            total += venta.getImporteTotal();
        }
    }
    fclose(p);
    return total;
}


