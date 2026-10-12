#include "usuario.h"

Usuario::Usuario(const string& nombre, const string& clave)
{
    nombreUsuario = nombre;
    contrasena = clave;
}

string Usuario::getNombreUsuario() const
{
    return nombreUsuario;
}

bool Usuario::verificarContrasena(const string& clave) const
{
    return contrasena == clave;
}