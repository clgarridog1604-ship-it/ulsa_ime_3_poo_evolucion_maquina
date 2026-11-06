#ifndef CONTROLDELINEA_H
#define CONTROLDELINEA_H

#include <vector>
#include "Maquina.h"

class ControlDeLinea
{
private:

    std::vector<Maquina*> maquinas;

public:

    bool agregar(Maquina* maquina);

    void ejecutarTurno(int ciclos);

    void imprimirReporte() const;
};

#endif