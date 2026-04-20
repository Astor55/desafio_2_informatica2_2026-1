#ifndef GRUPO_H
#define GRUPO_H

#include "equipo.h"

class Grupo
{
private:

    //Atributos Grupo
    char letra;

    Equipo* equipos[4];
    unsigned short cantidad_equipos;

    unsigned short puntos[4];
    short dif_goles[4];

public:

    //constructor Grupo
    Grupo(char);
    Grupo(const Grupo& otro);

    //gestion del grupo
    void agregar_equipos(Equipo* e);
    Equipo* tomar_equipo(unsigned short)const;

    void actualizar_tabla(unsigned short i, unsigned short j,
                          unsigned short goles_i, unsigned short goles_j);

    void ordenar();

    Equipo* primero();
    Equipo* segundo();

    Equipo* operator[](unsigned short)const;

    ~Grupo();

};

#endif // GRUPO_H
