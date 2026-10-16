#include <iostream>
#include "redsocial.h"

using namespace std;

int main()
{
    RedSocial red;

    red.agregarUsuario("juan", "clave1");
    red.agregarUsuario("ana", "clave2");
    red.agregarUsuario("pedro", "clave3");

    cout << "=== PRUEBA DE SOLICITUDES ===\n\n";

    if (red.enviarSolicitud("juan", "ana", "2026-10-16"))
        cout << "Solicitud de Juan a Ana enviada.\n";
    else
        cout << "No se pudo enviar la solicitud.\n";

    if (!red.enviarSolicitud("juan", "ana", "2026-10-16"))
        cout << "Solicitud duplicada rechazada correctamente.\n";

    cout << "\nSolicitudes registradas: "
         << red.getCantidadSolicitudes() << "\n";

    SolicitudAmistad* solicitud =
        red.obtenerSolicitudPorIndice(0);

    if (solicitud != nullptr)
    {
        cout << "Emisor: "
             << solicitud->getEmisor()->getNombreUsuario() << "\n";

        cout << "Receptor: "
             << solicitud->getReceptor()->getNombreUsuario() << "\n";

        cout << "Pendiente: "
             << (solicitud->estaPendiente() ? "Si" : "No") << "\n";
    }

    if (red.responderSolicitud(0, true))
        cout << "\nSolicitud aceptada.\n";

    if (red.sonAmigos("juan", "ana"))
        cout << "Juan y Ana ahora son amigos.\n";

    cout << "Total de amistades: "
         << red.getCantidadAmistades() << "\n";

    if (!red.enviarSolicitud("juan", "juan", "2026-10-16"))
        cout << "No se permiten solicitudes a uno mismo.\n";

    return 0;
}