
#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <filesystem>

#include "redsocial.h"
#include "almacenamiento.h"
#include "usuario.h"
#include "solicitudamistad.h"
#include "mensaje.h"
#include "album.h"
#include "foto.h"

using namespace std;
namespace fs = std::filesystem;

// --------------------------------------------------
// Lectura segura de datos
// --------------------------------------------------

int leerEntero(const string& mensaje)
{
    int numero;

    while (true)
    {
        cout << mensaje;

        if (cin >> numero)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return numero;
        }

        cout << "Entrada invalida. Escribe un numero.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string leerTexto(const string& mensaje)
{
    string texto;

    cout << mensaje;
    getline(cin, texto);

    return texto;
}

// --------------------------------------------------
// Inicio de sesion
// --------------------------------------------------

Usuario* iniciarSesion(RedSocial& red)
{
    for (int intento = 1; intento <= 3; intento++)
    {
        cout << "\n========== INICIO DE SESION ==========\n";

        string usuario = leerTexto("Nombre de usuario: ");
        string contrasena = leerTexto("Contrasena: ");

        Usuario* encontrado = red.buscarUsuario(usuario);

        if (encontrado != nullptr &&
            encontrado->verificarContraseña(contrasena))
        {
            cout << "\nBienvenido a Ude@Book, "
                 << encontrado->getNombreUsuario() << "!\n";

            return encontrado;
        }

        cout << "Usuario o contrasena incorrectos.\n";
        cout << "Intento " << intento << " de 3.\n";
    }

    cout << "\nSe agotaron los intentos de inicio de sesion.\n";
    return nullptr;
}

// --------------------------------------------------
// Crear una cuenta de prueba si no hay usuarios
// --------------------------------------------------

bool prepararUsuarios(RedSocial& red, Almacenamiento& almacenamiento)
{
    cout << "\nCarpeta de ejecucion:\n"
         << fs::current_path().string() << "\n";

    cout << "Buscando archivo: "
         << fs::absolute("usuarios.txt").string() << "\n";

    bool existeArchivo = fs::exists("usuarios.txt");

    cout << "Existe usuarios.txt: "
         << (existeArchivo ? "SI" : "NO") << "\n";

    if (existeArchivo)
    {
        almacenamiento.cargarUsuarios(red, "usuarios.txt");
    }
    else
    {
        cout << "\nEl archivo usuarios.txt no existe.\n";
    }

    if (red.getCantidadUsuarios() == 0)
    {
        cout << "\nNo se encontraron usuarios guardados.\n";
        cout << "Se creara una cuenta de prueba.\n";

        bool creado = red.agregarUsuario(
            "admin",
            "01/01/2000",
            "admin@udeabook.com",
            "perfil_admin.jpg",
            "1234",
            "Medellin",
            "Colombia",
            "18/10/2026"
            );

        if (!creado)
        {
            cout << "No se pudo crear la cuenta de prueba.\n";
            return false;
        }

        if (!almacenamiento.guardarUsuarios(red, "usuarios.txt"))
        {
            cout << "No se pudieron guardar los usuarios.\n";
            cout << "Revisa los permisos de la carpeta.\n";
            return false;
        }

        cout << "\nCuenta de prueba creada y guardada.\n";
        cout << "Usuario: admin\n";
        cout << "Contrasena: 1234\n";
    }

    return true;
}

// --------------------------------------------------
// Menu principal
// --------------------------------------------------

void mostrarMenu()
{
    cout << "\n";
    cout << "========================================\n";
    cout << "             Ude@Book\n";
    cout << "========================================\n";
    cout << "1. Mostrar amigos\n";
    cout << "2. Enviar solicitud de amistad\n";
    cout << "3. Ver solicitudes recibidas\n";
    cout << "4. Responder solicitud de amistad\n";
    cout << "5. Ver sugerencias de amistad\n";
    cout << "6. Mostrar tres amigos aleatorios\n";
    cout << "7. Enviar mensaje\n";
    cout << "8. Leer mensajes no leidos\n";
    cout << "9. Mostrar mensajes recibidos por fecha\n";
    cout << "10. Buscar mensajes en un rango de fechas\n";
    cout << "11. Ver albumes de otro usuario\n";
    cout << "0. Cerrar sesion y salir\n";
    cout << "========================================\n";
}

// --------------------------------------------------
// Programa principal
// --------------------------------------------------

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    RedSocial red;
    Almacenamiento almacenamiento;

    cout << "========================================\n";
    cout << "       BIENVENIDO A Ude@Book\n";
    cout << "========================================\n";

    if (!prepararUsuarios(red, almacenamiento))
    {
        cout << "\nNo se pudo preparar la red social.\n";
        return 1;
    }

    Usuario* usuarioActual = iniciarSesion(red);

    if (usuarioActual == nullptr)
    {
        return 0;
    }

    const string nombreActual = usuarioActual->getNombreUsuario();

    int opcion;
    int iteraciones = 0;

    do
    {
        mostrarMenu();
        opcion = leerEntero("Selecciona una opcion: ");

        switch (opcion)
        {
        case 1:
        {
            iteraciones = red.mostrarAmigos(nombreActual);
            break;
        }

        case 2:
        {
            string destinatario =
                leerTexto("Nombre del usuario al que deseas enviar solicitud: ");

            string fecha = leerTexto(
                "Fecha de la solicitud (AAAA-MM-DD): ");

            if (red.enviarSolicitud(nombreActual, destinatario, fecha))
            {
                cout << "Solicitud enviada correctamente.\n";
            }
            else
            {
                cout << "No se pudo enviar la solicitud.\n";
            }

            iteraciones = 1;
            break;
        }

        case 3:
        {
            iteraciones = red.mostrarSolicitudesRecibidas(nombreActual);
            break;
        }

        case 4:
        {
            int indice = leerEntero(
                "Escribe el indice de la solicitud que deseas responder: ");

            cout << "1. Aceptar\n";
            cout << "2. Rechazar\n";

            int respuesta = leerEntero("Selecciona una opcion: ");

            if (respuesta != 1 && respuesta != 2)
            {
                cout << "Opcion invalida.\n";
            }
            else if (red.responderSolicitudDeUsuario(
                         nombreActual, indice, respuesta == 1))
            {
                cout << "Solicitud respondida correctamente.\n";
            }
            else
            {
                cout << "No se pudo responder la solicitud.\n";
                cout << "Verifica el indice y que la solicitud sea tuya.\n";
            }

            iteraciones = 1;
            break;
        }

        case 5:
        {
            int k = leerEntero(
                "Cuantas sugerencias deseas consultar: ");

            if (k < 1)
            {
                cout << "La cantidad debe ser mayor que cero.\n";
                iteraciones = 0;
            }
            else
            {
                iteraciones = red.mostrarSugerencias(nombreActual, k);
            }

            break;
        }

        case 6:
        {
            iteraciones = red.mostrarTresAmigosAleatorios(nombreActual);
            break;
        }

        case 7:
        {
            string destinatario =
                leerTexto("Destinatario del mensaje: ");

            string contenido =
                leerTexto("Escribe el mensaje (maximo 512 caracteres): ");

            if (contenido.length() > 512)
            {
                cout << "El mensaje supera el limite de 512 caracteres.\n";
                iteraciones = 1;
                break;
            }

            string fecha = leerTexto(
                "Fecha y hora del mensaje (formato AAAA-MM-DD HH:MM): ");

            if (red.enviarMensaje(
                    nombreActual, destinatario, contenido, fecha))
            {
                cout << "Mensaje enviado correctamente.\n";
            }
            else
            {
                cout << "No se pudo enviar el mensaje.\n";
                cout << "Comprueba que ambos usuarios sean amigos.\n";
            }

            iteraciones = 1;
            break;
        }

        case 8:
        {
            iteraciones = red.leerMensajesNoLeidos(nombreActual);
            break;
        }

        case 9:
        {
            iteraciones =
                red.mostrarMensajesRecibidosOrdenados(nombreActual);
            break;
        }

        case 10:
        {
            string fechaInicio =
                leerTexto("Fecha inicial (AAAA-MM-DD): ");

            string fechaFin =
                leerTexto("Fecha final (AAAA-MM-DD): ");

            iteraciones = red.buscarMensajesPorFecha(
                nombreActual, fechaInicio, fechaFin);

            break;
        }

        case 11:
        {
            string nombreVisitado =
                leerTexto("Nombre del usuario cuyos albumes deseas ver: ");

            iteraciones = red.mostrarAlbumesVisibles(
                nombreActual, nombreVisitado);

            break;
        }

        case 0:
        {
            cout << "\nGuardando usuarios...\n";

            if (almacenamiento.guardarUsuarios(red, "usuarios.txt"))
            {
                cout << "Usuarios guardados correctamente.\n";
            }
            else
            {
                cout << "No se pudieron guardar los usuarios.\n";
            }

            cout << "Cerrando Ude@Book. Hasta pronto!\n";
            break;
        }

        default:
        {
            cout << "Opcion invalida. Intenta de nuevo.\n";
            iteraciones = 0;
            break;
        }
        }

        if (opcion != 0)
        {
            cout << "\n---------- ESTADISTICAS ----------\n";
            red.mostrarEstadisticas(iteraciones);
        }

    } while (opcion != 0);

    return 0;
}
