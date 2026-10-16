#include <iostream>
#include "usuario.h"
#include "mensaje.h"

using namespace std;

int main()
{
    Usuario juan("juan", "clave1");
    Usuario ana("ana", "clave2");

    Mensaje mensaje(
        &juan,
        &ana,
        "Hola Ana, como estas?",
        "2026-10-16 10:30"
        );

    cout << "=== PRUEBA DE MENSAJES ===\n\n";

    cout << "Remitente: "
         << mensaje.getRemitente()->getNombreUsuario() << "\n";

    cout << "Destinatario: "
         << mensaje.getDestinatario()->getNombreUsuario() << "\n";

    cout << "Contenido: "
         << mensaje.getContenido() << "\n";

    cout << "Fecha: "
         << mensaje.getFecha() << "\n";

    cout << "Longitud: "
         << mensaje.getContenido().length()
         << " caracteres\n";

    cout << "Mensaje valido: "
         << (mensaje.esValido() ? "Si" : "No") << "\n";

    cout << "Leido inicialmente: "
         << (mensaje.estaLeido() ? "Si" : "No") << "\n";

    mensaje.marcarLeido();

    cout << "Leido despues de marcarlo: "
         << (mensaje.estaLeido() ? "Si" : "No") << "\n";

    Mensaje copia(mensaje);

    cout << "Contenido de la copia: "
         << copia.getContenido() << "\n";

    string textoLargo(513, 'A');

    Mensaje mensajeLargo(
        &juan,
        &ana,
        textoLargo,
        "2026-10-16 10:31"
        );

    cout << "Mensaje de 513 caracteres valido: "
         << (mensajeLargo.esValido() ? "Si" : "No") << "\n";

    return 0;
}