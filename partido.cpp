#include "partido.h"
#include <cmath>

Partido::Partido(Equipo* _equipo_1, Equipo* _equipo_2, string _sede, const string _arbitros[3], string _hora, string _fecha) : equipo_1(_equipo_1), equipo_2(_equipo_2),
    goles_equipo1(0), goles_equipo2(0), faltas_1(0), faltas_2(0), duracion(90), posesion_balon_equipo1(0), posesion_balon_equipo2(0), sede(_sede), hora(_hora), fecha(_fecha){

    for(int i = 0; i < 3; i++){

        arbitros[i] = _arbitros[i];
    }
}

Partido :: Partido(const Partido& otro){

    equipo_1 = otro.equipo_1;
    equipo_2 = otro.equipo_2;

    goles_equipo1 = otro.goles_equipo1;
    goles_equipo2 = otro.goles_equipo2;

    faltas_1 = otro.faltas_1;
    faltas_2 = otro.faltas_2;

    duracion = otro.duracion;

    posesion_balon_equipo1 = otro.posesion_balon_equipo1;
    posesion_balon_equipo2 = otro.posesion_balon_equipo2;

    sede = otro.sede;
    hora = otro.hora;
    fecha = otro.fecha;

    for(int i = 0; i < 3; i++){

        arbitros[i] = otro.arbitros[i];
    }
}


void Partido::jugar()
{

    if(equipo_1 == nullptr || equipo_2 == nullptr) return;

    goles_equipo1 = calcular_goles_equipo1();
    goles_equipo2 = calcular_goles_equipo2();

    faltas_1 = calcular_faltas1();
    faltas_2 = calcular_faltas2();

    posesion_balon_equipo1 = calcular_posesion1();
    posesion_balon_equipo2 = calcular_posesion2();

    estimar_duracion();

    if(es_empate())
    {

        desempatar();

    }

    equipo_1->sumar_goles_a_favor(goles_equipo1);
    equipo_1->sumar_goles_en_contra(goles_equipo2);

    equipo_2->sumar_goles_a_favor(goles_equipo2);
    equipo_2->sumar_goles_en_contra(goles_equipo1);

    if(goles_equipo1 > goles_equipo2)
    {

        equipo_1->sumar_partidos_ganados();
        equipo_2->sumar_partidos_perdidos();

    }

    else if(goles_equipo2 > goles_equipo1)
    {

        equipo_2->sumar_partidos_ganados();
        equipo_1->sumar_partidos_perdidos();

    }

    else
    {

        equipo_1->sumar_partidos_empatados();
        equipo_2->sumar_partidos_empatados();

    }
}



unsigned short Partido::calcular_goles_equipo1()
{

    //constantes
    const float nu = 1.35;
    const float alpha = 0.6;
    const float beta = 0.4;

    float gf = 0.0;
    float gc = 0.0;

    //goles equipo 1
    if(equipo_1->getPartidosJugados() > 0)
    {
        gf = (float)equipo_1->getGolesAFavor() / equipo_1->getPartidosJugados();
    }

    if(equipo_2->getPartidosJugados() > 0)
    {
        gc = (float)equipo_2->getGolesEnContra() / equipo_2->getPartidosJugados();
    }

    //formula
    float goles_1 = nu * pow(gf/nu, alpha) * pow(gc/nu, beta);

    return (unsigned short)round(goles_1);

}


unsigned short Partido::calcular_goles_equipo2()
{

    const float nu = 1.35;
    const float alpha = 0.6;
    const float beta = 0.4;

    float gf = 0.0;
    float gc = 0.0;


    //goles equipo 2
    if(equipo_2->getPartidosJugados() > 0)
    {
        gf = equipo_2->getGolesAFavor() / equipo_2->getPartidosJugados();
    }

    if(equipo_1->getPartidosJugados() > 0)
    {
        gc = equipo_1->getGolesEnContra() / equipo_1->getPartidosJugados();
    }

    //formula
    float goles_2 = nu * pow(gf/nu, alpha) * pow(gc/nu, beta);

    return(unsigned short)round(goles_2);

}


float Partido::calcular_posesion1()
{

    //ranking FIFA
    float Rank1 = (float)equipo_1->getRankingFIFA();
    float Rank2 = (float)equipo_2->getRankingFIFA();

    float total = Rank1 + Rank2;

    if(total == 0)
        return 50.0;

    return (Rank2 / total) * 100.0;

}


float Partido::calcular_posesion2()
{

    return 100.0 - posesion_balon_equipo1;

}


Partido::~Partido(){}
