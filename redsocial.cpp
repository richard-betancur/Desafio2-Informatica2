#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "redsocial.h"
#include "album.h"
#include "foto.h"


using namespace std;

RedSocial::RedSocial()
{
    capacidadUsuarios = 2;
    cantidadUsuarios = 0;
    usuarios = new Usuario*[capacidadUsuarios];

    capacidadSolicitudes = 2;
    cantidadSolicitudes = 0;
    solicitudes = new SolicitudAmistad*[capacidadSolicitudes];

    capacidadAmistades = 2;
    cantidadAmistades = 0;
    amigosA = new Usuario*[capacidadAmistades];
    amigosB = new Usuario*[capacidadAmistades];

    capacidadMensajes = 2;
    cantidadMensajes = 0;
    mensajes = new Mensaje*[capacidadMensajes];
}

RedSocial::~RedSocial()
{
    for (int i = 0; i < cantidadSolicitudes; i++)
        delete solicitudes[i];

    delete[] solicitudes;

    for (int i = 0; i < cantidadMensajes; i++)
        delete mensajes[i];

    delete[] mensajes;

    for (int i = 0; i < cantidadUsuarios; i++)
        delete usuarios[i];

    delete[] usuarios;
    delete[] amigosA;
    delete[] amigosB;
}

void RedSocial::ampliarCapacidad()
{
    int nuevaCapacidad = capacidadUsuarios * 2;
    Usuario** nuevoArreglo = new Usuario*[nuevaCapacidad];

    for (int i = 0; i < cantidadUsuarios; i++)
        nuevoArreglo[i] = usuarios[i];

    delete[] usuarios;
    usuarios = nuevoArreglo;
    capacidadUsuarios = nuevaCapacidad;
}

void RedSocial::ampliarSolicitudes()
{
    int nuevaCapacidad = capacidadSolicitudes * 2;
    SolicitudAmistad** nuevoArreglo = new SolicitudAmistad*[nuevaCapacidad];

    for (int i = 0; i < cantidadSolicitudes; i++)
    nuevoArreglo[i] = solicitudes[i];

    delete[] solicitudes;
    solicitudes = nuevoArreglo;
    capacidadSolicitudes = nuevaCapacidad;
}

void RedSocial::ampliarAmistades()
{
    int nuevaCapacidad = capacidadAmistades * 2;

    Usuario** nuevoA = new Usuario*[nuevaCapacidad];
    Usuario** nuevoB = new Usuario*[nuevaCapacidad];

    for (int i = 0; i < cantidadAmistades; i++)
    {
        nuevoA[i] = amigosA[i];
        nuevoB[i] = amigosB[i];
    }

    delete[] amigosA;
    delete[] amigosB;

    amigosA = nuevoA;
    amigosB = nuevoB;
    capacidadAmistades = nuevaCapacidad;
}

// Agregar usuario con nombre y contraseña
bool RedSocial::agregarUsuario(const std::string& nombre, const std::string& clave)
{
    if (buscarUsuario(nombre) != nullptr)
        return false;

    if (cantidadUsuarios == capacidadUsuarios)
        ampliarCapacidad();

    usuarios[cantidadUsuarios] = new Usuario(nombre, clave);
    cantidadUsuarios++;

    return true;
}

// Agregar usuario con todos sus datos
bool RedSocial::agregarUsuario(const string& nombre,
                               const string& nacimiento,
                               const string& correo,
                               const string& rutaFoto,
                               const string& clave,
                               const string& ciudad,
                               const string& pais,
                               const string& inscripcion)
{
    if (buscarUsuario(nombre) != nullptr)
        return false;

    if (cantidadUsuarios == capacidadUsuarios)
        ampliarCapacidad();

    usuarios[cantidadUsuarios] = new Usuario(
        nombre, nacimiento, correo, rutaFoto,
        clave, ciudad, pais, inscripcion
        );

    cantidadUsuarios++;
    return true;
}

Usuario* RedSocial::buscarUsuario(const string& nombre) const
{
    for (int i = 0; i < cantidadUsuarios; i++)
    {
        if (usuarios[i]->getNombreUsuario() == nombre)
            return usuarios[i];
    }

    return nullptr;
}

Usuario* RedSocial::obtenerUsuarioPorIndice(int indice) const
{
    if (indice < 0 || indice >= cantidadUsuarios)
        return nullptr;

    return usuarios[indice];
}

int RedSocial::getCantidadUsuarios() const
{
    return cantidadUsuarios;
}

// Enviar solicitud de amistad
bool RedSocial::enviarSolicitud(
    const string& nombreEmisor,
    const string& nombreReceptor,
    const string& fecha)
{
    Usuario* emisor = buscarUsuario(nombreEmisor);
    Usuario* receptor = buscarUsuario(nombreReceptor);

    if (emisor == nullptr || receptor == nullptr)
        return false;

    if (emisor == receptor)
        return false;

    if (sonAmigos(nombreEmisor, nombreReceptor))
        return false;

    // Evitar solicitudes pendientes duplicadas en cualquier dirección
    for (int i = 0; i < cantidadSolicitudes; i++)
    {
        SolicitudAmistad* solicitud = solicitudes[i];

        if (solicitud->estaPendiente())
        {
            bool mismaDireccion =
                solicitud->getEmisor() == emisor &&
                solicitud->getReceptor() == receptor;

            bool direccionContraria =
                solicitud->getEmisor() == receptor &&
                solicitud->getReceptor() == emisor;

            if (mismaDireccion || direccionContraria)
                return false;
        }
    }

    if (cantidadSolicitudes == capacidadSolicitudes)
        ampliarSolicitudes();

    solicitudes[cantidadSolicitudes] =
        new SolicitudAmistad(emisor, receptor, fecha);

    cantidadSolicitudes++;
    return true;
}

int RedSocial::getCantidadSolicitudes() const
{
    return cantidadSolicitudes;
}

SolicitudAmistad* RedSocial::obtenerSolicitudPorIndice(int indice) const
{
    if (indice < 0 || indice >= cantidadSolicitudes)
        return nullptr;

    return solicitudes[indice];
}

// Aceptar o rechazar una solicitud por su índice
bool RedSocial::responderSolicitud(int indice, bool aceptar)
{
    SolicitudAmistad* solicitud =
        obtenerSolicitudPorIndice(indice);

    if (solicitud == nullptr || !solicitud->estaPendiente())
        return false;

    if (!aceptar)
    {
        solicitud->rechazar();
        return true;
    }

    Usuario* emisor = solicitud->getEmisor();
    Usuario* receptor = solicitud->getReceptor();

    if (sonAmigos(emisor->getNombreUsuario(),
                  receptor->getNombreUsuario()))
    {
        solicitud->aceptar();
        return true;
    }

    if (cantidadAmistades == capacidadAmistades)
        ampliarAmistades();

    amigosA[cantidadAmistades] = emisor;
    amigosB[cantidadAmistades] = receptor;
    cantidadAmistades++;

    solicitud->aceptar();
    return true;
}

// Comprobar si existe una amistad mutua
bool RedSocial::sonAmigos(const string& nombreA,
                          const string& nombreB) const
{
    Usuario* usuarioA = buscarUsuario(nombreA);
    Usuario* usuarioB = buscarUsuario(nombreB);

    if (usuarioA == nullptr || usuarioB == nullptr)
        return false;

    for (int i = 0; i < cantidadAmistades; i++)
    {
        bool direccionNormal =
            amigosA[i] == usuarioA && amigosB[i] == usuarioB;

        bool direccionInversa =
            amigosA[i] == usuarioB && amigosB[i] == usuarioA;

        if (direccionNormal || direccionInversa)
            return true;
    }

    return false;
}

int RedSocial::getCantidadAmistades() const
{
    return cantidadAmistades;
}

void RedSocial::ampliarMensajes()
{
    int nuevaCapacidad = capacidadMensajes * 2;
    Mensaje** nuevoArreglo = new Mensaje*[nuevaCapacidad];

    for (int i = 0; i < cantidadMensajes; i++)
        nuevoArreglo[i] = mensajes[i];

    delete[] mensajes;
    mensajes = nuevoArreglo;
    capacidadMensajes = nuevaCapacidad;
}

bool RedSocial::enviarMensaje(
    const string& nombreEmisor,
    const string& nombreReceptor,
    const string& contenido,
    const string& fecha)
{
    Usuario* emisor = buscarUsuario(nombreEmisor);
    Usuario* receptor = buscarUsuario(nombreReceptor);

    // Ambos usuarios deben existir.
    if (emisor == nullptr || receptor == nullptr)
        return false;

    // Un usuario no puede enviarse mensajes a sí mismo.
    if (emisor == receptor)
        return false;

    // Solo se permiten mensajes entre amigos.
    if (!sonAmigos(nombreEmisor, nombreReceptor))
        return false;

    // El mensaje debe tener contenido y máximo 512 caracteres.
    if (contenido.empty() || contenido.length() > 512)
        return false;

    // La fecha es obligatoria.
    if (fecha.empty())
        return false;

    // Ampliar el arreglo si no queda espacio.
    if (cantidadMensajes == capacidadMensajes)
        ampliarMensajes();

    // Crear el mensaje dinámicamente.
    Mensaje* nuevoMensaje =
        new Mensaje(emisor, receptor, contenido, fecha);

    // Validar antes de guardarlo.
    if (!nuevoMensaje->esValido())
    {
        delete nuevoMensaje;
        return false;
    }

    mensajes[cantidadMensajes] = nuevoMensaje;
    cantidadMensajes++;

    return true;
}

int RedSocial::getCantidadMensajes() const
{
    return cantidadMensajes;
}

Mensaje* RedSocial::obtenerMensajePorIndice(int indice) const
{
    if (indice < 0 || indice >= cantidadMensajes)
        return nullptr;

    return mensajes[indice];
}

int RedSocial::leerMensajesNoLeidos(
    const string& nombreUsuario)
{
    Usuario* receptor = buscarUsuario(nombreUsuario);

    if (receptor == nullptr)
        return -1;

    int encontrados = 0;

    for (int i = 0; i < cantidadMensajes; i++)
    {
        if (mensajes[i]->getDestinatario() == receptor &&
            !mensajes[i]->estaLeido())
        {
            cout << "De: " << mensajes[i]->getRemitente()->getNombreUsuario() << "\n";

            cout << "Fecha: " << mensajes[i]->getFecha() << "\n";

            cout << "Mensaje: " << mensajes[i]->getContenido() << "\n\n";

            mensajes[i]->marcarLeido();
            encontrados++;
        }
    }

    return encontrados;
}

int RedSocial::buscarMensajesPorFecha(
    const string& nombreUsuario,
    const string& fechaInicio,
    const string& fechaFin) const
{
    Usuario* receptor = buscarUsuario(nombreUsuario);

    if (receptor == nullptr || fechaInicio > fechaFin)
        return -1;

    int encontrados = 0;

    for (int i = 0; i < cantidadMensajes; i++)
    {
        Mensaje* mensaje = mensajes[i];

        if (mensaje->getDestinatario() == receptor &&
            mensaje->getFecha().substr(0, 10) >= fechaInicio &&
            mensaje->getFecha().substr(0, 10) <= fechaFin)
        {
            cout << "De: " << mensaje->getRemitente()->getNombreUsuario() << "\n";

            cout << "Fecha: " << mensaje->getFecha() << "\n";

            cout << "Mensaje: " << mensaje->getContenido() << "\n\n";

            encontrados++;
        }
    }

    return encontrados;
}

int RedSocial::mostrarMensajesRecibidosOrdenados(
    const string& nombreUsuario) const
{
    Usuario* receptor = buscarUsuario(nombreUsuario);

    if (receptor == nullptr)
        return -1;

    // Reservar espacio para los mensajes recibidos
    Mensaje** recibidos = new Mensaje*[cantidadMensajes];
    int cantidadRecibidos = 0;

    // Buscar los mensajes dirigidos a este usuario
    for (int i = 0; i < cantidadMensajes; i++)
    {
        if (mensajes[i]->getDestinatario() == receptor)
        {
            recibidos[cantidadRecibidos] = mensajes[i];
            cantidadRecibidos++;
        }
    }

    // Ordenar por fecha ascendente mediante inserción
    for (int i = 1; i < cantidadRecibidos; i++)
    {
        Mensaje* actual = recibidos[i];
        int j = i - 1;

        while (j >= 0 && *actual < *recibidos[j])
        {
            recibidos[j + 1] = recibidos[j];
            j--;
        }

        recibidos[j + 1] = actual;
    }

    // Mostrar los mensajes del más antiguo al más reciente
    for (int i = 0; i < cantidadRecibidos; i++)
    {
        cout << "De: " << recibidos[i]->getRemitente()->getNombreUsuario() << "\n";

        cout << "Fecha: " << recibidos[i]->getFecha() << "\n";

        cout << "Mensaje: " << recibidos[i]->getContenido() << "\n\n";
    }

    delete[] recibidos;

    return cantidadRecibidos;
}


int RedSocial::mostrarAlbumesVisibles(
    const string& nombreVisitante,
    const string& nombrePropietario) const
{
    Usuario* visitante = buscarUsuario(nombreVisitante);
    Usuario* propietario = buscarUsuario(nombrePropietario);

    if (visitante == nullptr || propietario == nullptr)
        return -1;

    bool amistad = sonAmigos(nombreVisitante, nombrePropietario);
    int encontrados = 0;

    cout << "\nAlbumes de " << nombrePropietario << ":\n\n";

    for (int i = 0; i < propietario->getCantidadAlbumes(); i++)
    {
        Album* album = propietario->obtenerAlbumPorIndice(i);

        if (album != nullptr &&
            album->puedeVerlo(visitante, propietario, amistad))
        {
            cout << encontrados << ". " << album->getNombre() << " | Fotos: " << album->getCantidadFotos() << '\n';

            encontrados++;
        }
    }

    if (encontrados == 0)
        cout << "No hay albumes visibles.\n";

    return encontrados;
}


Album* RedSocial::obtenerAlbumVisible(
    const string& nombreVisitante,
    const string& nombrePropietario,
    int indiceAlbumVisible) const
{
    if (indiceAlbumVisible < 0)
        return nullptr;

    Usuario* visitante = buscarUsuario(nombreVisitante);
    Usuario* propietario = buscarUsuario(nombrePropietario);

    if (visitante == nullptr || propietario == nullptr)
        return nullptr;

    bool amistad = sonAmigos(nombreVisitante, nombrePropietario);
    int indiceVisible = 0;

    for (int i = 0; i < propietario->getCantidadAlbumes(); i++)
    {
        Album* album = propietario->obtenerAlbumPorIndice(i);

        if (album != nullptr &&
            album->puedeVerlo(visitante, propietario, amistad))
        {
            if (indiceVisible == indiceAlbumVisible)
                return album;

            indiceVisible++;
        }
    }

    return nullptr;
}


bool RedSocial::darLikeFoto(
    const string& nombreVisitante,
    const string& nombrePropietario,
    int indiceAlbumVisible,
    int indiceFoto)
{
    Album* album = obtenerAlbumVisible(
        nombreVisitante,
        nombrePropietario,
        indiceAlbumVisible);

    if (album == nullptr)
        return false;

    Foto* foto = album->obtenerFotoPorIndice(indiceFoto);

    if (foto == nullptr)
        return false;

    return foto->darLike();
}


bool RedSocial::quitarLikeFoto(
    const string& nombreVisitante,
    const string& nombrePropietario,
    int indiceAlbumVisible,
    int indiceFoto)
{
    Album* album = obtenerAlbumVisible(
        nombreVisitante,
        nombrePropietario,
        indiceAlbumVisible);

    if (album == nullptr)
        return false;

    Foto* foto = album->obtenerFotoPorIndice(indiceFoto);

    if (foto == nullptr)
        return false;

    return foto->quitarLike();
}

int RedSocial::contarAmigosEnComun(
    const string& nombreUsuario1,
    const string& nombreUsuario2) const
{
    Usuario* usuario1 = buscarUsuario(nombreUsuario1);
    Usuario* usuario2 = buscarUsuario(nombreUsuario2);

    if (usuario1 == nullptr || usuario2 == nullptr)
        return -1;

    int comunes = 0;

    for (int i = 0; i < cantidadAmistades; i++)
    {
        Usuario* posibleAmigo = nullptr;

        // Buscar un extremo de la amistad que corresponda
        // al primer usuario.
        if (amigosA[i] == usuario1)
            posibleAmigo = amigosB[i];
        else if (amigosB[i] == usuario1)
            posibleAmigo = amigosA[i];

        if (posibleAmigo != nullptr)
        {
            // Verificar si ese amigo también es amigo del segundo.
            for (int j = 0; j < cantidadAmistades; j++)
            {
                if ((amigosA[j] == usuario2 &&
                     amigosB[j] == posibleAmigo) ||
                    (amigosB[j] == usuario2 &&
                     amigosA[j] == posibleAmigo))
                {
                    comunes++;
                    break;
                }
            }
        }
    }

    return comunes;
}

int RedSocial::mostrarAmigos(
    const string& nombreUsuario) const
{
    Usuario* usuario = buscarUsuario(nombreUsuario);

    if (usuario == nullptr)
    {
        cout << "El usuario no existe.\n";
        return -1;
    }

    int encontrados = 0;

    cout << "\nAmigos de " << nombreUsuario << ":\n";

    for (int i = 0; i < cantidadAmistades; i++)
    {
        Usuario* amigo = nullptr;

        if (amigosA[i] == usuario)
            amigo = amigosB[i];
        else if (amigosB[i] == usuario)
            amigo = amigosA[i];

        if (amigo != nullptr)
        {
            cout << "- " << amigo->getNombreUsuario() << '\n';
            encontrados++;
        }
    }

    if (encontrados == 0)
        cout << "Este usuario todavía no tiene amigos.\n";

    cout << "Total de amigos: " << encontrados << '\n';

    return encontrados;
}

int RedSocial::mostrarSugerencias(
    const string& nombreUsuario,
    int cantidadMaxima) const
{
    Usuario* usuario = buscarUsuario(nombreUsuario);

    if (usuario == nullptr || cantidadMaxima <= 0)
    {
        cout << "No se pueden mostrar las sugerencias.\n";
        return -1;
    }

    // Arreglos temporales creados dinámicamente.
    Usuario** candidatos = new Usuario*[cantidadUsuarios];
    int* puntuaciones = new int[cantidadUsuarios];

    int cantidadCandidatos = 0;

    // Buscar usuarios que todavía no sean amigos.
    for (int i = 0; i < cantidadUsuarios; i++)
    {
        Usuario* candidato = usuarios[i];

        if (candidato == nullptr || candidato == usuario)
            continue;

        if (sonAmigos(nombreUsuario, candidato->getNombreUsuario()))
            continue;

        int comunes = contarAmigosEnComun(
            nombreUsuario,
            candidato->getNombreUsuario());

        // Solo sugerir personas con al menos un amigo en común.
        if (comunes > 0)
        {
            candidatos[cantidadCandidatos] = candidato;
            puntuaciones[cantidadCandidatos] = comunes;
            cantidadCandidatos++;
        }
    }

    // Ordenar por amigos en común, de mayor a menor.
    for (int i = 1; i < cantidadCandidatos; i++)
    {
        Usuario* candidatoActual = candidatos[i];
        int puntuacionActual = puntuaciones[i];
        int j = i - 1;

        while (j >= 0 && puntuaciones[j] < puntuacionActual)
        {
            candidatos[j + 1] = candidatos[j];
            puntuaciones[j + 1] = puntuaciones[j];
            j--;
        }

        candidatos[j + 1] = candidatoActual;
        puntuaciones[j + 1] = puntuacionActual;
    }

    cout << "\nSugerencias de amistad para "
         << nombreUsuario << ":\n";

    int mostrados = cantidadCandidatos;

    if (mostrados > cantidadMaxima)
        mostrados = cantidadMaxima;

    for (int i = 0; i < mostrados; i++)
    {
        cout << i + 1 << ". "
             << candidatos[i]->getNombreUsuario()
             << " | Amigos en comun: "
             << puntuaciones[i] << '\n';
    }

    if (mostrados == 0)
    {
        cout << "No hay sugerencias con amigos en comun.\n";
    }

    delete[] candidatos;
    delete[] puntuaciones;

    return mostrados;
}

int RedSocial::mostrarTresAmigosAleatorios(
    const string& nombreUsuario) const
{
    Usuario* usuario = buscarUsuario(nombreUsuario);

    if (usuario == nullptr)
    {
        cout << "El usuario no existe.\n";
        return -1;
    }

    // Contar cuántos amigos tiene el usuario.
    int totalAmigos = 0;

    for (int i = 0; i < cantidadAmistades; i++)
    {
        if (amigosA[i] == usuario || amigosB[i] == usuario)
            totalAmigos++;
    }

    if (totalAmigos == 0)
    {
        cout << "Este usuario no tiene amigos para mostrar.\n";
        return 0;
    }

    // Guardar temporalmente los amigos y sus pesos.
    Usuario** candidatos = new Usuario*[totalAmigos];
    int* pesos = new int[totalAmigos];
    bool* seleccionados = new bool[totalAmigos];

    int posicion = 0;

    for (int i = 0; i < cantidadAmistades; i++)
    {
        Usuario* amigo = nullptr;

        if (amigosA[i] == usuario)
            amigo = amigosB[i];
        else if (amigosB[i] == usuario)
            amigo = amigosA[i];

        if (amigo == nullptr)
            continue;

        candidatos[posicion] = amigo;
        seleccionados[posicion] = false;

        int comunes = contarAmigosEnComun(
            nombreUsuario,
            amigo->getNombreUsuario());

        // Multiplicamos por dos los pesos para usar enteros:
        // peso 1.0 -> 2
        // peso 2.5 -> 5
        // peso 3.5 -> 7
        if (comunes <= 10)
            pesos[posicion] = 2;
        else if (comunes <= 20)
            pesos[posicion] = 5;
        else
            pesos[posicion] = 7;

        posicion++;
    }

    int cantidadAMostrar = totalAmigos;

    if (cantidadAMostrar > 3)
        cantidadAMostrar = 3;

    cout << "\nAmigos seleccionados aleatoriamente:\n";

    int mostrados = 0;

    while (mostrados < cantidadAMostrar)
    {
        int pesoTotal = 0;

        for (int i = 0; i < totalAmigos; i++)
        {
            if (!seleccionados[i])
                pesoTotal += pesos[i];
        }

        if (pesoTotal == 0)
            break;

        int sorteo = rand() % pesoTotal;
        int acumulado = 0;

        for (int i = 0; i < totalAmigos; i++)
        {
            if (seleccionados[i])
                continue;

            acumulado += pesos[i];

            if (sorteo < acumulado)
            {
                seleccionados[i] = true;

                cout << "\nUsuario: "
                     << candidatos[i]->getNombreUsuario()
                     << "\nFoto de perfil: "
                     << candidatos[i]->getRutaFotoPerfil()
                     << "\nPeso de seleccion: "
                     << pesos[i] << "\n";

                mostrados++;
                break;
            }
        }
    }

    delete[] candidatos;
    delete[] pesos;
    delete[] seleccionados;

    return mostrados;
}

void RedSocial::mostrarEstadisticas(int iteraciones) const
{
    if (iteraciones < 0)
        iteraciones = 0;

    unsigned long long memoriaEstimada = 0;

    // Memoria de los arreglos dinámicos de punteros.
    memoriaEstimada +=
        static_cast<unsigned long long>(capacidadUsuarios) *
        sizeof(Usuario*);

    memoriaEstimada +=
        static_cast<unsigned long long>(capacidadSolicitudes) *
        sizeof(SolicitudAmistad*);

    memoriaEstimada +=
        static_cast<unsigned long long>(capacidadAmistades) *
        sizeof(Usuario*) * 2;

    memoriaEstimada +=
        static_cast<unsigned long long>(capacidadMensajes) *
        sizeof(Mensaje*);

    // Tamaño base de los objetos almacenados.
    for (int i = 0; i < cantidadUsuarios; i++)
    {
        if (usuarios[i] != nullptr)
            memoriaEstimada += sizeof(Usuario);
    }

    for (int i = 0; i < cantidadSolicitudes; i++)
    {
        if (solicitudes[i] != nullptr)
            memoriaEstimada += sizeof(SolicitudAmistad);
    }

    for (int i = 0; i < cantidadMensajes; i++)
    {
        if (mensajes[i] != nullptr)
            memoriaEstimada += sizeof(Mensaje);
    }

    cout << "\n========== ESTADISTICAS ==========\n";
    cout << "Iteraciones realizadas: " << iteraciones << '\n';
    cout << "Memoria estimada: "
         << memoriaEstimada << " bytes\n";
    cout << "==================================\n";
}

int RedSocial::mostrarSolicitudesRecibidas(
    const string& nombreUsuario) const
{
    Usuario* usuario = buscarUsuario(nombreUsuario);

    if (usuario == nullptr)
        return -1;

    int encontrados = 0;

    cout << "\nSolicitudes recibidas pendientes:\n";

    for (int i = 0; i < cantidadSolicitudes; i++)
    {
        SolicitudAmistad* solicitud = solicitudes[i];

        if (solicitud->getReceptor() == usuario &&
            solicitud->estaPendiente())
        {
            cout << "Indice: " << i
                 << " | De: "
                 << solicitud->getEmisor()->getNombreUsuario()
                 << " | Fecha: "
                 << solicitud->getFecha() << '\n';

            encontrados++;
        }
    }

    if (encontrados == 0)
        cout << "No tienes solicitudes pendientes.\n";

    return encontrados;
}

bool RedSocial::responderSolicitudDeUsuario(
    const string& nombreUsuario,
    int indiceSolicitud,
    bool aceptar)
{
    Usuario* usuario = buscarUsuario(nombreUsuario);

    if (usuario == nullptr)
        return false;

    SolicitudAmistad* solicitud =
        obtenerSolicitudPorIndice(indiceSolicitud);

    if (solicitud == nullptr)
        return false;

    if (solicitud->getReceptor() != usuario)
        return false;

    if (!solicitud->estaPendiente())
        return false;

    return responderSolicitud(indiceSolicitud, aceptar);
}
