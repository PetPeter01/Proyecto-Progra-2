#pragma once
#include <iostream>
using namespace std;

char* PedirTextoValido(string mensaje);

float pedirFloatValido(string texto);

bool esTextoValido(const char* texto);

bool esEnteroValido(const char* entrada, int& numero);

int PedirEnteroValido(string texto);

long long PedirEnteroValidoLargo(string texto);
