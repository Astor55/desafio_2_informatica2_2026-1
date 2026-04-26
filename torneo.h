#ifndef TORNEO_H
#define TORNEO_H

#include "equipo.h"
#include "bombo.h"
#include "partido.h"
#include "grupo.h"

using namespace std;


class Torneo
{

    private:

    Equipo** equipos;
    Bombo** bombos;
    Grupo** grupos;

    unsigned short cantidad_equipos;
    unsigned short cantidad_bombos;
    unsigned short cantidad_grupos;


    public:

        Torneo(Equipo* equipos_jugando);
        Torneo(const Torneo& otro);

        void crear_bombos();
        void generar_grupos();
        void simular_fase_de_grupos();
        void clasificar_equipos();
        void clasificar_mejores_terceros(Equipo* mejores_terceros[8]);
        void simular_eliminatorias();

        ~Torneo();
};

#endif // TORNEO_H
