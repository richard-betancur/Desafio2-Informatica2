#ifndef ALBUM_H
#define ALBUM_H

#include <string>
#include "foto.h"

class Usuario;

class Album
{
private:
    string nombre;
    string ruta;
    int privacidad;

    Foto** fotos;
    int cantidadFotos;
    int capacidadFotos;

    void ampliarCapacidad();

public:
    // Constructor
    Album(const string& nombreAlbum,
          const string& rutaAlbum,
          int nivelPrivacidad);

    // Constructor de copia
    Album(const Album& otro);

    // Destructor
    ~Album();

    // Getters
    string getNombre() const;
    string getRuta() const;
    int getPrivacidad() const;
    int getCantidadFotos() const;
    Foto* obtenerFotoPorIndice(int indice) const;

    // Consultar privacidad
    bool esPublico() const;
    bool esSoloAmigos() const;
    bool esPrivado() const;
    bool puedeVerlo(const Usuario* visitante,
                    const Usuario* propietario,
                    bool sonAmigos) const;

    // Incorporar fotos preexistentes al album
    bool agregarFoto(const Foto& foto);

    // Sobrecarga de operadores
    Album& operator=(const Album& otro);
};

#endif
