#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>
#include <algorithm>

using namespace std;

// Clase para representar un país
class Pais {
public:
    string continente;
    string nombre;
    int identificador;
    int cantidadInfanteria;
    int estado;

    Pais(string cont, string nom, int id, int inf, int est)
        : continente(cont), nombre(nom), identificador(id), cantidadInfanteria(inf), estado(est) {}
};

// Clase para representar una Tarjeta
class Tarjeta {
public:
    int identificador;
    string tipo;
    string territorio;
    string simbolo;

    Tarjeta(int id, string tip, string terr, string sim) 
        : identificador(id), tipo(tip), territorio(terr), simbolo(sim) {}
};

// Clase para representar un jugador
class Jugador {
public:
    string nombre;
    string color;
    int turno;
    vector<Pais> paises;
    vector<Tarjeta> Tarjetas;
    int cantidadTropas;

    Jugador(string nom, string col, int turn, int cantTropas)
        : nombre(nom), color(col), turno(turn), cantidadTropas(cantTropas) {}
};

// Función para leer los Paises del txt
vector<Pais> leerPaisesDesdeArchivo(const string& nombreArchivo) {
    vector<Pais> paises;
    ifstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            istringstream ss(linea);
            string continente, nombre;
            int id;

            getline(ss, continente, ';');
            getline(ss, nombre, ';');
            ss >> id;
        

            paises.push_back(Pais(continente, nombre, id, 0, 0));

        }

        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo." << endl;
    }

    return paises;
}

// Función para imprimir los Paises
void imprimirPaises(const vector<Pais>& paises) {
    // Organizar los países por continente
    map<string, vector<Pais>> paisesPorContinente;
    for (const Pais& pais : paises) {
        paisesPorContinente[pais.continente].push_back(pais);
    }

    cout << "------------------------------------------------" << endl;

    // Imprimir los países divididos por continente con estado 0
    for (const auto& par : paisesPorContinente) {
        cout << "Continente: " << par.first << endl;
        cout << "------------------------------------------------" << endl;

        for (const Pais& pais : par.second) {
            if (pais.estado == 0) {
                cout << "ID: " << pais.identificador << "\tNombre: " << pais.nombre << endl;
            }
        }

        cout << "------------------------------------------------" << endl;
    }
}

// Función para leer las Tarjetas del txt
vector<Tarjeta> leerTarjetasDesdeArchivo(const string& nombreArchivo) {
    vector<Tarjeta> tarjetas;
    ifstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            istringstream ss(linea);
            int id;
            string tipo, territorio, simbolo, identificador;

            getline(ss, identificador, ';');
            getline(ss, tipo, ';');
            getline(ss, territorio, ';');
            getline(ss, simbolo, ';');

            id = stoi(identificador);

            tarjetas.push_back(Tarjeta(id, tipo, territorio, simbolo));

        }

        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo." << endl;
    }

    return tarjetas;
}

// Función para imprimir las Tarjetas
void imprimirTarjetas(const vector<Tarjeta>& tarjetas) {
    // Organizar las tarjetas por tipo
    map<string, vector<Tarjeta>> tarjetasPorTipo;
    for (const Tarjeta& tarjeta : tarjetas) {
        tarjetasPorTipo[tarjeta.tipo].push_back(tarjeta);
    }

    cout << "------------------------------------------------" << endl;

    // Imprimir las tarjetas divididas por tipo
    for (const auto& par : tarjetasPorTipo) {
        cout << "Tipo: " << par.first << endl;
        cout << "------------------------------------------------" << endl;

        for (const Tarjeta& tarjeta : par.second) {
            cout << "ID: " << tarjeta.identificador << "\tTerritorio: " << tarjeta.territorio << "\tSimbolo: " << tarjeta.simbolo << endl;
        }

        cout << "------------------------------------------------" << endl;
    }
}

// Función para sortear los turnos de los jugadores
void sortearTurnos(vector<int>& turnos, int numJugadores) {
    // Llenar un vector con números del 1 al número de jugadores
    for (int i = 1; i <= numJugadores; i++) {
        turnos.push_back(i);
    }

    // Mezclar los números aleatoriamente
    random_shuffle(turnos.begin(), turnos.end());
}

// Funcion para retornar un string de paises de un jugador con sus tropas
string paisesJugador(vector<Pais>& paises) {
    string paisesJugador = "";
    for (Pais& pais : paises) {
        paisesJugador += ";" + pais.continente + ";" + pais.nombre + ";" + to_string(pais.identificador) + ";" + to_string(pais.cantidadInfanteria);
    }
    return paisesJugador;
}

// Funcion para Guardar informacion de los jugadores en un txt
void guardarJugadores(vector<Jugador>& jugadores) {
    ofstream archivo("Jugadores.txt");

    if (archivo.is_open()) {
        for (const Jugador& jugador : jugadores) {
            vector <Pais> paises = jugador.paises;
            archivo << jugador.nombre << ";" << jugador.color << ";" << jugador.turno << ";" << jugador.cantidadTropas << ";" << paises.size() << paisesJugador(paises) << endl;
        } 
        archivo.close();
}


}

// Funcion para leer la informacion de los jugadores desde un txt
vector<Jugador> leerJugadoresDesdeArchivo(const string& nombreArchivo) {
    vector<Jugador> jugadores;
    ifstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            istringstream ss(linea);
            string nombre, color, turno, cantidadTropas, cantidadPaises;
            vector<Pais> paises;

            getline(ss, nombre, ';');
            getline(ss, color, ';');
            getline(ss, turno, ';');
            getline(ss, cantidadTropas, ';');
            getline(ss, cantidadPaises, ';');

            int turn = stoi(turno);
            int cantTropas = stoi(cantidadTropas);
            int cantPaises = stoi(cantidadPaises);

            for (int i = 0; i < cantPaises; i++) {
                string continente, nombrePais, identificador, cantidadInfanteria;
                getline(ss, continente, ';');
                getline(ss, nombrePais, ';');
                getline(ss, identificador, ';');
                getline(ss, cantidadInfanteria, ';');

                int id = stoi(identificador);
                int cantInfanteria = stoi(cantidadInfanteria);

                paises.push_back(Pais(continente, nombrePais, id, cantInfanteria, 1));
            }

            jugadores.push_back(Jugador(nombre, color, turn, cantTropas));
            jugadores.back().paises = paises;
        }


        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo." << endl;
    }

    return jugadores;
}

// Funcion para leer la informacion de las relaciones entre paises desde un txt
vector<vector<int>> leerRelacionesDesdeArchivo(const string& nombreArchivo) {
    vector<vector<int>> relaciones;
    ifstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            istringstream ss(linea);
            string idPais, idRelacion;
            vector<int> relacion;

            //Ignorar el primer ID
            getline(ss, idPais, ',');

            //Guardar los ID de las relaciones
            while (getline(ss, idRelacion, ',')) {
                int id = stoi(idRelacion);
                relacion.push_back(id);
            }

            relaciones.push_back(relacion);
        }

        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo." << endl;
    }

    return relaciones;
}

int main() {

    vector<Jugador> jugadores;
    vector<Pais> paises = leerPaisesDesdeArchivo("Paises.txt");
    vector<Tarjeta> tarjetas = leerTarjetasDesdeArchivo("Tarjetas.txt");

    //Matriz de vectores para representar las conexiones entre paises
    vector<vector<int>> conexiones;

    //Montar las conexiones entre paises
    conexiones = leerRelacionesDesdeArchivo("Relaciones.txt");

    /*
    
    cout << "Hola, bienvenido a Risk!" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "Cuantos jugadores van a jugar? (2-6)" << endl;
    int cantidadJugadores;
    cin >> cantidadJugadores;
    cout << "------------------------------------------------" << endl;

    // Tropas por default
    int tropas;
    if (cantidadJugadores == 2) {
        tropas = 40;
    } else if (cantidadJugadores == 3) {
        tropas = 35;
    } else if (cantidadJugadores == 4) {
        tropas = 30;
    } else if (cantidadJugadores == 5) {
        tropas = 25;
    } else if (cantidadJugadores == 6) {
        tropas = 20;
    }
   
    for (int i = 0; i < cantidadJugadores; i++) {
        string nombre;
        string color;
        cout << "Ingrese el nombre del jugador " << i+1 << endl;
        cin >> nombre;
        cout << "Ingrese el color del jugador " << i+1 << endl;
        cin >> color;
        jugadores.push_back(Jugador(nombre, color, 0, tropas));
        cout << "------------------------------------------------" << endl;
    }

    cout << "Sorteando turnos..." << endl;
    vector<int> turnos;

    // Semilla para la generación de números aleatorios
    srand(static_cast<unsigned>(time(nullptr)));

    sortearTurnos(turnos, cantidadJugadores);

    cout << "Turnos asignados aleatoriamente:" << endl;
    for (int i = 0; i < cantidadJugadores; i++) {
        // Asignar el turno al jugador
        jugadores[i].turno = turnos[i];
    }

    cout << "------------------------------------------------" << endl;

    //Organizar los jugadores de menor a mayor por turno
    sort(jugadores.begin(), jugadores.end(), [](const Jugador& a, const Jugador& b) {
        return a.turno < b.turno;
    });

    // Imprimir los jugadores
    cout << "Jugadores:" << endl;
    for (const Jugador& jugador : jugadores) {
        cout << "Nombre: " << jugador.nombre << "\tColor: " << jugador.color << "\tTurno: " << jugador.turno << endl;
    }

    cout << "------------------------------------------------" << endl;

    // Asignar los países a los jugadores
    cout << "Se van a asignar los paises a los jugadores..." << endl;
    int cantidadPaises = 42;

    while (cantidadPaises > 0) {
        for (Jugador& jugador : jugadores) {
            cout << "Turno de " << jugador.nombre << endl;
            imprimirPaises(paises);
            cout << "Digite el ID del pais que desea asignar" << endl;
            int idPais;
            cin >> idPais;

            // Buscar el país con el ID ingresado
            bool encontrado = false;
            int estado = 0;
            int posicion = 0;
            for (Pais& pais : paises) {
                if (pais.identificador == idPais) {
                    encontrado = true;
                    estado = pais.estado;
                    break;
                }
                posicion++;
            }

            // Comprobar que el país existe y no está asignado a ningún jugador
            while (encontrado == false || estado == 1) {
                cout << "El pais ya esta asignado a otro jugador, por favor ingrese otro" << endl;
                cin >> idPais;
                posicion = 0;
                for (Pais& pais : paises) {
                if (pais.identificador == idPais) {
                    encontrado = true;
                    estado = pais.estado;
                    break;
                }
                posicion++;
            }
            }

            // Si el país existe y no está asignado a ningún jugador lo asigna
            cout << "Asignando pais..." << endl;
            cout << "Tropas disponibles: " << jugador.cantidadTropas << endl;
            cout << "Digite la cantidad de tropas que desea asignar" << endl;
            int tropasAsignadas;
            cin >> tropasAsignadas;
            while (tropasAsignadas > jugador.cantidadTropas) {
                cout << "No tiene suficientes tropas, por favor ingrese otra cantidad" << endl;
                cin >> tropasAsignadas;
            }
            jugador.cantidadTropas -= tropasAsignadas;
            paises[posicion].cantidadInfanteria = tropasAsignadas;

            // Cambiar el estado del país a asignado
            paises[posicion].estado = 1;

            // Agregar el país al vector de países del jugador
            jugador.paises.push_back(paises[posicion]);

            // Disminuir la cantidad de países disponibles
            cantidadPaises--;

            // Poner enter para continuar
            cout << "Presione enter para continuar" << endl;
            cin.ignore();
            cin.get();
        }
    }
    
    cout << "------------------------------------------------" << endl;

    //Revizar si todos los jugadores asignaron todas sus tropas
    bool asignado = false;
    while (asignado == false) {
        for (Jugador& jugador : jugadores) {
            if (jugador.cantidadTropas > 0) {
                cout << "Aun le quedan tropas por asignar, por favor asigne todas sus tropas" << endl;
                cout << "Tropas disponibles: " << jugador.cantidadTropas << endl;
                cout << "Digite la cantidad de tropas que desea asignar" << endl;
                int tropasAsignadas;
                cin >> tropasAsignadas;
                while (tropasAsignadas > jugador.cantidadTropas) {
                    cout << "No tiene suficientes tropas, por favor ingrese otra cantidad" << endl;
                    cin >> tropasAsignadas;
                }
                jugador.cantidadTropas -= tropasAsignadas;
                // Buscar el país con el ID ingresado en su vector de países
                cout << "Digite el ID del pais que desea asignar" << endl;
                int idPais;
                cin >> idPais;
                bool encontrado = false;
                int posicion = 0;
                while (encontrado == false) {
                    for (Pais& pais : jugador.paises) {
                        if (pais.identificador == idPais) {
                            encontrado = true;
                            break;
                        }
                        posicion++;
                    }
                    if (encontrado == false) {
                        cout << "No tiene ese pais, por favor ingrese otro" << endl;
                        cin >> idPais;
                    }
                }
                jugador.paises[posicion].cantidadInfanteria += tropasAsignadas;

            } else {
                asignado = true;
            }
        }
    }
    
    // Guardar la información de los jugadores en un txt
    guardarJugadores(jugadores);

    //imprimirPaises(paises);

    //imprimirTarjetas(tarjetas);

    cout << "------------------------------------------------" << endl;

    */


    // Parte de Carga

    // Leer la información de los jugadores desde un txt
    paises.clear();
    jugadores = leerJugadoresDesdeArchivo("Jugadores.txt");
    // Recorrer los paises de cada jugador y cambiar status y tropas de los paises
    for (Jugador& jugador : jugadores) {
        vector<Pais> paisesJugador = jugador.paises;
        for (Pais& pais : paisesJugador) {
            paises[pais.identificador].estado = 1;
            paises[pais.identificador].cantidadInfanteria = pais.cantidadInfanteria;
        }
    }



    // Parte de Guerra

    // Guerra y ubicar nuevas unidades de ejército
    for (Jugador& jugador : jugadores) {

        if (jugador.turno == 1) 
        { 
            cout << "Turno de " << jugador.nombre << endl;

            //Añadir tropas adicionales por territorios
            int cantidadPaises = jugador.paises.size();
            jugador.cantidadTropas += cantidadPaises / 3;

            //Añadir tropas adicionales por continentes
            int cantidadAsia = 0;
            int cantidadEuropa = 0;
            int cantidadAmericaNorte = 0;
            int cantidadAmericaSur = 0;
            int cantidadAfrica = 0;
            int cantidadAustralia = 0;

            for (Pais& pais : jugador.paises) {
                if (pais.continente == "Asia") {
                    cantidadAsia++;
                } else if (pais.continente == "Europa") {
                    cantidadEuropa++;
                } else if (pais.continente == "America del Norte") {
                    cantidadAmericaNorte++;
                } else if (pais.continente == "America del Sur") {
                    cantidadAmericaSur++;
                } else if (pais.continente == "Africa") {
                    cantidadAfrica++;
                } else if (pais.continente == "Australia") {
                    cantidadAustralia++;
                }
            }
            
            if (cantidadAsia == 12) {
                jugador.cantidadTropas += 7;
            } else if (cantidadEuropa == 7) {
                jugador.cantidadTropas += 5;
            } else if (cantidadAmericaNorte == 9) {
                jugador.cantidadTropas += 5;
            } else if (cantidadAmericaSur == 4) {
                jugador.cantidadTropas += 2;
            } else if (cantidadAfrica == 6) {
                jugador.cantidadTropas += 3;
            } else if (cantidadAustralia == 4) {
                jugador.cantidadTropas += 2;
            }

            // Mostrar la cantidad de tropas disponibles
            cout << "Tropas disponibles: " << jugador.cantidadTropas << endl;

            // Mostrar los países del jugador
            cout << "Paises:" << endl;
            for (const Pais& pais : jugador.paises) {
                cout << "ID: " << pais.identificador << "\tNombre: " << pais.nombre << "\tTropas: " << pais.cantidadInfanteria << endl;
            }

            cout << "Digite la cantidad de tropas que desea asignar" << endl;
            int tropasAsignadas;
            cin >> tropasAsignadas;
            while (tropasAsignadas > jugador.cantidadTropas) {
                cout << "No tiene suficientes tropas, por favor ingrese otra cantidad" << endl;
                cin >> tropasAsignadas;
            }
            jugador.cantidadTropas -= tropasAsignadas;
            // Buscar el país con el ID ingresado en su vector de países
            cout << "Digite el ID del pais que desea asignar" << endl;
            int idPais;
            cin >> idPais;
            bool encontrado = false;
            int posicion = 0;
            while (encontrado == false) {
                for (Pais& pais : jugador.paises) {
                    if (pais.identificador == idPais) {
                        encontrado = true;
                        break;
                    }
                    posicion++;
                }
                if (encontrado == false) {
                    cout << "No tiene ese pais, por favor ingrese otro" << endl;
                    cin >> idPais;
                }
            }
            jugador.paises[posicion].cantidadInfanteria += tropasAsignadas;


            // Atacar

            cout << "------------------------------------------------" << endl;
            cout << "Desea atacar? (1 = Si, 2 = No)" << endl;
            int opcion;
            cin >> opcion;
            while (opcion != 1 && opcion != 2) {
                cout << "Opcion invalida, por favor ingrese otra" << endl;
                cin >> opcion;
            }

            while (opcion == 1)
            {
                //Mostrar los paises del jugador
                cout << "Paises:" << endl;
                for (const Pais& pais : jugador.paises) {
                    cout << "ID: " << pais.identificador << "\tNombre: " << pais.nombre << "\tTropas: " << pais.cantidadInfanteria << endl;
                }

                //Preguntar por el pais a atacar
                cout << "Digite el ID del pais desde el que desea atacar" << endl;
                int idPais;
                cin >> idPais;
                bool encontrado = false;
                int posicion = 0;
                while (encontrado == false) {
                    for (Pais& pais : jugador.paises) {
                        if (pais.identificador == idPais) {
                            encontrado = true;
                            break;
                        }
                        posicion++;
                    }
                    if (encontrado == false) {
                        cout << "No tiene ese pais, por favor ingrese otro" << endl;
                        cin >> idPais;
                    }
                }

                //Mostrar los paises vecinos del pais a atacar
                cout << "Paises vecinos:" << endl;
                vector<int> vecinos = conexiones[posicion];

                vector<int> idVecinos;
                //Impriir los paises vecinos
                for (int i = 0; i < vecinos.size(); i++) {         
                    if (vecinos[i]== 1)
                    {
                        cout << "ID: " << paises[i].identificador << "\tNombre: " << paises[i].nombre << "\tTropas: " << paises[i].cantidadInfanteria << endl;
                        idVecinos.push_back(paises[i].identificador);
                    }       
                }

                //Preguntar por el pais a atacar
                cout << "Digite el ID del pais que desea atacar" << endl;
                int idPaisAtacar;
                cin >> idPaisAtacar;

                //Verificar que el pais a atacar sea vecino
                while (find(idVecinos.begin(), idVecinos.end(), idPaisAtacar) == idVecinos.end()) {
                    cout << "No es un pais vecino, por favor ingrese otro" << endl;
                    cin >> idPaisAtacar;
                }

                cout << "------------------------------------------------" << endl;
                //Mostrar tres dados del atacante al azar
                cout << "Jugador atacante:" << endl;
                int dado1 = rand() % 6 + 1;
                int dado2 = rand() % 6 + 1;
                int dado3 = rand() % 6 + 1;
                cout << "Dado 1: " << dado1 << endl;
                cout << "Dado 2: " << dado2 << endl;
                cout << "Dado 3: " << dado3 << endl;
                cout << "------------------------------------------------" << endl;
                cout << "Jugador defensor:" << endl;
                int dado4 = rand() % 6 + 1;
                int dado5 = rand() % 6 + 1;
                cout << "Dado 1: " << dado4 << endl;
                cout << "Dado 2: " << dado5 << endl;
                cout << "------------------------------------------------" << endl;

                //Ordenar los dados del atacante de mayor a menor
                vector<int> dadosAtacante = {dado1, dado2, dado3};
                sort(dadosAtacante.begin(), dadosAtacante.end(), greater<int>());

                //Ordenar los dados del defensor de mayor a menor
                vector<int> dadosDefensor = {dado4, dado5};
                sort(dadosDefensor.begin(), dadosDefensor.end(), greater<int>());

                //Comparar los dados
                if (dadosAtacante[0] > dadosDefensor[0]) {
                    cout << "El jugador atacante gano" << endl;

                    paises[posicion].cantidadInfanteria++;
                    jugador.paises[posicion].cantidadInfanteria++;

                    paises[idPaisAtacar-1].cantidadInfanteria--;
                    //Cambiar la informacion del jugador que tiene el pais a atacar
                    for (vector<Jugador>::iterator it = jugadores.begin(); it != jugadores.end(); ++it) {
                        for (vector<Pais>::iterator it2 = it->paises.begin(); it2 != it->paises.end(); ++it2) {
                            if (it2->identificador == idPaisAtacar) {
                                it2->cantidadInfanteria--;
                            }
                        }
                    }
                    
                   
                } else {
                    cout << "El jugador defensor gano" << endl;
                    
                    paises[posicion].cantidadInfanteria--;
                    jugador.paises[posicion].cantidadInfanteria--;

                    paises[idPaisAtacar-1].cantidadInfanteria++;
                    //Buscar al jugador que tiene el pais a atacar
                    for (vector<Jugador>::iterator it = jugadores.begin(); it != jugadores.end(); ++it) {
                        for (vector<Pais>::iterator it2 = it->paises.begin(); it2 != it->paises.end(); ++it2) {
                            if (it2->identificador == idPaisAtacar) {
                                it2->cantidadInfanteria++;
                            }
                        }
                    }
                    
                    
                }
              
                cout << "Desea seguir atacando? (1 = Si, 2 = No)" << endl;
                cin >> opcion;
                while (opcion != 1 && opcion != 2) {
                    cout << "Opcion invalida, por favor ingrese otra" << endl;
                    cin >> opcion;
                }

            }
        
            //Fortificar la posición
            cout << "------------------------------------------------" << endl;
            cout << "Desea fortificar la posicion? (1 = Si, 2 = No)" << endl;
            int ans;
            cin >> ans;
            while (ans != 1 && ans != 2) {
                cout << "Opcion invalida, por favor ingrese otra" << endl;
                cin >> ans;
            }

            while (ans == 1 )
            {

                //Mostrar los paises del jugador
                cout << "Paises:" << endl;
                for (const Pais& pais : jugador.paises) {
                    cout << "ID: " << pais.identificador << "\tNombre: " << pais.nombre << "\tTropas: " << pais.cantidadInfanteria << endl;
                }

                //Preguntar por el pais del cual van a salir las tropas
                cout << "Digite el ID del pais desde el que desea mover tropas" << endl;
                int idPais;
                cin >> idPais;
                bool encontrado = false;
                int posicion = 0;
                while (encontrado == false) {
                    for (Pais& pais : jugador.paises) {
                        if (pais.identificador == idPais) {
                            encontrado = true;

                            //preguntar por la cantidad de tropas a mover
                            cout << "Digite la cantidad de tropas que desea mover" << endl;
                            int tropasMover;
                            cin >> tropasMover;
                            while (tropasMover > pais.cantidadInfanteria) {
                                cout << "No tiene suficientes tropas, por favor ingrese otra cantidad" << endl;
                                cin >> tropasMover;
                            }

                            //Buscar el pais al que se van a mover las tropas
                            cout << "Digite el ID del pais al que desea mover las tropas" << endl;
                            int idPaisMover;
                            cin >> idPaisMover;
                            bool encontrado2 = false;
                            int posicion2 = 0;
                            while (encontrado2 == false) {
                                for (Pais& pais2 : jugador.paises) {
                                    if (pais2.identificador == idPaisMover) {
                                        encontrado2 = true;

                                        //Mover las tropas
                        
                                        for (Pais& pais3 : jugador.paises) {
                                            if (pais3.identificador == idPais) {
                                                pais3.cantidadInfanteria -= tropasMover;
                                            }
                                            if (pais3.identificador == idPaisMover) {
                                                pais3.cantidadInfanteria += tropasMover;
                                            }
                                        }

                                        //Cambiar los valores de los paises en el vector de paises

                                        for (Pais& pais4 : paises) {
                                            if (pais4.identificador == idPais) {
                                                pais4.cantidadInfanteria -= tropasMover;
                                            }
                                            if (pais4.identificador == idPaisMover) {
                                                pais4.cantidadInfanteria += tropasMover;
                                            }
                                        }

                                        //Mostrar solo los 2 paises que se movieron
                                        cout << "Paises:" << endl;
                                        cout << "ID: " << pais.identificador << "\tNombre: " << pais.nombre << "\tTropas: " << pais.cantidadInfanteria << endl;
                                        cout << "ID: " << pais2.identificador << "\tNombre: " << pais2.nombre << "\tTropas: " << pais2.cantidadInfanteria << endl;


                                        break;

                                    }
                                    posicion2++;
                                }
                                if (encontrado2 == false) {
                                    cout << "No tiene ese pais, por favor ingrese otro" << endl;
                                    cin >> idPaisMover;
                                }
                            }

                            break;
                        }
                        posicion++;
                    }
                    if (encontrado == false) {
                        cout << "No tiene ese pais, por favor ingrese otro" << endl;
                        cin >> idPais;
                    }
                }

                cout << "Desea fortificar otra posicion? (1 = Si, 2 = No)" << endl;
                cin >> ans;
                while (ans != 1 && ans != 2) {
                    cout << "Opcion invalida, por favor ingrese otra" << endl;
                    cin >> ans;
                }
                if (ans == 2) {
                    break;
                }

            }
         

            //Cambiar los turnos, no se sabe cuantos son, entonces el del turno 1 toma el ultimo o el size de jugadores, y a los demas le quitas 1
            int turno = jugadores.size();
            for (Jugador& jugador : jugadores) {
                if (jugador.turno == 1) {
                    jugador.turno = turno;
                } else {
                    jugador.turno--;
                }
            }

        }

        break;

    }

    return 0;
}
