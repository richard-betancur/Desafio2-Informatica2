#include "usuario.h"

using namespace std;

// Constructor por defecto
Usuario::Usuario()
{
    nombreUsuario = "";
    fechaNacimiento = "";
    correo = "";
    rutaFotoPerfil = "";
    contrasena = "";
    ciudad = "";
    pais = "";
    fechaInscripcion = "";
}

// Constructor básico
Usuario::Usuario(const string& nombre, const string& clave)
{
    nombreUsuario = nombre;
    contrasena = clave;

    fechaNacimiento = "";
    correo = "";
    rutaFotoPerfil = "";
    ciudad = "";
    pais = "";
    fechaInscripcion = "";
}

// Constructor completo
Usuario::Usuario(const string& nombre,
                 const string& nacimiento,
                 const string& email,
                 const string& rutaPerfil,
                 const string& clave,
                 const string& ciudadUsuario,
                 const string& paisUsuario,
                 const string& inscripcion)
{
    nombreUsuario = nombre;
    fechaNacimiento = nacimiento;
    correo = email;
    rutaFotoPerfil = rutaPerfil;
    contrasena = clave;
    ciudad = ciudadUsuario;
    pais = paisUsuario;
    fechaInscripcion = inscripcion;
}

// Constructor de copia
Usuario::Usuario(const Usuario& otro)
{
    nombreUsuario = otro.nombreUsuario;
    fechaNacimiento = otro.fechaNacimiento;
    correo = otro.correo;
    rutaFotoPerfil = otro.rutaFotoPerfil;
    contrasena = otro.contrasena;
    ciudad = otro.ciudad;
    pais = otro.pais;
    fechaInscripcion = otro.fechaInscripcion;
}

// Getters
string Usuario::getNombreUsuario() const
{
    return nombreUsuario;
}

string Usuario::getFechaNacimiento() const
{
    return fechaNacimiento;
}

string Usuario::getCorreo() const
{
    return correo;
}

string Usuario::getRutaFotoPerfil() const
{
    return rutaFotoPerfil;
}

string Usuario::getCiudad() const
{
    return ciudad;
}

string Usuario::getPais() const
{
    return pais;
}

string Usuario::getFechaInscripcion() const
{
    return fechaInscripcion;
}

// Verificación de contraseña
bool Usuario::verificarContrasena(const string& clave) const
{
    return contrasena == clave;
}

// Setters
void Usuario::setFechaNacimiento(const string& fecha)
{
    fechaNacimiento = fecha;
}

void Usuario::setCorreo(const string& email)
{
    correo = email;
}

void Usuario::setRutaFotoPerfil(const string& ruta)
{
    rutaFotoPerfil = ruta;
}

void Usuario::setContrasena(const string& clave)
{
    contrasena = clave;
}

void Usuario::setCiudad(const string& ciudadUsuario)
{
    ciudad = ciudadUsuario;
}

void Usuario::setPais(const string& paisUsuario)
{
    pais = paisUsuario;
}

void Usuario::setFechaInscripcion(const string& fecha)
{
    fechaInscripcion = fecha;
}