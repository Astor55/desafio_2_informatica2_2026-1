#include "torneo.h"
#include "partido.h"
#include "funciones.h"
#include <iostream>

Torneo::Torneo(Equipo** equipos_jugando): cantidad_equipos(48), cantidad_bombos(4), cantidad_grupos(12){

    equipos = new Equipo*[cantidad_equipos];
    equipos_originales = new Equipo*[48];
    memoria_usada += sizeof(Equipo*) * cantidad_equipos;
    memoria_usada += sizeof(Equipo*) * 48;

    for(unsigned short i = 0 ;i < cantidad_equipos ; i++){

        equipos[i] = equipos_jugando[i];
    }

    bombos = new Bombo*[cantidad_bombos];
    memoria_usada += sizeof(Bombo*) * cantidad_bombos;

    grupos = new Grupo*[cantidad_grupos];
    memoria_usada += sizeof(Grupo*) * cantidad_grupos;

    for(unsigned short i = 0; i < cantidad_bombos; i++){

        bombos[i] = new Bombo();
        memoria_usada += sizeof(Bombo);
    }

    for (unsigned short k = 0; k < cantidad_grupos; k++) {

        grupos[k]= new Grupo('A' + k);
        memoria_usada += sizeof(Grupo);
    }

    for(int m = 0; m < 48; m++)
    {
        equipos_originales[m] = equipos[m];
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

        bombos[j] = new Bombo(*otro.bombos[j]);
        cont_trabajo++;

    }

    for(unsigned short a = 0; a < cantidad_grupos; a++){

        grupos[a] = new Grupo(*otro.grupos[a]);
        cont_trabajo++;

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

void Torneo::reiniciar_bombos()
{
    for(int i = 0; i < cantidad_bombos; i++)
    {
        bombos[i]->vaciar();
    }

    int index = 0;

    for(int i = 0; i < cantidad_bombos; i++)
    {
        for(int j = 0; j < 12; j++)
        {

            if(index >= 48)
            {
                cout << "ERROR: overflow en reiniciar_bombos" << endl;
                return;
            }

            Equipo* e = equipos_originales[index++];

            if(e == nullptr)
            {
                cout << "ERROR: equipo null en reinicio" << endl;
                return;
            }

            bombos[i]->Agregar_equipo(e);
        }
    }


}


void Torneo::limpiar_grupos()
{
    for(unsigned short i = 0; i < cantidad_grupos; i++)
    {
        unsigned short n = grupos[i]->getCantidadEquipos();

        for(unsigned short j = 0; j < n; j++)
        {
            Equipo* equipo = grupos[i]->tomar_equipo(j);

            if(equipo != nullptr)
            {

                int bombo_index = equipo->getBombo();
                bombos[bombo_index]->Agregar_equipo(equipo);

            }
        }

        grupos[i]->vaciar();
    }
}


void Torneo::generar_grupos()
{
    bool valido = false;

    int max_intentos = 100;
    int ciclos = 0;

    while(!valido && ciclos < max_intentos)
    {
        ciclos++;
        valido = true;

        limpiar_grupos();
        reiniciar_bombos();

        for(unsigned short j = 0; j < cantidad_grupos; j++)
        {
            for(unsigned short i = 0; i < cantidad_bombos; i++)
            {
                bool asignado = false;
                unsigned short intentos = 0;

                Equipo* ultimo = nullptr;

                while(!asignado && intentos < 100)
                {
                    intentos++;

                    Equipo* equipo = bombos[i]->Sacar_aleatorio();

                    if(equipo == nullptr) break;

                    ultimo = equipo;

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

                if(!asignado)
                {
                    if(ultimo != nullptr)
                    {
                        grupos[j]->agregar_equipos(ultimo);
                        asignado = true;
                    }
                    else
                    {
                        valido = false;
                        break;
                    }
                }
            }

            if(!valido) break;
        }
    }

    if(!valido)
    {
        cout << "ERROR: no se pudieron generar grupos validos" << endl;
    }
}



void Torneo :: simular_fase_de_grupos(){

    for(unsigned short g = 0; g < cantidad_grupos; g++)
    {
        Grupo* grupo = grupos[g];

        cout << "\n=== GRUPO " << char('A' + g) << " ===\n";

        for(int i = 0; i < 4; i++)
        {
            for(int j = i + 1; j < 4; j++)
            {
                Equipo* equipo1 = grupo->tomar_equipo(i);
                Equipo* equipo2 = grupo->tomar_equipo(j);

                string arbitros[3] ={"codArbitro1","codArbitro2","codArbitro3"};

                Partido game(equipo1, equipo2, "nombreSede", arbitros, "00:00", "20/07/2026");
                game.jugar();

                cout << equipo1->getnombre() << " "
                     << game.getgoles1() << " - "
                     << game.getgoles2() << " "
                     << equipo2->getnombre() << endl;

                cont_trabajo++;

                grupo->actualizar_tabla(i, j, game.getgoles1(), game.getgoles2());
            }
        }

        grupo->ordenar();

    }

}


void Torneo :: clasificar_mejores_terceros(Equipo* mejores_terceros[8]){

    Equipo* terceros[12];
    unsigned short puntos[12] = {0};
    short dif_goles[12] = {0};


    for(unsigned short i = 0; i < cantidad_grupos; i++)
    {
        grupos[i]->ordenar();

        terceros[i] = (*grupos[i])[2]; //Se realiza la indireccion debido a que un grupo en esta clase es un arreglo de arreglos de tipo grupo,
                                       // y necesitamos trabajar con los grupos, no con punteros

        puntos[i] = grupos[i]->getpuntos(2);

        dif_goles[i] = grupos[i]->getdiffgoles(2);

        cont_trabajo++;
    }

    for(unsigned short i = 0; i < cantidad_grupos; i++) //Bubble sort para equipos, sus puntos y la diferencia de goles en el grupo
    {
        for(unsigned short j = 0; j < cantidad_grupos - i - 1; j++)
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


    for(unsigned short i = 0; i < 8; i++)
    {
        mejores_terceros[i] = terceros[i];
        cont_trabajo++;
    }
}


Equipo** Torneo :: clasificar_equipos(Equipo* clasificados[32]){

    Equipo* mejores_terceros[8];

    clasificar_mejores_terceros(mejores_terceros);

    // primeros y segundos
    for(unsigned short i = 0; i < 12; i++){
        clasificados[i*2]     = grupos[i]->primero(); //se usa i*2 y luego i*2+1, debido a que estos seran los indices de cada equipo en el arreglo
                                                      // de clasificados, y por cada iteracion es un grupo, por tanto cada iteracion ocupa 2 indices.
        clasificados[i*2 +1 ] = grupos[i]->segundo();
        cont_trabajo++;
    }

    // agregar mejores terceros
    for(unsigned short i = 0; i < 8; i++){ //Aqui se usa 24+ i debido a que en el for anterior, clasifican los primeros y segundos, genrando un total de 23
                                // y despues estos indices de 24 a 31 se rellenan con los mejores terceros
        clasificados[24 + i] = mejores_terceros[i];
        cont_trabajo++;
    }

    for(unsigned short i = 0; i < 32; i++)
    {

        clasificados_R16[i] = clasificados[i];

    }

    return clasificados;
}



void Torneo::simular_eliminatorias(Equipo* clasificados[32])
{
    clasificar_equipos(clasificados);

    // OCTAVOS (R16)
    for (unsigned short i = 0; i < 16; i++)
    {
        cont_trabajo++;

        Equipo* equipo1 = clasificados[i * 2];
        Equipo* equipo2 = clasificados[i * 2 + 1];

        string arbitros[3] = {"codArbitro1","codArbitro2","codArbitro3"};

        Partido game(equipo1, equipo2, "nombreSede", arbitros, "00:00", "10/07/2026");
        game.jugar();

        cout << "\n[OCTAVOS]\n";
        cout << equipo1->getnombre() << " "
             << game.getgoles1() << " - "
             << game.getgoles2() << " "
             << equipo2->getnombre() << endl;

        cout << "Posesion: "
             << game.getposesion1() << "% - "
             << game.getposesion2() << "%\n";

        if (game.getgoles1() > game.getgoles2())
            this->R16[i] = equipo1;
        else
            this->R16[i] = equipo2;
    }

    // CUARTOS (R8)
    for (unsigned short j = 0; j < 8; j++)
    {
        cont_trabajo++;

        Equipo* team1 = this->R16[j * 2];
        Equipo* team2 = this->R16[j * 2 + 1];

        string arbitros2[3] = {"codArbitro1","codArbitro2","codArbitro3"};

        Partido game(team1, team2, "nombreSede", arbitros2, "00:00", "10/07/2026");
        game.jugar();

        cout << "\n[CUARTOS]\n";
        cout << team1->getnombre() << " "
             << game.getgoles1() << " - "
             << game.getgoles2() << " "
             << team2->getnombre() << endl;

        cout << "Posesion: "
             << game.getposesion1() << "% - "
             << game.getposesion2() << "%\n";

        if (game.getgoles1() > game.getgoles2())
            this->R8[j] = team1;
        else
            this->R8[j] = team2;
    }

    // SEMIFINALES (R4)
    Equipo* perdedores_semi[2];

    for (unsigned short k = 0; k < 4; k++)
    {
        cont_trabajo++;

        Equipo* team1 = this->R8[k * 2];
        Equipo* team2 = this->R8[k * 2 + 1];

        string arbitrosS[3] = {"codArbitro1","codArbitro2","codArbitro3"};

        Partido game3(team1, team2, "nombreSede", arbitrosS, "00:00", "10/07/2026");
        game3.jugar();
        cout << "\n[SEMIFINALES]\n";
        cout << team1->getnombre() << " "
             << game3.getgoles1() << " - "
             << game3.getgoles2() << " "
             << team2->getnombre() << endl;

        cout << "Posesion: "
             << game3.getposesion1() << "% - "
             << game3.getposesion2() << "%\n";

        if (game3.getgoles1() >= game3.getgoles2())
        {
            this->R4[k] = team1;
            perdedores_semi[k / 2] = team2;
        }
        else
        {
            this->R4[k] = team2;
            perdedores_semi[k / 2] = team1;
        }
    }

    // FINAL
    Equipo* final1 = this->R4[0];
    Equipo* final2 = this->R4[1];

    string arbitrosF[3] = {"codArbitro1","codArbitro2","codArbitro3"};

    Partido final(final1, final2, "nombreSede", arbitrosF, "00:00", "10/07/2026");
    final.jugar();

    cout << "\n[FINAL]\n";
    cout << final1->getnombre() << " "
         << final.getgoles1() << " - "
         << final.getgoles2() << " "
         << final2->getnombre() << endl;

    cout << "Posesion: "
         << final.getposesion1() << "% - "
         << final.getposesion2() << "%\n";

    Equipo* campeon;
    Equipo* subcampeon;

    if (final.getgoles1() > final.getgoles2())
    {
        campeon = final1;
        subcampeon = final2;
    }
    else
    {
        campeon = final2;
        subcampeon = final1;
    }

    // TERCER PUESTO
    string arbitros3[3] = {"codArbitro1","codArbitro2","codArbitro3"};

    Partido tercerPuesto(perdedores_semi[0], perdedores_semi[1],
                         "nombreSede", arbitros3, "00:00", "10/07/2026");

    tercerPuesto.jugar();

    cout << "\n[TERCER PUESTO]\n";
    cout << perdedores_semi[0]->getnombre() << " "
         << tercerPuesto.getgoles1() << " - "
         << tercerPuesto.getgoles2() << " "
         << perdedores_semi[1]->getnombre() << endl;

    cout << "Posesion: "
         << tercerPuesto.getposesion1() << "% - "
         << tercerPuesto.getposesion2() << "%\n";

    Equipo* tercero;
    Equipo* cuarto;

    if (tercerPuesto.getgoles1() >= tercerPuesto.getgoles2())
    {
        tercero = perdedores_semi[0];
        cuarto = perdedores_semi[1];
    }
    else
    {
        tercero = perdedores_semi[1];
        cuarto = perdedores_semi[0];
    }

    // GUARDAR RESULTADOS
    this->campeon = campeon;
    this->subcampeon = subcampeon;
    this->tercero = tercero;
    this->cuarto = cuarto;
}



void Torneo::generar_estadisticas()
{

    //RESULTADOS
    cout << "\nCampeon: " << campeon->getnombre() << endl;
    cout << "Subcampeon: " << subcampeon->getnombre() << endl;
    cout << "Tercero: " << tercero->getnombre() << endl;
    cout << "Cuarto: " << cuarto->getnombre() << endl;

    //TOP goleador campeon
    Jugador* maxG = nullptr;
    unsigned int max = 0;

    for(unsigned short i = 0; i < campeon->getcantidadJugadores(); i++)
    {

        Jugador* player = &campeon->getJugadores()[i];

        if(player->getGoles() > max)
        {

            max = player->getGoles();
            maxG = player;

        }
    }
    if(maxG != nullptr)
    {
        cout << "\n--- MEJOR GOLEADOR ---\n"
             << maxG->getNombre() << " "
             << maxG->getApellido()
             << "con " << max << " goles\n";
    }

    else
    {
        cout << "\n--- MEJOR GOLEADOR ---\n";
        cout << "No hubo goles en el equipo campeon.\n";
    }

    // Top 3 goleadores global

    Jugador* todos[2000];
    unsigned int total = 0;

    for(unsigned int e = 0; e < cantidad_equipos; e++)
    {

        if(equipos[e] != nullptr)
        {

            for(unsigned int j = 0; j < equipos[e]->getcantidadJugadores(); j++)
            {

                todos[total++] = &equipos[e]->getJugadores()[j];

            }
        }
    }

    for (int i = 0; i < total - 1; i++) //Bubble sort
    {
        for (int j = 0; j < total - i - 1; j++)
        {
            if (todos[j]->getGoles() < todos[j + 1]->getGoles())
            {
                Jugador* temp = todos[j];
                todos[j] = todos[j + 1];
                todos[j + 1] = temp;
            }
        }
    }

    cout << "\n--- TOP 3 GOLEADORES ---\n";
    for (int i = 0; i < 3 && i < total; i++)
    {
        cout << i + 1 << ". "
             << todos[i]->getNombre() << " "
             << todos[i]->getApellido()
             << " - " << todos[i]->getGoles() << " goles\n";
    }

    //El equipo con más cantidad de goles históricos
    if(cantidad_equipos > 0 && equipos[0] != nullptr)
    {
        Equipo* best = equipos[0];

        for (int i = 1; i < cantidad_equipos; i++)
        {
            if (equipos[i] != nullptr &&
                equipos[i]->getGolesAFavor() > best->getGolesAFavor())
            {
                best = equipos[i];
            }
        }

        cout << "\n--- EL EQUIPO CON MAS GOLES HISTORICOS ---\n";
        cout << best->getnombre()
             << " con " << best->getGolesAFavor() << " goles\n";
    }
    else
    {
        cout << "\n--- EL EQUIPO CON MAS GOLES HISTORICOS ---\n";
        cout << "No hay equipos validos.\n";
    }

    //La confederacion con mayor presencia de equipo en cada etapa
    int uefaR16 = 0, conmebolR16 = 0;
    int uefaR8 = 0, conmebolR8 = 0;
    int uefaR4 = 0, conmebolR4 = 0;

    for(int i = 0; i < 16; i++)
    {
        if(R16[i] != nullptr)
        {
            if(R16[i]->getconfederacion() == "UEFA") uefaR16++;
            if(R16[i]->getconfederacion() == "CONMEBOL") conmebolR16++;
        }
    }

    for(int i = 0; i < 8; i++)
    {

        if(R8[i] != nullptr)
        {
            if(R8[i]->getconfederacion() == "UEFA") uefaR8++;
            if(R8[i]->getconfederacion() == "CONMEBOL") conmebolR8++;
        }
    }

    for(int i = 0; i < 4; i++)
    {
        if(R4[i] != nullptr)
        {
            if(R4[i]->getconfederacion() == "UEFA") uefaR4++;
            if(R4[i]->getconfederacion() == "CONMEBOL") conmebolR4++;

        }
    }

    cout << "\n--- CONFEDERACIONES ---\n";
    cout << "R16 UEFA: " << uefaR16 << " CONMEBOL: " << conmebolR16 << endl;
    cout << "R8  UEFA: " << uefaR8 << " CONMEBOL: " << conmebolR8 << endl;
    cout << "R4  UEFA: " << uefaR4 << " CONMEBOL: " << conmebolR4 << endl;


}



Torneo :: ~Torneo(){

    for(unsigned int j = 0 ; j < 4; j++){
        delete bombos[j];
    }
    delete[] bombos;

    for(unsigned int k = 0 ; k < cantidad_grupos; k++){
        delete grupos[k];
    }
    delete[] grupos;

    delete[] equipos_originales;
}

