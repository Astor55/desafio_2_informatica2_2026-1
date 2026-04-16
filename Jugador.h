#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
using namespace std;

class Jugador
{

private:

    //atributos
    string nombre;
    string apellido;
    unsigned short numero_camisa;

    unsigned short goles;
    unsigned short asistencias;
    unsigned short amarillas;
    unsigned short rojas;
    unsigned short faltas;

    unsigned int minutos;
    unsigned int partidos;

public:

    //constructor
    Jugador(string, string, unsigned short);

    Jugador(const Jugador& otro);

    //metodos
    void Anotar_gol();
    void Sumar_roja();
    void Sumar_amarilla();
    void Sumar_minutos(unsigned int);
    void Sumar_asistencias();
    void Sumar_partidos_jugados();
    void Sumar_faltas();

    //Getters
    unsigned short getNumero();
    unsigned short getGoles();

    //Destructor
    ~Jugador();
};

#endif // JUGADOR_H
