#ifndef PARTIDO_H
#define PARTIDO_H

#include "equipo.h"
#include <string>

using namespace std;

class Partido
{
    private:

    Equipo* equipo_1;
    Equipo* equipo_2;

    unsigned short goles_equipo1;
    unsigned short goles_equipo2;

    unsigned short faltas_1;
    unsigned short faltas_2;

    unsigned short duracion;

    string sede;
    string arbitros[3];
    string hora;
    string fecha;

    float posesion_balon_equipo1;
    float posesion_balon_equipo2;



    public:

        //constructor
        Partido(Equipo* _equipo_1, Equipo* _equipo_2, string _sede, const string _arbitros[3], string _hora, string _fecha);
        //cosntructor de copia
        Partido(const Partido& otro);

        void jugar();

        //calculos
        unsigned short calcular_goles_equipo1();
        unsigned short calcular_goles_equipo2();

        unsigned short calcular_faltas1();
        unsigned short calcular_faltas2();

        float calcular_posesion1();
        float calcular_posesion2();

        void estimar_duracion();

        //logica de los resultados
        bool es_empate() const;

        void desempatar() const;

        Equipo* ganador();

        //destructor
        ~Partido();


};

#endif // PARTIDO_H
