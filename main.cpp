#include <iostream>
#include "funciones.h"

using namespace std;

int main()
{
    cout << "===== UdeA World Cup Simulator =====" << endl;

    string archivo = "C:\\Users\\ASUS\\OneDrive\\Desktop\\c++\\desafio_2\\desafio_2_2026_1\\desafio_2_informatica2_2026-1\\selecciones_clasificadas_mundial.csv";


    Equipo** equipos = leerCSV(archivo);

    if(equipos == nullptr)
    {
        cout << "Error: no se pudieron cargar los equipos." << endl;
        return 1;
    }

    cout << "Equipos cargados correctamente." << endl;


    Torneo* torneo = inicializacion_torneo(equipos);

    if(torneo == nullptr)
    {
        cout << "Error al inicializar el torneo." << endl;
        liberar_memoria(equipos, 48);
        return 1;
    }

    cout << "Torneo inicializado." << endl;


    cout << "\n=== Iniciando simulacion ===\n" << endl;

    ejecutar_torneo(torneo);

    cout << "\n=== Simulacion finalizada ===\n" << endl;


    cout << "\n--- METRICAS ---" << endl;
    cout << "Trabajo total: " << cont_trabajo << endl;
    cout << "Memoria usada: " << memoria_usada << " bytes" << endl;


    liberar_torneo(torneo);
    liberar_memoria(equipos, 48);

    cout << "\nMemoria liberada correctamente." << endl;

    return 0;
}

