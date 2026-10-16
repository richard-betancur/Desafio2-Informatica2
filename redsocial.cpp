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

bool RedSocial::agregarUsuario(const string& nombre, const string& clave)
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

Usuario* RedSocial::buscarUsuario(const string& nombre) const
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

Usuario* RedSocial::obtenerUsuarioPorIndice(int indice) const
{
    if (indice < 0 || indice >= cantidadUsuarios)
        return nullptr;

    return usuarios[indice];
}

bool RedSocial::agregarUsuario(const string& nombre,
                               const string& nacimiento,
                               const string& correo,
                               const string& rutaFoto,
                               const string& clave,
                               const string& ciudad,
                               const string& pais,
                               const string& inscripcion)
{
    // Evitar usuarios duplicados
    if (buscarUsuario(nombre) != nullptr)
        return false;

    // Ampliar el arreglo si está lleno
    if (cantidadUsuarios == capacidadUsuarios)
        ampliarCapacidad();

    // Crear el usuario con todos sus datos
    usuarios[cantidadUsuarios] = new Usuario(
        nombre,
        nacimiento,
        correo,
        rutaFoto,
        clave,
        ciudad,
        pais,
        inscripcion
        );

    cantidadUsuarios++;

    return true;
}