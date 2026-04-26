#include "torneo.h"
#include "funciones.h"

Torneo::Torneo(Equipo* equipos_jugando): cantidad_equipos(48), cantidad_bombos(4), cantidad_grupos(12){

    equipos = new Equipo*[cantidad_equipos];
    memoria_usada += sizeof(Equipo*) * cantidad_equipos;

    for(unsigned short i = 0 ;i < cantidad_equipos ; i++){

        equipos[i] = &equipos_jugando[i];
    }

    bombos = new Bombo*[cantidad_bombos];
    memoria_usada += sizeof(Bombo*) * cantidad_bombos;

    grupos = new Grupo*[cantidad_grupos];
    memoria_usada += sizeof(Grupo*) * cantidad_grupos;

    for(unsigned short i = 0; i < cantidad_bombos; i++){

        bombos[i] = new Bombo();
        memoria_usada += sizeof(Bombo);
    }

    for (unsigned short i = 0; i < cantidad_grupos; i++) {

        grupos[i] = new Grupo('A' + i);
        memoria_usada += sizeof(Grupo);
    }

}

Torneo :: Torneo(const Torneo& otro){

    cantidad_equipos = otro.cantidad_equipos;
    cantidad_bombos = otro.cantidad_bombos;
    cantidad_grupos = otro.cantidad_grupos;

    equipos = new Equipo*[cantidad_equipos];
    memoria_usada += sizeof(Equipo*) * cantidad_equipos;

    bombos = new Bombo*[cantidad_bombos];
    memoria_usada += sizeof(Bombo*) * cantidad_bombos;

    grupos = new Grupo*[cantidad_grupos];
    memoria_usada += sizeof(Grupo*) * cantidad_grupos;

    for(unsigned short i = 0; i < cantidad_equipos; i++){

        equipos[i] = otro.equipos[i];
        cont_trabajo++;
    }

    for(unsigned short j = 0; j < cantidad_bombos; j++){

        for(unsigned short equi = 0; equi < 12; equi++){

            bombos[j][equi] = otro.bombos[j][equi];
            cont_trabajo++;
        }
    }

    for(unsigned short a = 0; a < cantidad_grupos; a++){

        for(unsigned short teams = 0; teams < 4; teams++){

            grupos[a][teams] = otro.grupos[a][teams];
            cont_trabajo++;
        }
    }
}

void Torneo :: crear_bombos(){

    for(unsigned short i = 0; i < cantidad_equipos - 1; i++){ //Bubble sort, ordena los equipos segun su ranking fifa

        for(unsigned short j = 0; j < cantidad_equipos - i - 1; j++){

            if(equipos[j]->getRankingFIFA() > equipos[j+1]->getRankingFIFA()){

                cont_trabajo++;

                Equipo* temp = equipos[j];

                equipos[j] = equipos[j+1];

                equipos[j+1] = temp;
            }

        }
    }

    for(unsigned short a = 0; a < cantidad_equipos; a++){ //Guarda en cada bombo del arreglo de bombos, los equipos segun su ranking fifa

        cont_trabajo++;

        if(a < 12)
            bombos[0]->Agregar_equipo(equipos[a]);

        else if(a < 24)
            bombos[1]->Agregar_equipo(equipos[a]);

        else if(a < 36)
            bombos[2]->Agregar_equipo(equipos[a]);

        else
            bombos[3]->Agregar_equipo(equipos[a]);
    }
}

void Torneo :: generar_grupos(){

    for(unsigned short j = 0; j < cantidad_grupos; j++)
    {
        for(unsigned short i = 0; i < cantidad_bombos; i++)
        {
            bool asignado = false;

            while(!asignado)
            {
                cont_trabajo++;

                Equipo* equipo = bombos[i]->Sacar_aleatorio();

                if(equipo == nullptr) break;

                if(grupos[j]->confederacion_valida(equipo))
                {
                    grupos[j]->agregar_equipos(equipo);
                    asignado = true;
                }
                else
                {

                    bombos[i]->Agregar_equipo(equipo);
                }
            }
        }
    }
}

void Torneo :: simular_fase_de_grupos(){

    for(unsigned short g = 0; g < cantidad_grupos; g++)
    {
        Grupo* grupo = grupos[g];

        for(int i = 0; i < 4; i++)
        {
            for(int j = i + 1; j < 4; j++)
            {
                Equipo* equipo1 = grupo->tomar_equipo(i);
                Equipo* equipo2 = grupo->tomar_equipo(j);

                string arbitros[3] ={"codArbitro1","codArbitro2","codArbitro3"};

                Partido game(equipo1, equipo2, "nombreSede", arbitros, "00:00", "20/07/2026");
                game.jugar();

                cont_trabajo++;

                grupo->actualizar_tabla(i, j, game.getgoles1(), game.getgoles2());
            }
        }

        grupo->ordenar();

    }

}


void Torneo :: clasificar_mejores_terceros(Equipo* mejores_terceros[8]){

    Equipo* terceros[12];
    unsigned short puntos[12];
    short dif_goles[12];

    for(unsigned short i = 0; i < cantidad_grupos; i++)
    {
        grupos[i]->ordenar();

        terceros[i] = (*grupos[i])[2]; //Se realiza la indireccion debido a que un grupo en esta clase es un arreglo de arreglos de tipo grupo,
                                       // y necesitamos trabajar con los grupos, no con punteros

        puntos[i] = grupos[i]->getpuntos(2);

        dif_goles[i] = grupos[i]->getdiffgoles(2);

        cont_trabajo++;
    }

    for(int i = 0; i < 11; i++) //Bubble sort para equipos, sus puntos y la diferencia de goles en el grupo
    {
        for(int j = 0; j < 11 - i; j++)
        {
            if(puntos[j+1] > puntos[j] ||
                (puntos[j+1] == puntos[j] &&
                 dif_goles[j+1] > dif_goles[j]))
            {

                Equipo* tempE = terceros[j];
                terceros[j] = terceros[j+1];
                terceros[j+1] = tempE;


                unsigned short tempP = puntos[j];
                puntos[j] = puntos[j+1];
                puntos[j+1] = tempP;


                short tempD = dif_goles[j];
                dif_goles[j] = dif_goles[j+1];
                dif_goles[j+1] = tempD;

                cont_trabajo++;
            }
        }
    }

    for(int i = 0; i < 8; i++)
    {
        mejores_terceros[i] = terceros[i];
        cont_trabajo++;
    }
}


void Torneo :: clasificar_equipos(){

    Equipo* clasificados[32];
    Equipo* mejores_terceros[8];

    clasificar_mejores_terceros(mejores_terceros);

    // primeros y segundos
    for(int i = 0; i < 12; i++){
        clasificados[i*2]     = grupos[i]->primero(); //se usa i*2 y luego i*2+1, debido a que estos seran los indices de cada equipo en el arreglo
                                                      // de clasificados, y por cada iteracion es un grupo, por tanto cada iteracion ocupa 2 indices.
        clasificados[i*2 +1 ] = grupos[i]->segundo();
        cont_trabajo++;
    }

    // agregar mejores terceros
    for(int i = 0; i < 8; i++){ //Aqui se usa 24+ i debido a que en el for anterior, clasifican los primeros y segundos, genrando un total de 23
                                // y despues estos indices de 24 a 31 se rellenan con los mejores terceros
        clasificados[24 + i] = mejores_terceros[i];
        cont_trabajo++;
    }
}

void Torneo :: simular_eliminatorias(){

    Equipo* equipos_clasificados[32] = clasificar_equipos();
    Equipo* equipos_ganadores[];

    for(unsigned int i = 0; i < 32; i++){

        cont_trabajo++;

        Equipo* equipo1 = equipos_clasificados[i*2];
        Equipo* equipo2 = equipos_clasificados[(i*2) + 1];

        string arbitros[3] ={"codArbitro1","codArbitro2","codArbitro3"};

        Partido game(equipo1, equipo2, "nombreSede", arbitros, "00:00", "10/07/2026");

        game.jugar();

    }


}

