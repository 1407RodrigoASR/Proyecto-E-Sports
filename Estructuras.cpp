#include <iostream>
#include <cstring>

#define MAX 50

using namespace std;

//------------------ STRUCTS ------------------

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

//------------------ INICIALIZAR ------------------

void inicializarLista(ListaJugadores &lista) {
    lista.tamano = 0;
}

void inicializarCola(ColaPartidas &cola) {
    cola.frente = 0;
    cola.final = -1;
}

void inicializarPila(PilaHistorial &pila) {
    pila.tope = -1;
}

//------------------ JUGADORES ------------------

void registrarJugador(ListaJugadores &lista) {
    if (lista.tamano >= MAX) {
        cout << "\nLista llena.\n";
        return;
    }

    Jugador j;

    cout << "\nID Jugador: ";
    cin >> j.idJugador;

    for(int i=0;i<lista.tamano;i++) {
        if(lista.elementos[i].idJugador == j.idJugador) {
            cout << "ID ya existe.\n";
            return;
        }
    }

    cin.ignore();

    cout << "Alias: ";
    cin.getline(j.alias,30);

    cout << "Nombre: ";
    cin.getline(j.nombre,50);

    cout << "Ranking: ";
    cin >> j.ranking;

    lista.elementos[lista.tamano++] = j;

    cout << "\nJugador registrado correctamente.\n";
}

void mostrarJugadores(ListaJugadores lista) {

    if(lista.tamano == 0){
        cout << "\nNo existen jugadores.\n";
        return;
    }

    cout << "\n===== JUGADORES =====\n";

    for(int i=0;i<lista.tamano;i++) {
        cout << "\nID: " << lista.elementos[i].idJugador;
        cout << "\nAlias: " << lista.elementos[i].alias;
        cout << "\nNombre: " << lista.elementos[i].nombre;
        cout << "\nRanking: " << lista.elementos[i].ranking;
        cout << "\n-------------------";
    }
}

int buscarJugador(ListaJugadores lista, int id) {

    for(int i=0;i<lista.tamano;i++) {
        if(lista.elementos[i].idJugador == id)
            return i;
    }

    return -1;
}

//------------------ COLA ------------------

bool colaVacia(ColaPartidas cola) {
    return cola.final < cola.frente;
}

bool colaLlena(ColaPartidas cola) {
    return cola.final == MAX - 1;
}

void encolarPartida(ColaPartidas &cola, Partida p) {

    if(colaLlena(cola)) {
        cout << "\nCola llena.\n";
        return;
    }

    cola.elementos[++cola.final] = p;
}

Partida desencolarPartida(ColaPartidas &cola) {
    return cola.elementos[cola.frente++];
}

void mostrarPartidas(ColaPartidas cola) {

    if(colaVacia(cola)) {
        cout << "\nNo hay partidas pendientes.\n";
        return;
    }

    cout << "\n===== PARTIDAS PENDIENTES =====\n";

    for(int i=cola.frente;i<=cola.final;i++) {

        cout << "\nPartida: "
             << cola.elementos[i].idPartida;

        cout << "\nJugador 1: "
             << cola.elementos[i].jugador1.alias;

        cout << "\nJugador 2: "
             << cola.elementos[i].jugador2.alias;

        cout << "\nEstado: "
             << cola.elementos[i].estado;

        cout << "\n--------------------";
    }
}

//------------------ PILA ------------------

bool pilaVacia(PilaHistorial pila) {
    return pila.tope == -1;
}

bool pilaLlena(PilaHistorial pila) {
    return pila.tope == MAX - 1;
}

void pushResultado(PilaHistorial &pila, Resultado r) {

    if(pilaLlena(pila)) {
        cout << "\nHistorial lleno.\n";
        return;
    }

    pila.elementos[++pila.tope] = r;
}

void mostrarHistorial(PilaHistorial pila) {

    if(pilaVacia(pila)) {
        cout << "\nNo existen resultados.\n";
        return;
    }

    cout << "\n===== HISTORIAL =====\n";

    for(int i=pila.tope;i>=0;i--) {

        cout << "\nPartida: "
             << pila.elementos[i].idPartida;

        cout << "\nGanador ID: "
             << pila.elementos[i].idGanador;

        cout << "\nPuntaje J1: "
             << pila.elementos[i].puntajeJ1;

        cout << "\nPuntaje J2: "
             << pila.elementos[i].puntajeJ2;

        cout << "\n-------------------";
    }
}

//------------------ PARTIDAS ------------------

void programarPartida(
        ColaPartidas &cola,
        ListaJugadores lista) {

    if(lista.tamano < 2) {
        cout << "\nSe necesitan minimo 2 jugadores.\n";
        return;
    }

    Partida p;
    int id1,id2;

    cout << "\nID Partida: ";
    cin >> p.idPartida;

    cout << "ID Jugador 1: ";
    cin >> id1;

    cout << "ID Jugador 2: ";
    cin >> id2;

    int pos1 = buscarJugador(lista,id1);
    int pos2 = buscarJugador(lista,id2);

    if(pos1==-1 || pos2==-1) {
        cout << "\nJugador no encontrado.\n";
        return;
    }

    p.jugador1 = lista.elementos[pos1];
    p.jugador2 = lista.elementos[pos2];

    strcpy(p.estado,"Pendiente");

    encolarPartida(cola,p);

    cout << "\nPartida programada correctamente.\n";
}

//------------------ RESULTADOS ------------------

void registrarResultado(
        ColaPartidas &cola,
        PilaHistorial &historial) {

    if(colaVacia(cola)) {
        cout << "\nNo existen partidas.\n";
        return;
    }

    Partida partidaActual;

    partidaActual = desencolarPartida(cola);

    Resultado r;

    r.idPartida = partidaActual.idPartida;

    cout << "\nPartida "
         << partidaActual.idPartida;

    cout << "\n"
         << partidaActual.jugador1.alias
         << " vs "
         << partidaActual.jugador2.alias;

    cout << "\nPuntaje Jugador 1: ";
    cin >> r.puntajeJ1;

    cout << "Puntaje Jugador 2: ";
    cin >> r.puntajeJ2;

    if(r.puntajeJ1 > r.puntajeJ2)
        r.idGanador = partidaActual.jugador1.idJugador;
    else
        r.idGanador = partidaActual.jugador2.idJugador;

    pushResultado(historial,r);

    cout << "\nResultado registrado.\n";
}

//------------------ REPORTES ------------------

void reporteGeneral(
        ListaJugadores lista,
        ColaPartidas cola,
        PilaHistorial historial) {

    cout << "\n===== REPORTE GENERAL =====";

    cout << "\nJugadores registrados: "
         << lista.tamano;

    int pendientes = 0;

    if(!colaVacia(cola))
        pendientes =
            cola.final - cola.frente + 1;

    cout << "\nPartidas pendientes: "
         << pendientes;

    cout << "\nResultados almacenados: "
         << historial.tope + 1;

    cout << "\n==========================";
}

//------------------ MAIN ------------------

int main() {

    ListaJugadores jugadores;
    ColaPartidas partidas;
    PilaHistorial historial;

    inicializarLista(jugadores);
    inicializarCola(partidas);
    inicializarPila(historial);

    int opcion;

    do {

        cout << "\n\n===== TORNEO E-SPORTS =====";
        cout << "\n1. Registrar jugador";
        cout << "\n2. Mostrar jugadores";
        cout << "\n3. Programar partida";
        cout << "\n4. Mostrar partidas";
        cout << "\n5. Registrar resultado";
        cout << "\n6. Ver historial";
        cout << "\n7. Reporte general";
        cout << "\n8. Salir";

        cout << "\nSeleccione: ";
        cin >> opcion;

        switch(opcion) {

            case 1:
                registrarJugador(jugadores);
                break;

            case 2:
                mostrarJugadores(jugadores);
                break;

            case 3:
                programarPartida(partidas,jugadores);
                break;

            case 4:
                mostrarPartidas(partidas);
                break;

            case 5:
                registrarResultado(partidas,historial);
                break;

            case 6:
                mostrarHistorial(historial);
                break;

            case 7:
                reporteGeneral(
                    jugadores,
                    partidas,
                    historial
                );
                break;

            case 8:
                cout << "\nGracias por usar el sistema.\n";
                break;

            default:
                cout << "\nOpcion invalida.\n";
        }

    } while(opcion != 8);

    return 0;
}
