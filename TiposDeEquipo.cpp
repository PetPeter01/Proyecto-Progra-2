#include "TiposDeEquipo.h"
#include <iostream>

using namespace std;

TiposDeEquipo::TiposDeEquipo() {
    _idTiposDeEquipo = 0;
    strcpy(_descripcion, "");
    _estado = false;
}

void TiposDeEquipo::mostrar() const {
    cout << "CODIGO: " << _idTiposDeEquipo << "\n";
    cout << "DESCRIPCION: " << _descripcion << "\n";
    cout << "ESTADO: " << (_estado ? "ACTIVO" : "INACTIVO") << "\n";
    cout << "-----------------------------\n";
}

int TiposDeEquipo::getIdTiposDeEquipo() const { return _idTiposDeEquipo; }
const char* TiposDeEquipo::getDescripcion() const { return _descripcion; }
bool TiposDeEquipo::getEstado() const { return _estado; }

std::string TiposDeEquipo::getEstadoStr() const {
    return _estado ? "ACTIVO" : "INACTIVO";
}

void TiposDeEquipo::setIdTiposDeEquipo(int id) { _idTiposDeEquipo = id; }
void TiposDeEquipo::setDescripcion(const char* desc) { strcpy(_descripcion, desc); }
void TiposDeEquipo::setEstado(bool estado) { _estado = estado; }
