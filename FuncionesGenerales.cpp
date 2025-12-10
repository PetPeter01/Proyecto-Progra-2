#include "FuncionesGenerales.h"
#include <iostream>

bool esTextoValido(const char* texto) {
    for (int i = 0; texto[i] != '\0'; i++) {
        if (!isalpha(texto[i]) && texto[i] != ' ') {
            return false;
        }
    }
    return true;
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
