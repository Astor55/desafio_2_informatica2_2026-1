#include "equipo.h"

Equipo :: Equipo(string _nombre, string _confederacion, unsigned int _goles_a_favor, unsigned int _goles_en_contra,
               unsigned int _ranking_fifa, unsigned int _partidos_ganados, unsigned int _partidos_empatados, unsigned int _partidos_perdidos){

    nombre = _nombre;
    confederacion = _confederacion;
    goles_a_favor = _goles_a_favor;
    goles_en_contra = _goles_en_contra;
    ranking_fifa = _ranking_fifa;
    partidos_ganados = _partidos_ganados;
    partidos_empatados = _partidos_empatados;
    partidos_perdidos = _partidos_perdidos;
}


Equipo :: Equipo(const Equipo& otro){

    nombre = otro.nombre;
    confederacion = otro.confederacion;
    goles_a_favor = otro,goles_a_favor;
    goles_en_contra = otro.goles_en_contra;
    ranking_fifa = otro.ranking_fifa;
    partidos_ganados = otro.partidos_ganados;
    partidos_empatados = otro.partidos_empatados;
    partidos_perdidos = otro.partidos_perdidos;
}


void Equipo :: lista_jugadores(Jugador jugadores[11]){


}


void Equipo :: sumar_goles_a_favor(unsigned short num){

    goles_a_favor+= num;
}


void Equipo :: sumar_goles_en_contra(unsigned short n){

    goles_en_contra+= n;

}


void Equipo :: sumar_partidos_ganados(){

    partidos_ganados++;
}


void Equipo :: sumar_partidos_perdidos(){

    partidos_perdidos++;
}

void Equipo :: sumar_partidos_empatados(){

    partidos_empatados++;
}


Equipo :: ~Equipo(){


}
