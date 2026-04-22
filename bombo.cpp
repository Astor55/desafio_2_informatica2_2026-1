#include "bombo.h"

Bombo :: Bombo(){

    cantidad = 12;

    posicion_equipo = 0;

    equipos = new Equipo*[cantidad];
}


Bombo :: Bombo(const Bombo& otro){

    cantidad = otro.cantidad;

    posicion_equipo = otro.posicion_equipo;

    equipos = new Equipo*[cantidad];

    for(int i = 0; i < posicion_equipo ; i++){

        equipos[i] = otro.equipos[i];
    }


}


void Bombo :: Agregar_equipo(Equipo* nuevo_equipo){

    if(posicion_equipo < cantidad){

        equipos[posicion_equipo] = nuevo_equipo;
        posicion_equipo++;
    }
}


Equipo* Bombo :: Sacar_aleatorio(){


    if(posicion_equipo == 0){

        return nullptr;
    }

    static random_device rd;
    static mt19937 gen(rd());

    uniform_int_distribution<> dist(0, posicion_equipo -1);

    indice = dist(gen);

    Equipo* seleccionado = equipos[indice];

    equipos[indice] = equipos[posicion_equipo - 1];

    posicion_equipo--;

    return seleccionado;
}



Bombo& Bombo :: operator=(const Bombo& otro){

    if(this != &otro){

        delete[] equipos;

        cantidad = otro.cantidad;

        posicion_equipo = otro.posicion_equipo;

        equipos = new Equipo*[cantidad];

        for(int i = 0; i < posicion_equipo; i++){

            equipos[i] = otro.equipos[i];
        }

        return *this;
    }


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

            return false;
        }
    }


    return true;

}



Bombo :: ~Bombo(){

    delete[] equipos;

}
