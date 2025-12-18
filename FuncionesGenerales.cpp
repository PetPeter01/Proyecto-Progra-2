#include "FuncionesGenerales.h"
#include <limits>
#include <iostream>
using namespace std;

bool esTextoValido(const char* texto) {
    for (int i = 0; texto[i] != '\0'; i++) {
        if (!isalpha(texto[i]) && texto[i] != ' ') {
            return false;
        }
    }
    return true;
}

float pedirFloatValido(string texto) {
    float numero;

    while (true) {
        cout << texto;
        cin >> numero;

        if (cin.good()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return numero;
        }
        else {
            cout << "Entrada invalida. Por favor, ingrese un numero valido (ej: 3.14 o -0.5).\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

bool esEnteroValido(const char* entrada, int& numero) {
    for (int i = 0; entrada[i] != '\0'; i++) {
        if (!isdigit(entrada[i])) {
            return false;
        }
    }
    numero = atoi(entrada);
    return true;
}

int PedirEnteroValido(string texto) {
    char entrada[20];
    int numero;

    while (true) {
        cout << texto;
        cin >> entrada;

        if (esEnteroValido(entrada, numero)) {
            cin.ignore();
            break;
        }

        cout << "Numero invalido." << endl;
        system("pause");
        cin.ignore();
    }

    return numero;
}

long long PedirEnteroValidoLargo(string texto) {
    char entrada[30];
    long long numero;

    while (true) {
        cout << texto;
        cin >> entrada;

        bool esValido = true;
        for (int i = 0; entrada[i] != '\0'; i++) {
            if (!isdigit(entrada[i])) {
                esValido = false;
                break;
            }
        }

        if (esValido) {
            numero = stoll(entrada);
            cin.ignore();
            break;
        }

        cout << "Numero invalido." << endl;
        system("pause");
        cin.ignore();
    }

    return numero;
}
