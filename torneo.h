#ifndef TORNEO_H
#define TORNEO_H

#include "equipo.h"
#include "bombo.h"
#include "grupo.h"

using namespace std;


class Torneo
{

    private:

    Equipo** equipos;
    Bombo** bombos;
    Grupo** grupos;

    Equipo* campeon;
    Equipo* subcampeon;
    Equipo* tercero;
    Equipo* cuarto;
    Equipo* R16[16];
    Equipo* R8[8];
    Equipo* R4[4];
    Equipo** equipos_originales;

    unsigned short cantidad_equipos;
    unsigned short cantidad_bombos;
    unsigned short cantidad_grupos;


    public:

        Torneo(Equipo** equipos_jugando);
        Torneo(const Torneo& otro);

        Equipo** clasificar_equipos(Equipo* calsificados[32]);

        void crear_bombos();
        void generar_grupos();
        void simular_fase_de_grupos();
        void clasificar_mejores_terceros(Equipo* mejores_terceros[8]);
        void simular_eliminatorias(Equipo* clasificados[32]);
        void generar_estadisticas();
        void limpiar_grupos();
        void reiniciar_bombos();

        // Eliminatorias
        Equipo* clasificados_R16[32];
        Equipo* clasificados_R8[16];
        Equipo* clasificados_R4[8];
        Equipo* clasificados_final[4];

        ~Torneo();
};

#endif // TORNEO_H
