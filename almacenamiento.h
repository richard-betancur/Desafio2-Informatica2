#ifndef ALMACENAMIENTO_H
#define ALMACENAMIENTO_H

#include <string>

using namespace std;

class RedSocial;

class Almacenamiento
{
public:
    bool guardarUsuarios(const RedSocial& red, const string& rutaArchivo);

    bool cargarUsuarios(RedSocial& red, const string& rutaArchivo);
};

#endif