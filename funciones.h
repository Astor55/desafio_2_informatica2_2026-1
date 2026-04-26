#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "equipo.h"
#include "torneo.h"

//lectura del csv
Equipo** leerCSV(const string& NombreArchivo);

//torneo
Torneo* inicializacion_torno(Equipo** equipos);
void ejecutar_torneo(Torneo* torneo);

//liberacion de memoria
void liberar_memoria(Equipo** equipos, unsigned short n);
void liberar_torneo(Torneo* torneo);

//mediciones del sistema
extern long long cont_trabajo;
extern long long memoria_usada;

#endif // FUNCIONES_H
