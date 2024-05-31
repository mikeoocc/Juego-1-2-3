#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include<vector>
#include<string>

using namespace std;

struct Carta
{

    string palo;
    int valor;
    string id_carta;

};

struct Jugador
{
    bool jugadorActual;
    string nombre;
    vector<Carta>mano;
    int victorias;
    bool jugadorInactivo;
    Carta cartaActual;
    int valorCantado;

};

//Base

vector<Jugador>CrearJugadores(int numj);
vector<Carta>GenerarCartas();
void barajar(vector<Carta> &baraja);
vector<vector<Carta>>repartirCartas(int numJ, vector<Carta> &baraja);

//Dinámica

void ponerCarta(Jugador& jugador);
void cantarTurno(Jugador& jugador, int turno);
bool comprobarCoincidencia(const Jugador&jugador);
bool jugadorInactivo(const Jugador&jugador);
bool jugarTurno(int& turno, int numJ, vector<Jugador>& jugadores, bool& hayGanador);

//Fichero Puntuaciones

void crearFichero(vector<Jugador>& jugadores);


#endif // HEADER_H
