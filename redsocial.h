#ifndef REDSOCIAL_H
#define REDSOCIAL_H

#include <string>
#include "usuario.h"
#include "solicitudamistad.h"

class RedSocial
{
private:
    // Usuarios
    Usuario** usuarios;
    int cantidadUsuarios;
    int capacidadUsuarios;

    // Solicitudes de amistad
    SolicitudAmistad** solicitudes;
    int cantidadSolicitudes;
    int capacidadSolicitudes;

    // Amistades mutuas: cada amistad conecta dos usuarios
    Usuario** amigosA;
    Usuario** amigosB;
    int cantidadAmistades;
    int capacidadAmistades;

    void ampliarCapacidad();
    void ampliarSolicitudes();
    void ampliarAmistades();

public:
    RedSocial();
    ~RedSocial();

    RedSocial(const RedSocial&) = delete;
    RedSocial& operator=(const RedSocial&) = delete;

    // Usuarios
    bool agregarUsuario(const string& nombre,
                        const string& clave);

    bool agregarUsuario(const string& nombre,
                        const string& nacimiento,
                        const string& correo,
                        const string& rutaFoto,
                        const string& clave,
                        const string& ciudad,
                        const string& pais,
                        const string& inscripcion);

    Usuario* buscarUsuario(const string& nombre) const;
    Usuario* obtenerUsuarioPorIndice(int indice) const;
    int getCantidadUsuarios() const;

    // Solicitudes
    bool enviarSolicitud(const string& nombreEmisor, const string& nombreReceptor, const string& fecha);

    int getCantidadSolicitudes() const;

    SolicitudAmistad* obtenerSolicitudPorIndice(int indice) const;

    bool responderSolicitud(int indice, bool aceptar);

    // Amistades
    bool sonAmigos(const string& nombreA, const string& nombreB) const;

    int getCantidadAmistades() const;
};

#endif