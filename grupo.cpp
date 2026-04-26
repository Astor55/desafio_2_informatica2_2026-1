#include "grupo.h"

//constructor
Grupo::Grupo(char l) : letra(l), cantidad_equipos(0), puntos{0}, dif_goles{0}
{

    equipos = new Equipo*[4];

    for(unsigned short i = 0; i < 4; i++)
    {

        equipos[i] = nullptr;

    }

}


//contructor de copia
Grupo::Grupo(const Grupo& otro)
{

    letra = otro.letra;
    cantidad_equipos = otro.cantidad_equipos;

    equipos = new Equipo*[4];

    for(unsigned short i = 0; i < 4; i++)
    {

        equipos[i] = otro.equipos[i];
        puntos[i] = otro.puntos[i];
        dif_goles[i] = otro.dif_goles[i];

    }

}


// agrega equipos
void Grupo::agregar_equipos(Equipo* e)
{

    if(e!= nullptr && cantidad_equipos < 4)
    {

        equipos[cantidad_equipos++] = e;

    }

}


//acceso
Equipo* Grupo::tomar_equipo(unsigned short i)const
{

    if(i < cantidad_equipos)
    {

        return equipos[i];

    }

    return nullptr;

}


//actualizacion de tabla del rankin en el grupo
void Grupo::actualizar_tabla(unsigned short i, unsigned short j,
                                 unsigned short goles_i, unsigned short goles_j)
{

    if(i >= 4 || j>= 4) return; //verifica los limites

    //diferencia de goles
    short dif = (short)goles_i - (short)goles_j;
    dif_goles[i] += dif;
    dif_goles[j] -= dif;

    //si gana equipo 1
    if(goles_i > goles_j)
    {

        puntos[i] += 3;

    }

    //si gana equipo 2
    else if(goles_j > goles_i)
    {

        puntos[j] += 3;

    }

    //es empate
    else
    {

        puntos[i] += 1;
        puntos[j] += 1;

    }
}


//sobrecarga []
Equipo* Grupo::operator[](unsigned short i)const
{

    if(i < cantidad_equipos)
    {

        return equipos[i];

    }

    return nullptr;

}


void Grupo::ordenar()
{

    for(unsigned short i = 0; i < cantidad_equipos - 1; i++)
    {

        bool cambio = false;

        for (unsigned short j = 0; j < cantidad_equipos - 1 - i; j++)
        {

            if(puntos[j + 1] > puntos[j] ||
                (puntos[j + 1] == puntos[j] &&
                                              dif_goles [j + 1] > dif_goles[j]))
            {

                //reordenamiento
                Equipo* tempE = equipos[j];

                equipos[j] = equipos[j + 1];
                equipos[j + 1] = tempE;

                unsigned short tempP = puntos[j];

                puntos[j] = puntos[j + 1];
                puntos[j +1] = tempP;

                short tempD = dif_goles[j];

                dif_goles[j] = dif_goles[j + 1];
                dif_goles[j + 1] = tempD;

                cambio = true;

            }

        }

        if(!cambio) break;

    }

}


//clasificados
Equipo* Grupo::primero()
{

    return equipos[0];

}


Equipo* Grupo::segundo()
{

    return equipos[1];

}


bool Grupo :: confederacion_valida(Equipo * equipo) const{

    if(equipo == nullptr) return false;

    string conf = equipo->getConfederacion();
    int contador = 0;

    for(unsigned short i = 0; i < cantidad_equipos; i++)
    {
        if(equipos[i] != nullptr &&
            equipos[i]->getConfederacion() == conf)
        {
            contador++;
        }
    }

    if(conf == "UEFA" || conf == "uefa")
    {
        return contador < 2;
    }

    return contador == 0;

}

//Getters

unsigned short Grupo :: getpuntos(unsigned short i)const{

    return puntos[i];
}

short Grupo :: getdiffgoles(unsigned short j)const{

    return dif_goles[j];
}


//destructor
Grupo::~Grupo(){

    delete[] equipos;
}
