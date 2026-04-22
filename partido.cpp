#include "partido.h"

partido::partido(Equipo* _equipo_1, Equipo* _equipo_2, string _sede, string _arbitros, string _hora, string _fecha) : goles_equipo1(0),
    goles_equipo2(0), faltas(0), posesion_balon_equipo1(0), posesion_balon_equipo2(0){

    equipo_1 = _equipo_1;

    equipo_2 = _equipo_2;

    sede = _sede;

    for(int i = 0; i < 3; i++){

        arbitros[i] = _arbitros[i];
    }

    hora = _hora;

    fecha = _fecha;
}

partido :: partido(const partido& otro){

    equipo_1 = otro.equipo_1;

    equipo_2 = otro.equipo_2;

    sede = otro.sede;

    for(int i = 0; i < 3; i++){

        arbitros[i] = otro.arbitros[i];
    }

    hora = otro.hora;

    fecha = otro.fecha;
}


unsigned int partido :: calcular_goles_equipo1(Equipo* _equipo1){

    static float nu = 1.35;
    static float alpha = 0.6;
    static float beta = 0.4;

    goles_1 = nu * (promedio_goles_a_favor1/nu);
}


unsigned int partido :: calcular_goles_equipo2(Equipo* _equipo2){


}




