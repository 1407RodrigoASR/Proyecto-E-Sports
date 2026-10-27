#include <iostream>
#include <cstring>
#define MAX 50

using namespace std;

// --- STRUCTS ---
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
