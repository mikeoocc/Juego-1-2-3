
/*
 * Este proyecto está escrito por Miguel Oliver.
 * Universidad: Antonio de Nebrija
*/

#include <iostream>
#include"header.h"
#include<vector>
#include<string>

#include<algorithm> //Esta libreria la he utilizado para mezclar aleatoriamente las cartas.

#include <conio.h> //Tanto conio.h como stdlib son dos librerias que he utilizado para limpiar la terminal cada vez que ejecuto una parte del programa,
#include <stdlib.h> // de modo que quede más limpio.

#include <ctime> // ctime y cstdlib sirven en este caso para generar un numero aleatorio
#include <cstdlib>

#include <iomanip> //para setw(), de modo que los jugadores salgan en una línea ordenada.

#include <fstream> // para ir guardando puntuaciones en fichero de texto

#include<unistd.h> // para sleep(). Retrasa la salida del codigo al mostrarse por pantalla

//NOTAS: Para quitar tiempos comentar 'sleep()'. En el header las dos primeras lineas (ifndef, define) y la ultima (endif) creo que deberian borrarse cuando se pegue el codigo.
//Ultima actualizacion: He hecho paso por referencia constante en las funciones jugadorInactivo y comprobarCoincidencia

using namespace std;

int main()
{
    int numJ;
    srand(time(NULL));

    cout << "-- BIENVENIDO A AS23 --" << endl;
    cout<< "Pulsa 'enter' para continuar"<<endl;
    getch();
    system("cls");

    cout << "Introduce el numero de jugadores (2 a 4): ";
    cin >> numJ;

    if (numJ < 2 || numJ > 4) {
        cout << "El numero de jugadores debe estar entre 2 y 4." << endl;
        return 1;
    }
    cout<<endl;

    vector<Jugador>jugadores = CrearJugadores(numJ);
    cout << "Check Jugadores Creados: -----------------------------------------" << endl;

    for(int i=0; i<numJ; ++i){
        cout <<jugadores[i].nombre << " creado." <<endl;

    }
    cout<< endl;

    vector<Carta> baraja = GenerarCartas();
    cout << "Check Baraja Creada: -----------------------------------------" << endl;

    int contador = 0;
    for (int i = 0; i < baraja.size(); i++) {
      cout << baraja[i].palo << " " << baraja[i].valor << " ";
      contador++;
      if (contador % 10 == 0) {
        cout << endl;
      }
    }

    cout<<endl;
    barajar(baraja);
    cout<< endl;

    cout << "Check Baraja Mezclada: -----------------------------------------" << endl;
    for (int i = 0; i < baraja.size(); i++) {
      cout << baraja[i].palo << " " << baraja[i].valor << " ";
      contador++;
      if (contador % 10 == 0) {
        cout << endl;
      }
    }

    vector<vector<Carta>> manos = repartirCartas(numJ, baraja);
    for(int i=0; i<numJ; ++i){
        jugadores[i].mano = manos[i];
    }

    cout<<endl;

    cout << "Check manos de jugadores: -----------------------------------------" << endl;
    for (auto jugador_ : jugadores) {
      cout << "Mano de " << jugador_.nombre << ": " << endl;
      int contador = 0;
      for (auto carta_ : jugador_.mano) {
        cout << setw(2) << carta_.valor << " de " << carta_.palo << " ";
        contador++;
        if (contador % 5 == 0) {
          cout << endl;
        }
      }
      cout << endl;
    }

    cout << "Iniciar partida .............." << endl;

    getch();
    system("cls");




    char respuesta;

    do{

        system("cls");

        int turno = 1;
        int ronda = 1;
        int aux = 0;

        bool hayGanador = false;

        if(numJ == 2){
            aux=20;
        }
        else if(numJ==3){
            aux=13;
        }
        else if(numJ==4){
            aux=10;
        }

        for (auto& jugador : jugadores) {
                jugador.mano.clear();
            }

        vector<Carta> baraja = GenerarCartas();

        barajar(baraja);

        vector<vector<Carta>> manos = repartirCartas(numJ, baraja);

        for(int i=0; i<numJ; ++i){
            jugadores[i].mano = manos[i];
        }

        while(ronda<=aux && hayGanador==false){

            cout<<endl;

            sleep(1);
            cout<<"-----------------------"<<endl;
            cout<< "RONDA " << ronda << endl;

            jugarTurno(turno, numJ, jugadores, hayGanador);

            ronda++;

            if(ronda > aux){
                cout<<endl;

                cout<<"---------------------     EL JUEGO HA TERMINADO  ------------------------------ " <<  endl;
                cout<<"NINGUN JUGADOR HA GANADO. Todos se han quedado sin cartas, la partida finaliza.";
                cout<<endl;
                crearFichero(jugadores);
            }

            else if(hayGanador==true){
                crearFichero(jugadores);
            }

        }

      cout<<endl;
      cout<<"Desea jugar otra partida: (S/N) ";
      cin>>respuesta;
    } while (respuesta=='S');

    if(respuesta=='N'){
        exit(0);
    }

    cout<<endl;

    return 0;
}
