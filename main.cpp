#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "Paises.h"
#include "Jugador.h"

void menu()
{
    cout << "1. Iniciar" << endl;
    cout << "2. Guardar" << endl;
    cout << "3. Cargar" << endl;
    cout << "4. Parte_1" << endl;
    cout << "5. Parte_2" << endl;
}

// Función para leer la información de los países de un archivo
void leerPaises(vector<Paises> &paises) {
    ifstream archivo("Lista.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        int id;
        string continente;
        string nombre;
        char delimiter; // Para leer las comas

        // Leer el ID del país y omitir la coma
        if (!(ss >> id >> delimiter)) {
            cerr << "Error al leer el ID de un país." << endl;
            continue; // Ir a la siguiente línea si hay un error
        }

        // Leer el nombre del continente hasta la próxima coma
        if (!getline(ss, continente, ',')) {
            cerr << "Error al leer el continente de un país." << endl;
            continue;
        }

        // Omitir los espacios en blanco después de la coma
        ss >> ws;

        // Leer el nombre del país hasta el final de la línea
        if (!getline(ss, nombre)) {
            cerr << "Error al leer el nombre de un país." << endl;
            continue;
        }

        // Crear un nuevo país y añadirlo al vector
        Paises pais(id, continente, nombre, 0, 0, 0);
        paises.push_back(pais);
    }

    archivo.close();
}

//Leer la informacion de las relaciones
void leerRelaciones(map<int, vector<int>>& relaciones) 
{
    ifstream file("Relaciones.txt");
    string line;

    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    while (getline(file, line)) {
        istringstream iss(line);
        int country_id;
        char delimiter;

        // Leer el ID del país
        if (!(iss >> country_id >> delimiter)) {
            continue; // Si no se puede leer el ID, ignora la línea
        }

        // Leer los IDs de los países adyacentes y almacenarlos en el vector
        string connection_ids;
        getline(iss, connection_ids);
        istringstream connection_stream(connection_ids);
        int id;
        
        // Leer cada ID de los países adyacentes separados por comas
        while (connection_stream >> id) {
            relaciones[country_id].push_back(id);
            if (connection_stream.peek() == ',') {
                connection_stream.ignore();
            }
        }
    }

    file.close();
}

//Guardar la informacion de la partida
void guardar(vector<Paises> paises, vector<Jugador> jugadores, string nombre_archivo)
{
    ofstream archivo(nombre_archivo);
    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    //Recorrer los jugadores
    for (int i = 0; i < jugadores.size(); i++)
    {
        //Guardar informacion de los jugadores
        archivo << jugadores[i].getNombre() << ",";
        archivo << jugadores[i].getTurno() << ",";
        archivo << jugadores[i].getId() << ",";
        archivo << jugadores[i].getTropas() << ",";

        int cant_paises = 0;

        for (int j = 0; j < paises.size(); j++)
        {
            if (paises[j].getId_jugador() == jugadores[i].getId())
            {
                cant_paises++;
            }
        }

        archivo << cant_paises << ",";

        for (int j = 0; j < paises.size(); j++)
        {
            if (paises[j].getId_jugador() == jugadores[i].getId())
            {
                archivo << paises[j].getId() << ",";
                archivo << paises[j].getEstado() << ",";
                archivo << paises[j].getId_jugador() << ",";
                archivo << paises[j].getEjercitos() << ",";
            }
        }

        archivo << endl;

    }


    archivo.close();
}

//Leer la informacion de la partida
void leerPartida(vector<Paises> &paises, vector<Jugador> &jugadores, string nombre_archivo)
{
    ifstream archivo(nombre_archivo);
    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    string nombre;
    int turno;
    int id;
    int tropas;
    int cant_paises;

    string line;
    while (getline(archivo, line)) 
    {
        vector<string> tokens;
        stringstream ss(line);
        string token;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        nombre = tokens[0];
        turno = stoi(tokens[1]);
        id = stoi(tokens[2]);
        tropas = stoi(tokens[3]);
        cant_paises = stoi(tokens[4]);

        Jugador jugador(nombre, turno, id, tropas);
        jugadores.push_back(jugador);

        for (int i = 0; i < cant_paises; i++)
        {
            int id_pais = stoi(tokens[5 + i * 4]);
            for (int j = 0; j < paises.size(); j++)
            {
                if (paises[j].getId() == id_pais)
                {
                    paises[j].setEstado(stoi(tokens[6 + i * 4]));
                    paises[j].setId_jugador(stoi(tokens[7 + i * 4]));
                    paises[j].setEjercitos(stoi(tokens[8 + i * 4]));
                }
            }
        }
        
    }
        

}

int main()
{
// Función para leer la información de los países de un archivo
void leerPaises(vector<Paises> &paises) {
    ifstream archivo("Lista.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        int id;
        string continente;
        string nombre;
        char delimiter; // Para leer las comas

        // Leer el ID del país y omitir la coma
        if (!(ss >> id >> delimiter)) {
            cerr << "Error al leer el ID de un país." << endl;
            continue; // Ir a la siguiente línea si hay un error
        }

        // Leer el nombre del continente hasta la próxima coma
        if (!getline(ss, continente, ',')) {
            cerr << "Error al leer el continente de un país." << endl;
            continue;
        }

        // Omitir los espacios en blanco después de la coma
        ss >> ws;

        // Leer el nombre del país hasta el final de la línea
        if (!getline(ss, nombre)) {
            cerr << "Error al leer el nombre de un país." << endl;
            continue;
        }

        // Crear un nuevo país y añadirlo al vector
        Paises pais(id, continente, nombre, 0, 0, 0);
        paises.push_back(pais);
    }

    archivo.close();
}

//Leer la informacion de las relaciones
void leerRelaciones(map<int, vector<int>>& relaciones) 
{
    ifstream file("Relaciones.txt");
    string line;

    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    while (getline(file, line)) {
        istringstream iss(line);
        int country_id;
        char delimiter;

        // Leer el ID del país
        if (!(iss >> country_id >> delimiter)) {
            continue; // Si no se puede leer el ID, ignora la línea
        }

        // Leer los IDs de los países adyacentes y almacenarlos en el vector
        string connection_ids;
        getline(iss, connection_ids);
        istringstream connection_stream(connection_ids);
        int id;
        
        // Leer cada ID de los países adyacentes separados por comas
        while (connection_stream >> id) {
            relaciones[country_id].push_back(id);
            if (connection_stream.peek() == ',') {
                connection_stream.ignore();
            }
        }
    }

    file.close();
}

//Guardar la informacion de la partida
void guardar(vector<Paises> paises, vector<Jugador> jugadores, string nombre_archivo)
{
    ofstream archivo(nombre_archivo);
    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    //Recorrer los jugadores
    for (int i = 0; i < jugadores.size(); i++)
    {
        //Guardar informacion de los jugadores
        archivo << jugadores[i].getNombre() << ",";
        archivo << jugadores[i].getTurno() << ",";
        archivo << jugadores[i].getId() << ",";
        archivo << jugadores[i].getTropas() << ",";

        int cant_paises = 0;

        for (int j = 0; j < paises.size(); j++)
        {
            if (paises[j].getId_jugador() == jugadores[i].getId())
            {
                cant_paises++;
            }
        }

        archivo << cant_paises << ",";

        for (int j = 0; j < paises.size(); j++)
        {
            if (paises[j].getId_jugador() == jugadores[i].getId())
            {
                archivo << paises[j].getId() << ",";
                archivo << paises[j].getEstado() << ",";
                archivo << paises[j].getId_jugador() << ",";
                archivo << paises[j].getEjercitos() << ",";
            }
        }

        archivo << endl;

    }


    archivo.close();
}

//Leer la informacion de la partida
void leerPartida(vector<Paises> &paises, vector<Jugador> &jugadores, string nombre_archivo)
{
    ifstream archivo(nombre_archivo);
    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo" << endl;
        return;
    }

    string nombre;
    int turno;
    int id;
    int tropas;
    int cant_paises;

    string line;
    while (getline(archivo, line)) 
    {
        vector<string> tokens;
        stringstream ss(line);
        string token;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        nombre = tokens[0];
        turno = stoi(tokens[1]);
        id = stoi(tokens[2]);
        tropas = stoi(tokens[3]);
        cant_paises = stoi(tokens[4]);

        Jugador jugador(nombre, turno, id, tropas);
        jugadores.push_back(jugador);

        for (int i = 0; i < cant_paises; i++)
        {
            int id_pais = stoi(tokens[5 + i * 4]);
            for (int j = 0; j < paises.size(); j++)
            {
                if (paises[j].getId() == id_pais)
                {
                    paises[j].setEstado(stoi(tokens[6 + i * 4]));
                    paises[j].setId_jugador(stoi(tokens[7 + i * 4]));
                    paises[j].setEjercitos(stoi(tokens[8 + i * 4]));
                }
            }
        }
        
    }
        

}


    
    //Inicio del juego
    int opcion= 0;

    while (opcion != 8)
    {
        menu();
        cin >> opcion;
        
        if (opcion == 1)
        {
            cout << "Bienvenido al juego de Risk" << endl << endl;
            cout << "Ingrese el numero de jugadores: ";
            int num_jugadores;
            cin >> num_jugadores;
            cout << "--------------------------------" << endl;


            int tropas;
            //Asignacion de las tropas
            if (num_jugadores == 2)
            {
                tropas = 40;
            }
            else if (num_jugadores == 3)
            {
                tropas = 35;
            }
            else if (num_jugadores == 4)
            {
                tropas = 30;
            }
            else if (num_jugadores == 5)
            {
                tropas = 25;
            }
            else if (num_jugadores == 6)
            {
                tropas = 20;
            }
            

            //Creacion de los jugadores
            for (int i = 0; i < num_jugadores; i++)
            {
                cout << "Jugador " << i + 1 << endl;
                string nombre;
                int turno= i + 1;
                cout << "Ingrese el nombre del jugador: ";
                cin >> nombre;
                Jugador jugador(nombre, turno, i + 1, tropas);
                jugadores.push_back(jugador);
                cout << "Turno: " << turno << endl;
                cout << "ID: " << i + 1 << endl;
                cout << "Tropas: " << tropas << endl;
                cout << "--------------------------------" << endl;
            }
            cout << endl;

            cout << "Se van a asignar los paises" << endl;
            cout << "En principio se va a asignar 1 tropa por pais" << endl;
            cout << "Luego se van a asignar las tropas restantes" << endl << endl;

            //Pedir un enter para continuar
            cout << "Presione enter para continuar...";
            cin.ignore();
            cin.get();


            //Asignacion de los paises
            int num_paises;
            num_paises = paises.size();
            while (num_paises > 0)
            {
                for (int i = 0; i < jugadores.size(); i++)
                {
                    cout << "Jugador: " << jugadores[i].getNombre() << endl;
                    cout << "Paises disponibles: " << endl;

                    //Imprimir los paises con estado 0
                    for (int j = 0; j < paises.size(); j++)
                    {
                        if (paises[j].getEstado() == 0)
                        {
                            cout << paises[j].getId() << ". " << paises[j].getNombre() << endl;
                        }
                    }

                    //Asignacion de los paises
                    int pais;
                    cout << "Ingrese el numero del pais que desea: ";
                    cin >> pais;
                    //Validacion del pais
                    while (paises[pais - 1].getEstado() != 0 || pais > paises.size())
                    {
                        cout << "El pais ya esta ocupado o no existe, ingrese otro: ";
                        cin >> pais;
                    }
                    paises[pais - 1].setEstado(1);
                    paises[pais - 1].setId_jugador(jugadores[i].getId());
                    jugadores[i].setTropas(jugadores[i].getTropas() - 1);
                    paises[pais - 1].setEjercitos(1);
                    num_paises--;
                    cout << "--------------------------------" << endl;   

                    if (num_paises == 0)
                    {
                        break;
                    } 
                }
            }

            cout << endl;
            cout << "Se van a asignar las tropas restantes" << endl;
            for (int i = 0; i < jugadores.size(); i++)
            {
                cout << "Jugador: " << jugadores[i].getNombre() << endl;
                cout << "Tropas restantes: " << jugadores[i].getTropas() << endl;
                cout << "Paises ocupados: " << endl;

                //Imprimir los paises
                for (int j = 0; j < paises.size(); j++)
                {
                    if (paises[j].getEstado() == 1 && paises[j].getId_jugador() == jugadores[i].getId())
                    {
                        cout << paises[j].getId() << ". " << paises[j].getNombre() << " (" << paises[j].getEjercitos() << ")" << endl;
                    }
                }

                while (jugadores[i].getTropas() > 0)
                {
                    //Asignacion de las tropas
                    int pais;
                    int tropas;
                    cout << "Ingrese el numero del pais al que desea asignar tropas: ";
                    cin >> pais;
                    //Validacion del pais
                    while (paises[pais - 1].getEstado() != 1 || paises[pais - 1].getId_jugador() != jugadores[i].getId() || pais > paises.size())
                    {
                        cout << "El pais no le pertenece, ingrese otro: ";
                        cin >> pais;
                    }
                    cout << "Ingrese el numero de tropas que desea asignar: ";
                    cin >> tropas;
                    //Validacion de las tropas
                    while (tropas > jugadores[i].getTropas())
                    {
                        cout << "No tiene suficientes tropas, ingrese otro numero: ";
                        cin >> tropas;
                    }
                    jugadores[i].setTropas(jugadores[i].getTropas() - tropas);
                    paises[pais - 1].setEjercitos(paises[pais - 1].getEjercitos() + tropas);
                    //Mostrar solo el pais que se modifico
                    cout << paises[pais - 1].getId() << ". " << paises[pais - 1].getNombre() << " (" << paises[pais - 1].getEjercitos() << ")" << endl;
                    cout << "Tropas restantes: " << jugadores[i].getTropas() << endl;
                }

                cout << "--------------------------------" << endl;
            }

            cout << "Listo, se ha terminado de asignar las tropas" << endl;
        }
        
        if (opcion == 2)
        {
            string nombre_archivo;
            cout << "Ingrese el nombre del archivo: ";
            cin >> nombre_archivo;
            guardar(paises, jugadores, nombre_archivo);
        }

        if (opcion ==3)
        {
            string nombre_archivo;
            cout << "Ingrese el nombre del archivo: ";
            cin >> nombre_archivo;
            leerPartida(paises, jugadores, nombre_archivo);
        }

        if (opcion == 4)
        {
            cout << "Parte 1" << endl;
            cout << "Digite el nombre del jugador: ";
            string nombre;
            cin >> nombre;

            //Buscar el jugador
            int id_jugador;
            for (int i = 0; i < jugadores.size(); i++)
            {
                if (jugadores[i].getNombre() == nombre)
                {
                    if (jugadores[i].getTurno() == 1)
                    {
                        cout << "Hola " << nombre << endl;

                        //Obtener y ubicar nuevas unidades de ejército

                        //Territorios
                        int cant_p = 0;
                        for (int j = 0; j < paises.size(); j++)
                        {
                            if (paises[j].getId_jugador() == jugadores[i].getId())
                            {
                                cant_p++;
                            }
                        }

                        int tropas = cant_p / 3;
                        if (tropas < 3)
                        {
                            tropas = 3;
                        }

                        //Continentes
                        int America_Norte = 0;
                        int America_Sur = 0;
                        int Europa = 0;
                        int Africa = 0;
                        int Asia = 0;
                        int Australia = 0;

                        for (int j = 0; j < paises.size(); j++)
                        {
                            if (paises[j].getId_jugador() == jugadores[i].getId())
                            {
                                if (paises[j].getContinente() == "América del Norte")
                                {
                                    America_Norte++;
                                }
                                else if (paises[j].getContinente() == "América del Sur")
                                {
                                    America_Sur++;
                                }
                                else if (paises[j].getContinente() == "Europa")
                                {
                                    Europa++;
                                }
                                else if (paises[j].getContinente() == "África")
                                {
                                    Africa++;
                                }
                                else if (paises[j].getContinente() == "Asia")
                                {
                                    Asia++;
                                }
                                else if (paises[j].getContinente() == "Australia")
                                {
                                    Australia++;
                                }
                            }
                        }
                       
                        if (America_Norte == 9)
                        {
                            tropas += 5;
                        }

                        if (America_Sur == 4)
                        {
                            tropas += 2;
                        }

                        if (Europa == 7)
                        {
                            tropas += 5;
                        }

                        if (Africa == 6)
                        {
                            tropas += 3;
                        }

                        if (Asia == 12)
                        {
                            tropas += 7;
                        }

                        if (Australia == 4)
                        {
                            tropas += 2;
                        }

                        cout << "Tropas Adicionales: " << tropas << endl;
                        jugadores[i].setTropas(jugadores[i].getTropas() + tropas);

                        //Imprimir los paises
                        cout << "Paises ocupados: " << endl;
                        for (int j = 0; j < paises.size(); j++)
                        {
                            if (paises[j].getEstado() == 1 && paises[j].getId_jugador() == jugadores[i].getId())
                            {
                                cout << paises[j].getId() << ". " << paises[j].getNombre() << " (" << paises[j].getEjercitos() << ")" << endl;
                            }
                        }

                        while (jugadores[i].getTropas() > 0)
                        {
                            //Asignacion de las tropas
                            int pais;
                            int tropas;
                            cout << "Ingrese el numero del pais al que desea asignar tropas: ";
                            cin >> pais;
                            //Validacion del pais
                            while (paises[pais - 1].getEstado() != 1 || paises[pais - 1].getId_jugador() != jugadores[i].getId() || pais > paises.size())
                            {
                                cout << "El pais no le pertenece, ingrese otro: ";
                                cin >> pais;
                            }
                            cout << "Ingrese el numero de tropas que desea asignar: ";
                            cin >> tropas;
                            //Validacion de las tropas
                            while (tropas > jugadores[i].getTropas())
                            {
                                cout << "No tiene suficientes tropas, ingrese otro numero: ";
                                cin >> tropas;
                            }
                            jugadores[i].setTropas(jugadores[i].getTropas() - tropas);
                            paises[pais - 1].setEjercitos(paises[pais - 1].getEjercitos() + tropas);
                            //Mostrar solo el pais que se modifico
                            cout << paises[pais - 1].getId() << ". " << paises[pais - 1].getNombre() << " (" << paises[pais - 1].getEjercitos() << ")" << endl;
                            cout << "Tropas restantes: " << jugadores[i].getTropas() << endl;
                        }

                        cout << "--------------------------------" << endl;
                    }
                    else
                    {
                        cout << "No es el turno del jugador" << endl;
                        break;
                    }
                }
            }
          
        }

        if (opcion == 5)
        {
            cout << "Parte 2" << endl;
            cout << "Digite el nombre del jugador: ";
            string nombre;
            cin >> nombre;

            //Buscar el jugador
            int id_jugador;
            for (int i = 0; i < jugadores.size(); i++)
            {
                if (jugadores[i].getNombre() == nombre)
                {
                    if (jugadores[i].getTurno() == 1)
                    {
                        
                        cout << "Paises ocupados: " << endl;
                        for (int j = 0; j < paises.size(); j++)
                        {
                            if (paises[j].getEstado() == 1 && paises[j].getId_jugador() == jugadores[i].getId())
                            {
                                cout << paises[j].getId() << ". " << paises[j].getNombre() << " (" << paises[j].getEjercitos() << ")" << endl;
                            }
                        }
                        cout << "Digite el id del pais desde el que desea atacar: ";
                        int id_pais;
                        cin >> id_pais;

                        //Validacion del pais
                        while (paises[id_pais - 1].getEstado() != 1 || paises[id_pais - 1].getId_jugador() != jugadores[i].getId() || id_pais > paises.size())
                        {
                            cout << "El pais no le pertenece, ingrese otro: ";
                            cin >> id_pais;
                        }

                        //Mostrar los paises adyacentes
                        cout << "Paises adyacentes que puede atacar: " << endl;
                        vector<int> lista_adyacentes;
                        for (int j = 0; j < relaciones.size(); j++)
                        {
                            if (j == id_pais-1)
                            {
                                vector<int> adyacentes = relaciones[j + 1];
                                //Mostrar los paises adyacentes que no le pertenecen
                                for (int k = 0; k < adyacentes.size(); k++)
                                {
                                    if (paises[adyacentes[k] - 1].getId_jugador() != jugadores[i].getId())
                                    {
                                        cout << paises[adyacentes[k] - 1].getId() << ". " << paises[adyacentes[k] - 1].getNombre() << " (" << paises[adyacentes[k] - 1].getEjercitos() << ")" << endl;
                                        lista_adyacentes.push_back(paises[adyacentes[k] - 1].getId());
                                    }
                                }
                            }
                        }

                        bool adyacente = false;

                        //Validacion del pais con el vector de adyacentes
                        int id_pais_atacado;
                        while (adyacente == false)
                        {
                            cout << "Digite el id del pais que desea atacar: ";
                            cin >> id_pais_atacado;
                            for (int j = 0; j < lista_adyacentes.size(); j++)
                            {
                                if (lista_adyacentes[j] == id_pais_atacado)
                                {
                                    adyacente = true;
                                }
                            }
                            if (adyacente == false)
                            {
                                cout << "Digito mal el pais, intente de nuevo" << endl;
                            }
                        }

                        //Ataque
                        cout << "Ataque" << endl;
                        cout << "Pais atacante: " << paises[id_pais - 1].getNombre() << " (" << paises[id_pais - 1].getEjercitos() << ")" << endl;
                        cout << "Pais atacado: " << paises[id_pais_atacado - 1].getNombre() << " (" << paises[id_pais_atacado - 1].getEjercitos() << ")" << endl;

                        //Dados
                        cout << "Sorteo de dados" << endl;
                        int dado_atacante_1= rand() % 6 + 1;
                        int dado_atacante_2= rand() % 6 + 1;
                        int dado_atacante_3= rand() % 6 + 1;
                        int dado_defensor_1= rand() % 6 + 1;
                        int dado_defensor_2= rand() % 6 + 1;

                        cout << "Dados atacante: " << dado_atacante_1 << ", " << dado_atacante_2 << ", " << dado_atacante_3 << endl;
                        cout << "Dados defensor: " << dado_defensor_1 << ", " << dado_defensor_2 << endl;

                        vector<int> dados_atacante= { dado_atacante_1, dado_atacante_2, dado_atacante_3 };
                        vector<int> dados_defensor= { dado_defensor_1, dado_defensor_2 };

                        //Ordenar los dados de mayor a menor con un for
                        for (int j = 0; j < dados_atacante.size(); j++)
                        {
                            for (int k = 0; k < dados_atacante.size() - 1; k++)
                            {
                                if (dados_atacante[k] < dados_atacante[k + 1])
                                {
                                    int temp = dados_atacante[k];
                                    dados_atacante[k] = dados_atacante[k + 1];
                                    dados_atacante[k + 1] = temp;
                                }
                            }
                        }

                        for (int j = 0; j < dados_defensor.size(); j++)
                        {
                            for (int k = 0; k < dados_defensor.size() - 1; k++)
                            {
                                if (dados_defensor[k] < dados_defensor[k + 1])
                                {
                                    int temp = dados_defensor[k];
                                    dados_defensor[k] = dados_defensor[k + 1];
                                    dados_defensor[k + 1] = temp;
                                }
                            }
                        }

                        //Eliminar el menor de los dados del atacante
                        dados_atacante.pop_back();

                        //Sumar los dados del atacante
                        int suma_atacante = 0;
                        for (int j = 0; j < dados_atacante.size(); j++)
                        {
                            suma_atacante += dados_atacante[j];
                        }

                        //sumar los dados del defensor
                        int suma_defensor = 0;
                        for (int j = 0; j < dados_defensor.size(); j++)
                        {
                            suma_defensor += dados_defensor[j];
                        }

                        //Comparar los dados
                        if (suma_atacante > suma_defensor)
                        {
                            cout << "El atacante gano" << endl;
                            paises[id_pais_atacado - 1].setEjercitos(paises[id_pais_atacado - 1].getEjercitos() - 1);
                            cout << "Pais atacado: " << paises[id_pais_atacado - 1].getNombre() << " (" << paises[id_pais_atacado - 1].getEjercitos() << ")" << endl;
                            if (paises[id_pais_atacado - 1].getEjercitos() == 0)
                            {
                                cout << "El pais ha sido conquistado" << endl;
                                paises[id_pais_atacado - 1].setId_jugador(jugadores[i].getId());
                            }
                        }

                        else
                        {
                            cout << "El defensor gano" << endl;
                            paises[id_pais - 1].setEjercitos(paises[id_pais - 1].getEjercitos() - 1);
                        }
                    

                    }

                }

            }
        }

        if (opcion ==6)
        {
            cout << "Fortificar la posicion" << endl;
            cout << "Solo se puede fortificar una vez por turno" << endl;
            cout << "Parte 2" << endl;
            cout << "Digite el nombre del jugador: ";
            string nombre;
            cin >> nombre;

            //Buscar el jugador
            int id_jugador;
            for (int i = 0; i < jugadores.size(); i++)
            {
                if (jugadores[i].getNombre() == nombre)
                {
                    if (jugadores[i].getTurno() == 1)
                    {
                        cout << "Paises ocupados: " << endl;
                        for (int j = 0; j < paises.size(); j++)
                        {
                            if (paises[j].getEstado() == 1 && paises[j].getId_jugador() == jugadores[i].getId())
                            {
                                cout << paises[j].getId() << ". " << paises[j].getNombre() << " (" << paises[j].getEjercitos() << ")" << endl;
                            }
                        }

                        cout << "Digite el id del pais desde el que desea mover: ";
                        int id_pais;
                        cin >> id_pais;

                        //Validacion del pais
                        while (paises[id_pais - 1].getEstado() != 1 || paises[id_pais - 1].getId_jugador() != jugadores[i].getId() || id_pais > paises.size())
                        {
                            cout << "El pais no le pertenece, ingrese otro: ";
                            cin >> id_pais;
                        }

                        //Mostrar los paises adyacentes
                        cout << "Paises adyacentes a los que puede mover: " << endl;
                        vector<int> lista_adyacentes;
                        for (int j = 0; j < relaciones.size(); j++)
                        {
                            if (j == id_pais-1)
                            {
                                vector<int> adyacentes = relaciones[j + 1];
                                //Mostrar los paises adyacentes que no le pertenecen
                                for (int k = 0; k < adyacentes.size(); k++)
                                {
                                    if (paises[adyacentes[k] - 1].getId_jugador() == jugadores[i].getId())
                                    {
                                        cout << paises[adyacentes[k] - 1].getId() << ". " << paises[adyacentes[k] - 1].getNombre() << " (" << paises[adyacentes[k] - 1].getEjercitos() << ")" << endl;
                                        lista_adyacentes.push_back(paises[adyacentes[k] - 1].getId());
                                    }
                                }
                            }
                        }
                        
                        if (lista_adyacentes.size() == 0)
                        {
                            cout << "No tiene paises adyacentes para mover" << endl;
                            break;
                        }

                        bool adyacente = false;

                        //Validacion del pais con el vector de adyacentes
                        int id_pais_2;
                        while (adyacente == false)
                        {
                            cout << "Digite el id del pais al que desea mover: ";
                            cin >> id_pais_2;
                            for (int j = 0; j < lista_adyacentes.size(); j++)
                            {
                                if (lista_adyacentes[j] == id_pais_2)
                                {
                                    adyacente = true;
                                }
                            }
                            if (adyacente == false)
                            {
                                cout << "Digito mal el pais, intente de nuevo" << endl;
                            }
                        }

                        //Mover las tropas
                        cout << "Digite el numero de tropas que desea mover: ";
                        int tropas;
                        cin >> tropas;
                        //Validacion de las tropas
                        while (tropas > paises[id_pais - 1].getEjercitos())
                        {
                            cout << "No tiene suficientes tropas, ingrese otro numero: ";
                            cin >> tropas;
                        }

                        paises[id_pais - 1].setEjercitos(paises[id_pais - 1].getEjercitos() - tropas);
                        paises[id_pais_2 - 1].setEjercitos(paises[id_pais_2 - 1].getEjercitos() + tropas);

                        cout << "Cambios" << endl;
                        cout << "Pais: " << paises[id_pais - 1].getNombre() << " (" << paises[id_pais - 1].getEjercitos() << ")" << endl;
                        cout << "Pais: " << paises[id_pais_2 - 1].getNombre() << " (" << paises[id_pais_2 - 1].getEjercitos() << ")" << endl;




                    }

                }
            }

        }

    }



    return 0;
}