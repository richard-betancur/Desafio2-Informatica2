#ifndef ALMACENAMIENTO_H
#define ALMACENAMIENTO_H

#include <string>

class RedSocial;

// Persistencia local de toda la red social en un único archivo de texto.
class Almacenamiento
{
public:
    bool guardarTodo(const RedSocial& red, const std::string& rutaArchivo) const;
    bool cargarTodo(RedSocial& red, const std::string& rutaArchivo) const;

    // Compatibilidad con el código previo.
    bool guardarUsuarios(const RedSocial& red, const std::string& rutaArchivo) const;
    bool cargarUsuarios(RedSocial& red, const std::string& rutaArchivo) const;
};

#endif
