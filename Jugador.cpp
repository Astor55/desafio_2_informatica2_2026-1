#include "Jugador.h"

//Constructor
Jugador::Jugador()
{

    nombre = "";
    apellido = "";
    numero_camisa = 0;

    goles = 0;
    asistencias = 0;
    amarillas = 0;
    rojas = 0;
    faltas = 0;

    minutos = 0;
    partidos = 0;

}

//constructor de copia
Jugador::Jugador(const Jugador& otro)
{

    nombre = otro.nombre;
    apellido = otro.apellido;
    numero_camisa = otro.numero_camisa;

    goles = otro.goles;
    asistencias = otro.asistencias;
    amarillas = otro.amarillas;
    rojas = otro.rojas;
    faltas = otro.faltas;

    minutos = otro.minutos;
    partidos = otro.partidos;

}

bool Jugador::operator!=(const Jugador& otro) const{

    return this->numero_camisa;

}

//Metodos de la clase
void Jugador::Anotar_gol()
{

    goles++;

}

void Jugador::Sumar_roja()
{

    rojas++;

}

void Jugador::Sumar_amarilla()
{

    amarillas++;

}

void Jugador::Sumar_minutos(unsigned int m)
{

    minutos += m;

}

void Jugador::Sumar_asistencias()
{

    asistencias++;

}

void Jugador::Sumar_partidos_jugados()
{

    partidos++;

}

void Jugador::Sumar_faltas()
{

    faltas++;

}

//Getters

unsigned short Jugador::getNumero()
{

    return numero_camisa;
}

unsigned short Jugador::getGoles()
{

    return goles;

}

//Destructor
Jugador::~Jugador() {}
