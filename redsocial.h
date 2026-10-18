
#ifndef REDSOCIAL_H
#define REDSOCIAL_H

#include <string>
#include "usuario.h"
#include "solicitudamistad.h"
#include "mensaje.h"
#include "album.h"

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

    // Amistades mutuas
    Usuario** amigosA;
    Usuario** amigosB;
    int cantidadAmistades;
    int capacidadAmistades;

    void ampliarCapacidad();
    void ampliarSolicitudes();
    void ampliarAmistades();

    // Mensajes
    Mensaje** mensajes;
    int cantidadMensajes;
    int capacidadMensajes;

    void ampliarMensajes();

public:
    RedSocial();
    ~RedSocial();

    RedSocial(const RedSocial&) = delete;
    RedSocial& operator=(const RedSocial&) = delete;

    // Usuarios
    bool agregarUsuario(const string& nombre, const string& clave);

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

    // Mensajes
    bool enviarMensaje(const string& nombreEmisor, const string& nombreReceptor,
                       const string& contenido, const string& fecha);

    int getCantidadMensajes() const;

    Mensaje* obtenerMensajePorIndice(int indice) const;

    int leerMensajesNoLeidos(const string& nombreUsuario);

    int buscarMensajesPorFecha(const string& nombreUsuario, const string& fechaInicio, const string& fechaFin) const;

    int mostrarMensajesRecibidosOrdenados(
        const string& nombreUsuario) const;

    // Albumes y fotos
    int mostrarAlbumesVisibles(
        const string& nombreVisitante,
        const string& nombrePropietario) const;

    Album* obtenerAlbumVisible(
        const string& nombreVisitante,
        const string& nombrePropietario,
        int indiceAlbumVisible) const;

    bool darLikeFoto(
        const string& nombreVisitante,
        const string& nombrePropietario,
        int indiceAlbumVisible,
        int indiceFoto);

    bool quitarLikeFoto(
        const string& nombreVisitante,
        const string& nombrePropietario,
        int indiceAlbumVisible,
        int indiceFoto);

    int contarAmigosEnComun(
        const string& nombreUsuario1,
        const string& nombreUsuario2) const;

    int mostrarAmigos(const string& nombreUsuario) const;

    int mostrarSugerencias(
        const string& nombreUsuario,
        int cantidadMaxima) const;

    int mostrarTresAmigosAleatorios(
        const string& nombreUsuario) const;

    void mostrarEstadisticas(int iteraciones) const;

    int mostrarSolicitudesRecibidas(
        const string& nombreUsuario) const;

    bool responderSolicitudDeUsuario(
        const string& nombreUsuario,
        int indiceSolicitud,
        bool aceptar);
};

#endif
