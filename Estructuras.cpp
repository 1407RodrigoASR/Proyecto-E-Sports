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

void mostrarJugadores(ListaJugadores 
