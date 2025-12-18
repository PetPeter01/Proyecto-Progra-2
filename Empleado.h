#pragma once
 class Empleado{
 private:
     int _IdEmpleado;
     char _Nombre[30];
     char _Apellido[30];
     char _Dni[15];
     char _Telefono[20];
     char _Cargo[30];
     bool _Estado;
 public:
    Empleado();
    void Cargar(int id);
    void Mostrar();


 void setIdEmpleado(int IdEmpleado);
 void SetNombre(char *Nombre);
void setApellido(char *Apellido);
void setDni(char *Dni);
void setTelefono(char *Telefono);
void setCargo(const char *Cargo);
void SetEstado(bool Estado);

int GetIdEmpleado();
char* GetNombre();
char* GetApellido();
char* GetDni();
char* GetTelefono();
const char* GetCargo();
bool GetEstado();
 };
