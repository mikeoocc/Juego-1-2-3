#include <iostream>
#include"header.h"
#include<vector>
#include<string>
#include<algorithm>
#include <ctime>
#include <cstdlib>
#include<fstream>
#include<unistd.h>

using namespace std;



vector<Jugador>CrearJugadores(int numjugadores){

    vector<Jugador>jugadores;

    for (int i = 1; i <= numjugadores; i++) {
        jugadores.push_back( {false, "Jugador" + to_string(i) , {}, 0, false, {}, 0});
    }

    return jugadores;
}

vector<Carta>GenerarCartas(){

    vector<Carta> baraja;
      string palos[] = {"Oros", "Copas", "Espadas", "Bastos"};
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 12; j++) {
          if (j == 7 || j == 8) continue;
          Carta c;
          c.palo = palos[i];
          c.valor = j + 1;
          c.id_carta = c.palo + to_string(c.valor);
          baraja.push_back(c);
        }
      }


      return baraja;

}

void barajar(vector<Carta> &baraja) {
  random_shuffle(baraja.begin(), baraja.end());
}

vector<vector<Carta>>repartirCartas(int numJ, vector<Carta> &baraja){

    srand(time(nullptr));

    random_shuffle(baraja.begin(), baraja.end());

    vector<vector<Carta>> manos(numJ);
      int numCartasPorJugador = 40 / numJ;

      for (int i = 0; i < numJ; i++) {
        for (int j = 0; j < numCartasPorJugador; j++) {
          manos[i].push_back(baraja[i * numCartasPorJugador + j]);
        }

      }

      return manos;

}

void ponerCarta(Jugador& jugador) {


  if (jugador.mano.empty()) return;

  Carta carta = jugador.mano[0];

  jugador.mano.erase(jugador.mano.begin());

  cout << jugador.nombre << " ha puesto la carta [" << carta.valor << "]. Le quedan (" << jugador.mano.size() << ") cartas."  << endl;

  jugador.cartaActual = carta;


}

void cantarTurno(Jugador& jugador, int turno) {

  int numeroTurno = turno;

  // Imprimime el valor del turno que se ha cantado
  cout << jugador.nombre << " ha cantado  [" << numeroTurno << "]"  << endl;

  jugador.valorCantado = numeroTurno;

}

bool comprobarCoincidencia(const Jugador&jugador){
    if(jugador.cartaActual.valor == jugador.valorCantado){
        return true;
    }
    else{
        return false;
    }
}

bool jugadorInactivo(const Jugador&jugador){

    if(jugador.mano.empty()){
        return true;
    }
    else{
        return false;
    }

}

bool jugarTurno(int& turno, int numJ, vector<Jugador>& jugadores, bool& hayGanador){

    for(auto &jugador:jugadores){

        if(!jugadorInactivo(jugador)){

            cout<<endl;
            sleep(2);
            ponerCarta(jugador);
            sleep(2);
            cantarTurno(jugador, turno);

            cout<<endl;
            turno++;

            if(turno==8){
                turno++;
            }

            if(turno==9){
                turno++;
            }

            if(turno==13){
                turno=1;
            }

            if(comprobarCoincidencia(jugador)==true){

                cout<<endl;
                sleep(2);
                cout<<"*****************************************************"<< endl;
                cout<<"El " << jugador.nombre << " ha coincidido! " << endl;
                cout<<"*****************************************************"<< endl;
                cout<<endl;

                for (int i = turno + 1; i < turno + numJ; i++) {

                  if (i % numJ == turno) {
                    continue;
                  }
                  int siguienteJug = i % numJ;  // Siguiente jugador
                  int probability;

                  probability = 30; //Probabilidad de que el siguiente ponga carta

                  if (i > turno + 1) {
                    probability = probability - (probability * 0.1) ;

                  }

                  if (rand() % 100 < probability) {

                    // Si el numero es menor, uno de los siguientes pone carta
                    sleep(2);
                    ponerCarta(jugadores[siguienteJug]);
                    cout<<endl;

                    sleep(1);
                    cout<<"Uno de los siguientes jugadores ha puesto carta despues de una coincidencia! ";

                    sleep(1);
                    cout<<"Se lleva todas las cartas del " <<jugador.nombre << "." << endl;
                    cout<<endl;

                    cout<<"---------------------     EL JUEGO HA TERMINADO  ------------------------------ " << endl;
                    cout<<endl;

                    cout<<"El ganador es " << jugador.nombre << endl;
                    jugador.victorias++;
                    cout<<endl;

                    hayGanador = true;

                    break;
                  }
                }
                if(hayGanador==false){

                    sleep(2);
                    cout<<"Nadie ha puesto carta. Se sigue jugando.";
                    cout<<endl;
                    continue;

                }


                  }

            }

        else{

            cout<<endl;
            cout<<"El " << jugador.nombre << " se ha quedado sin cartas ";

        }

        if(hayGanador==true){
            return hayGanador;
            break;
        }

    }

    return hayGanador;

}

void crearFichero(vector<Jugador>& jugadores){

    ofstream outFile;

    outFile.open("puntuaciones.txt", ios::app);


    outFile<<" PUNTUACIONES " <<endl;
    outFile<<" ------------ ";
    outFile<<endl;


    for(auto &jugador:jugadores){
        outFile << "El jugador " << jugador.nombre << " tiene " << jugador.victorias << " puntos " << endl;
    }

    outFile<<endl;

    // close the file
    outFile.close();

}


