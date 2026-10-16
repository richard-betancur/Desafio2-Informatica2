#ifndef SOLICITUDAMISTAD_H
#define SOLICITUDAMISTAD_H

#include <string>

using namespace std;

class Usuario;

class SolicitudAmistad
{
private:
    Usuario* emisor;
    Usuario* receptor;
    string fecha;
    int estado; // 0: pendiente, 1: aceptada, 2: rechazada

public:
    SolicitudAmistad(Usuario* quienEnvia, Usuario* quienRecibe, const std::string& fechaSolicitud);

    SolicitudAmistad(const SolicitudAmistad& otra);

    Usuario* getEmisor() const;
    Usuario* getReceptor() const;
    string getFecha() const;
    int getEstado() const;

    void aceptar();
    void rechazar();
    bool estaPendiente() const;
};

#endif