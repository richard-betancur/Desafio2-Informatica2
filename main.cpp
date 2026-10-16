#include <iostream>
#include "redsocial.h"
#include "usuario.h"

using namespace std;

int main()
{
    RedSocial red;

    // Prueba de la clase RedSocial
    red.agregarUsuario("Richard34", "clave123");
    red.agregarUsuario("Ana3232", "clave456");

    cout << "=== PRUEBA DE Ude@Book ===\n\n";

    // Crear un usuario con todos sus datos
    Usuario usuario(
        "pedro99",
        "2005-08-14",
        "pedro@example.com",
        "/users/pedro99/albums/profile.png",
        "clave789",
        "Medellin",
        "Colombia",
        "2026-01-15"
        );

    cout << "Datos del usuario:\n";
    cout << "Nombre: " << usuario.getNombreUsuario() << '\n';
    cout << "Nacimiento: " << usuario.getFechaNacimiento() << '\n';
    cout << "Correo: " << usuario.getCorreo() << '\n';
    cout << "Ruta del perfil: " << usuario.getRutaFotoPerfil() << '\n';
    cout << "Ciudad: " << usuario.getCiudad() << '\n';
    cout << "Pais: " << usuario.getPais() << '\n';
    cout << "Inscripcion: " << usuario.getFechaInscripcion() << '\n';

    // Probar un setter
    usuario.setCiudad("Bogota");

    cout << "\nCiudad despues del cambio: "
         << usuario.getCiudad() << '\n';

    // Probar la verificacion de contrasena
    if (usuario.verificarContraseña("clave789"))
    {
        cout << "Contrasena correcta.\n";
    }
    else
    {
        cout << "Contrasena incorrecta.\n";
    }

    // Probar el constructor de copia
    Usuario copia(usuario);

    cout << "\nUsuario copiado: "
         << copia.getNombreUsuario() << '\n';

    cout << "Ciudad del usuario copiado: "
         << copia.getCiudad() << '\n';

    // Verificar que la copia es independiente
    copia.setCiudad("Cali");

    cout << "\nCiudad original: "
         << usuario.getCiudad() << '\n';

    cout << "Ciudad de la copia: "
         << copia.getCiudad() << '\n';

    // Verificar que RedSocial sigue funcionando
    cout << "\nUsuarios en RedSocial: "
         << red.getCantidadUsuarios() << '\n';

    return 0;
}