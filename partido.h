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

        Equipo* desempatar();

        //calculos
        unsigned short calcular_goles_equipo(Equipo* equipoA, Equipo* equipoB);

        void jugar();

        void actualizar_estado();

        void resultados();

        void eventos();

        void calcular_faltas(Equipo* equipo, unsigned short& faltas);

        void calcular_tarjetas(Equipo* equipo);

        void calcular_posesion();

        void asignar_min(unsigned short minutos);

        void sumar_partidos();

        //logica de los resultados
        bool es_empate() const;

        //Getters
        float getposesion1();
        float getposesion2();


        //destructor
        ~Partido();


};

#endif // PARTIDO_H
