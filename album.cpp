#include "album.h"
#include "usuario.h"

// Constructor
Album::Album(const string& nombreAlbum, const string& rutaAlbum, int nivelPrivacidad)
    :nombre(nombreAlbum),
    ruta(rutaAlbum),
    privacidad(nivelPrivacidad),
    fotos(nullptr),
    cantidadFotos(0),
    capacidadFotos(0)
{
    if (privacidad < 0 || privacidad > 2)
        privacidad = 2;
}

// Constructor de copia
Album::Album(const Album& otro)
    : nombre(otro.nombre),
    ruta(otro.ruta),
    privacidad(otro.privacidad),
    fotos(nullptr),
    cantidadFotos(0),
    capacidadFotos(0)
{
    if (otro.cantidadFotos > 0)
    {
        capacidadFotos = otro.cantidadFotos;
        fotos = new Foto*[capacidadFotos];

        for (int i = 0; i < otro.cantidadFotos; i++)
        {
            fotos[i] = new Foto(*otro.fotos[i]);
            cantidadFotos++;
        }
    }
}

// Destructor
Album::~Album()
{
    for (int i = 0; i < cantidadFotos; i++)
        delete fotos[i];

    delete[] fotos;
}

// Ampliar capacidad del arreglo dinamico
void Album::ampliarCapacidad()
{
    int nuevaCapacidad;

    if (capacidadFotos == 0)
        nuevaCapacidad = 2;
    else
        nuevaCapacidad = capacidadFotos * 2;

    Foto** nuevoArreglo = new Foto*[nuevaCapacidad];

    for (int i = 0; i < cantidadFotos; i++)
        nuevoArreglo[i] = fotos[i];

    delete[] fotos;

    fotos = nuevoArreglo;
    capacidadFotos = nuevaCapacidad;
}

// Getters
string Album::getNombre() const
{
    return nombre;
}

string Album::getRuta() const
{
    return ruta;
}

int Album::getPrivacidad() const
{
    return privacidad;
}

int Album::getCantidadFotos() const
{
    return cantidadFotos;
}

Foto* Album::obtenerFotoPorIndice(int indice) const
{
    if (indice < 0 || indice >= cantidadFotos)
        return nullptr;

    return fotos[indice];
}

// Consultas de privacidad
bool Album::esPublico() const
{
    return privacidad == 0;
}

bool Album::esSoloAmigos() const
{
    return privacidad == 1;
}

bool Album::esPrivado() const
{
    return privacidad == 2;
}

bool Album::puedeVerlo(const Usuario* visitante, const Usuario* propietario, bool sonAmigos) const
{
    if (visitante == nullptr || propietario == nullptr)
        return false;

    // El propietario siempre puede ver su album
    if (visitante == propietario)
        return true;

    if (esPublico())
        return true;

    if (esSoloAmigos() && sonAmigos)
        return true;

    return false;
}

// Agregar una foto preexistente
bool Album::agregarFoto(const Foto& foto)
{
    if (!foto.esValida())
        return false;

    if (cantidadFotos == capacidadFotos)
        ampliarCapacidad();

    fotos[cantidadFotos] = new Foto(foto);
    cantidadFotos++;

    return true;
}

// Operador de asignacion
Album& Album::operator=(const Album& otro)
{
    if (this == &otro)
        return *this;

    // Liberar las fotos actuales
    for (int i = 0; i < cantidadFotos; i++)
        delete fotos[i];

    delete[] fotos;

    fotos = nullptr;
    cantidadFotos = 0;
    capacidadFotos = 0;

    nombre = otro.nombre;
    ruta = otro.ruta;
    privacidad = otro.privacidad;

    // Copiar las fotos
    if (otro.cantidadFotos > 0)
    {
        capacidadFotos = otro.cantidadFotos;
        fotos = new Foto*[capacidadFotos];

        for (int i = 0; i < otro.cantidadFotos; i++)
        {
            fotos[i] = new Foto(*otro.fotos[i]);
            cantidadFotos++;
        }
    }

    return *this;
}
