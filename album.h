#ifndef ALBUM_H
#define ALBUM_H

#include <string>
#include "foto.h"

class Usuario;

class Album
{
    friend class Almacenamiento;
private:
    string nombre;
    string ruta;
    int privacidad;

    Foto** fotos;
    int cantidadFotos;
    int capacidadFotos;

    void ampliarCapacidad();

public:
    Album(const string& nombreAlbum,
          const string& rutaAlbum,
          int nivelPrivacidad);

    Album(const Album& otro);
    ~Album();

    string getNombre() const;
    string getRuta() const;
    int getPrivacidad() const;
    int getCantidadFotos() const;
    Foto* obtenerFotoPorIndice(int indice) const;

    bool esPublico() const;
    bool esSoloAmigos() const;
    bool esPrivado() const;

    bool puedeVerlo(const Usuario* visitante,
                    const Usuario* propietario,
                    bool sonAmigos) const;
    bool agregarFoto(const Foto& foto);

    Album& operator=(const Album& otro);
};

#endif
