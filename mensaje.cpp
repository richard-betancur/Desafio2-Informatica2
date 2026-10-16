#include "mensaje.h"

Mensaje::Mensaje(Usuario* quienEnvia,
                 Usuario* quienRecibe,
                 const string& texto,
                 const string& fechaMensaje)
{
    remitente = quienEnvia;
    destinatario = quienRecibe;
    contenido = texto;
    fecha = fechaMensaje;
    leido = false;
}

Mensaje::Mensaje(const Mensaje& otro)
{
    remitente = otro.remitente;
    destinatario = otro.destinatario;
    contenido = otro.contenido;
    fecha = otro.fecha;
    leido = otro.leido;
}

Usuario* Mensaje::getRemitente() const
{
    return remitente;
}

Usuario* Mensaje::getDestinatario() const
{
    return destinatario;
}

std::string Mensaje::getContenido() const
{
    return contenido;
}

std::string Mensaje::getFecha() const
{
    return fecha;
}

bool Mensaje::estaLeido() const
{
    return leido;
}

bool Mensaje::marcarLeido()
{
    if (leido)
        return false;

    leido = true;
    return true;
}

bool Mensaje::esValido() const
{
    return remitente != nullptr
           && destinatario != nullptr
           && !contenido.empty()
           && contenido.length() <= 512
           && !fecha.empty();
}

bool Mensaje::operator<(const Mensaje& otro) const
{
    return fecha < otro.fecha;
}