#include "partido.h"
#include <cmath>
#include <random>

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

    calcular_faltas1();
    calcular_faltas2();

    posesion_balon_equipo1 = calcular_posesion1();
    posesion_balon_equipo2 = calcular_posesion2();

    equipo_1->sumar_goles_a_favor(goles_equipo1);
    equipo_1->sumar_goles_en_contra(goles_equipo2);

    equipo_2->sumar_goles_a_favor(goles_equipo2);
    equipo_2->sumar_goles_en_contra(goles_equipo1);

    if(es_empate())
    {

        desempatar();
        duracion = 120;

    }


    else if(goles_equipo1 > goles_equipo2)
    {

        equipo_1->sumar_partidos_ganados();
        equipo_2->sumar_partidos_perdidos();

    }

    else
    {

        equipo_2->sumar_partidos_ganados();
        equipo_1->sumar_partidos_perdidos();

    }

}



unsigned short Partido::calcular_goles_equipo1()
{

    //constantes
    static const float nu = 1.35;
    static const float alpha = 0.6;
    static const float beta = 0.4;

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
        gf = (float)equipo_2->getGolesAFavor() / equipo_2->getPartidosJugados();
    }

    if(equipo_1->getPartidosJugados() > 0)
    {
        gc = (float)equipo_1->getGolesEnContra() / equipo_1->getPartidosJugados();
    }

    //formula
    float goles_2 = nu * pow(gf/nu, alpha) * pow(gc/nu, beta);

    return(unsigned short)round(goles_2);

}

bool Partido ::  es_empate() const{

    return goles_equipo1 == goles_equipo2;

}


Equipo* Partido :: desempatar(){

    if((equipo_1 -> getRankingFIFA()) > (equipo_2 ->getRankingFIFA()) ){

        goles_equipo1++;
        equipo_1 -> sumar_partidos_ganados();
        equipo_2 -> sumar_partidos_perdidos();
        return equipo_1;

    }

    else if((equipo_1 -> getRankingFIFA()) < (equipo_2 ->getRankingFIFA())){

        goles_equipo2++;
        equipo_2 -> sumar_partidos_ganados();
        equipo_1 -> sumar_partidos_perdidos();
        return equipo_2;

    }

    else{

        //sorteo
        static std::mt19937 gen(std::random_device{}());

        static std::uniform_int_distribution <int> dist(0, 1);

        if(dist(gen) == 0)
        {
            goles_equipo1++;
            equipo_1 ->sumar_partidos_ganados();
            equipo_2 ->sumar_partidos_perdidos();
            return equipo_1;


        }

        else
        {
            goles_equipo2++;
            equipo_2 ->sumar_partidos_ganados();
            equipo_1 ->sumar_partidos_perdidos();
            return equipo_2;


        }
    }
}

void Partido :: calcular_posesion1(){

    //ranking FIFA
    float Rank1 = (float)equipo_1->getRankingFIFA();
    float Rank2 = (float)equipo_2->getRankingFIFA();

    float total = Rank1 + Rank2;

    if(total == 0)
        posesion_balon_equipo1 = 50.0;

    posesion_balon_equipo1 = (Rank1 / total) * 100.0;
}


void Partido :: calcular_posesion2(){

    posesion_balon_equipo2 = 100.0 - posesion_balon_equipo1;
}


void Partido :: calcular_faltas1(){

    static std::mt19937 gen(std::random_device{}());

    static std::uniform_int_distribution <int> distJugador(0, 10);

    unsigned short a = distJugador(gen);

    Jugador* jugador_seleccionado = equipo_1 ->getJugador_en_partido(a);

    static std::uniform_int_distribution <int> distCaso(0, 2);

    unsigned short b = distCaso(gen);

    if(b == 0){

        jugador_seleccionado->Sumar_faltas();
        faltas_1++;
    }

    else if(b == 1){

        jugador_seleccionado->Sumar_amarilla();
        faltas_1++;
    }

    else if(b == 2){

        jugador_seleccionado->Sumar_roja();
        faltas_1++;
    }

}

void Partido :: calcular_faltas2(){

    static std::mt19937 gen(std::random_device{}());

    static std::uniform_int_distribution <int> distJugador(0, 10);

    unsigned short a = distJugador(gen);

    Jugador* jugador_seleccionado = equipo_2 ->getJugador_en_partido(a);

    static std::uniform_int_distribution <int> distCaso(0, 2);

    unsigned short casos = distCaso(gen);

    if(casos == 0){

        jugador_seleccionado->Sumar_faltas();
        faltas_2++;
    }

    else if(casos == 1){

        jugador_seleccionado->Sumar_amarilla();
        faltas_2++;

    }

    else if(casos == 2){

        jugador_seleccionado->Sumar_roja();
        faltas_2++;
    }

}



//getters
float Partido :: getposesion1(){


    return posesion_balon_equipo1;
}



float Partido :: getposesion2(){


    return posesion_balon_equipo2;
}






Partido::~Partido(){

}
