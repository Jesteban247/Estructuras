#include <vector>
#include <sstream>
#include <bitset>

#include "Pais.h"
#include "Jugador.h"
#include "Arbol_Huffman.h"
#include "Tarjeta.h"


int menu()
{
    cout << "1. Asignar paises" << endl;
    cout << "2. Atacar" << endl;
    cout << "3. Guardar partida txt" << endl;
    cout << "4. Cargar partida txt" << endl;
    cout << "5. Guardar partida bin" << endl;
    cout << "6. Cargar partida bin" << endl;
    cout << "10. Salir" << endl;

    cout << "Ingrese una opcion: ";
    int opcion;
    cin >> opcion;

    return opcion;
}

// Funcion para leer los paises
vector<Pais> leerPaises()
{
    vector<Pais> paises;

    ifstream archivo("Paises.txt");

    string linea;

    while (getline(archivo, linea))
    {
        int posPuntoComa = linea.find(';');
        string continente = linea.substr(0, posPuntoComa);
        linea = linea.substr(posPuntoComa + 1);
        posPuntoComa = linea.find(';');
        string nombre = linea.substr(0, posPuntoComa);
        linea = linea.substr(posPuntoComa + 1);
        int id = stoi(linea);

        Pais pais(id, continente, nombre);

        paises.push_back(pais);
    }

    archivo.close();

    return paises;
}

// Funcion para imprimir los paises
void imprimirPaises(vector<Pais> &paises)
{
    string continenteActual = "";

    cout << "-------------------------" << endl;

    //Si el estado del pais es diferente a 0, significa que ya fue asignado y no se imprime
    for (int i = 0; i < paises.size(); i++)
    {
        if (paises[i].getContinente() != continenteActual)
        {
            continenteActual = paises[i].getContinente();
            cout << "Continente: " << continenteActual << endl;
        }

        if (paises[i].getEstado() == 0)
        {
            cout << "  " << paises[i].getId() << ". " << paises[i].getNombre() << endl;
        }
    }

    cout << "-------------------------" << endl;
}

// Guardar partida en un txt, la info de los jugadores
void guardarPartida(vector<Jugador> &jugadores)
{
    ofstream archivo("Partida.txt");

    for (int i = 0; i < jugadores.size(); i++)
    {
        archivo << jugadores[i].getNombre() << ";";
        archivo << jugadores[i].getTurno() << ";";
        archivo << jugadores[i].getEjercitos() << ";";

        map<int, int> paises = jugadores[i].getPaises();

        archivo << paises.size() << ";";

        for (auto it = paises.begin(); it != paises.end(); it++)
        {
            archivo << it->first << ",";
            archivo << it->second << ";";
        }

        set<int> tarjetas = jugadores[i].getTarjetas();

        archivo << tarjetas.size() << ";";

        for (auto it = tarjetas.begin(); it != tarjetas.end(); it++)
        {
            archivo << *it << ";";
        }

        archivo << endl;
    }

    archivo.close();
}

// Cargar partida desde un txt, la info de los jugadores
vector<Jugador> cargarPartida(string nombreArchivo)
{
    vector<Jugador> jugadores;

    ifstream archivo(nombreArchivo);

    string linea;

    while (getline(archivo, linea))
    {
        int posPuntoComa = linea.find(';');
        string nombre = linea.substr(0, posPuntoComa);
        linea = linea.substr(posPuntoComa + 1);
        posPuntoComa = linea.find(';');
        int turno = stoi(linea.substr(0, posPuntoComa));
        linea = linea.substr(posPuntoComa + 1);
        posPuntoComa = linea.find(';');
        int ejercitos = stoi(linea.substr(0, posPuntoComa));
        linea = linea.substr(posPuntoComa + 1);
        posPuntoComa = linea.find(';');
        int cantidadPaises = stoi(linea.substr(0, posPuntoComa));
        linea = linea.substr(posPuntoComa + 1);

        Jugador jugador(nombre, turno, ejercitos);

        for (int i = 0; i < cantidadPaises; i++)
        {
            posPuntoComa = linea.find(';');
            string pais = linea.substr(0, posPuntoComa);
            linea = linea.substr(posPuntoComa + 1);
            posPuntoComa = pais.find(',');
            int id = stoi(pais.substr(0, posPuntoComa));
            int ejercitos = stoi(pais.substr(posPuntoComa + 1));

            jugador.agregarPais(id, ejercitos);
        }

        posPuntoComa = linea.find(';');
        int cantidadTarjetas = stoi(linea.substr(0, posPuntoComa));

        for (int i = 0; i < cantidadTarjetas; i++)
        {
            linea = linea.substr(posPuntoComa + 1);
            posPuntoComa = linea.find(';');
            int id = stoi(linea.substr(0, posPuntoComa));

            jugador.agregarTarjeta(id);
        }

        jugadores.push_back(jugador);
    }

    archivo.close();

    return jugadores;
}

// Cargar paises vecinos
map<int, vector<int>> cargarPaisesVecinos() {
    map<int, vector<int>> paisesVecinos;

    ifstream archivo("Relaciones.txt");

    if (archivo.is_open()) {
        string linea;

        while (getline(archivo, linea)) {
            istringstream iss(linea);
            int clave;
            char separador;
            iss >> clave >> separador;

            string valores;
            iss >> valores;

            istringstream valoresStream(valores);
            vector<int> vecinos;
            int vecino;
            while (valoresStream >> vecino) {
                vecinos.push_back(vecino);
                valoresStream.ignore(1, ',');
            }
            paisesVecinos[clave] = vecinos;
        }

        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo 'Relaciones.txt'" << endl;
    }

    return paisesVecinos;
}


// Tarjetas

//Funcion para leer las tarjetas
vector<Tarjeta> leerTarjetas()
{
    vector<Tarjeta> tarjetas;

    ifstream archivo("Tarjetas.txt");

    string linea;

    while (getline(archivo, linea))
    {
        int posPuntoComa = linea.find(';');
        int id = stoi(linea.substr(0, posPuntoComa));
        linea = linea.substr(posPuntoComa + 1);
        posPuntoComa = linea.find(';');
        string pais = linea.substr(0, posPuntoComa);
        linea = linea.substr(posPuntoComa + 1);
        string tipo = linea;

        Tarjeta tarjeta(id, pais, tipo);

        tarjetas.push_back(tarjeta);
    }

    archivo.close();

    return tarjetas;
}

// Arbol Huffman

// Lee el contenido de un archivo y lo devuelve como string
string readFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo: " << filename << endl;
        exit(1);
    }
    string content((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
    file.close();
    return content;
}

// Función para serializar un unordered_map
void SerializeMap(const std::map<char, int>& map, const std::string& filename) {
    std::ofstream outfile(filename, std::ios::binary);
    std::vector<std::pair<char, int>> pairs(map.begin(), map.end()); // Copia pares clave-valor en un vector
    for (const auto& pair : pairs) {
        outfile.write(reinterpret_cast<const char*>(&pair.first), sizeof(char));
        outfile.write(reinterpret_cast<const char*>(&pair.second), sizeof(int));
    }
    outfile.close();
}

// Función para deserializar un unordered_map
map<char, int> DeserializeMap(const std::string& filename) {
    ifstream infile(filename, std::ios::binary);
    map<char, int> loaded_map;
    char key;
    int value;
    while (infile.read(reinterpret_cast<char*>(&key), sizeof(char)) &&
           infile.read(reinterpret_cast<char*>(&value), sizeof(int))) {
        loaded_map[key] = value;
    }
    infile.close();
    return loaded_map;
}

// Función para guardar un string binario en un archivo binario
void guardarEnArchivoBinario(const string& str, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo, ios::out | ios::binary);
    if (archivo.is_open()) {
        archivo.write(str.c_str(), str.size());
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

// Función para leer un archivo binario y obtener el contenido como string binario
string leerDesdeArchivoBinario(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo, ios::in | ios::binary);
    if (archivo.is_open()) {
        // Obtener el tamaño del archivo
        archivo.seekg(0, ios::end);
        size_t tamano = archivo.tellg();
        archivo.seekg(0, ios::beg);
        
        // Leer el contenido del archivo en un string
        string str(tamano, 0);
        archivo.read(&str[0], tamano);
        archivo.close();
        
        return str;
    } else {
        cout << "No se pudo abrir el archivo." << endl;
        return "";
    }
}


int main() 
{
    cout << "Hola, bienvenido a Risk" << endl;

    vector<Pais> paises = leerPaises();
    vector<Jugador> jugadores;
    map<int, vector<int>> paisesVecinos= cargarPaisesVecinos();
    vector<Tarjeta> tarjetas = leerTarjetas();

    int opcion = menu();

    while (opcion != 10)
    {

        if (opcion == 1)
        {
            cout << "Cantidad de jugadores: " << endl;
            int cantidadJugadores;
            cin >> cantidadJugadores;

            int tropas = 0;

            if (cantidadJugadores == 2)
            {
                tropas = 40;
            }
            else if (cantidadJugadores == 3)
            {
                tropas = 35;
            }
            else if (cantidadJugadores == 4)
            {
                tropas = 30;
            }
            else if (cantidadJugadores == 5)
            {
                tropas = 25;
            }
            else if (cantidadJugadores == 6)
            {
                tropas = 20;
            }

            for (int i = 0; i < cantidadJugadores; i++)
            {
                cout << "Nombre del jugador " << i + 1 << ": ";
                string nombre;
                cin >> nombre;

                Jugador jugador(nombre, i + 1, tropas);

                jugadores.push_back(jugador);
            }

            cout << "Se van a asignar los paises" << endl;

            int cantidadPaises = paises.size();
            while (cantidadPaises > 0)
            {
                for (int i = 0; i < jugadores.size(); i++)
                {
                    imprimirPaises(paises);

                    cout << "Turno de " << jugadores[i].getNombre() << endl;
                    cout << "Ingrese el id del pais: ";
                    int idPais;
                    cin >> idPais;

                    bool condicion = false;
                    while (!condicion)
                    {
                        for (int j = 0; j < paises.size(); j++)
                        {
                            if (paises[j].getId() == idPais && paises[j].getEstado() == 0)
                            {
                                condicion = true;
                                paises[j].setEstado(1);
                                jugadores[i].agregarPais(idPais, 1);
                                jugadores[i].setEjercitos(jugadores[i].getEjercitos() - 1);
                                cantidadPaises--;
                                break;
                            }
                        }

                        if (!condicion)
                        {
                            cout << "Ingrese un id valido: ";
                            cin >> idPais;
                        }
                    }
                }  
            }

            cout << "Se asignaron todos los paises" << endl;
        }


        if (opcion == 2)
        {
            cout << "Atacar" << endl;

            for (int i = 0; i < jugadores.size(); i++)
            {
                if (jugadores[i].getTurno() ==1)
                {
                    //Parte 1: Obtener y ubicar nuevas unidades de ejército.

                    cout << "Turno de " << jugadores[i].getNombre() << endl;
                    cout << "Ejercitos viejos: " << jugadores[i].getEjercitos() << endl;

                    //Territorios
                    int territorios = jugadores[i].getPaises().size();
                    int ejercitos = territorios / 3;
                    jugadores[i].setEjercitos(jugadores[i].getEjercitos() + ejercitos);

                    //Continentes
                    map<int, int> paises_jugador = jugadores[i].getPaises();
                    int America_N = 0;
                    int America_S = 0;
                    int Europa = 0;
                    int Asia = 0;
                    int Africa = 0;
                    int Australia = 0;
                    for (auto it = paises_jugador.begin(); it != paises_jugador.end(); it++)
                    {
                        for (int j = 0; j < paises.size(); j++)
                        {
                            if (it->first == paises[j].getId())
                            {
                                if (paises[j].getContinente() == "América del Norte")
                                {
                                    America_N++;
                                }
                                else if (paises[j].getContinente() == "América del Sur")
                                {
                                    America_S++;
                                }
                                else if (paises[j].getContinente() == "Europa")
                                {
                                    Europa++;
                                }
                                else if (paises[j].getContinente() == "Asia")
                                {
                                    Asia++;
                                }
                                else if (paises[j].getContinente() == "África")
                                {
                                    Africa++;
                                }
                                else if (paises[j].getContinente() == "Australia")
                                {
                                    Australia++;
                                }
                            }
                        }
                    }

                    if (America_N == 9)
                    {
                        jugadores[i].setEjercitos(jugadores[i].getEjercitos() + 5);
                    }
                    else if (America_S == 4)
                    {
                        jugadores[i].setEjercitos(jugadores[i].getEjercitos() + 2);
                    }
                    else if (Europa == 7)
                    {
                        jugadores[i].setEjercitos(jugadores[i].getEjercitos() + 5);
                    }
                    else if (Asia == 12)
                    {
                        jugadores[i].setEjercitos(jugadores[i].getEjercitos() + 7);
                    }
                    else if (Africa == 6)
                    {
                        jugadores[i].setEjercitos(jugadores[i].getEjercitos() + 3);
                    }
                    else if (Australia == 4)
                    {
                        jugadores[i].setEjercitos(jugadores[i].getEjercitos() + 2);
                    }

                    //Revisar tarjetas

                    set<int> tarjetas_j = jugadores[i].getTarjetas();
                    int cantidadTarjetas = tarjetas_j.size();

                    if (cantidadTarjetas >=3)
                    {
                        jugadores[i].setEjercitos(jugadores[i].getEjercitos() + 5);
                        //Eliminar solo las tres primeras tarjetas
                        int contador = 0;
                        for (auto it = tarjetas_j.begin(); it != tarjetas_j.end(); it++)
                        {
                            if (contador < 3)
                            {
                                //Cambiar el estado de la tarjeta a 0
                                for (int j = 0; j < tarjetas.size(); j++)
                                {
                                    if (tarjetas[j].getID() == *it)
                                    {
                                        tarjetas[j].setEstado(0);
                                    }
                                }

                                jugadores[i].eliminarTarjeta(*it);
                                contador++;
                            }
                        }
                    }


                    cout << "Ejercitos nuevos: " << jugadores[i].getEjercitos() << endl;



                    //Parte 2: Atacar

                    cout << "Desear atacar? (1 = si, 0 = no): ";
                    int opcion;
                    cin >> opcion;

                    while (opcion != 0 && opcion != 1)
                    {
                        cout << "Ingrese una opcion valida: ";
                        cin >> opcion;
                    }

                    while (opcion ==1) 
                    {
                        map<int, int> paises_jugador = jugadores[i].getPaises();

                        //Mostrar paises del jugador
                        cout << "Paises del jugador: " << endl;
                        for (auto it = paises_jugador.begin(); it != paises_jugador.end(); it++)
                        {
                            for (int j = 0; j < paises.size(); j++)
                            {
                                if (it->first == paises[j].getId())
                                {
                                    cout << "Id: " << paises[j].getId() << ". Nombre: " << paises[j].getNombre() << ". Ejercitos: " << it->second << endl;
                                }
                            }
                        }

                        cout << "Ingrese el id del pais del que va a atacar: ";
                        int idPaisAtacante;
                        cin >> idPaisAtacante;
                        bool condicion = false;
                        while (!condicion)
                        {
                            for (auto it = paises_jugador.begin(); it != paises_jugador.end(); it++)
                            {
                                if (it->first == idPaisAtacante)
                                {
                                    condicion = true;
                                    break;
                                }
                            }

                            if (!condicion)
                            {
                                cout << "Ingrese un id valido: ";
                                cin >> idPaisAtacante;
                            }
                        }

                        //Mostrar paises vecinos
                        cout << "Paises vecinos: " << endl;
                        vector<int> vecinos = paisesVecinos[idPaisAtacante];
                        for (int j = 0; j < vecinos.size(); j++)
                        {
                            for (int k = 0; k < paises.size(); k++)
                            {
                                if (vecinos[j] == paises[k].getId())
                                {
                                    cout << "Id: " << paises[k].getId() << ". Nombre: " << paises[k].getNombre() << endl;
                                }
                            }
                        }

                        cout << "Ingrese el id del pais que va a atacar: ";
                        int idPaisAtacado;
                        cin >> idPaisAtacado;
                        condicion = false;
                        while (!condicion)
                        {
                            for (int j = 0; j < vecinos.size(); j++)
                            {
                                if (vecinos[j] == idPaisAtacado)
                                {
                                    condicion = true;
                                    break;
                                }
                            }

                            if (!condicion)
                            {
                                cout << "Ingrese un id valido: ";
                                cin >> idPaisAtacado;
                            }
                        }

                        //Sortear dados del atacante y defensor
                        vector<int> dadosAtacante;
                        vector<int> dadosDefensor;
                        int cantidadDadosAtacante = 3;
                        int cantidadDadosDefensor = 2;
                        
                        for (int j = 0; j < cantidadDadosAtacante; j++)
                        {
                            int dado = rand() % 6 + 1;
                            dadosAtacante.push_back(dado);
                        }

                        for (int j = 0; j < cantidadDadosDefensor; j++)
                        {
                            int dado = rand() % 6 + 1;
                            dadosDefensor.push_back(dado);
                        }

                        //Ordenar dados, no acepta el sort
                        for (int j = 0; j < dadosAtacante.size(); j++)
                        {
                            for (int k = 0; k < dadosAtacante.size() - 1; k++)
                            {
                                if (dadosAtacante[k] < dadosAtacante[k + 1])
                                {
                                    int aux = dadosAtacante[k];
                                    dadosAtacante[k] = dadosAtacante[k + 1];
                                    dadosAtacante[k + 1] = aux;
                                }
                            }
                        }

                        for (int j = 0; j < dadosDefensor.size(); j++)
                        {
                            for (int k = 0; k < dadosDefensor.size() - 1; k++)
                            {
                                if (dadosDefensor[k] < dadosDefensor[k + 1])
                                {
                                    int aux = dadosDefensor[k];
                                    dadosDefensor[k] = dadosDefensor[k + 1];
                                    dadosDefensor[k + 1] = aux;
                                }
                            }
                        }

                        //Mostrar dados
                        cout << "Dados del atacante: " << endl;
                        for (int j = 0; j < dadosAtacante.size(); j++)
                        {
                            cout << dadosAtacante[j] << ", ";
                        }
                        cout << endl;

                        cout << "Dados del defensor: " << endl;
                        for (int j = 0; j < dadosDefensor.size(); j++)
                        {
                            cout << dadosDefensor[j] << ", ";
                        }
                        cout << endl;
                        
                        //Sumar los dos primeros dados y definir el ganador y el perdedor
                        int sumaAtacante = dadosAtacante[0] + dadosAtacante[1];
                        int sumaDefensor = dadosDefensor[0] + dadosDefensor[1];

                        if (sumaAtacante > sumaDefensor)
                        {
                            cout << "Gana el atacante" << endl;

                            //Sumar un ejercito al pais del atacante
                            for (auto it = paises_jugador.begin(); it != paises_jugador.end(); it++)
                            {
                                if (it->first == idPaisAtacante)
                                {
                                    it->second++;
                                }
                            }

                            //Recorrer los jugadores, excepto el del turno 1 y quitar una tropa al pais del defensor
                            for (int j = 0; j < jugadores.size(); j++)
                            {
                                if (jugadores[j].getTurno() != 1)
                                {
                                    map<int, int> paises_jugador = jugadores[j].getPaises();
                                    for (auto it = paises_jugador.begin(); it != paises_jugador.end(); it++)
                                    {
                                        if (it->first == idPaisAtacado)
                                        {
                                            it->second--;
                                        }
                                    }
                                    jugadores[j].setPaises(paises_jugador);
                                }
                            }

                        }

                        else
                        {
                            cout << "Gana el defensor" << endl;
                            
                            //Restar un ejercito al pais del atacante
                            for (auto it = paises_jugador.begin(); it != paises_jugador.end(); it++)
                            {
                                if (it->first == idPaisAtacante)
                                {
                                    it->second--;
                                }
                            }

                            //Recorrer los jugadores, excepto el del turno 1 y quitar una tropa al pais del defensor
                            for (int j = 0; j < jugadores.size(); j++)
                            {
                                if (jugadores[j].getTurno() != 1)
                                {
                                    map<int, int> paises_jugador = jugadores[j].getPaises();
                                    for (auto it = paises_jugador.begin(); it != paises_jugador.end(); it++)
                                    {
                                        if (it->first == idPaisAtacado)
                                        {
                                            it->second++;
                                        }
                                    }
                                    jugadores[j].setPaises(paises_jugador);
                                }
                            }

                        }

                        //Volver a asignar el map de paises
                        jugadores[i].setPaises(paises_jugador);

                        //Mostrar los cambios de ambos paises
                        cout << "Pais del atacante: " << endl;
                        for (auto it = paises_jugador.begin(); it != paises_jugador.end(); it++)
                        {
                            if (it->first == idPaisAtacante)
                            {
                                cout << "Id: " << it->first << ". Ejercitos: " << it->second << endl;
                            }
                        }

                        cout << "Pais del defensor: " << endl;
                        
                        //Recorrer los jugadores, excepto el del turno 1 y quitar una tropa al pais del defensor
                        for (int j = 0; j < jugadores.size(); j++)
                        {
                            if (jugadores[j].getTurno() != 1)
                            {
                                map<int, int> paises_jugador_2 = jugadores[j].getPaises();
                                for (auto it = paises_jugador_2.begin(); it != paises_jugador_2.end(); it++)
                                {
                                    if (it->first == idPaisAtacado)
                                    {
                                        cout << "Id: " << it->first << ". Ejercitos: " << it->second << endl;
                                    }
                                }
        
                            }
                        }

                
                        //Si el pais del defensor tiene 0 ejercitos, se le asigna al atacante
                        // Recorremos la lista de jugadores
                        for (auto it = jugadores.begin(); it != jugadores.end(); ++it) 
                        {
                            if (it->getTurno() !=1)
                            {
                                // Recorremos el map de paises de cada jugador
                                map<int, int> paises_jugador_2 = it->getPaises();
                                for (auto it2 = paises_jugador_2.begin(); it2 != paises_jugador_2.end(); ++it2) 
                                {
                                    if (it2->first == idPaisAtacado && it2->second == 0)
                                    {
                                        cout << "El pais " << idPaisAtacado << " se le asigna al jugador " << jugadores[i].getNombre() << endl;
                                        jugadores[i].agregarPais(idPaisAtacado, 1);
                                        jugadores[i].setEjercitos(jugadores[i].getEjercitos() - 1);
                                        it->EliminarPais(idPaisAtacado);


                                        //Se informa al jugador que puede recibir una tarjeta
                                        cout << "El jugador " << jugadores[i].getNombre() << " puede recibir una tarjeta" << endl;

                                        for (int j = 0; j < tarjetas.size(); j++)
                                        {
                                            if (tarjetas[j].getID() == idPaisAtacado)
                                            {
                                                cout << "El jugador " << jugadores[i].getNombre() << " recibe la tarjeta " << tarjetas[j].getTipo() << " de " << tarjetas[j].getPais() << endl;
                                                jugadores[i].agregarTarjeta(tarjetas[j].getID());
                                                tarjetas[j].setEstado(1);
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }


                        //Mostrar los paises del jugador
                        cout << "Id de los paises del jugador: ";
                        jugadores[i].imprimirPaises();

                        cout << "Desear atacar? (1 = si, 0 = no): ";
                        cin >> opcion;

                        while (opcion != 0 && opcion != 1)
                        {
                            cout << "Ingrese una opcion valida: ";
                            cin >> opcion;
                        }

                        if (opcion == 0)
                        {
                            break;
                        }

                    }
                
                
                    //Parte 3: Mover ejercitos

                    cout << "Desear movee ejercitos? (1 = si, 0 = no): ";
                    cin >> opcion;
                    while (opcion != 0 && opcion != 1)
                    {
                        cout << "Ingrese una opcion valida: ";
                        cin >> opcion;
                    }

                    while (opcion == 1)
                    {
                        //Mostrar paises del jugador
                        cout << "Paises del jugador: " << endl;
                        map <int, int> paises_jugador = jugadores[i].getPaises();
                        for (auto it = paises_jugador.begin(); it != paises_jugador.end(); it++)
                        {
                            for (int j = 0; j < paises.size(); j++)
                            {
                                if (it->first == paises[j].getId())
                                {
                                    cout << "Id: " << paises[j].getId() << ". Nombre: " << paises[j].getNombre() << ". Ejercitos: " << it->second << endl;
                                }
                            }
                        }

                        cout << "Ingrese el id del pais del que va a mover: ";
                        int idPaisMover;
                        cin >> idPaisMover;
                        bool condicion = false;
                        while (!condicion)
                        {
                            for (auto it = paises_jugador.begin(); it != paises_jugador.end(); it++)
                            {
                                if (it->first == idPaisMover)
                                {
                                    condicion = true;
                                    break;
                                }
                            }

                            if (!condicion)
                            {
                                cout << "Ingrese un id valido: ";
                                cin >> idPaisMover;
                            }
                        }

                        //Mostrar paises vecinos del pais a mover y que sean propios
                        cout << "Paises vecinos: " << endl;
                        bool condicion2 = false;
                        vector<int> vecinos = paisesVecinos[idPaisMover];
                        for (int j = 0; j < vecinos.size(); j++)
                        {
                            for (int k = 0; k < paises.size(); k++)
                            {
                                if (vecinos[j] == paises[k].getId())
                                {
                                    for (auto it = paises_jugador.begin(); it != paises_jugador.end(); it++)
                                    {
                                        if (it->first == vecinos[j])
                                        {
                                            cout << "Id: " << paises[k].getId() << ". Nombre: " << paises[k].getNombre() << ". Ejercitos: " << it->second << endl;
                                            condicion2 = true;
                                        }
                                    }
                                }
                            }
                        }

                        if (!condicion2)
                        {
                            cout << "No hay paises vecinos propios" << endl;
                            break;
                        }

                        else 
                        {
                            cout << "Ingrese el id del pais al que va a mover: ";
                            int idPais;
                            cin >> idPais;
                            condicion = false;
                            while (!condicion)
                            {
                                for (int j = 0; j < vecinos.size(); j++)
                                {
                                    if (vecinos[j] == idPais)
                                    {
                                        condicion = true;
                                        break;
                                    }
                                }

                                if (!condicion)
                                {
                                    cout << "Ingrese un id valido: ";
                                    cin >> idPais;
                                }
                            }

                            cout << "Digite la cantidad de ejercitos a mover: ";
                            int cantidadEjercitos;
                            cin >> cantidadEjercitos;
                            map<int, int>::iterator it;
                            it=paises_jugador.find(idPaisMover);
                            while (cantidadEjercitos > it->second)
                            {
                                cout << "Ingrese una cantidad valida: ";
                                cin >> cantidadEjercitos;
                            }

                            //Cambiar la cantidad de ejercitos del pais a mover
                            it->second = it->second - cantidadEjercitos;
                            it=paises_jugador.find(idPais);
                            it->second = it->second + cantidadEjercitos;

                            //Volver a asignar el map de paises
                            jugadores[i].setPaises(paises_jugador);

                            //Mostrar los cambios de ambos paises
                            cout << "Pais del que se mueven los ejercitos: " << endl;
                            for (auto it = paises_jugador.begin(); it != paises_jugador.end(); it++)
                            {
                                if (it->first == idPaisMover)
                                {
                                    cout << "Id: " << it->first << ". Ejercitos: " << it->second << endl;
                                }
                            }

                            cout << "Pais al que se mueven los ejercitos: " << endl;
                            for (auto it = paises_jugador.begin(); it != paises_jugador.end(); it++)
                            {
                                if (it->first == idPais)
                                {
                                    cout << "Id: " << it->first << ". Ejercitos: " << it->second << endl;
                                }
                            }
                        }

                        cout << "Desear seguir moviendo ejercitos? (1 = si, 0 = no): ";
                        cin >> opcion;
                        while (opcion != 0 && opcion != 1)
                        {
                            cout << "Ingrese una opcion valida: ";
                            cin >> opcion;
                        }

                        if (opcion == 0)
                        {
                            break;
                        }


                    }


                    //Parte 4: Cambiar turnos
                    for (int j = 0; j < jugadores.size(); j++)
                    {
                        if (jugadores[j].getTurno() == 1)
                        {
                            jugadores[j].setTurno(jugadores.size());
                        }
                        else
                        {
                            jugadores[j].setTurno(jugadores[j].getTurno() - 1);
                        }
                    }


                    //Verificar si el jugador gano
                    if (jugadores[i].getPaises().size() == paises.size())
                    {
                        cout << "El jugador " << jugadores[i].getNombre() << " ha ganado" << endl;
                        return 0;
                    }

                    break;
                }
            }



        }   


        if (opcion == 3)
        {
            cout << "Guardar partida" << endl;
            guardarPartida(jugadores);
        } 


        if (opcion == 4)
        {
            cout << "Cargar partida txt" << endl;
            jugadores = cargarPartida("Partida.txt");

            //Cambiar el estado del vector de paises
            for (Pais &pais : paises)
            {
                pais.setEstado(1);
            }

            //Mostrar solo los jugadores
            for (int i = 0; i < jugadores.size(); i++)
            {
                cout << "Nombre: " << jugadores[i].getNombre() << endl;
                cout << "Turno: " << jugadores[i].getTurno() << endl;
                cout << "Ejercitos: " << jugadores[i].getEjercitos() << endl;
                set <int> tarjetas = jugadores[i].getTarjetas();
                if (tarjetas.size() > 0)
                {
                    cout << "Tarjetas: ";
                    for (auto it = tarjetas.begin(); it != tarjetas.end(); it++)
                    {
                        cout << "Id: " << *it << ", "; 
                    }
                    cout << endl;
                }
                cout << "-------------------------" << endl;
            }
        }


        if (opcion == 5)
        {
            cout << "Guardar partida" << endl;
            guardarPartida(jugadores);

            string filename = "Partida.txt";  // Nombre del archivo de entrada
            string text = readFromFile(filename);  // Leer contenido del archivo

            HuffmanResult result = buildHuffmanTree(text);
            Node* root = result.root;
            map<char, int> huffmanCodes = result.huffmanCodes;

            string str = Huffman_codes(root, text);

            string nombreArchivo = "Partida.bin";
            // Guardar el string binario en un archivo binario
            guardarEnArchivoBinario(str, nombreArchivo);
        
            // Serializar el mapa
            SerializeMap(huffmanCodes, "map.data");
        }

        if (opcion ==6)
        {
            map<char, int> loaded_freq = DeserializeMap("map.data");
            Node *root2 = buildHuffmanTree(loaded_freq);
            
            string nombreArchivo = "Partida.bin";
            // Leer desde el archivo binario y restaurar el string original
            string str= leerDesdeArchivoBinario(nombreArchivo);

            decode_Huffman(root2, str);

            cout << "Cargar partida Bin" << endl;
            jugadores = cargarPartida("Decodificado.txt");

            //Cambiar el estado del vector de paises
            for (Pais &pais : paises)
            {
                pais.setEstado(1);
            }

            //Mostrar solo los jugadores
            for (int i = 0; i < jugadores.size(); i++)
            {
                cout << "Nombre: " << jugadores[i].getNombre() << endl;
                cout << "Turno: " << jugadores[i].getTurno() << endl;
                cout << "Ejercitos: " << jugadores[i].getEjercitos() << endl;
                set <int> tarjetas = jugadores[i].getTarjetas();
                if (tarjetas.size() > 0)
                {
                    cout << "Tarjetas: ";
                    for (auto it = tarjetas.begin(); it != tarjetas.end(); it++)
                    {
                        cout << "Id: " << *it << ", "; 
                    }
                    cout << endl;
                }
                cout << "-------------------------" << endl;
            }

            
            

        }

        opcion = menu();
    }





    return 0;
}
