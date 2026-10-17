
#include <iostream>
#include "foto.h"

using namespace std;

int main()
{
    cout << "===== PRUEBA DE LA CLASE FOTO =====\n\n";

    // Crear una foto de prueba
    Foto foto1("2026-10-15", 2500000,
               "fotos/foto1.jpg", 3);

    cout << "Fecha: " << foto1.getFechaCaptura() << endl;
    cout << "Ruta: " << foto1.getRuta() << endl;
    cout << "Tamano: " << foto1.getTamanoBytes()
         << " bytes" << endl;
    cout << "Likes iniciales: "
         << foto1.getCantidadLikes() << endl;

    // Dar un like
    cout << "\nDando un like..." << endl;
    foto1.darLike();

    cout << "Likes actuales: "
         << foto1.getCantidadLikes() << endl;

    // Quitar un like
    cout << "\nQuitando un like..." << endl;
    foto1.quitarLike();

    cout << "Likes actuales: "
         << foto1.getCantidadLikes() << endl;

    // Probar el constructor de copia
    Foto foto2(foto1);

    cout << "\nLikes de la copia: "
         << foto2.getCantidadLikes() << endl;

    // Probar la validacion
    cout << "\nFoto valida: "
         << (foto1.esValida() ? "Si" : "No") << endl;

    // Intentar quitar likes cuando no quedan
    Foto foto3("2026-10-16", 100000,
               "fotos/foto3.jpg", 0);

    cout << "\nIntentando quitar un like de una foto sin likes..."
         << endl;

    if (foto3.quitarLike())
        cout << "Like eliminado." << endl;
    else
        cout << "No se puede quitar: la foto ya tiene cero likes."
             << endl;

    cout << "\n===== FIN DE LA PRUEBA =====\n";

    return 0;
}
