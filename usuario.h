#ifndef USUARIO_H
#define USUARIO_H

#include <string>

using namespace std;

class Usuario
{
private:
    string nombreUsuario;
    string fechaNacimiento;
    string correo;
    string rutaFotoPerfil;
    string contraseña;
    string ciudad;
    string pais;
    string fechaInscripcion;

public:
    // Constructores
    Usuario();

    Usuario(const string& nombre, const string& clave);

    Usuario(const string& nombre,
            const string& nacimiento,
            const string& email,
            const string& rutaPerfil,
            const string& clave,
            const string& ciudadUsuario,
            const string& paisUsuario,
            const string& inscripcion);

    Usuario(const Usuario& otro);

    // Getters
    string getNombreUsuario() const;
    string getFechaNacimiento() const;
    string getCorreo() const;
    string getRutaFotoPerfil() const;
    string getContraseña() const;
    string getCiudad() const;
    string getPais() const;
    string getFechaInscripcion() const;

    // Verificación de credenciales
    bool verificarContraseña(const string& clave) const;

    // Setters
    void setFechaNacimiento(const string& fecha);
    void setCorreo(const string& email);
    void setRutaFotoPerfil(const string& ruta);
    void setContraseña(const string& clave);
    void setCiudad(const string& ciudadUsuario);
    void setPais(const string& paisUsuario);
    void setFechaInscripcion(const string& fecha);
};

#endif