#include "solicitudamistad.h"
#include "usuario.h"

SolicitudAmistad::SolicitudAmistad(
    Usuario* quienEnvia,
    Usuario* quienRecibe,
    const string& fechaSolicitud)
{
    emisor = quienEnvia;
    receptor = quienRecibe;
    fecha = fechaSolicitud;
    estado = 0;
}

SolicitudAmistad::SolicitudAmistad(
    const SolicitudAmistad& otra)
{
    emisor = otra.emisor;
    receptor = otra.receptor;
    fecha = otra.fecha;
    estado = otra.estado;
}

Usuario* SolicitudAmistad::getEmisor() const
{
    return emisor;
}

Usuario* SolicitudAmistad::getReceptor() const
{
    return receptor;
}

string SolicitudAmistad::getFecha() const
{
    return fecha;
}

int SolicitudAmistad::getEstado() const
{
    return estado;
}

void SolicitudAmistad::aceptar()
{
    if (estado == 0)
        estado = 1;
}

void SolicitudAmistad::rechazar()
{
    if (estado == 0)
        estado = 2;
}

bool SolicitudAmistad::estaPendiente() const
{
    return estado == 0;
}