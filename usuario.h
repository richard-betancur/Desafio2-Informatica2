#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <iostream>

using namespace std;

class Usuario
{
private:
    string nombreUsuario;
    string contrasena;

public:
    Usuario(const string& nombre, const string& clave);

    string getNombreUsuario() const;
    bool verificarContrasena(const string& clave) const;
};

#endif