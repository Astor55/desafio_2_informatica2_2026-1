#ifndef BOMBO_H
#define BOMBO_H

#include "equipo.h"

class Bombo
{
    private: //Atributos

    Equipo** equipos;
    unsigned int cantidad; //Cantidad de equipos dentro de un bombo
    unsigned int posicion_equipo; //posicion (indice) de cada equipo dentro del bombo


    public: //Metodos

        Bombo();
        Bombo(const Bombo& otro);

        void Agregar_equipo(Equipo*);
        void vaciar();
        Equipo* Sacar_aleatorio();

        Bombo& operator=(const Bombo& otro);

        bool operator==(const Bombo& otro) const;

        ~Bombo();
};

#endif // BOMBO_H
