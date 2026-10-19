#include "almacenamiento.h"
#include "redsocial.h"
#include "usuario.h"
#include "album.h"
#include "foto.h"
#include "mensaje.h"
#include "solicitudamistad.h"

#include <fstream>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

bool Almacenamiento::guardarTodo(const RedSocial& red, const string& rutaArchivo) const
{
    ofstream out(rutaArchivo, ios::trunc);
    if (!out) return false;
    out << "UDEABOOK 2\n";
    out << "USUARIOS " << red.cantidadUsuarios << '\n';
    for (int i = 0; i < red.cantidadUsuarios; ++i) {
        const Usuario* u = red.usuarios[i];
        out << quoted(u->nombreUsuario) << ' ' << quoted(u->fechaNacimiento) << ' '
            << quoted(u->correo) << ' ' << quoted(u->rutaFotoPerfil) << ' '
            << quoted(u->contraseña) << ' ' << quoted(u->ciudad) << ' '
            << quoted(u->pais) << ' ' << quoted(u->fechaInscripcion) << '\n';
    }

    int totalAlbumes = 0;
    for (int i = 0; i < red.cantidadUsuarios; ++i)
        totalAlbumes += red.usuarios[i]->cantidadAlbumes;
    out << "ALBUMES " << totalAlbumes << '\n';
    for (int i = 0; i < red.cantidadUsuarios; ++i) {
        const Usuario* u = red.usuarios[i];
        for (int j = 0; j < u->cantidadAlbumes; ++j) {
            const Album* a = u->albumes[j];
            out << quoted(u->nombreUsuario) << ' ' << quoted(a->nombre) << ' '
                << quoted(a->ruta) << ' ' << a->privacidad << ' ' << a->cantidadFotos << '\n';
            for (int k = 0; k < a->cantidadFotos; ++k) {
                const Foto* f = a->fotos[k];
                out << quoted(f->fechaCaptura) << ' ' << f->tamanoBytes << ' '
                    << quoted(f->ruta) << ' ' << f->cantidadLikes << '\n';
            }
        }
    }

    out << "AMISTADES " << red.cantidadAmistades << '\n';
    for (int i = 0; i < red.cantidadAmistades; ++i)
        out << quoted(red.amigosA[i]->nombreUsuario) << ' '
            << quoted(red.amigosB[i]->nombreUsuario) << '\n';

    out << "SOLICITUDES " << red.cantidadSolicitudes << '\n';
    for (int i = 0; i < red.cantidadSolicitudes; ++i) {
        const SolicitudAmistad* s = red.solicitudes[i];
        out << quoted(s->emisor->nombreUsuario) << ' ' << quoted(s->receptor->nombreUsuario)
            << ' ' << quoted(s->fecha) << ' ' << s->estado << '\n';
    }

    out << "MENSAJES " << red.cantidadMensajes << '\n';
    for (int i = 0; i < red.cantidadMensajes; ++i) {
        const Mensaje* m = red.mensajes[i];
        out << quoted(m->remitente->nombreUsuario) << ' '
            << quoted(m->destinatario->nombreUsuario) << ' '
            << quoted(m->contenido) << ' ' << quoted(m->fecha) << ' '
            << (m->leido ? 1 : 0) << '\n';
    }
    out.flush();
    return static_cast<bool>(out);
}

bool Almacenamiento::cargarTodo(RedSocial& red, const string& rutaArchivo) const
{
    ifstream in(rutaArchivo);
    if (!in) return false;

    string magic;
    int version = 0;
    if (!(in >> magic >> version) || magic != "UDEABOOK" || version != 2)
        return false;

    string seccion;
    int cantidad = 0;
    if (!(in >> seccion >> cantidad) || seccion != "USUARIOS" || cantidad < 0 || cantidad > 100000)
        return false;
    for (int i = 0; i < cantidad; ++i) {
        string nombre, nacimiento, correo, rutaFoto, clave, ciudad, pais, inscripcion;
        if (!(in >> quoted(nombre) >> quoted(nacimiento) >> quoted(correo) >> quoted(rutaFoto)
              >> quoted(clave) >> quoted(ciudad) >> quoted(pais) >> quoted(inscripcion))) return false;
        if (!red.agregarUsuario(nombre, nacimiento, correo, rutaFoto, clave, ciudad, pais, inscripcion))
            return false;
    }

    if (!(in >> seccion >> cantidad) || seccion != "ALBUMES" || cantidad < 0 || cantidad > 1000000)
        return false;
    for (int i = 0; i < cantidad; ++i) {
        string propietario, nombreAlbum, rutaAlbum;
        int privacidad, cantidadFotos;
        if (!(in >> quoted(propietario) >> quoted(nombreAlbum) >> quoted(rutaAlbum) >> privacidad >> cantidadFotos)
            || cantidadFotos < 0 || cantidadFotos > 1000000) return false;
        Usuario* u = red.buscarUsuario(propietario);
        if (!u) return false;
        Album album(nombreAlbum, rutaAlbum, privacidad);
        for (int j = 0; j < cantidadFotos; ++j) {
            string fecha, ruta;
            unsigned long long tamano;
            int likes;
            if (!(in >> quoted(fecha) >> tamano >> quoted(ruta) >> likes) || likes < 0) return false;
            Foto foto(fecha, tamano, ruta, 0);
            for (int k = 0; k < likes; ++k) foto.darLike();
            if (!album.agregarFoto(foto)) return false;
        }
        if (!u->agregarAlbum(album)) return false;
    }

    if (!(in >> seccion >> cantidad) || seccion != "AMISTADES" || cantidad < 0 || cantidad > 10000000)
        return false;
    for (int i = 0; i < cantidad; ++i) {
        string a, b;
        if (!(in >> quoted(a) >> quoted(b))) return false;
        Usuario* ua = red.buscarUsuario(a); Usuario* ub = red.buscarUsuario(b);
        if (!ua || !ub || ua == ub) return false;
        if (red.cantidadAmistades == red.capacidadAmistades) red.ampliarAmistades();
        red.amigosA[red.cantidadAmistades] = ua;
        red.amigosB[red.cantidadAmistades] = ub;
        ++red.cantidadAmistades;
    }

    if (!(in >> seccion >> cantidad) || seccion != "SOLICITUDES" || cantidad < 0 || cantidad > 10000000)
        return false;
    for (int i = 0; i < cantidad; ++i) {
        string emisor, receptor, fecha; int estado;
        if (!(in >> quoted(emisor) >> quoted(receptor) >> quoted(fecha) >> estado) || estado < 0 || estado > 2)
            return false;
        Usuario* ue = red.buscarUsuario(emisor); Usuario* ur = red.buscarUsuario(receptor);
        if (!ue || !ur) return false;
        if (red.cantidadSolicitudes == red.capacidadSolicitudes) red.ampliarSolicitudes();
        SolicitudAmistad* s = new SolicitudAmistad(ue, ur, fecha);
        s->estado = estado;
        red.solicitudes[red.cantidadSolicitudes++] = s;
    }

    if (!(in >> seccion >> cantidad) || seccion != "MENSAJES" || cantidad < 0 || cantidad > 10000000)
        return false;
    for (int i = 0; i < cantidad; ++i) {
        string emisor, receptor, contenido, fecha; int leido;
        if (!(in >> quoted(emisor) >> quoted(receptor) >> quoted(contenido) >> quoted(fecha) >> leido)) return false;
        Usuario* ue = red.buscarUsuario(emisor); Usuario* ur = red.buscarUsuario(receptor);
        if (!ue || !ur) return false;
        if (red.cantidadMensajes == red.capacidadMensajes) red.ampliarMensajes();
        Mensaje* m = new Mensaje(ue, ur, contenido, fecha);
        if (leido) m->marcarLeido();
        red.mensajes[red.cantidadMensajes++] = m;
    }
    return true;
}

// Compatibilidad: estos métodos conservan el nombre antiguo, pero guardan/cargan todo.
bool Almacenamiento::guardarUsuarios(const RedSocial& red, const string& rutaArchivo) const
{ return guardarTodo(red, rutaArchivo); }

bool Almacenamiento::cargarUsuarios(RedSocial& red, const string& rutaArchivo) const
{ return cargarTodo(red, rutaArchivo); }
