#include "foto.h"

Foto::Foto(const std::string& fecha,
           unsigned long long tamano,
           const std::string& rutaArchivo,
           int likes)
    : fechaCaptura(fecha),
    tamanoBytes(tamano),
    ruta(rutaArchivo),
    cantidadLikes(likes)
{
}

Foto::Foto(const Foto& otra)
    : fechaCaptura(otra.fechaCaptura),
    tamanoBytes(otra.tamanoBytes),
    ruta(otra.ruta),
    cantidadLikes(otra.cantidadLikes)
{
}

std::string Foto::getFechaCaptura() const
{
    return fechaCaptura;
}

unsigned long long Foto::getTamanoBytes() const
{
    return tamanoBytes;
}

std::string Foto::getRuta() const
{
    return ruta;
}

int Foto::getCantidadLikes() const
{
    return cantidadLikes;
}

bool Foto::darLike()
{
    if (!esValida())
        return false;

    cantidadLikes++;
    return true;
}

bool Foto::quitarLike()
{
    if (cantidadLikes <= 0)
        return false;

    cantidadLikes--;
    return true;
}

bool Foto::esValida() const
{
    return !fechaCaptura.empty()
    && !ruta.empty()
        && tamanoBytes > 0
        && cantidadLikes >= 0;
}

bool Foto::operator<(const Foto& otra) const
{
    return fechaCaptura < otra.fechaCaptura;
}
