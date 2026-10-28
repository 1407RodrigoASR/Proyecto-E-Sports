#include <iostream>
#include <cstring>

#define MAX 50

using namespace std;

//=====================================================
// ESTRUCTURAS
//=====================================================

// Estructura para almacenar información de un jugador
struct Jugador {
    int idJugador;
    char alias[30];
    char nombre[50];
    int ranking;
};

// Estructura para almacenar una partida
struct Partida {
    int idPartida;
    Jugador jugador1;
    Jugador jugador2;
    char estado[20];
};

// Estructura para almacenar resultados
struct Resultado {
    int idPartida;
    int idGanador;
    int puntajeJ1;
    int puntajeJ2;
};

// Lista estática de jugadores
struct ListaJugadores {
    Jugador elementos[MAX];
    int tamano;
};

// Cola FIFO de partidas pendientes
struct ColaPartidas {
    Partida elementos[MAX];
    int frente;
    int final;
};

// Pila LIFO para historial de resultados
struct PilaHistorial {
    Resultado elementos[MAX];
    int tope;
};

//=====================================================
// INICIALIZACIÓN
//=====================================================

// Inicializa la lista de jugadores
void inicializarLista(ListaJugadores *lista) {
    lista->tamano = 0;
}

// Inicializa la cola
void inicializarCola(ColaPartidas *cola) {
    cola->frente = 0;
    cola->final = -1;
}

// Inicializa la pila
void inicializarPila(PilaHistorial *pila) {
    pila->tope = -1;
}

// Busca un jugador por ID
int buscarJugador(ListaJugadores *lista, int id) {

    for(int i = 0; i < lista->tamano; i++) {

        if(lista->elementos[i].idJugador == id) {
            return i;
        }
    }

    return -1;
}

// Registra un nuevo jugador
void registrarJugador(ListaJugadores *lista) {

    if(lista->tamano >= MAX) {
        cout << "\nLista llena.\n";
        return;
    }

    Jugador nuevo;

    cout << "\nID del jugador: ";
    cin >> nuevo.idJugador;

    // Validar ID repetido
    if(buscarJugador(lista, nuevo.idJugador) != -1) {
        cout << "El ID ya existe.\n";
        return;
    }

    cin.ignore();

    cout << "Alias: ";
    cin.getline(nuevo.alias, 30);

    cout << "Nombre completo: ";
    cin.getline(nuevo.nombre, 50);

    cout << "Ranking: ";
    cin >> nuevo.ranking;

    lista->elementos[lista->tamano] = nuevo;
    lista->tamano++;

    cout << "\nJugador registrado correctamente.\n";
}

void actualizarJugador(ListaJugadores* lista) {
    if (lista->tamano == 0) {
        cout << "\n--- No hay jugadores para actualizar. ---\n";
        return;
    }

    int id;
    cout << "\nIngrese el ID del jugador a actualizar: ";
    cin >> id;

    for (int i = 0; i < lista->tamano; i++) {
        Jugador* ptrJ = &lista->elementos[i];
        if (ptrJ->idJugador == id) {
            cout << "\n--- Ingrese los nuevos datos ---" << endl;
            cin.ignore();
            cout << "Nuevo Alias: ";
            cin.getline(ptrJ->alias, 30);

            cout << "Nuevo Nombre: ";
            cin.getline(ptrJ->nombre, 50);

            cout << "Nuevo Ranking: ";
            cin >> ptrJ->ranking;

            cout << ">> Jugador actualizado con exito.\n";
            return;
        }
    }
    cout << ">> No se encontro un jugador con ese ID.\n";
}

bool retirarJugador(ListaJugadores* lista) {
    if (lista->tamano == 0) {
        cout << "\n--- No hay jugadores para retirar. ---\n";
        return false;
    }

    int id;
    cout << "\nIngrese ID a retirar: ";
    cin >> id;

    for (int i = 0; i < lista->tamano; i++) {
        Jugador* ptrJ = &lista->elementos[i];
        if (ptrJ->idJugador == id) {
            for (int j = i; j < lista->tamano - 1; j++) {
                Jugador* ptrActual = &lista->elementos[j];
                Jugador* ptrSiguiente = &lista->elementos[j + 1];
                *ptrActual = *ptrSiguiente;
            }
            lista->tamano--;
            cout << ">> Jugador retirado correctamente.\n";
            return true;
        }
    }
    cout << ">> No se encontro el ID.\n";
    return false;
}

// Mostrar todos los jugadores
void mostrarJugadores(ListaJugadores *lista) {

    if(lista->tamano == 0) {
        cout << "\nNo existen jugadores.\n";
        return;
    }

    cout << "\n===== LISTA DE JUGADORES =====\n";

    for(int i = 0; i < lista->tamano; i++) {

        cout << "\nID: "
             << lista->elementos[i].idJugador;

        cout << "\nAlias: "
             << lista->elementos[i].alias;

        cout << "\nNombre: "
             << lista->elementos[i].nombre;

        cout << "\nRanking: "
             << lista->elementos[i].ranking;

        cout << "\n------------------------------";
    }
}

//=====================================================
// FUNCIONES DE COLA (FIFO)
//=====================================================

// Verificar si la cola está vacía
bool colaVacia(ColaPartidas *cola) {
    return cola->final < cola->frente;
}

// Verificar si la cola está llena
bool colaLlena(ColaPartidas *cola) {
    return cola->final == MAX - 1;
}

// Agregar una partida a la cola
void encolarPartida(ColaPartidas *cola, Partida partida) {

    if(colaLlena(cola)) {
        cout << "\nCola llena.\n";
        return;
    }

    cola->final++;
    cola->elementos[cola->final] = partida;
}

// Sacar una partida de la cola
Partida desencolarPartida(ColaPartidas *cola) {

    Partida p;

    if(colaVacia(cola)) {
        cout << "\nNo hay partidas.\n";
        return p;
    }

    p = cola->elementos[cola->frente];
    cola->frente++;

    return p;
}

// Mostrar partidas pendientes
void mostrarPartidas(ColaPartidas *cola) {

    if(colaVacia(cola)) {
        cout << "\nNo existen partidas pendientes.\n";
        return;
    }

    cout << "\n===== PARTIDAS PENDIENTES =====\n";

    for(int i = cola->frente; i <= cola->final; i++) {

        cout << "\nID Partida: "
             << cola->elementos[i].idPartida;

        cout << "\nJugador 1: "
             << cola->elementos[i].jugador1.alias;

        cout << "\nJugador 2: "
             << cola->elementos[i].jugador2.alias;

        cout << "\nEstado: "
             << cola->elementos[i].estado;

        cout << "\n-----------------------------";
    }
}

//=====================================================
// FUNCIONES DE PILA (LIFO)
//=====================================================

// Verificar si la pila está vacía
bool pilaVacia(PilaHistorial *pila) {
    return pila->tope == -1;
}

// Insertar resultado en la pila
void pushResultado(PilaHistorial *pila, Resultado resultado) {

    if(pila->tope == MAX - 1) {
        cout << "\nHistorial lleno.\n";
        return;
    }

    pila->tope++;
    pila->elementos[pila->tope] = resultado;
}

// Mostrar historial
void mostrarHistorial(PilaHistorial *pila) {

    if(pilaVacia(pila)) {
        cout << "\nNo existen resultados.\n";
        return;
    }

    cout << "\n===== HISTORIAL DE RESULTADOS =====\n";

    for(int i = pila->tope; i >= 0; i--) {

        cout << "\nPartida: "
             << pila->elementos[i].idPartida;

        cout << "\nGanador ID: "
             << pila->elementos[i].idGanador;

        cout << "\nPuntaje J1: "
             << pila->elementos[i].puntajeJ1;

        cout << "\nPuntaje J2: "
             << pila->elementos[i].puntajeJ2;

        cout << "\n---------------------------";
    }
}

//=====================================================
// PROGRAMAR PARTIDA
//=====================================================

void programarPartida(
        ColaPartidas *cola,
        ListaJugadores *lista) {

    if(lista->tamano < 2) {

        cout << "\nDebe registrar al menos 2 jugadores.\n";
        return;
    }

    Partida partida;

    int id1;
    int id2;

    cout << "\nID Partida: ";
    cin >> partida.idPartida;

    cout << "ID Jugador 1: ";
    cin >> id1;

    cout << "ID Jugador 2: ";
    cin >> id2;

    int pos1 = buscarJugador(lista,id1);
    int pos2 = buscarJugador(lista,id2);

    if(pos1 == -1 || pos2 == -1) {

        cout << "\nJugador no encontrado.\n";
        return;
    }

    partida.jugador1 = lista->elementos[pos1];
    partida.jugador2 = lista->elementos[pos2];

    strcpy(partida.estado,"Pendiente");

    encolarPartida(cola, partida);

    cout << "\nPartida programada correctamente.\n";
}

//=====================================================
// REGISTRAR RESULTADO
//=====================================================

void registrarResultado(
        ColaPartidas *cola,
        PilaHistorial *historial) {

    if(colaVacia(cola)) {

        cout << "\nNo existen partidas pendientes.\n";
        return;
    }

    Partida actual;

    actual = desencolarPartida(cola);

    Resultado resultado;

    resultado.idPartida = actual.idPartida;

    cout << "\nPartida "
         << actual.idPartida;

    cout << "\n"
         << actual.jugador1.alias
         << " VS "
         << actual.jugador2.alias;

    cout << "\n\nPuntaje Jugador 1: ";
    cin >> resultado.puntajeJ1;

    cout << "Puntaje Jugador 2: ";
    cin >> resultado.puntajeJ2;

    if(resultado.puntajeJ1 > resultado.puntajeJ2) {

        resultado.idGanador =
        actual.jugador1.idJugador;

    } else {

        resultado.idGanador =
        actual.jugador2.idJugador;
    }

    pushResultado(historial, resultado);

    cout << "\nResultado registrado correctamente.\n";
}

//=====================================================
// REPORTE GENERAL
//=====================================================

void reporteGeneral(
        ListaJugadores *lista,
        ColaPartidas *cola,
        PilaHistorial *historial) {

    cout << "\n===== REPORTE GENERAL =====";

    cout << "\nJugadores: "
         << lista->tamano;

    int pendientes = 0;

    if(!colaVacia(cola)) {

        pendientes =
        cola->final - cola->frente + 1;
    }

    cout << "\nPartidas pendientes: "
         << pendientes;

    cout << "\nResultados registrados: "
         << historial->tope + 1;

    cout << "\n==========================";
}

//=====================================================
// MAIN
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

        cout << "\n\n========== TORNEO E-SPORTS ==========";
        cout << "\n1. Registrar jugador";
        cout << "\n2. Mostrar jugadores";
        cout << "\n3. Programar partida";
        cout << "\n4. Mostrar partidas";
        cout << "\n5. Registrar resultado";
        cout << "\n6. Ver historial";
        cout << "\n7. Reporte general";
        cout << "\n8. Salir";
        cout << "\nSeleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {

            case 1:
                registrarJugador(&jugadores);
                break;

            case 2:
                mostrarJugadores(&jugadores);
                break;

            case 3:
                programarPartida(&partidas,&jugadores);
                break;

            case 4:
                mostrarPartidas(&partidas);
                break;

            case 5:
                registrarResultado(&partidas,&historial);
                break;

            case 6:
                mostrarHistorial(&historial);
                break;

            case 7:
                reporteGeneral(&jugadores,&partidas,&historial);
                break;

            case 8:
                cout << "\nGracias por utilizar el sistema.\n";
                break;

            default:
                cout << "\nOpcion incorrecta.\n";
        }

    }while(opcion != 8);

    return 0;
}
