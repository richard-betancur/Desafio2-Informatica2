#include "almacenamiento.h"
#include "redsocial.h"
#include "usuario.h"

#include <fstream>
#include <sstream>

bool Almacenamiento::guardarUsuarios(const RedSocial& red, const std::string& rutaArchivo)
{
    std::ofstream archivo(rutaArchivo);

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

bool Almacenamiento::cargarUsuarios(RedSocial& red,
                                    const std::string& rutaArchivo)
{
    std::ifstream archivo(rutaArchivo);

    if (!archivo.is_open())
        return false;

    std::string linea;

    while (std::getline(archivo, linea))
    {
        if (linea.empty())
            continue;

        std::stringstream separador(linea);

        std::string nombre;
        std::string nacimiento;
        std::string correo;
        std::string rutaFoto;
        std::string contraseña;
        std::string ciudad;
        std::string pais;
        std::string inscripcion;

        if (!std::getline(separador, nombre, ';') ||
            !std::getline(separador, nacimiento, ';') ||
            !std::getline(separador, correo, ';') ||
            !std::getline(separador, rutaFoto, ';') ||
            !std::getline(separador, contraseña, ';') ||
            !std::getline(separador, ciudad, ';') ||
            !std::getline(separador, pais, ';') ||
            !std::getline(separador, inscripcion, ';'))
        {
            continue;
        }

        red.agregarUsuario(nombre, nacimiento, correo, rutaFoto,
                           contraseña, ciudad, pais, inscripcion);
    }

    archivo.close();
    return true;
}