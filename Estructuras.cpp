
#include <iostream>
#include <cstring>
#include <fstream> 

#define MAX 50

using namespace std;

//=====================================================
// ESTRUCTURAS
//=====================================================

struct Jugador {
    int idJugador;
    char alias[30];
    char nombre[50];
    int ranking;
};

struct Partida {
    int idPartida;
    Jugador jugador1;
    Jugador jugador2;
    char estado[20];
};

struct Resultado {
    int idPartida;
    int idGanador;
    int puntajeJ1;
    int puntajeJ2;
};

struct ListaJugadores {
    Jugador elementos[MAX];
    int tamano;
};

struct ColaPartidas {
    Partida elementos[MAX];
    int frente;
    int final;
};

struct PilaHistorial {
    Resultado elementos[MAX];
    int tope;
};

//=====================================================
// INICIALIZACIÓN Y BÚSQUEDA
//=====================================================

void inicializarLista(ListaJugadores *lista) {
    lista->tamano = 0;
}

void inicializarCola(ColaPartidas *cola) {
    cola->frente = 0;
    cola->final = -1;
}

void inicializarPila(PilaHistorial *pila) {
    pila->tope = -1;
}

int buscarJugador(ListaJugadores *lista, int id) {
    for(int i = 0; i < lista->tamano; i++) {
        if(lista->elementos[i].idJugador == id) {
            return i;
        }
    }
    return -1;
}

void buscarJugadorUI(ListaJugadores *lista) {
    if(lista->tamano == 0) {
        cout << "\n[!] No existen jugadores registrados.\n";
        return;
    }
    int id;
    cout << "\nIngrese el ID a buscar: ";
    while (!(cin >> id)) {
        cout << "[!] Ingrese un numero valido para el ID: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    int pos = buscarJugador(lista, id);
    if(pos != -1) {
        cout << "\n+---------------------------------------+";
        cout << "\n|          JUGADOR ENCONTRADO           |";
        cout << "\n+---------------------------------------+";
        cout << "\n  ID      : " << lista->elementos[pos].idJugador;
        cout << "\n  Alias   : " << lista->elementos[pos].alias;
        cout << "\n  Nombre  : " << lista->elementos[pos].nombre;
        cout << "\n  Ranking : " << lista->elementos[pos].ranking << " pts";
        cout << "\n+---------------------------------------+\n";
    } else {
        cout << "\n[X] Jugador no encontrado.\n";
    }
}

//=====================================================
// MÓDULO LISTA (JUGADORES)
//=====================================================

void registrarJugador(ListaJugadores *lista) {
    if(lista->tamano >= MAX) {
        cout << "\n[!] Error: Lista de jugadores llena.\n";
        return;
    }

    Jugador nuevo;
    cout << "\n>>> REGISTRO DE NUEVO JUGADOR <<<\n";
    cout << "ID del jugador : ";
    while (!(cin >> nuevo.idJugador)) {
        cout << "[!] Ingrese un numero entero valido para el ID: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    if(buscarJugador(lista, nuevo.idJugador) != -1) {
        cout << "\n[X] Error: El ID ya se encuentra registrado.\n";
        return;
    }

    cin.ignore(10000, '\n');
    cout << "Alias          : ";
    cin.getline(nuevo.alias, 30);

    cout << "Nombre completo: ";
    cin.getline(nuevo.nombre, 50);

    cout << "Ranking        : ";
    while (!(cin >> nuevo.ranking)) {
        cout << "[!] Ingrese un numero entero valido para el Ranking: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    lista->elementos[lista->tamano] = nuevo;
    lista->tamano++;

    cout << "\n[V] Jugador registrado correctamente.\n";
}

void actualizarJugador(ListaJugadores* lista) {
    if (lista->tamano == 0) {
        cout << "\n[!] No hay jugadores para actualizar.\n";
        return;
    }

    int id;
    cout << "\nIngrese el ID del jugador a actualizar: ";
    while (!(cin >> id)) {
        cout << "[!] Ingrese un numero valido: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    for (int i = 0; i < lista->tamano; i++) {
        Jugador* ptrJ = &lista->elementos[i];
        if (ptrJ->idJugador == id) {
            cout << "\n--- Ingrese los nuevos datos ---\n";
            cin.ignore(10000, '\n');
            cout << "Nuevo Alias  : ";
            cin.getline(ptrJ->alias, 30);

            cout << "Nuevo Nombre : ";
            cin.getline(ptrJ->nombre, 50);

            cout << "Nuevo Ranking: ";
            while (!(cin >> ptrJ->ranking)) {
                cout << "[!] Ingrese un numero valido: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }

            cout << "\n[V] Jugador actualizado con exito.\n";
            return;
        }
    }
    cout << "\n[X] No se encontro un jugador con ese ID.\n";
}

bool retirarJugador(ListaJugadores* lista) {
    if (lista->tamano == 0) {
        cout << "\n[!] No hay jugadores para retirar.\n";
        return false;
    }

    int id;
    cout << "\nIngrese ID a retirar: ";
    while (!(cin >> id)) {
        cout << "[!] Ingrese un numero valido: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    for (int i = 0; i < lista->tamano; i++) {
        Jugador* ptrJ = &lista->elementos[i];
        if (ptrJ->idJugador == id) {
            for (int j = i; j < lista->tamano - 1; j++) {
                Jugador* ptrActual = &lista->elementos[j];
                Jugador* ptrSiguiente = &lista->elementos[j + 1];
                *ptrActual = *ptrSiguiente;
            }
            lista->tamano--;
            cout << "\n[V] Jugador retirado correctamente.\n";
            return true;
        }
    }
    cout << "\n[X] No se encontro el ID.\n";
    return false;
}

void mostrarJugadores(ListaJugadores *lista) {
    if(lista->tamano == 0) {
        cout << "\n[!] No existen jugadores registrados.\n";
        return;
    }

    cout << "\n=========================================================\n";
    cout << "                   LISTA DE JUGADORES                    \n";
    cout << "=========================================================\n";

    for(int i = 0; i < lista->tamano; i++) {
        cout << "  ID: " << lista->elementos[i].idJugador
             << " | Alias: " << lista->elementos[i].alias
             << " | Nombre: " << lista->elementos[i].nombre
             << " | Ranking: " << lista->elementos[i].ranking << " pts\n";
        cout << "---------------------------------------------------------\n";
    }
}

// FUNCION PARA GUARDAR JUGADORES EN EXCEL (.CSV)
void guardarJugadoresCSV(ListaJugadores *lista) {
    if (lista->tamano == 0) {
        cout << "\n[!] No hay jugadores para exportar a Excel.\n";
        return;
    }

    ofstream archivo("jugadores.csv");
    if (!archivo.is_open()) {
        cout << "\n[X] Error al crear el archivo Excel.\n";
        return;
    }

    archivo << "ID;Alias;Nombre;Ranking\n";
    for (int i = 0; i < lista->tamano; i++) {
        archivo << lista->elementos[i].idJugador << ";"
                << lista->elementos[i].alias << ";"
                << lista->elementos[i].nombre << ";"
                << lista->elementos[i].ranking << "\n";
    }

    archivo.close();
    cout << "\n[V] Jugadores exportados exitosamente a 'jugadores.csv'.\n";
}

//=====================================================
// MÓDULO COLA (PARTIDAS)
//=====================================================

bool colaVacia(ColaPartidas *cola) {
    return cola->final < cola->frente;
}

bool colaLlena(ColaPartidas *cola) {
    return cola->final == MAX - 1;
}

void encolarPartida(ColaPartidas *cola, Partida partida) {
    if(colaLlena(cola)) {
        cout << "\n[!] Error: Cola de partidas llena.\n";
        return;
    }

    cola->final++;
    cola->elementos[cola->final] = partida;
}

Partida desencolarPartida(ColaPartidas *cola) {
    Partida p;
    if(colaVacia(cola)) {
        cout << "\n[!] No hay partidas pendientes.\n";
        return p;
    }

    p = cola->elementos[cola->frente];
    cola->frente++;

    return p;
}

void mostrarPartidas(ColaPartidas *cola) {
    if(colaVacia(cola)) {
        cout << "\n[!] No existen partidas pendientes.\n";
        return;
    }

    cout << "\n=========================================================\n";
    cout << "                  PARTIDAS PENDIENTES                    \n";
    cout << "=========================================================\n";

    for(int i = cola->frente; i <= cola->final; i++) {
        cout << "  ID Partida     : #" << cola->elementos[i].idPartida << "\n";
        cout << "  Enfrentamiento : " << cola->elementos[i].jugador1.alias 
             << " VS " << cola->elementos[i].jugador2.alias << "\n";
        cout << "  Estado         : " << cola->elementos[i].estado << "\n";
        cout << "---------------------------------------------------------\n";
    }
}

void programarPartida(ColaPartidas *cola, ListaJugadores *lista) {
    if(lista->tamano < 2) {
        cout << "\n[!] Debe registrar al menos 2 jugadores para programar partidas.\n";
        return;
    }

    Partida partida;
    int id1, id2;

    cout << "\n>>> PROGRAMAR NUEVA PARTIDA <<<\n";
    
    cout << "ID Partida   : ";
    while (!(cin >> partida.idPartida)) {
        cout << "[!] Error: Ingrese un numero entero valido para ID Partida: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "ID Jugador 1 : ";
    while (!(cin >> id1)) {
        cout << "[!] Error: Ingrese un numero entero valido para ID Jugador 1: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "ID Jugador 2 : ";
    while (!(cin >> id2)) {
        cout << "[!] Error: Ingrese un numero entero valido para ID Jugador 2: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    int pos1 = buscarJugador(lista, id1);
    int pos2 = buscarJugador(lista, id2);

    if(pos1 == -1 || pos2 == -1) {
        cout << "\n[X] Error: Uno o ambos jugadores no existen.\n";
        return;
    }

    partida.jugador1 = lista->elementos[pos1];
    partida.jugador2 = lista->elementos[pos2];
    strcpy(partida.estado, "Pendiente");

    encolarPartida(cola, partida);
    cout << "\n[V] Partida programada correctamente.\n";
}

// FUNCION PARA GUARDAR PARTIDAS EN EXCEL (.CSV)
void guardarPartidasCSV(ColaPartidas *cola) {
    if (colaVacia(cola)) {
        cout << "\n[!] No hay partidas pendientes para exportar.\n";
        return;
    }

    ofstream archivo("partidas_pendientes.csv");
    if (!archivo.is_open()) {
        cout << "\n[X] Error al crear el archivo Excel.\n";
        return;
    }

    archivo << "ID Partida;Jugador 1;Jugador 2;Estado\n";
    for (int i = cola->frente; i <= cola->final; i++) {
        archivo << cola->elementos[i].idPartida << ";"
                << cola->elementos[i].jugador1.alias << ";"
                << cola->elementos[i].jugador2.alias << ";"
                << cola->elementos[i].estado << "\n";
    }

    archivo.close();
    cout << "\n[V] Partidas pendientes exportadas exitosamente a 'partidas_pendientes.csv'.\n";
}

//=====================================================
// MÓDULO PILA (HISTORIAL)
//=====================================================

bool pilaVacia(PilaHistorial *pila) {
    return pila->tope == -1;
}

void pushResultado(PilaHistorial *pila, Resultado resultado) {
    if(pila->tope == MAX - 1) {
        cout << "\n[!] Error: Historial lleno.\n";
        return;
    }

    pila->tope++;
    pila->elementos[pila->tope] = resultado;
}

void mostrarHistorial(PilaHistorial *pila) {
    if(pilaVacia(pila)) {
        cout << "\n[!] No existen resultados registrados en el historial.\n";
        return;
    }

    cout << "\n=========================================================\n";
    cout << "                 HISTORIAL DE RESULTADOS                 \n";
    cout << "=========================================================\n";

    for(int i = pila->tope; i >= 0; i--) {
        cout << "  Partida ID  : #" << pila->elementos[i].idPartida << "\n";
        cout << "  ID Ganador  : " << pila->elementos[i].idGanador << "\n";
        cout << "  Puntajes    : J1 [" << pila->elementos[i].puntajeJ1 
             << "] - J2 [" << pila->elementos[i].puntajeJ2 << "]\n";
        cout << "---------------------------------------------------------\n";
    }
}

void registrarResultado(ColaPartidas *cola, PilaHistorial *historial) {
    if(colaVacia(cola)) {
        cout << "\n[!] No existen partidas pendientes para procesar.\n";
        return;
    }

    Partida actual = desencolarPartida(cola);
    Resultado resultado;

    resultado.idPartida = actual.idPartida;

    cout << "\n>>> REGISTRANDO RESULTADO <<<\n";
    cout << "Partida #" << actual.idPartida << ": " 
         << actual.jugador1.alias << " VS " << actual.jugador2.alias << "\n\n";

    cout << "Puntaje " << actual.jugador1.alias << " (J1): ";
    while (!(cin >> resultado.puntajeJ1)) {
        cout << "[!] Ingrese un numero valido para el puntaje: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Puntaje " << actual.jugador2.alias << " (J2): ";
    while (!(cin >> resultado.puntajeJ2)) {
        cout << "[!] Ingrese un numero valido para el puntaje: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    if(resultado.puntajeJ1 > resultado.puntajeJ2) {
        resultado.idGanador = actual.jugador1.idJugador;
    } else {
        resultado.idGanador = actual.jugador2.idJugador;
    }

    pushResultado(historial, resultado);
    cout << "\n[V] Resultado registrado correctamente.\n";
}

// FUNCION PARA GUARDAR HISTORIAL EN EXCEL (.CSV)
void guardarHistorialCSV(PilaHistorial *pila) {
    if (pilaVacia(pila)) {
        cout << "\n[!] No hay resultados en el historial para exportar.\n";
        return;
    }

    ofstream archivo("historial_resultados.csv");
    if (!archivo.is_open()) {
        cout << "\n[X] Error al crear el archivo Excel.\n";
        return;
    }

    archivo << "ID Partida;ID Ganador;Puntaje J1;Puntaje J2\n";
    for (int i = pila->tope; i >= 0; i--) {
        archivo << pila->elementos[i].idPartida << ";"
                << pila->elementos[i].idGanador << ";"
                << pila->elementos[i].puntajeJ1 << ";"
                << pila->elementos[i].puntajeJ2 << "\n";
    }

    archivo.close();
    cout << "\n[V] Historial exportado exitosamente a 'historial_resultados.csv'.\n";
}

//=====================================================
// REPORTE GENERAL
//=====================================================

void reporteGeneral(ListaJugadores *lista, ColaPartidas *cola, PilaHistorial *historial) {
    int pendientes = 0;
    if(!colaVacia(cola)) {
        pendientes = cola->final - cola->frente + 1;
    }

    cout << "\n+---------------------------------------+";
    cout << "\n|           REPORTE GENERAL             |";
    cout << "\n+---------------------------------------+";
    cout << "\n  Jugadores Registrados : " << lista->tamano;
    cout << "\n  Partidas Pendientes   : " << pendientes;
    cout << "\n  Resultados en Pila    : " << historial->tope + 1;
    cout << "\n+---------------------------------------+\n";
}

//=====================================================
// SUBMENÚS CON PROTECCIÓN Y EXPORTACIÓN A EXCEL
//=====================================================

void subMenuJugadores(ListaJugadores *jugadores) {
    int subOpcion;
    do {
        cout << "\n=========================================\n";
        cout << "      GESTION DE JUGADORES (LISTAS)      \n";
        cout << "=========================================\n";
        cout << "  [1] Registrar jugador\n";
        cout << "  [2] Buscar jugador por ID\n";
        cout << "  [3] Actualizar jugador\n";
        cout << "  [4] Retirar jugador\n";
        cout << "  [5] Mostrar todos los jugadores\n";
        cout << "  [6] Exportar lista a Excel (.csv)\n";
        cout << "  [7] Volver al menu principal\n";
        cout << "-----------------------------------------\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> subOpcion)) {
            cout << "\n[!] Error: Ingrese solo numeros.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            subOpcion = 0;
            continue;
        }

        switch(subOpcion) {
            case 1: registrarJugador(jugadores); break;
            case 2: buscarJugadorUI(jugadores); break;
            case 3: actualizarJugador(jugadores); break;
            case 4: retirarJugador(jugadores); break;
            case 5: mostrarJugadores(jugadores); break;
            case 6: guardarJugadoresCSV(jugadores); break;
            case 7: cout << "\nRegresando al menu principal...\n"; break;
            default: cout << "\n[!] Opcion invalida.\n";
        }
    } while(subOpcion != 7);
}

void subMenuPartidas(ColaPartidas *partidas, ListaJugadores *jugadores) {
    int subOpcion;
    do {
        cout << "\n=========================================\n";
        cout << "       GESTION DE PARTIDAS (COLAS)       \n";
        cout << "=========================================\n";
        cout << "  [1] Programar partida\n";
        cout << "  [2] Mostrar partidas pendientes\n";
        cout << "  [3] Exportar partidas a Excel (.csv)\n";
        cout << "  [4] Volver al menu principal\n";
        cout << "-----------------------------------------\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> subOpcion)) {
            cout << "\n[!] Error: Ingrese solo numeros.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            subOpcion = 0;
            continue;
        }

        switch(subOpcion) {
            case 1: programarPartida(partidas, jugadores); break;
            case 2: mostrarPartidas(partidas); break;
            case 3: guardarPartidasCSV(partidas); break;
            case 4: cout << "\nRegresando al menu principal...\n"; break;
            default: cout << "\n[!] Opcion invalida.\n";
        }
    } while(subOpcion != 4);
}

void subMenuHistorial(PilaHistorial *historial, ColaPartidas *partidas) {
    int subOpcion;
    do {
        cout << "\n=========================================\n";
        cout << "     HISTORIAL DE RESULTADOS (PILAS)     \n";
        cout << "=========================================\n";
        cout << "  [1] Registrar resultado de partida\n";
        cout << "  [2] Ver historial de resultados\n";
        cout << "  [3] Exportar historial a Excel (.csv)\n";
        cout << "  [4] Volver al menu principal\n";
        cout << "-----------------------------------------\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> subOpcion)) {
            cout << "\n[!] Error: Ingrese solo numeros.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            subOpcion = 0;
            continue;
        }

        switch(subOpcion) {
            case 1: registrarResultado(partidas, historial); break;
            case 2: mostrarHistorial(historial); break;
            case 3: guardarHistorialCSV(historial); break;
            case 4: cout << "\nRegresando al menu principal...\n"; break;
            default: cout << "\n[!] Opcion invalida.\n";
        }
    } while(subOpcion != 4);
}

//=====================================================
// MAIN (MENÚ PRINCIPAL)
//=====================================================

int main() {
    ListaJugadores jugadores;
    ColaPartidas partidas;
    PilaHistorial historial;

    inicializarLista(&jugadores);
    inicializarCola(&partidas);
    inicializarPila(&historial);

    int opcion;

    do {
        cout << "\n=========================================\n";
        cout << "         SISTEMA TORNEO E-SPORTS         \n";
        cout << "=========================================\n";
        cout << "  [1] Modulo de Jugadores (Lista)\n";
        cout << "  [2] Modulo de Partidas (Cola)\n";
        cout << "  [3] Modulo de Historial (Pila)\n";
        cout << "  [4] Reporte general del sistema\n";
        cout << "  [5] Salir\n";
        cout << "-----------------------------------------\n";
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion)) {
            cout << "\n[!] Error: Ingrese solo numeros.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            opcion = 0;
            continue;
        }

        switch(opcion) {
            case 1: subMenuJugadores(&jugadores); break;
            case 2: subMenuPartidas(&partidas, &jugadores); break;
            case 3: subMenuHistorial(&historial, &partidas); break;
            case 4: reporteGeneral(&jugadores, &partidas, &historial); break;
            case 5:
                cout << "\n=========================================\n";
                cout << "   Gracias por utilizar el sistema.\n";
                cout << "=========================================\n\n";
                break;
            default:
                cout << "\n[!] Opcion invalida.\n";
        }

    } while(opcion != 5);

    return 0;
}
