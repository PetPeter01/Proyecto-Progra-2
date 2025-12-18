#include <iostream>
#include <cstdio>
#include <cstring>
#include "ClienteArchivo.h"
using namespace std;

int ClienteArchivo::altaCliente(long long documento, int tipo) {
    Cliente reg;

    int pos = BuscarPorDocumento(documento);
    if (pos < 0) {
        reg.cargar(documento, tipo);
        reg.setEstado(true);
        if (agregarRegistro(reg) == 1) {
            return 1;
        } else {
            return -1;
        }
    }

    Cliente existente = leerRegistro(pos);
    if (!existente.getEstado()) {
        return -2;
    }

    return 0;
}

int ClienteArchivo::agregarRegistro(Cliente reg) {
    FILE* pCliente = fopen(_nombreArchivo, "ab");
    if (pCliente == nullptr) {
        cout << "ERROR DE ARCHIVO";
        return -1;
    }

    int escribio = fwrite(&reg, tamanioRegistro, 1, pCliente);
    fclose(pCliente);

    return escribio;
}

bool ClienteArchivo::listarRegistros() {
    Cliente cliente;
    FILE* pCliente = fopen(_nombreArchivo, "rb");

    if (pCliente == nullptr) {
        return false;
    }

    while (fread(&cliente, tamanioRegistro, 1, pCliente) == 1) {
        if (cliente.getEstado()) {
            cliente.mostrar();
        }
    }

    fclose(pCliente);
    return true;
}

Cliente ClienteArchivo::leerRegistro(int pos) {
    Cliente obj;
    FILE* pCliente = fopen(_nombreArchivo, "rb");

    if (pCliente == nullptr) {
        return obj;
    }

    fseek(pCliente, pos * tamanioRegistro, 0);
    fread(&obj, tamanioRegistro, 1, pCliente);
    fclose(pCliente);

    return obj;
}

bool ClienteArchivo::bajaLogica() {

    Cliente reg;
    FILE* pCliente = fopen(_nombreArchivo, "rb");

    if (pCliente == nullptr) {
        cout << "ERROR AL ABRIR ARCHIVO\n";
        return false;
    }

    bool hay = false;
    cout << "Documentos cargados:\n";
    while (fread(&reg, tamanioRegistro, 1, pCliente) == 1) {
        if (reg.getEstado()) {
            cout << "- " << reg.getDocumento() << "\n";
            hay = true;
        }
    }

    fclose(pCliente);

    if (!hay) {
        cout << "No hay clientes activos para borrar.\n";
        return false;
    }

    cout << "Ingrese el documento (DNI/CUIT) del cliente a borrar: ";
    long long documento;
    cin >> documento;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Entrada invalida. Operacion cancelada.\n";
        return false;
    }

    int pos = BuscarPorDocumento(documento);
    if (pos < 0) {
        cout << "No existe un cliente con ese documento.\n";
        return false;
    }

    reg = leerRegistro(pos);
    if (!reg.getEstado()) {
        cout << "El cliente ya esta dado de baja.\n";
        return false;
    }

    reg.setEstado(false);
    if (modificarRegistro(reg, pos) == 1) {
        cout << "Cliente dado de baja correctamente.\n";
        return true;
    }

    cout << "No se pudo dar de baja al cliente.\n";
    return false;
}

int ClienteArchivo::modificarRegistro(Cliente reg, int pos) {
    FILE* pCliente = fopen(_nombreArchivo, "rb+");

    if (pCliente == nullptr) {
        return -1;
    }

    fseek(pCliente, pos * tamanioRegistro, 0);
    int escribio = fwrite(&reg, tamanioRegistro, 1, pCliente);
    fclose(pCliente);

    if (escribio != 1) {
        return -2;
    }

    return 1;
}

int ClienteArchivo::BuscarPorDocumento(long long documentoBuscado) {
    Cliente cliente;
    FILE* pCliente = fopen(_nombreArchivo, "rb");

    if (pCliente == nullptr) {
        return -2;
    }

    int pos = 0;
    while (fread(&cliente, tamanioRegistro, 1, pCliente) == 1) {
        if (cliente.getDocumento() == documentoBuscado) {
            fclose(pCliente);
            return pos;
        }
        pos++;
    }

    fclose(pCliente);
    return -1;
}
void ClienteArchivo::BuscarPorNombre(const char* nombreBuscado) {
    Cliente reg;
    FILE* p = fopen(_nombreArchivo, "rb");

    if (p == nullptr) {
        cout << "ERROR AL ABRIR ARCHIVO\n";
        return;
    }

    bool encontrado = false;
    while (fread(&reg, tamanioRegistro, 1, p) == 1) {
        if (reg.getEstado() && strcmp(reg.getNombre(), nombreBuscado) == 0) {
            reg.mostrar();
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron clientes con ese nombre." << endl;
    }

    fclose(p);
}

void ClienteArchivo::BuscarPorApellido(const char* apellidoBuscado) {
    Cliente reg;
    FILE* p = fopen(_nombreArchivo, "rb");

    if (p == nullptr) {
        cout << "ERROR AL ABRIR ARCHIVO\n";
        return;
    }

    bool encontrado = false;
    while (fread(&reg, tamanioRegistro, 1, p) == 1) {
        if (reg.getEstado() && strcmp(reg.getApellido(), apellidoBuscado) == 0) {
            reg.mostrar();
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron clientes con ese apellido." << endl;
    }

    fclose(p);
}


int ClienteArchivo::reactivarCliente(long long documento) {
    int pos = BuscarPorDocumento(documento);
    if (pos >= 0) {
        Cliente c = leerRegistro(pos);
        if (c.getEstado()) {
            return 0;
        }
        c.setEstado(true);
        if (modificarRegistro(c, pos) == 1) {
            return 1;
        } else {
            return -1;
        }
    }
    return -2;
}

void ClienteArchivo::listarDocumentosDadosDeBaja() {
    Cliente reg;
    FILE* p = fopen(_nombreArchivo, "rb");

    if (p == nullptr) {
        cout << "ERROR AL ABRIR ARCHIVO\n";
        return;
    }

    bool hay = false;
    cout << "Documentos dados de baja:\n";
    while (fread(&reg, tamanioRegistro, 1, p) == 1) {
        if (!reg.getEstado()) {
            cout << "- " << reg.getDocumento() << "\n";
            hay = true;
        }
    }

    if (!hay) {
        cout << "No hay clientes dados de baja.\n";
    }

    fclose(p);
}

