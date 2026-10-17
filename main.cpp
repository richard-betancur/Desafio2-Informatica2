
#include <iostream>
#include "album.h"
#include "usuario.h"

using namespace std;


int main()
{
    cout << "===== PRUEBA DE LA CLASE ALBUM =====\n\n";

    // Crear usuarios de prueba
    Usuario propietario("juan", "clave1");
    Usuario amigo("ana", "clave2");
    Usuario desconocido("pedro", "clave3");

    // Crear fotos de prueba
    Foto foto1("2026-10-15", 2500000,
               "fotos/foto1.jpg", 3);

    Foto foto2("2026-10-16", 1800000,
               "fotos/foto2.jpg", 5);

    // Crear album publico
    Album albumPublico("Vacaciones", "albumes/vacaciones", 0);

    albumPublico.agregarFoto(foto1);
    albumPublico.agregarFoto(foto2);

    cout << "Album: " << albumPublico.getNombre() << endl;
    cout << "Cantidad de fotos: "
         << albumPublico.getCantidadFotos() << endl;

    cout << "\n--- Privacidad publica ---\n";
    cout << "Propietario: "
         << (albumPublico.puedeVerlo(&propietario, &propietario, false)
                 ? "Puede ver" : "No puede ver") << endl;

    cout << "Amigo: "
         << (albumPublico.puedeVerlo(&amigo, &propietario, true)
                 ? "Puede ver" : "No puede ver") << endl;

    cout << "Desconocido: "
         << (albumPublico.puedeVerlo(&desconocido, &propietario, false)
                 ? "Puede ver" : "No puede ver") << endl;

    // Crear album solo para amigos
    Album albumAmigos("Amigos", "albumes/amigos", 1);

    cout << "\n--- Privacidad solo amigos ---\n";
    cout << "Propietario: "
         << (albumAmigos.puedeVerlo(&propietario, &propietario, false)
                 ? "Puede ver" : "No puede ver") << endl;

    cout << "Amigo: "
         << (albumAmigos.puedeVerlo(&amigo, &propietario, true)
                 ? "Puede ver" : "No puede ver") << endl;

    cout << "Desconocido: "
         << (albumAmigos.puedeVerlo(&desconocido, &propietario, false)
                 ? "Puede ver" : "No puede ver") << endl;

    // Crear album privado
    Album albumPrivado("Personal", "albumes/personal", 2);

    cout << "\n--- Privacidad privada ---\n";
    cout << "Propietario: "
         << (albumPrivado.puedeVerlo(&propietario, &propietario, false)
                 ? "Puede ver" : "No puede ver") << endl;

    cout << "Amigo: "
         << (albumPrivado.puedeVerlo(&amigo, &propietario, true)
                 ? "Puede ver" : "No puede ver") << endl;

    // Probar el constructor de copia
    Album copia(albumPublico);

    cout << "\n--- Constructor de copia ---\n";
    cout << "Fotos en el original: "
         << albumPublico.getCantidadFotos() << endl;
    cout << "Fotos en la copia: "
         << copia.getCantidadFotos() << endl;

    // Consultar una foto
    Foto* fotoConsultada = copia.obtenerFotoPorIndice(0);

    if (fotoConsultada != nullptr)
    {
        cout << "\nPrimera foto de la copia: "
             << fotoConsultada->getRuta() << endl;

        cout << "Likes: "
             << fotoConsultada->getCantidadLikes() << endl;
    }

    cout << "\n===== FIN DE LA PRUEBA =====\n";

    return 0;
}

