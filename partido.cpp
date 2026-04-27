#include "partido.h"
#include "funciones.h"
#include <cmath>
#include <random>



Partido::Partido(Equipo* _equipo_1, Equipo* _equipo_2, string _sede, const string _arbitros[3], string _hora, string _fecha) : equipo_1(_equipo_1), equipo_2(_equipo_2),
    goles_equipo1(0), goles_equipo2(0), faltas_1(0), faltas_2(0), duracion(90), posesion_balon_equipo1(0), posesion_balon_equipo2(0), sede(_sede), hora(_hora), fecha(_fecha){

    for(unsigned short i = 0; i < 3; i++){

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
        cont_trabajo++;
    }
}



void Partido::jugar()
{
    if(equipo_1 == nullptr || equipo_2 == nullptr) return;

    resultados();

    equipo_1->sumar_goles_a_favor(goles_equipo1);
    equipo_2->sumar_goles_a_favor(goles_equipo2);

    for(int i = 0; i < goles_equipo1; i++)
    {
        int j = rand() % equipo_1->getcantidadJugadores();
        equipo_1->getJugadores()[j].Anotar_gol();
    }

    for(int i = 0; i < goles_equipo2; i++)
    {
        int j = rand() % equipo_2->getcantidadJugadores();
        equipo_2->getJugadores()[j].Anotar_gol();
    }

    eventos();
    calcular_posesion();

    sumar_partidos();

    if(es_empate())
    {
        desempatar();
        duracion = 120;
        asignar_min(120);
    }
    else
    {
        asignar_min(90);
    }

    actualizar_estado();
}



void Partido::resultados()
{

    //goles
    goles_equipo1 = calcular_goles_equipo(equipo_1, equipo_2);
    goles_equipo2 = calcular_goles_equipo(equipo_2, equipo_1);

}



void Partido::eventos()
{

    //faltas
    calcular_faltas(equipo_1, faltas_1);
    calcular_faltas(equipo_2, faltas_2);

    //tarjetas
    calcular_tarjetas(equipo_1);
    calcular_tarjetas(equipo_2);

}



void Partido::asignar_min(unsigned short minutos)
{

    for (unsigned short i = 0; i < 11; i++)
    {

        equipo_1->getJugador_en_partido(i)->Sumar_minutos(minutos);
        equipo_2->getJugador_en_partido(i)->Sumar_minutos(minutos);
        cont_trabajo++;

    }

}



void Partido::sumar_partidos()
{

    for (int i = 0; i < 11; i++)
    {

        equipo_1->getJugador_en_partido(i)->Sumar_partidos_jugados();
        equipo_2->getJugador_en_partido(i)->Sumar_partidos_jugados();
        cont_trabajo++;

    }

}



void Partido::actualizar_estado()
{

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
}



unsigned short Partido::calcular_goles_equipo(Equipo* equipoA, Equipo* equipoB)
{

    //constantes
    static const float nu = 1.35;
    static const float alpha = 0.6;
    static const float beta = 0.4;

    float gf = 0.0;
    float gc = 0.0;

    //goles del equipo
    if(equipoA->getPartidosJugados() > 0)
    {
        gf = (float)equipoA->getGolesAFavor() / equipoA->getPartidosJugados();
    }

    if(equipoB->getPartidosJugados() > 0)
    {
        gc = (float)equipoB->getGolesEnContra() / equipoB->getPartidosJugados();
    }

    //formula
    float goles = nu * pow(gf/nu, alpha) * pow(gc/nu, beta);

    return (unsigned short)round(goles);

}



bool Partido ::  es_empate() const{

    return goles_equipo1 == goles_equipo2;

}



Equipo* Partido :: desempatar(){

    //sorteo
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_real_distribution<float>prob(0.0f, 1.0f);

    //El menor numero es el mejor
    float rank1 = (float)equipo_1->getRankingFIFA();
    float rank2 = (float)equipo_2->getRankingFIFA();

    if(rank1 == 0) rank1 = 1;
    if(rank2 == 0) rank2 = 1;

    //acomodar logica del mejor
    float f1 = 1.0f / rank1;
    float f2 = 1.0f / rank2;

    //calcular solo equipo 1
    float total = f1 + f2;
    float p1 = f1 / total;

    float x = prob(gen);

    if(x < p1) //gana equipo 1
    {

        goles_equipo1++;

        return equipo_1;

    }

    else //gana equipo 2
    {

        goles_equipo2++;

        return equipo_2;

    }
}



void Partido :: calcular_posesion(){

    //ranking FIFA
    float Rank1 = (float)equipo_1->getRankingFIFA();
    float Rank2 = (float)equipo_2->getRankingFIFA();

    if(Rank1 == 0) Rank1 = 1;
    if(Rank2 == 0) Rank2 = 1;

    float f1 = 1.0f / Rank1;
    float f2 = 1.0f / Rank2;

    float total = f1 + f2;

    if(total == 0)
    {

        posesion_balon_equipo1 = 50.0;
        posesion_balon_equipo2 = 50.0;

    }

    else
    {

        posesion_balon_equipo1 = (f1 / total) * 100.0;
        posesion_balon_equipo2 = 100 - posesion_balon_equipo1;

    }
}



void Partido :: calcular_faltas(Equipo* equipo, unsigned short& faltas)
{

    static std::mt19937 gen(std::random_device{}());

    static std::uniform_real_distribution <float> probP(0.0f, 1.0f);

    for (unsigned short i = 0; i < 11; i++)
    {

        cont_trabajo++;

        float prob = probP(gen);

        Jugador* jugador_seleccionado = equipo->getJugador_en_partido(i);

        if(prob < 0.007f)
        {

            jugador_seleccionado->Sumar_faltas();
            faltas++;

        }

        else if(prob < 0.0275f + 0.007f)
        {

            jugador_seleccionado->Sumar_faltas();
            faltas++;

        }

        else if(prob < 0.13f + 0.0275f + 0.007f)
        {

            jugador_seleccionado->Sumar_faltas();
            faltas++;

        }
    }
}



void Partido::calcular_tarjetas(Equipo* equipo)
{

    static std::mt19937 gen(std::random_device{}());
    static std::uniform_real_distribution<float> probP(0.0f, 1.0f);

    for(unsigned short i = 0; i < 11; i++)
    {

        cont_trabajo++;

        Jugador* jugador_seleccionado = equipo->getJugador_en_partido(i);

        unsigned short amarillas = 0;

        if(probP(gen) < 0.06f) amarillas++;

        if(probP(gen) < 0.0115f) amarillas ++;

        if(amarillas == 1) jugador_seleccionado->Sumar_amarilla();

        if(amarillas == 2)
        {

            jugador_seleccionado->Sumar_amarilla();
            jugador_seleccionado->Sumar_amarilla();
            jugador_seleccionado->Sumar_roja();
        }
    }
}



//getters
float Partido :: getposesion1(){


    return posesion_balon_equipo1;
}



float Partido :: getposesion2(){


    return posesion_balon_equipo2;
}



unsigned short Partido::getgoles1() const
{

    return goles_equipo1;

}



unsigned short Partido::getgoles2() const
{

    return goles_equipo2;

}



Partido::~Partido(){

}
