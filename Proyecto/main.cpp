#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "Paises.h"
#include "Jugador.h"
#include "ArbolHuffman.h"
#include "Grafo.h"
#include "Ayuda.h"
#include "Tarjeta.h"

using namespace std;

// Funcion para Ayuda
void menu_ayuda()
{
    cout << "Comandos disponibles" <<endl;
    cout << "1: inicializar" <<endl;
    cout << "2: turno" <<endl;
    cout << "3: guardar" <<endl;
    cout << "4: guardar_comprimido" <<endl;
    cout << "5: inicializar _nombre_archivo" <<endl;
    cout << "6: costo_conquista" <<endl;
    cout << "7: conquista_mas_barata" <<endl;

    cout << "Para mayor ayuda escriba: ayuda <comando>" <<endl;
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

        //Guardar informacion de los paises

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

        //Guardar informacion de las tarjetas
        set <int> set_tarjetas = jugadores[i].getTarjetas();

        archivo << set_tarjetas.size() << ",";
        for (set<int>::iterator it=set_tarjetas.begin(); it!=set_tarjetas.end(); ++it)
        {
            archivo << *it << ",";
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

        int cant_tarjetas = stoi(tokens[5 + cant_paises * 4]);

        for (int i = 0; i < cant_tarjetas; i++)
        {
            int id_tarjeta = stoi(tokens[6 + cant_paises * 4 + i]);
            jugador.agregarTarjeta(id_tarjeta);
        }
        
    }
        

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


//Huffman
void construir_arbol(string nombreArchivo, string nombreArchivoBinario)
{
    ArbolHuffman arbol;
    ifstream archivo(nombreArchivo);
    string texto((istreambuf_iterator<char>(archivo)), istreambuf_iterator<char>());
    arbol.construirArbol(texto);
    arbol.codificar();
    cout << "----------------------------------------" << endl;
    cout << "Árbol de Huffman creado con éxito." << endl;

    /*

    cout << "Códigos Huffman son:\n" << endl;
    for (auto& par : arbol.codigoHuffman) {
        cout << par.first << " " << par.second << endl;
    }

    cout << "\nEl string original es:\n" << texto << endl;

    */

    string strCodificada;
    for (char ch : texto) {
        strCodificada += arbol.codigoHuffman[ch];
    }

    /*

    cout << "\nEl string codificado es:\n" << strCodificada << endl;

    cout << "\n----------------------------------------\n";

    */
    
    arbol.guardarEnArchivoBinario(strCodificada, nombreArchivoBinario);
    cout << "Árbol de Huffman guardado en archivo binario." << endl;
    
}

pair< map<int,int>, string > leerBinario(const string& nombreArchivo) 
{
    ifstream archivo(nombreArchivo, ios::binary);

    //Guarda toda la información del archivo en un string
    string str((istreambuf_iterator<char>(archivo)), istreambuf_iterator<char>());

    //n
    string n = str.substr(0, 16);
    bitset<16> twoByteRepresentation(n);
    int value = twoByteRepresentation.to_ulong();
    //cout << "n: " << value << endl;
    str.erase(0, 16);

    //ci y fi
    map<int, int> frecuencias;
    for (int i = 0; i < value; i++) {
        string ascii = str.substr(0, 8);
        bitset<8> asciiBit(ascii);
        int asciiInt = asciiBit.to_ulong();
        str.erase(0, 8);

        string freq = str.substr(0, 64);
        bitset<64> freqBit(freq);
        int freqInt = freqBit.to_ulong();
        str.erase(0, 64);

        frecuencias[asciiInt] = freqInt;
    }

    /*
    for (auto& par : frecuencias) {
        cout << "ascii: " << par.first << ", freq: " << par.second << endl;
    }
    */

    //w
    string w = str.substr(0, 64);
    bitset<64> wBit(w);
    int wInt = wBit.to_ulong();
    //cout << "w: " << wInt << endl;
    str.erase(0, 64);

    //binary_code
    //cout << "binary_code: " << str << endl;

    archivo.close();

    return make_pair(frecuencias, str);
}

void cargar_arbol(string nombreArchivo)
{
    
    cout << "----------------------------------------\n";
    pair < map<int,int>, string > resultado = leerBinario(nombreArchivo);
    ArbolHuffman arbol;
    map<int, int> frecuencias = resultado.first;
    string strCodificada = resultado.second;
    arbol.reconstruirArbol(frecuencias);
    cout << "Árbol de Huffman cargado desde archivo binario.\n";
    cout << "Decodificando...\n";
    arbol.decodificar(strCodificada);
}


int main()
{
    //Variables
    vector<Paises> paises;
    map<int, vector<int>> relaciones;
    vector<Jugador> jugadores;
    vector<Tarjeta> tarjetas;
    int intercambios = 0;
    string command;

    //Lectura de los archivos
    leerPaises(paises);
    leerRelaciones(relaciones);


    while (true)
    {
        cout << "$ ";
        getline(cin, command);

        istringstream iss(command);
        vector<string> tokens;
        string token;
        while (iss >> token)
        {
            tokens.push_back(token);
        }

        if (!tokens.empty())
        {
            //Componente 1: configuración del juego

            if (tokens[0] == "inicializar")
            {
                
                if (tokens.size() == 1)
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
                    

                        cout << "Listo, se ha terminado de asignar las tropas" << endl;
                
                        
                            
                    }

                    cout << endl;
                    //limpiar el buffer
                    cin.ignore();
                }

                else if (tokens.size() == 2)
                {
                    string nombre_archivo = tokens[1];
                    //Partir el nombre del archivo por un separador
                    vector<string> tokens_archivo;
                    stringstream ss(nombre_archivo);
                    string token_archivo;
                    while (getline(ss, token_archivo, '.'))
                    {
                        tokens_archivo.push_back(token_archivo);
                    }

                    if (tokens_archivo[1] == "txt")
                    {
                        cout << "Archivo con extension .txt" << endl;
                        leerPartida(paises, jugadores, nombre_archivo);
                    }

                    else if (tokens_archivo[1] == "bin")
                    {
                        cout << "Archivo con extension .bin" << endl;
                        cargar_arbol(nombre_archivo);
                        leerPartida(paises, jugadores, "Decodificado.txt");
                    }

                    else
                    {
                        cout << "Comando 'inicializar' mal ejecutado" << endl;
                    }
                    
                }

                else
                {
                    cout << "Comando 'inicializar' mal ejecutado" << endl;
                }

            }

            else if (tokens[0] == "turno")
            {
                if (tokens.size() == 2)
                {
                    if (jugadores.size() == 0)
                    {
                        cout << "No se ha inicializado el juego." << endl;
                    }

                    else
                    {
                        
                        bool turno = false;
                        for (int i = 0; i < jugadores.size(); i++)
                        {
                            if (jugadores[i].getNombre() == tokens[1])
                            {

                                if (jugadores[i].getTurno() == 1)
                                {
                                    turno = true;

                                    //Obtener y ubicar nuevas unidades de ejército
                                    if (1 == 1)
                                    {

                                        cout << "Hola " << jugadores[i].getNombre() << endl;

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

                                        //Tarjetas
                                        set <int> set_tarjetas = jugadores[i].getTarjetas();
                                        int cant_tarjetas = set_tarjetas.size();
                                        if (cant_tarjetas >= 3)
                                        {
                                            intercambios++;
                                            tropas += intercambios * 5;

                                            //Cambiar el estado de las tarjetas
                                            for (int j = 0; j < tarjetas.size(); j++)
                                            {
                                                for (set<int>::iterator it=set_tarjetas.begin(); it!=set_tarjetas.end(); ++it)
                                                {
                                                    if (tarjetas[j].getID() == *it)
                                                    {
                                                        tarjetas[j].setEstado(0);
                                                    }
                                                }
                                            }

                                            jugadores[i].eliminarTarjetas();

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

                                       
                                    }
                                
                                    cout << "--------------------------------" << endl;

                                    //Atacar
                                    if (2 == 2)
                                    {                           
                                        cout << "Quieres atacar?" << endl;
                                        cout << "1. Si" << endl;
                                        cout << "2. No" << endl;
                                        int opcion;
                                        cin >> opcion;
                                        //Validacion de la opcion
                                        while (opcion != 1 && opcion != 2)
                                        {
                                            cout << "Digito mal, intente de nuevo: ";
                                            cin >> opcion;
                                        }


                                        while (opcion == 1)
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
                                                    //Agregar una tarjeta
                                                    int id_tarjeta = rand() % 42 + 1;
                                                    
                                                    jugadores[i].agregarTarjeta(id_tarjeta);
                                                    cout << "Se ha agregado una tarjeta" << endl;
                                                    //Cambiar el estado de la tarjeta
                                                    for (int j = 0; j < tarjetas.size(); j++)
                                                    {
                                                        if (tarjetas[j].getID() == id_tarjeta)
                                                        {
                                                            tarjetas[j].setEstado(1);
                                                        }
                                                    }

                                                }
                                            }

                                            else
                                            {
                                                cout << "El defensor gano" << endl;
                                                paises[id_pais - 1].setEjercitos(paises[id_pais - 1].getEjercitos() - 1);
                                            }

                                            cout << "Quieres atacar?" << endl;
                                            cout << "1. Si" << endl;
                                            cout << "2. No" << endl;
                                            cin >> opcion;

                                            while (opcion != 1 && opcion != 2)
                                            {
                                                cout << "Digito mal, intente de nuevo: ";
                                                cin >> opcion;
                                            }

                                            if (opcion == 2)
                                            {
                                                break;
                                            }
                                        }
                                        
                                    }

                                    cout << "--------------------------------" << endl;

                                    //Fortificar la posición
                                    if (3 == 3)
                                    {
                                        cout << "Fortificar la posicion" << endl;
                                        cout << "Solo se puede fortificar una vez por turno" << endl;
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
                                        
                                        while (lista_adyacentes.size() == 0)
                                        {
                                            cout << "No tiene paises adyacentes para mover, vuelva a intentar" << endl;
                                            cout << "Digite el id del pais desde el que desea mover: ";
                                            cin >> id_pais;

                                            //Validacion del pais
                                            while (paises[id_pais - 1].getEstado() != 1 || paises[id_pais - 1].getId_jugador() != jugadores[i].getId() || id_pais > paises.size())
                                            {
                                                cout << "El pais no le pertenece, ingrese otro: ";
                                                cin >> id_pais;
                                            }

                                            //Mostrar los paises adyacentes
                                            cout << "Paises adyacentes a los que puede mover: " << endl;
                                            //Limpiar el vector
                                            lista_adyacentes.clear();
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

                                            if (lista_adyacentes.size() > 0)
                                            {
                                                break;
                                            }
                                
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

                                    cout << "--------------------------------" << endl;

                                    //Cambiar de turno
                                    if (4 == 4)
                                    {
                                        cout << "Cambio de turno" << endl;
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
                                    }
                                    
                                    cout << "--------------------------------" << endl;

                                    //limpiar el buffer
                                    cin.ignore();
                                    
                                    break;
                                }

                            }
                        
                        }

                        if (turno == false)
                        {
                            cout << "El jugador no existe o no es su turno." << endl;
                        }
    

                        

                    }
              
                }

                else
                {
                    cout << "Comando 'turno' incompleto. Debe proporcionar un <id_jugador>." << endl;
                }

              
            }

            else if (tokens[0] == "salir")
            {
                if (tokens.size() > 1)
                {
                    cout << "El comando 'salir' no debe tener argumentos adicionales." << endl;
                }
                else
                {
                    cout << "Comando 'salir' ingresado." << endl;
                    break;
                }
            }

            //Componente 2: almacenamiento de partidas

            else if (tokens[0] == "guardar")
            {
                if (tokens.size() == 2)
                {
                    //Guardar la informacion de la partida
                    guardar(paises, jugadores, tokens[1]);
                }
                else
                {
                    cout << "Comando 'guardar' incompleto. Debe proporcionar un archivo." << endl;
                }
            }

            else if (tokens[0] == "guardar_comprimido")
            {
                if (tokens.size() == 2)
                {
                    //Guardar la informacion de la partida
                    guardar(paises, jugadores, "Alterno.txt");
                    construir_arbol("Alterno.txt", tokens[1]);

                }
                else
                {
                    cout << "Comando 'guardar_comprimido' incompleto. Debe proporcionar un archivo." << endl;
                }
            }



            //Componente 3: estrategias de juego

            else if (tokens[0] == "costo_conquista")
            {
                if (tokens.size() == 2)
                {
                    string territorio = tokens[1];
                    cout << "Comando 'costo_conquista' ingresado para:" << territorio << endl;

                    Grafo<string> grafo;
                    //Agregar los nodos
                    for (int i = 0; i < paises.size(); i++)
                    {
                        grafo.agregarNodo(paises[i].getNombre());
                    }

                    //Agregar las aristas
                    for (int i = 0; i < relaciones.size(); i++)
                    {
                        vector<int> adyacentes = relaciones[i + 1];
                        for (int j = 0; j < adyacentes.size(); j++)
                        {
                            grafo.agregarArista(paises[i].getNombre(), paises[adyacentes[j] - 1].getNombre(), paises[adyacentes[j] - 1].getEjercitos());
                        }
                    }

                    grafo.imprimirVecinosEntrantes(territorio);

                    
                }
                else
                {
                    cout << "Comando 'costo_conquista' incompleto. Debe proporcionar un territorio." << endl;
                }
            }

            else if (tokens[0] == "conquista_mas_barata")
            {
                if (tokens.size() > 1)
                {
                    cout << "El comando 'conquista_mas_barata' no debe tener argumentos adicionales." << endl;
                }
                else
                {
                    cout << "Comando 'conquista_mas_barata' ingresado." << endl;
                }
            } 

            //Ayuda

            /*
            
            else if (tokens[0] == "ayuda")
            {
                if (tokens.size() > 3)
                {
                    cout << "El comando 'ayuda' no debe tener argumentos adicionales." << endl;
                }
                else
                {
                    if (tokens.size() == 1)
                    {
                        menu_ayuda();
                    }
                    
                    else if (tokens[1] == "inicializar") 
                    {
                        inicializar();
                    } 
                    
                    else if (tokens[1] == "turno") 
                    {
                        turno();
                    } 

                    else if (tokens[1] == "guardar")  
                    {
                        guardar();
                    } 

                    else if (tokens[1] == "guardar_comprimido") 
                    {
                        guardar_comprimido();
                    } 

                    else if (tokens[1] == "inicializar_nombre_archivo")  
                    {
                        inicializar_nombre_archivo();
                    } 

                    else if (tokens[1] == "costo_conquista") 
                    {
                        costo_conquista();
                    } 

                    else if (tokens[1] == "conquista_mas_barata")
                    {
                        conquista_mas_barata();
                    } 

                    else
                    {
                        cout << " Digito mal,Bye :)" <<endl;
                    }

                }
            }
            
            */

            //Comprobar
            else
            {
                cout << "Comando no reconocido." << endl;
            }
        

        }
    }

    return 0;

}