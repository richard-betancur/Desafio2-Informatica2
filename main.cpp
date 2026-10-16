#include <iostream>
#include "redsocial.h"

using namespace std;

int main()
{
    RedSocial red;

    red.agregarUsuario("juan", "clave1");
    red.agregarUsuario("ana", "clave2");
    red.agregarUsuario("pedro", "clave3");

    cout << "=== PRUEBA DE MENSAJES ===\n\n";

    red.enviarMensaje(
        "juan", "ana",
        "Mensaje del segundo dia",
        "2026-10-16 14:00"
        );

    red.enviarMensaje(
        "pedro", "ana",
        "Mensaje del primer dia",
        "2026-10-15 09:00"
        );

    red.enviarMensaje(
        "juan", "ana",
        "Mensaje de la manana",
        "2026-10-16 08:00"
        );

    cout << "Mensajes recibidos por Ana:\n\n";

    int cantidad =
        red.mostrarMensajesRecibidosOrdenados("ana");

    cout << "Total recibidos: " << cantidad << "\n\n";

    cout << "=== MENSAJES NO LEIDOS ===\n\n";

    int noLeidos = red.leerMensajesNoLeidos("ana");

    cout << "Mensajes marcados como leidos: "
         << noLeidos << "\n\n";

    cout << "=== BUSQUEDA POR FECHAS ===\n\n";

    int encontrados = red.buscarMensajesPorFecha(
        "ana",
        "2026-10-16",
        "2026-10-16"
        );

    cout << "Mensajes encontrados ese dia: "
         << encontrados << "\n";

    return 0;
}