#ifndef EQUIPO_H
#define EQUIPO_H

#include <string>
#include "Jugador.h"

using namespace std;

class Equipo
{

    private: //Atributos

    string nombre;
    string confederacion;
    Jugador* jugadores;
    int cantidad_jugadores;
    unsigned int goles_a_favor;
    unsigned int goles_en_contra;
    unsigned int ranking_fifa;
    unsigned int partidos_ganados;
    unsigned int partidos_empatados;
    unsigned int partidos_perdidos;
    unsigned short puntos;

    public: //Metodos

        Equipo(string, string, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int); //Constructor de la clase
        Equipo(const Equipo& otro); // Constructor de copia

        void lista_jugadores(const Jugador* players);
        void sumar_goles_a_favor(unsigned short);
        void sumar_goles_en_contra(unsigned short);
        void sumar_partidos_ganados();
        void sumar_partidos_perdidos();
        void sumar_partidos_empatados();
        void sumar_puntos(int puntos_ganados);
        Equipo& operator=(const Equipo& otra); //Sobrecarga del operador de asignacion
        bool operator==(const Equipo& otro) const; //Sobrecarga del operador de igualdad

        //No es necesario sobrecargar los operadores de suma en esta clase debido a que el tipo de dato numerico
        // usado tiene definido los operadores ++ y +=



        ~Equipo(); //Destructor de la clase

};

#endif // EQUIPO_H
