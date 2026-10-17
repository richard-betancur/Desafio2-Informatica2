#ifndef FOTO_H
#define FOTO_H

#include <string>

using namespace std;

class Foto
{
private:
    string fechaCaptura;
    unsigned long long tamanoBytes;
    string ruta;
    int cantidadLikes;

public:
    // Constructor
    Foto(const string& fecha,
         unsigned long long tamano,
         const string& rutaArchivo,
         int likes = 0);

    // Constructor de copia
    Foto(const Foto& otra);

    // Getters
    string getFechaCaptura() const;
    unsigned long long getTamanoBytes() const;
    string getRuta() const;
    int getCantidadLikes() const;

    // Gestion de likes
    bool darLike();
    bool quitarLike();

    // Validacion
    bool esValida() const;

    // Sobrecarga de operadores
    bool operator<(const Foto& otra) const;
};

#endif
