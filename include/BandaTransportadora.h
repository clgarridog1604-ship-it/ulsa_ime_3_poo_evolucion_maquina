#ifndef BANDATRANSPORTADORA_H
#define BANDATRANSPORTADORA_H

#include "Maquina.h"
#include "Motor.h"

class BandaTransportadora : public Maquina
{
private:

    Motor motor;

    void ejecutarCiclo();

public:

    explicit BandaTransportadora(const std::string& nombre);

    int tiempoCicloSeg() const;
};

#endif
