#ifndef PARTIDO_H
#define PARTIDO_H

#include "equipo.h"
#include <string>

using namespace std;

class partido
{
    private:

    Equipo* equipo_1;
    Equipo* equipo_2;
    unsigned short goles_equipo1;
    unsigned short goles_equipo2;
    unsigned short faltas_1;
    unsigned short faltas_2();
    unsigned short duracion;
    string sede;
    string arbitros[3];
    string hora;
    string fecha;
    float posesion_balon_equipo1;
    float posesion_balon_equipo2;



    public:

        partido(Equipo* _equipo_1, Equipo* _equipo_2, string _sede, string _arbitros, string _hora, string _fecha);
        partido(const partido& otro);

        unsigned short calcular_goles_equipo1();
        unsigned short calulcar_goles_equipo2();
        unsigned short calcular_faltas1();
        unsigned short calcular_faltas2();

        bool es_empate();

        void desempatar();
        void estimar_duracion();

        float calcular_posesion1();
        float calcular_posesion2();


        Equipo* ganador();

        ~partido();


};

#endif // PARTIDO_H
