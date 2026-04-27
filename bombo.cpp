#include "bombo.h"
#include "funciones.h"
#include <random>

Bombo :: Bombo(){

    cantidad = 12;

    posicion_equipo = 0;

    equipos = new Equipo*[cantidad];
    memoria_usada += sizeof(Equipo*) * cantidad;

    for (unsigned short i = 0; i < cantidad; ++i)
    {

        equipos[i] = nullptr;
        cont_trabajo++;

    }
}


Bombo :: Bombo(const Bombo& otro){

    cantidad = otro.cantidad;

    posicion_equipo = otro.posicion_equipo;

    equipos = new Equipo*[cantidad];
    memoria_usada += sizeof(Equipo*) * cantidad;

    for(unsigned short i = 0; i < cantidad; i++){

        equipos[i] = otro.equipos[i];
        cont_trabajo++;
    }
}


void Bombo::Agregar_equipo(Equipo* equipo_nuevo)
{
    if(equipo_nuevo == nullptr) return;

    for(unsigned short i = 0; i < cantidad; i++)
    {
        if(equipos[i] == equipo_nuevo)
        {
            return;
        }
    }

    if(cantidad < 12)
    {
        equipos[cantidad++] = equipo_nuevo;
    }
}


Equipo* Bombo::Sacar_aleatorio()
{
    if(cantidad == 0)
    {
        return nullptr;
    }

    static random_device rd;
    static mt19937 gen(rd());

    uniform_int_distribution<int> dist(0, cantidad - 1);

    unsigned short indice = dist(gen);

    Equipo* seleccionado = equipos[indice];

    equipos[indice] = equipos[cantidad - 1];

    cantidad--;

    return seleccionado;
}

void Bombo :: vaciar(){

    for(unsigned short i = 0; i < cantidad; i++)
    {
        equipos[i] = nullptr;
    }
    cantidad = 0;
}


Bombo& Bombo :: operator=(const Bombo& otro)
{

    if(this == &otro) return *this;


    delete[] equipos;

    cantidad = otro.cantidad;

    posicion_equipo = otro.posicion_equipo;

    equipos = new Equipo*[cantidad];
    memoria_usada += sizeof(Equipo*) * cantidad;

    for(unsigned short i = 0; i < cantidad; i++){

        equipos[i] = otro.equipos[i];
        cont_trabajo++;
    }

    return *this;

}



bool Bombo :: operator==(const Bombo& otro) const{

    if(cantidad != otro.cantidad){

        return false;
    }

    else if(posicion_equipo != otro.posicion_equipo){

        return false;
    }

    for(int i = 0; i < cantidad; i++){

        if(equipos[i] != otro.equipos[i]){
            cont_trabajo++;

            return false;
        }
    }


    return true;

}



Bombo::~Bombo()
{

    delete[] equipos;

}
