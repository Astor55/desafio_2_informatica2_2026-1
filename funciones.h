#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "equipo.h"

Equipo** leerCSV(const string& NombreArchivo);

void liberar_memoria(Equipo** equipos, unsigned short n);

#endif // FUNCIONES_H
