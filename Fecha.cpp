#include "Fecha.h"

Fecha::Fecha() {
    _dia = _mes = _anio = 0;
}

Fecha::Fecha(int dia, int mes, int anio) {
    setAnio(anio);
    setMes(mes);
    setDia(dia);
}
void Fecha::cargar() {
    int dia, mes, anio;
    while (true) {
        std::cout << "Fecha (DD MM AAAA): ";

        std::cin >> dia >> mes >> anio;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Entrada invalida. Por favor, ingrese solo numeros.\n";
            continue;
        }

        if (!setDia(dia) || !setMes(mes) || !setAnio(anio)) {
            std::cout << "Fecha invalida. Intente nuevamente.\n";
            continue;
        }

        break;
    }
}

std::string Fecha::toString() {
    return std::to_string(_dia) + "/" +
           std::to_string(_mes) + "/" +
           std::to_string(_anio);
}

// ----------- Getters -----------

int Fecha::getDia() {
    return _dia;
}

int Fecha::getMes() {
    return _mes;
}

int Fecha::getAnio() {
    return _anio;
}

// ----------- Setters -----------

bool Fecha::setDia(int dia) {
    if (dia >= 1 && dia <= 31) {
        _dia = dia;
        return true;
    } else {
        return false;
    }
}

bool Fecha::setMes(int mes) {
    if (mes >= 1 && mes <= 12) {
        _mes = mes;
        return true;
    } else {
        return false;
    }
}

bool Fecha::setAnio(int anio){
    if (anio>=1925 && anio <=2100){
        _anio = anio;
        return true;
    } else {
        return false;
    }
}
