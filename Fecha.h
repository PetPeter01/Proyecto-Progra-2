#pragma once
#include <iostream>
#include <string>

class Fecha {
private:
    int _dia;
    int _mes;
    int _anio;

public:
    Fecha();
    void cargar();
    Fecha(int dia, int mes, int anio);

    int getDia();
    int getMes();
    int getAnio();

    bool setDia(int dia);
    bool setMes(int mes);
    bool setAnio(int anio);

    std::string toString();
};
