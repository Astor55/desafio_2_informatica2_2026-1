#ifndef EQUIPO_H
#define

#include <string>

using namespace std;

class Equipo
{

    private:

    string nombre;
    string confederacion;
    unsigned int goles_a_favor;
    unsigned int goles_en_contra;
    unsigned int ranking_fifa;
    unsigned int partidos_ganados;
    unsigned int partidos_empatados;
    unsigned int partidos_perdidos;

    public:

        Equipo(string, string, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int); //Constructor de la clase
        Equipo(const Equipo& otro); // Constructor de copia

        void lista_jugadores(Jugador jugadores[11]);
        void sumar_goles_a_favor(unsigned short);
        void sumar_goles_en_contra(unsigned short);
        void sumar_partidos_ganados();
        void sumar_partidos_perdidos();
        void sumar_partidos_empatados();

        ~Equipo();

};

#endif // EQUIPO_H
