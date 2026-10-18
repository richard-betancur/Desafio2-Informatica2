
#ifndef ALBUM_H
#define ALBUM_H

#include <string>
#include "foto.h"

class Usuario;

class Album
{
private:
    std::string nombre;
    std::string ruta;
    int privacidad;

    Foto** fotos;
    int cantidadFotos;
    int capacidadFotos;

    void ampliarCapacidad();

public:
    Album(const std::string& nombreAlbum,
          const std::string& rutaAlbum,
          int nivelPrivacidad);

    Album(const Album& otro);
    ~Album();

    std::string getNombre() const;
    std::string getRuta() const;
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
