#pragma once
 class Empleado{
 private:
     int _IdEmpleado;
     char _Nombre[30];
     char _Apellido[30];
     int _Dni;
     char _Telefono[20];
     int _TipoCargo;
     char _Cargo[30];
     bool _Estado;
 public:
    Empleado();
    void Cargar(int id, int dni);
    void Mostrar();

    std::string GetTipoCargoeStr();

    void setIdEmpleado(int IdEmpleado);
    bool setTipoCargo(int TipoCargo);
    bool setCargo(const char *Cargo);
    bool SetNombre(char *Nombre);
    bool setApellido(char *Apellido);
    bool setDni(int Dni);
    bool setTelefono(char *Telefono);
    void SetEstado(bool Estado);

    int GetIdEmpleado();
    int GetTipoCargo();
    const char* GetCargo();
    char* GetNombre();
    char* GetApellido();
    int GetDni();
    char* GetTelefono();
    bool GetEstado();
 };
