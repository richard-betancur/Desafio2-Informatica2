#include "redsocial.h"

RedSocial::RedSocial()
{
    capacidadUsuarios = 2;
    cantidadUsuarios = 0;

    usuarios = new Usuario*[capacidadUsuarios];
}

RedSocial::~RedSocial()
{
    for (int i = 0; i < cantidadUsuarios; i++)
    {
        delete usuarios[i];
    }

    delete[] usuarios;
}

void RedSocial::ampliarCapacidad()
{
    int nuevaCapacidad = capacidadUsuarios * 2;

    Usuario** nuevoArreglo = new Usuario*[nuevaCapacidad];

    for (int i = 0; i < cantidadUsuarios; i++)
    {
        nuevoArreglo[i] = usuarios[i];
    }

    delete[] usuarios;

    usuarios = nuevoArreglo;
    capacidadUsuarios = nuevaCapacidad;
}

bool RedSocial::agregarUsuario(const std::string& nombre, const std::string& clave)
{
    if (buscarUsuario(nombre) != nullptr)
    {
        return false;
    }

    if (cantidadUsuarios == capacidadUsuarios)
    {
        ampliarCapacidad();
    }

    usuarios[cantidadUsuarios] = new Usuario(nombre, clave);
    cantidadUsuarios++;

    return true;
}

Usuario* RedSocial::buscarUsuario(const std::string& nombre) const
{
    for (int i = 0; i < cantidadUsuarios; i++)
    {
        if (usuarios[i]->getNombreUsuario() == nombre)
        {
            return usuarios[i];
        }
    }

    return nullptr;
}

int RedSocial::getCantidadUsuarios() const
{
    return cantidadUsuarios;
}