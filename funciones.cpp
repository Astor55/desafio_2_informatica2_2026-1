#include "torneo.h"
#include "funciones.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

Equipo** leerCSV(const string& NombreArchivo)
{

    ifstream archivo(NombreArchivo);

    if(!archivo.is_open())
    {

        cout << "Error al abrir el archivo\n";
        return nullptr;

    }

    Equipo** equipos = new Equipo*[48];
    memoria_usada += sizeof(Equipo*) * 48;

    for(unsigned short i = 0; i < 48; i++)
    {

        cont_trabajo++;

        equipos[i] = nullptr;

    }

    string linea;

    getline(archivo, linea);
    getline(archivo, linea);

    unsigned short i = 0;

    while(getline(archivo, linea) && i < 48)
    {

        cont_trabajo++;

        stringstream ss(linea);

        string ranking, nombre, dt, federacion, confederacion;
        string goles_favor, goles_contra;
        string partidos_ganados, partidos_empatados, partidos_perdidos;

        getline(ss, ranking, ';');
        getline(ss, nombre, ';');
        getline(ss, dt, ';');
        getline(ss, federacion, ';');
        getline(ss, confederacion, ';');
        getline(ss, goles_favor, ';');
        getline(ss, goles_contra, ';');
        getline(ss, partidos_ganados, ';');
        getline(ss, partidos_empatados, ';');
        getline(ss, partidos_perdidos);

        try
        {

            equipos[i] = new Equipo(
                nombre, confederacion,
                stoi(goles_favor), stoi(goles_contra),
                stoi(ranking), stoi(partidos_ganados),
                stoi(partidos_empatados), stoi(partidos_perdidos)
            );
            memoria_usada += sizeof(Equipo);

            i++;

        }
        catch (...)
        {

            cout << "Error en linea CSV, ignorada\n";

        }
    }

    return equipos;

}



long long cont_trabajo = 0;

long long memoria_usada = 0;

Torneo* inicializacion_torno(Equipo** equipos)
{

    cont_trabajo++;
    Torneo* torneo = new Torneo(equipos[0]);
    memoria_usada += sizeof(Torneo);

    return torneo;

}



void ejecutar_torneo(Torneo* torneo)
{

    torneo->crear_bombos();

    torneo->generar_grupos();

    torneo->simular_fase_de_grupos();

    torneo->clasificar_equipos();

}



void liberar_memoria(Equipo** equipos, unsigned short n)
{

    for(unsigned int i = 0; i < n; i++)
    {

        cont_trabajo++;

        delete equipos[i];

    }

    delete[] equipos;

}



void liberar_torneo(Torneo* torneo)
{

    delete torneo;

}





