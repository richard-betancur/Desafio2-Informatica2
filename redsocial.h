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

    bool agregarUsuario(const std::string& nombre, const std::string& clave);

    Usuario* buscarUsuario(const std::string& nombre) const;

    int getCantidadUsuarios() const;
};

#endif