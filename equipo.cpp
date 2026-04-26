#include "equipo.h"
#include <random>

Equipo :: Equipo(string _nombre, string _confederacion, unsigned int _goles_a_favor, unsigned int _goles_en_contra,
                unsigned int _ranking_fifa, unsigned int _partidos_ganados, unsigned int _partidos_empatados, unsigned int _partidos_perdidos)
    : puntos(0) , cantidad_jugadores(26), cantidad_jugadores_jugando(11) {

    nombre =_nombre;

    confederacion = _confederacion;

    goles_a_favor = _goles_a_favor;

    goles_en_contra = _goles_en_contra;

    ranking_fifa = _ranking_fifa;

    partidos_ganados = _partidos_ganados;

    partidos_empatados = _partidos_empatados;

    partidos_perdidos = _partidos_perdidos;

    jugadores = new Jugador[cantidad_jugadores];

    jugadores_en_partido = new Jugador[cantidad_jugadores_jugando];
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

    cantidad_jugadores_jugando = otro.cantidad_jugadores_jugando;

    jugadores = new Jugador[cantidad_jugadores];

    for(int i = 0; i < cantidad_jugadores; i++){

        jugadores[i] = otro.jugadores[i];
    }

    jugadores_en_partido = new Jugador[cantidad_jugadores_jugando];

    for(int j = 0; j < cantidad_jugadores_jugando; j++){

        jugadores_en_partido[j] = otro.jugadores_en_partido[j];
    }

    puntos = otro.puntos;

}


void Equipo :: lista_jugadores(const Jugador* players){

    for(int i = 0; i < cantidad_jugadores; i++){

        jugadores[i] = players[i];
    }

}


void Equipo :: lista_jugadores_jugando(const Jugador* players){

    static std::mt19937 gen(std::random_device{}());

    static std::uniform_int_distribution <int> dist(0, 25);

    bool usados[26] = {false};

    for(unsigned short i = 0; i < 11; i++)
    {

        unsigned int a;

        do{

            a = dist(gen);

        } while (usados[a]);

        usados[a] = true;

        jugadores_en_partido[i] = players[a];

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

    if(this != &otra){


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

        delete[] jugadores_en_partido;

        jugadores_en_partido = new Jugador[cantidad_jugadores_jugando];

        for(int a = 0; a < cantidad_jugadores_jugando ; a++){

            jugadores_en_partido[a] = otra.jugadores_en_partido[a];
        }
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

    for(int j = 0 ; j < cantidad_jugadores_jugando; j++){

        if(jugadores_en_partido[j] != otro.jugadores_en_partido[j]){

            return false;
        }
    }



    return true;

}

//getters
unsigned int Equipo::getGolesAFavor()const
{

    return goles_a_favor;

}


unsigned int Equipo::getGolesEnContra()const
{

    return goles_en_contra;

}


unsigned int Equipo::getPartidosJugados()const
{

    return partidos_ganados + partidos_empatados + partidos_perdidos;

}


unsigned int Equipo::getRankingFIFA()const
{

    return ranking_fifa;

}



string Equipo::getnombre() const
{

    return nombre;

}



unsigned short Equipo::getPartidosEmpatados() const
{

    return partidos_empatados;

}



unsigned short Equipo::getPartidosPerdidos() const
{

    return partidos_perdidos;

}



unsigned short Equipo::getPartidosGanados()const
{

    return partidos_ganados;

}



Jugador* Equipo :: getJugador_en_partido(unsigned short indice) const{

    return &jugadores_en_partido[indice];

}


//destructor
Equipo :: ~Equipo(){

    delete[] jugadores;
    delete[] jugadores_en_partido;
}
