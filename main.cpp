#include <iostream>
#include "funciones.h"
using namespace std;

int main()
{

    Equipo** equipos = leerCSV("C:\\Users\\ASUS\\OneDrive\\Desktop\\c++\\desafio_2\\desafio_2_2026_1\\desafio_2_informatica2_2026-1\\selecciones_clasificadas_mundial.csv");

    if(equipos == nullptr)
    {

        cout << "No se cargaron equipos\n";
        return 1;

    }

    for (int j = 0; j < 48; j++)
    {

        cout << "Equipo: " << equipos[j]->getnombre() << endl;
        cout << "ranking: " << equipos[j]->getRankingFIFA() << endl;
        cout << "Goles a favor: " << equipos[j]->getGolesAFavor() << endl;
        cout << "Goles en contra: " << equipos[j]->getGolesEnContra() << endl;
        cout << "Partidos ganados: " << equipos[j]->getPartidosGanados() << endl;
        cout << "Partidos empatados: " << equipos[j]->getPartidosEmpatados() << endl;
        cout << "Partidos perdidos: " << equipos[j]->getPartidosPerdidos() << endl;
        cout << "----------------------" << endl;

    }

    liberar_memoria(equipos, 48);

    return 0;
}
