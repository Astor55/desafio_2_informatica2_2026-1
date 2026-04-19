#include "equipo.h"

Equipo :: Equipo(string _nombre, string _confederacion, unsigned int _goles_a_favor, unsigned int _goles_en_contra,
               unsigned int _ranking_fifa, unsigned int _partidos_ganados, unsigned int _partidos_empatados, unsigned int _partidos_perdidos){

    nombre =_nombre;

    confederacion = _confederacion;

    goles_a_favor = _goles_a_favor;

    goles_en_contra = _goles_en_contra;

    ranking_fifa = _ranking_fifa;

    partidos_ganados = _partidos_ganados;

    partidos_empatados = _partidos_empatados;

    partidos_perdidos = _partidos_perdidos;

    puntos = 0;

    cantidad_jugadores = 26;

    jugadores = new Jugador[cantidad_jugadores];
}


Equipo :: Equipo(const Equipo& otro){

    nombre = otro.nombre;

    confederacion = otro.confederacion;

    goles_a_favor = otro.goles_a_favor;

    goles_en_contra = otro.goles_en_contra;

    ranking_fifa = otro.ranking_fifa;

    partidos_ganados = otro.partidos_ganados;

    partidos_empatados = otro.partidos_empatados;

    partidos_perdidos = otro.partidos_perdidos;

    cantidad_jugadores = otro.cantidad_jugadores;

    jugadores = new Jugador[cantidad_jugadores];

    for(int i = 0; i < cantidad_jugadores; i++){

        jugadores[i] = otro.jugadores[i];
    }

    puntos = otro.puntos;

}


void Equipo :: lista_jugadores(const Jugador* players){

    for(int i = 0; i < cantidad_jugadores; i++){

        jugadores[i] = players[i];
    }

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

void Equipo :: sumar_puntos(int puntos_ganados){

    puntos+= puntos_ganados;
}

Equipo& Equipo :: operator=(const Equipo& otra){

    nombre = otra.nombre;

    confederacion = otra.confederacion;

    goles_a_favor = otra.goles_a_favor;

    goles_en_contra = otra.goles_en_contra;

    ranking_fifa = otra.ranking_fifa;

    partidos_ganados = otra.partidos_ganados;

    partidos_empatados= otra.partidos_empatados;

    partidos_perdidos = otra.partidos_perdidos;

    puntos = otra.puntos;

    cantidad_jugadores = otra.cantidad_jugadores;

    delete[] jugadores;

    jugadores = new Jugador[cantidad_jugadores];

    for(int j = 0; j < cantidad_jugadores; j++){

        jugadores[j] = otra.jugadores[j];
    }

    return *this;

}

bool Equipo :: operator==(const Equipo& otro) const{

    if(nombre != otro.nombre){
        return false;
    }

    else if(confederacion != otro.confederacion){
        return false;
    }

    else if(goles_a_favor != otro.goles_a_favor){
        return false;
    }
    else if(goles_en_contra != otro.goles_en_contra){
        return false;
    }
    else if(ranking_fifa != otro.ranking_fifa){
        return false;
    }
    else if(partidos_ganados != otro.partidos_ganados){
        return false;
    }
    else if(partidos_empatados != otro.partidos_empatados){
        return false;
    }
    else if(partidos_perdidos != otro.partidos_perdidos){
        return false;
    }
    else if(puntos != otro.puntos){
        return false;
    }

    for(int i = 0; i < cantidad_jugadores; i++){

        if(jugadores[i] != otro.jugadores[i]){

            return false;
        }
    }



    return true;

}


Equipo :: ~Equipo(){

    delete[] jugadores;
}
