
#include "usuario.h"
#include "album.h"

using namespace std;

// Constructor por defecto
Usuario::Usuario()
    : nombreUsuario(""),
    fechaNacimiento(""),
    correo(""),
    rutaFotoPerfil(""),
    contraseña(""),
    ciudad(""),
    pais(""),
    fechaInscripcion(""),
    albumes(nullptr),
    cantidadAlbumes(0),
    capacidadAlbumes(0)
{
}

// Constructor basico
Usuario::Usuario(const string& nombre, const string& clave)
    : nombreUsuario(nombre),
    fechaNacimiento(""),
    correo(""),
    rutaFotoPerfil(""),
    contraseña(clave),
    ciudad(""),
    pais(""),
    fechaInscripcion(""),
    albumes(nullptr),
    cantidadAlbumes(0),
    capacidadAlbumes(0)
{
}

// Constructor completo
Usuario::Usuario(const string& nombre,
                 const string& nacimiento,
                 const string& email,
                 const string& rutaPerfil,
                 const string& clave,
                 const string& ciudadUsuario,
                 const string& paisUsuario,
                 const string& inscripcion)
    : nombreUsuario(nombre),
    fechaNacimiento(nacimiento),
    correo(email),
    rutaFotoPerfil(rutaPerfil),
    contraseña(clave),
    ciudad(ciudadUsuario),
    pais(paisUsuario),
    fechaInscripcion(inscripcion),
    albumes(nullptr),
    cantidadAlbumes(0),
    capacidadAlbumes(0)
{
}

// Constructor de copia
Usuario::Usuario(const Usuario& otro)
    : nombreUsuario(otro.nombreUsuario),
    fechaNacimiento(otro.fechaNacimiento),
    correo(otro.correo),
    rutaFotoPerfil(otro.rutaFotoPerfil),
    contraseña(otro.contraseña),
    ciudad(otro.ciudad),
    pais(otro.pais),
    fechaInscripcion(otro.fechaInscripcion),
    albumes(nullptr),
    cantidadAlbumes(0),
    capacidadAlbumes(0)
{
    if (otro.cantidadAlbumes > 0)
    {
        albumes = new Album*[otro.cantidadAlbumes];
        capacidadAlbumes = otro.cantidadAlbumes;

        try
        {
            for (int i = 0; i < otro.cantidadAlbumes; i++)
            {
                albumes[i] = new Album(*otro.albumes[i]);
                cantidadAlbumes++;
            }
        }
        catch (...)
        {
            for (int i = 0; i < cantidadAlbumes; i++)
                delete albumes[i];

            delete[] albumes;
            throw;
        }
    }
}

// Destructor
Usuario::~Usuario()
{
    for (int i = 0; i < cantidadAlbumes; i++)
        delete albumes[i];

    delete[] albumes;
}

// Operador de asignacion
Usuario& Usuario::operator=(const Usuario& otro)
{
    if (this == &otro)
        return *this;

    // Preparar las copias antes de modificar el usuario actual
    Album** nuevosAlbumes = nullptr;
    int nuevosAlbumesCopiados = 0;
    int nuevaCapacidad = otro.cantidadAlbumes;

    if (nuevaCapacidad > 0)
    {
        nuevosAlbumes = new Album*[nuevaCapacidad];

        try
        {
            for (int i = 0; i < otro.cantidadAlbumes; i++)
            {
                nuevosAlbumes[i] = new Album(*otro.albumes[i]);
                nuevosAlbumesCopiados++;
            }
        }
        catch (...)
        {
            for (int i = 0; i < nuevosAlbumesCopiados; i++)
                delete nuevosAlbumes[i];

            delete[] nuevosAlbumes;
            throw;
        }
    }

    // Liberar los albumes anteriores
    for (int i = 0; i < cantidadAlbumes; i++)
        delete albumes[i];

    delete[] albumes;

    // Copiar los datos del usuario
    nombreUsuario = otro.nombreUsuario;
    fechaNacimiento = otro.fechaNacimiento;
    correo = otro.correo;
    rutaFotoPerfil = otro.rutaFotoPerfil;
    contraseña = otro.contraseña;
    ciudad = otro.ciudad;
    pais = otro.pais;
    fechaInscripcion = otro.fechaInscripcion;

    // Instalar el nuevo arreglo
    albumes = nuevosAlbumes;
    cantidadAlbumes = nuevosAlbumesCopiados;
    capacidadAlbumes = nuevaCapacidad;

    return *this;
}

// Getters
string Usuario::getNombreUsuario() const
{
    return nombreUsuario;
}

string Usuario::getFechaNacimiento() const
{
    return fechaNacimiento;
}

string Usuario::getCorreo() const
{
    return correo;
}

string Usuario::getRutaFotoPerfil() const
{
    return rutaFotoPerfil;
}

string Usuario::getContraseña() const
{
    return contraseña;
}

string Usuario::getCiudad() const
{
    return ciudad;
}

string Usuario::getPais() const
{
    return pais;
}

string Usuario::getFechaInscripcion() const
{
    return fechaInscripcion;
}

// Verificacion de contraseña
bool Usuario::verificarContraseña(const string& clave) const
{
    return contraseña == clave;
}

// Setters
void Usuario::setFechaNacimiento(const string& fecha)
{
    fechaNacimiento = fecha;
}

void Usuario::setCorreo(const string& email)
{
    correo = email;
}

void Usuario::setRutaFotoPerfil(const string& ruta)
{
    rutaFotoPerfil = ruta;
}

void Usuario::setContraseña(const string& clave)
{
    contraseña = clave;
}

void Usuario::setCiudad(const string& ciudadUsuario)
{
    ciudad = ciudadUsuario;
}

void Usuario::setPais(const string& paisUsuario)
{
    pais = paisUsuario;
}

void Usuario::setFechaInscripcion(const string& fecha)
{
    fechaInscripcion = fecha;
}

// Ampliar capacidad del arreglo dinamico de albumes
void Usuario::ampliarCapacidadAlbumes()
{
    int nuevaCapacidad;

    if (capacidadAlbumes == 0)
        nuevaCapacidad = 2;
    else
        nuevaCapacidad = capacidadAlbumes * 2;

    Album** nuevoArreglo = new Album*[nuevaCapacidad];

    for (int i = 0; i < cantidadAlbumes; i++)
        nuevoArreglo[i] = albumes[i];

    delete[] albumes;

    albumes = nuevoArreglo;
    capacidadAlbumes = nuevaCapacidad;
}

// Agregar un album
bool Usuario::agregarAlbum(const Album& album)
{
    if (album.getNombre().empty() || album.getRuta().empty())
        return false;

    if (album.getPrivacidad() < 0 || album.getPrivacidad() > 2)
        return false;

    if (cantidadAlbumes == capacidadAlbumes)
        ampliarCapacidadAlbumes();

    albumes[cantidadAlbumes] = new Album(album);
    cantidadAlbumes++;

    return true;
}

// Obtener cantidad de albumes
int Usuario::getCantidadAlbumes() const
{
    return cantidadAlbumes;
}

// Obtener album por indice
Album* Usuario::obtenerAlbumPorIndice(int indice) const
{
    if (indice < 0 || indice >= cantidadAlbumes)
        return nullptr;

    return albumes[indice];
}
