#include "redsocial.h"
#include "iostream"

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

    if (emisor == nullptr || receptor == nullptr)
        return false;

    if (emisor == receptor)
        return false;

    if (contenido.empty() || contenido.length() > 512)
        return false;

    if (fecha.empty())
        return false;

    if (cantidadMensajes == capacidadMensajes)
        ampliarMensajes();

    mensajes[cantidadMensajes] =
        new Mensaje(emisor, receptor, contenido, fecha);

    if (!mensajes[cantidadMensajes]->esValido())
    {
        delete mensajes[cantidadMensajes];
        return false;
    }

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