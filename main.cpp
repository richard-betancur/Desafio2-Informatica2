
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

namespace fs = filesystem;

// --------------------------------------------------
// Lectura segura
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

        if (cin.eof())
            return 0;

        cout << "Entrada invalida. Escribe un numero.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string leerTexto(const string& mensaje)
{
    string texto;

    cout << mensaje;

    if (!getline(cin, texto))
        return string();

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

        string nombre = leerTexto("Nombre de usuario: ");
        string contrasena = leerTexto("Contrasena: ");

        Usuario* encontrado = red.buscarUsuario(nombre);

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
// Carrusel de fotos de un album
// --------------------------------------------------

int recorrerAlbum(
    RedSocial& red,
    const string& visitante,
    const string& propietario,
    int indiceAlbum)
{
    Album* album =
        red.obtenerAlbumVisible(visitante, propietario, indiceAlbum);

    if (album == nullptr)
    {
        cout << "No se pudo abrir ese album.\n";
        return 0;
    }

    const int total = album->getCantidadFotos();

    if (total == 0)
    {
        cout << "Este album no tiene fotos.\n";
        return 0;
    }

    int actual = 0;
    int operaciones = 0;
    bool salir = false;

    while (!salir)
    {
        Foto* foto = album->obtenerFotoPorIndice(actual);

        if (foto == nullptr)
        {
            cout << "No se pudo obtener la foto.\n";
            break;
        }

        cout << "\n========== CARRUSEL ==========\n";
        cout << "Album: " << album->getNombre() << "\n";
        cout << "Foto " << actual + 1 << " de " << total << "\n";
        cout << "Ruta: " << foto->getRuta() << "\n";
        cout << "Fecha: " << foto->getFechaCaptura() << "\n";
        cout << "Tamano (bytes): " << foto->getTamanoBytes() << "\n";
        cout << "Likes: " << foto->getCantidadLikes() << "\n";
        cout << "1. Siguiente foto\n";
        cout << "2. Foto anterior\n";
        cout << "3. Dar like\n";
        cout << "4. Quitar like\n";
        cout << "0. Salir del album\n";

        int opcion = leerEntero("Opcion: ");

        switch (opcion)
        {
        case 1:
            actual = (actual + 1) % total;
            ++operaciones;
            break;

        case 2:
            actual = (actual - 1 + total) % total;
            ++operaciones;
            break;

        case 3:
            if (red.darLikeFoto(
                    visitante, propietario, indiceAlbum, actual))
            {
                cout << "Like agregado.\n";
            }
            else
            {
                cout << "No se pudo agregar el like.\n";
            }

            ++operaciones;
            break;

        case 4:
            if (red.quitarLikeFoto(
                    visitante, propietario, indiceAlbum, actual))
            {
                cout << "Like quitado.\n";
            }
            else
            {
                cout << "No se pudo quitar el like.\n";
            }

            ++operaciones;
            break;

        case 0:
            salir = true;
            break;

        default:
            cout << "Opcion invalida.\n";
            ++operaciones;
            break;
        }
    }

    return operaciones;
}

// --------------------------------------------------
// Crear datos de demostracion
// --------------------------------------------------

bool prepararUsuarios(RedSocial& red, Almacenamiento& almacenamiento)
{
    cout << "\nCarpeta de ejecucion:\n";
    cout << fs::current_path().string() << "\n";

    const string archivoDatos = "udeabook.dat";

    cout << "Archivo de datos: "
         << fs::absolute(archivoDatos).string() << "\n";

    if (fs::exists(archivoDatos))
    {
        if (!almacenamiento.cargarTodo(red, archivoDatos))
        {
            cout << "No se pudieron cargar los datos o el archivo esta danado.\n";
            return false;
        }

        cout << "Datos existentes cargados correctamente.\n";
    }
    else
    {
        cout << "No existe archivo de datos. Se creara una red nueva.\n";
    }

    // Solo se crean las cuentas base cuando la red esta vacia.
    const bool redNueva = (red.getCantidadUsuarios() == 0);

    if (redNueva)
    {
        cout << "\nCreando cuentas de demostracion...\n";

        if (!red.agregarUsuario(
                "admin", "01/01/2000", "admin@udeabook.com",
                "imagenes/perfil_admin.png", "1234",
                "Medellin", "Colombia", "18/10/2026"))
        {
            cout << "No se pudo crear la cuenta admin.\n";
            return false;
        }

        red.agregarUsuario(
            "camila", "12/03/2002", "camila@udeabook.com",
            "imagenes/camila.png", "1234",
            "Medellin", "Colombia", "01/02/2025");

        red.agregarUsuario(
            "juan", "23/07/2001", "juan@udeabook.com",
            "imagenes/juan.png", "1234",
            "Bogota", "Colombia", "10/03/2025");

        red.agregarUsuario(
            "sofia", "05/11/2003", "sofia@udeabook.com",
            "imagenes/sofia.png", "1234",
            "Cali", "Colombia", "15/04/2025");

        red.agregarUsuario(
            "diego", "19/08/2000", "diego@udeabook.com",
            "imagenes/diego.png", "1234",
            "Medellin", "Colombia", "20/05/2025");

        red.agregarUsuario(
            "andres", "02/02/2001", "andres@udeabook.com",
            "imagenes/andres.png", "1234",
            "Pereira", "Colombia", "21/05/2025");

        red.agregarUsuario(
            "valentina", "14/09/2002", "valentina@udeabook.com",
            "imagenes/valentina.png", "1234",
            "Manizales", "Colombia", "22/05/2025");

        red.agregarUsuario(
            "mateo", "30/12/2000", "mateo@udeabook.com",
            "imagenes/mateo.png", "1234",
            "Bogota", "Colombia", "23/05/2025");
    }

    // Completar hasta 1000 usuarios.
    // Se comprueba cada nombre para evitar duplicados.
    for (int i = 1; i <= 992; ++i)
    {
        string sufijo = to_string(i);

        if (i < 10)
            sufijo = "00" + sufijo;
        else if (i < 100)
            sufijo = "0" + sufijo;

        string nombre = "usuario" + sufijo;

        if (red.buscarUsuario(nombre) == nullptr)
        {
            string correo = nombre + "@udeabook.com";
            string foto = "imagenes/" + nombre + ".png";

            red.agregarUsuario(
                nombre,
                "01/01/2000",
                correo,
                foto,
                "1234",
                "Medellin",
                "Colombia",
                "01/01/2026");
        }
    }

    // Los datos de prueba se crean una sola vez en una red nueva.
    if (redNueva)
    {
        cout << "\nCreando albumes, amistades y mensajes de prueba...\n";

        // Cada album tiene cinco fotos.
        auto agregarAlbumDemo = [](
                                    Usuario* usuario,
                                    const string& nombreAlbum,
                                    const string& rutaAlbum,
                                    int privacidad,
                                    const string& prefijoFoto)
        {
            if (usuario == nullptr)
                return;

            Album album(nombreAlbum, rutaAlbum, privacidad);

            album.agregarFoto(Foto(
                "2026-05-10", 145000, prefijoFoto + "_1.png", 2));

            album.agregarFoto(Foto(
                "2026-06-12", 198000, prefijoFoto + "_2.png", 1));

            album.agregarFoto(Foto(
                "2026-07-15", 160000, prefijoFoto + "_3.png", 0));

            album.agregarFoto(Foto(
                "2026-08-20", 175000, prefijoFoto + "_4.png", 3));

            album.agregarFoto(Foto(
                "2026-09-25", 210000, prefijoFoto + "_5.png", 1));

            usuario->agregarAlbum(album);
        };

        agregarAlbumDemo(
            red.buscarUsuario("admin"),
            "Mis recuerdos", "albumes/admin", 2,
            "imagenes/admin");

        agregarAlbumDemo(
            red.buscarUsuario("camila"),
            "Viajes", "albumes/camila", 0,
            "imagenes/camila_viaje");

        agregarAlbumDemo(
            red.buscarUsuario("camila"),
            "Otros viajes", "albumes/camila_2", 0,
            "imagenes/camila_extra");

        agregarAlbumDemo(
            red.buscarUsuario("juan"),
            "Familia", "albumes/juan", 1,
            "imagenes/juan");

        agregarAlbumDemo(
            red.buscarUsuario("sofia"),
            "Momentos", "albumes/sofia", 0,
            "imagenes/sofia");

        agregarAlbumDemo(
            red.buscarUsuario("diego"),
            "Deportes", "albumes/diego", 0,
            "imagenes/diego");

        agregarAlbumDemo(
            red.buscarUsuario("andres"),
            "Paisajes", "albumes/andres", 0,
            "imagenes/andres");

        agregarAlbumDemo(
            red.buscarUsuario("valentina"),
            "Estudio", "albumes/valentina", 0,
            "imagenes/valentina");

        agregarAlbumDemo(
            red.buscarUsuario("mateo"),
            "Conciertos", "albumes/mateo", 0,
            "imagenes/mateo");

        // Funcion auxiliar para crear amistades aceptadas.
        auto hacerAmigos = [&red](
                               const string& a,
                               const string& b)
        {
            if (red.enviarSolicitud(a, b, "2026-10-18"))
            {
                int cantidad = red.getCantidadSolicitudes();

                if (cantidad > 0)
                {
                    red.responderSolicitud(cantidad - 1, true);
                }
            }
        };

        // Amistades de admin.
        hacerAmigos("admin", "camila");
        hacerAmigos("admin", "juan");
        hacerAmigos("admin", "diego");
        hacerAmigos("admin", "andres");
        hacerAmigos("admin", "valentina");
        hacerAmigos("admin", "mateo");

        // Camila y Juan tienen una amiga en comun: Sofia.
        hacerAmigos("camila", "sofia");
        hacerAmigos("juan", "sofia");

        // usuario001 comparte seis amigos con admin.
        hacerAmigos("usuario001", "camila");
        hacerAmigos("usuario001", "juan");
        hacerAmigos("usuario001", "diego");
        hacerAmigos("usuario001", "andres");
        hacerAmigos("usuario001", "valentina");
        hacerAmigos("usuario001", "mateo");

        // Otros candidatos comparten dos amigos con admin.
        for (int i = 2; i <= 20; ++i)
        {
            string sufijo = to_string(i);

            if (i < 10)
                sufijo = "00" + sufijo;
            else
                sufijo = "0" + sufijo;

            string candidato = "usuario" + sufijo;

            hacerAmigos(candidato, "camila");
            hacerAmigos(candidato, "juan");
        }

        // Mensajes distribuidos durante mas de seis semanas.
        red.enviarMensaje(
            "camila", "admin",
            "Hola, bienvenido a Ude@Book!",
            "2026-09-01 10:00");

        red.enviarMensaje(
            "juan", "admin",
            "Este es un mensaje de septiembre.",
            "2026-09-10 14:30");

        red.enviarMensaje(
            "diego", "admin",
            "Nos vemos pronto.",
            "2026-09-20 16:00");

        red.enviarMensaje(
            "andres", "admin",
            "Te envio una actualizacion.",
            "2026-10-01 09:15");

        red.enviarMensaje(
            "valentina", "admin",
            "Espero que estes bien.",
            "2026-10-10 11:45");

        red.enviarMensaje(
            "mateo", "admin",
            "Mensaje de prueba de octubre.",
            "2026-10-18 09:30");
    }

    // Guardar despues de crear todos los usuarios y datos de prueba.
    if (!almacenamiento.guardarTodo(red, archivoDatos))
    {
        cout << "No se pudieron guardar todos los datos.\n";
        cout << "Revisa los permisos de la carpeta.\n";
        return false;
    }

    cout << "\nUsuarios registrados: "
         << red.getCantidadUsuarios() << "\n";

    if (red.getCantidadUsuarios() < 1000)
    {
        cout << "Advertencia: todavia no hay 1000 usuarios.\n";
    }
    else
    {
        cout << "Requisito de 1000 usuarios cumplido.\n";
    }

    cout << "Datos guardados en " << archivoDatos << ".\n";
    cout << "Cuentas principales: admin, camila, juan, sofia, diego, andres, valentina y mateo.\n";
    cout << "Contrasena de las cuentas de demostracion: 1234.\n";

    return true;
}

// --------------------------------------------------
// Menu principal
// --------------------------------------------------

void mostrarMenu()
{
    cout << "\n========================================\n";
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
    cout << "11. Ver albumes y recorrer fotos de otro usuario\n";
    cout << "0. Guardar y salir\n";
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
        return 0;

    const string nombreActual = usuarioActual->getNombreUsuario();

    cout << "\nUsuarios registrados: "
         << red.getCantidadUsuarios() << "\n";

    cout << "\nTus tres perfiles de amigos para descubrir:\n";

    int iteracionesIniciales =
        red.mostrarTresAmigosAleatorios(nombreActual);

    cout << "\n---------- ESTADISTICAS ----------\n";
    red.mostrarEstadisticas(iteracionesIniciales);

    bool actualizacionPerfilesUsada = false;
    int opcion = -1;
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

            string fecha =
                leerTexto("Fecha de la solicitud (AAAA-MM-DD): ");

            if (red.enviarSolicitud(nombreActual, destinatario, fecha))
                cout << "Solicitud enviada correctamente.\n";
            else
                cout << "No se pudo enviar la solicitud.\n";

            iteraciones = 1;
            break;
        }

        case 3:
        {
            iteraciones =
                red.mostrarSolicitudesRecibidas(nombreActual);
            break;
        }

        case 4:
        {
            int indice = leerEntero(
                "Indice de la solicitud que deseas responder: ");

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
            }

            iteraciones = 1;
            break;
        }

        case 5:
        {
            int k = leerEntero(
                "Cuantas sugerencias deseas consultar (1-20): ");

            if (k < 1 || k > 20)
            {
                cout << "La cantidad debe estar entre 1 y 20.\n";
                iteraciones = 0;
                break;
            }

            iteraciones = red.mostrarSugerencias(nombreActual, k);

            if (iteraciones > 0)
            {
                string candidato = leerTexto(
                    "Nombre de una persona sugerida (Enter para omitir): ");

                if (!candidato.empty())
                {
                    string fecha = leerTexto(
                        "Fecha de solicitud (AAAA-MM-DD): ");

                    if (red.contarAmigosEnComun(
                            nombreActual, candidato) > 0 &&
                        red.enviarSolicitud(
                            nombreActual, candidato, fecha))
                    {
                        cout << "Solicitud enviada correctamente.\n";
                    }
                    else
                    {
                        cout << "No se pudo enviar la solicitud.\n";
                        cout << "Comprueba los amigos en comun y las solicitudes pendientes.\n";
                    }
                }
            }

            break;
        }

        case 6:
        {
            if (actualizacionPerfilesUsada)
            {
                cout << "Ya utilizaste la actualizacion permitida en esta sesion.\n";
                iteraciones = 0;
            }
            else
            {
                iteraciones =
                    red.mostrarTresAmigosAleatorios(nombreActual);

                actualizacionPerfilesUsada = true;
            }

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
                "Fecha y hora del mensaje (AAAA-MM-DD HH:MM): ");

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

            if (iteraciones > 0)
            {
                int indiceAlbum = leerEntero(
                    "Indice del album que deseas abrir (-1 para cancelar): ");

                if (indiceAlbum >= 0)
                {
                    iteraciones += recorrerAlbum(
                        red, nombreActual, nombreVisitado, indiceAlbum);
                }
            }

            break;
        }

        case 0:
        {
            cout << "\nGuardando todos los datos...\n";

            if (almacenamiento.guardarTodo(red, "udeabook.dat"))
                cout << "Datos guardados correctamente.\n";
            else
                cout << "No se pudieron guardar todos los datos.\n";

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
