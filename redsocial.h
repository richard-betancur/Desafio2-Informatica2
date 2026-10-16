#ifndef REDSOCIAL_H
#define REDSOCIAL_H

#include "usuario.h"

class RedSocial
{
private:
    Usuario** usuarios;
    int cantidadUsuarios;
    int capacidadUsuarios;

    void ampliarCapacidad();

public:
    RedSocial();
    ~RedSocial();

    RedSocial(const RedSocial&) = delete;
    RedSocial& operator=(const RedSocial&) = delete;

    bool agregarUsuario(const string& nombre, const string& clave);
    bool agregarUsuario(const string& nombre,
                        const string& nacimiento,
                        const string& correo,
                        const string& rutaFoto,
                        const string& clave,
                        const string& ciudad,
                        const string& pais,
                        const string& inscripcion);

    Usuario* buscarUsuario(const string& nombre) const;
    Usuario* obtenerUsuarioPorIndice(int indice) const;

    int getCantidadUsuarios() const;
};

#endif