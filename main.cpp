
#include <iostream>
#include "usuario.h"
#include "album.h"
#include "foto.h"

using namespace std;

int main()
{
    cout << "===== PRUEBA USUARIO Y ALBUMES =====\n\n";

    // Crear un usuario
    Usuario juan("juan", "clave123");

    // Crear fotos de prueba
    Foto foto1("2026-10-15", 2500000,
               "fotos/foto1.jpg", 3);

    Foto foto2("2026-10-16", 1800000,
               "fotos/foto2.jpg", 5);

    // Crear albumes
    Album vacaciones("Vacaciones", "albumes/vacaciones", 0);
    Album amigos("Amigos", "albumes/amigos", 1);

    vacaciones.agregarFoto(foto1);
    vacaciones.agregarFoto(foto2);

    // Asociar los albumes al usuario
    juan.agregarAlbum(vacaciones);
    juan.agregarAlbum(amigos);

    cout << "Usuario: " << juan.getNombreUsuario() << endl;
    cout << "Cantidad de albumes: "
         << juan.getCantidadAlbumes() << endl;

    cout << "\n--- Albumes del usuario ---\n";

    for (int i = 0; i < juan.getCantidadAlbumes(); i++)
    {
        Album* album = juan.obtenerAlbumPorIndice(i);

        if (album != nullptr)
        {
            cout << "Album: " << album->getNombre() << endl;
            cout << "Fotos: " << album->getCantidadFotos() << endl;
            cout << "Privacidad: " << album->getPrivacidad() << endl;
            cout << "----------------------\n";
        }
    }

    // Probar copia del usuario
    cout << "\n--- Copia del usuario ---\n";

    Usuario copiaJuan(juan);

    cout << "Usuario copiado: "
         << copiaJuan.getNombreUsuario() << endl;

    cout << "Albumes de la copia: "
         << copiaJuan.getCantidadAlbumes() << endl;

    // Comprobar que los albumes sean independientes
    Album* original = juan.obtenerAlbumPorIndice(0);
    Album* copia = copiaJuan.obtenerAlbumPorIndice(0);

    if (original != nullptr && copia != nullptr)
    {
        cout << "\nLikes originales antes: "
             << original->obtenerFotoPorIndice(0)->getCantidadLikes()
             << endl;

        copia->obtenerFotoPorIndice(0)->darLike();

        cout << "Likes en la copia despues de dar like: "
             << copia->obtenerFotoPorIndice(0)->getCantidadLikes()
             << endl;

        cout << "Likes originales despues: "
             << original->obtenerFotoPorIndice(0)->getCantidadLikes()
             << endl;
    }

    cout << "\n===== FIN DE LA PRUEBA =====\n";

    return 0;
}


