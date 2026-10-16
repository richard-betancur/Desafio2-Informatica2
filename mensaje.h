#ifndef MENSAJE_H
#define MENSAJE_H

#include <string>

using namespace std;

class Usuario;

class Mensaje
{
private:
    Usuario* remitente;
    Usuario* destinatario;
    string contenido;
    string fecha;
    bool leido;

public:
    Mensaje(Usuario* quienEnvia,
            Usuario* quienRecibe,
            const string& texto,
            const string& fechaMensaje);

    Mensaje(const Mensaje& otro);

    Usuario* getRemitente() const;
    Usuario* getDestinatario() const;
    string getContenido() const;
    string getFecha() const;
    bool estaLeido() const;

    bool marcarLeido();
    bool esValido() const;

    // Sobrecarga: permite comparar mensajes por fecha
    bool operator<(const Mensaje& otro) const;
};

#endif