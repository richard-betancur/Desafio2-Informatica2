#include <iostream>
#include "redsocial.h"

using namespace std;

int main()
{
    RedSocial red;

    //Usuarios temporales para probar las clases
    red.agregarUsuario("Richard111", "clave123");
    red.agregarUsuario("Ana34", "clave456");
    red.agregarUsuario("Simon786", "clave789");

    cout << "=== Prueba inicial de Ude@Book ===\n\n";

    cout << "Usuarios almacenados: "
         << red.getCantidadUsuarios() << "\n\n";

    string nombre;
    string clave;

    cout << "Nombre de usuario: ";
    cin >> nombre;

    cout << "Contrasena: ";
    cin >> clave;

    Usuario* usuario = red.buscarUsuario(nombre);

    if (usuario != nullptr &&
        usuario->verificarContrasena(clave))
    {
        cout << "\nInicio de sesion de prueba correcto.\n";
        cout << "Bienvenido, "
             << usuario->getNombreUsuario() << "\n";
    }
    else
    {
        cout << "\nCredenciales incorrectas.\n";
    }

    return 0;
}