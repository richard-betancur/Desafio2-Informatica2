#include "almacenamiento.h"
#include "redsocial.h"
#include "usuario.h"

#include <fstream>
#include <sstream>

bool Almacenamiento::guardarUsuarios(const RedSocial& red, const string& rutaArchivo)
{
    ofstream archivo(rutaArchivo);

    if (!archivo.is_open())
        return false;

    for (int i = 0; i < red.getCantidadUsuarios(); i++)
    {
        // Esta función la añadiremos a RedSocial.
        Usuario* usuario = red.obtenerUsuarioPorIndice(i);

        archivo << usuario->getNombreUsuario() << ";"
                << usuario->getFechaNacimiento() << ";"
                << usuario->getCorreo() << ";"
                << usuario->getRutaFotoPerfil() << ";"
                << usuario->getContraseña() << ";"
                << usuario->getCiudad() << ";"
                << usuario->getPais() << ";"
                << usuario->getFechaInscripcion() << "\n";
    }

    archivo.close();
    return true;
}

bool Almacenamiento::cargarUsuarios(RedSocial& red, const string& rutaArchivo)
{
    ifstream archivo(rutaArchivo);

    if (!archivo.is_open())
        return false;
    string linea;

    while (getline(archivo, linea))
    {
        if (linea.empty())
            continue;

        stringstream separador(linea);

        string nombre;
        string nacimiento;
        string correo;
        string rutaFoto;
        string contraseña;
        string ciudad;
        string pais;
        string inscripcion;

        if (!getline(separador, nombre, ';') ||
            !getline(separador, nacimiento, ';') ||
            !getline(separador, correo, ';') ||
            !getline(separador, rutaFoto, ';') ||
            !getline(separador, contraseña, ';') ||
            !getline(separador, ciudad, ';') ||
            !getline(separador, pais, ';') ||
            !getline(separador, inscripcion, ';'))
        {
            continue;
        }

        red.agregarUsuario(nombre, nacimiento, correo, rutaFoto, contraseña, ciudad, pais, inscripcion);
    }

    archivo.close();
    return true;
}