#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <bitset>

#include "Pais.h"
#include "Jugador.h"
using namespace std;

#define EMPTY_STRING ""

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


// Arbol Huffman


// Un nodo de árbol
struct Node
{
    char ch;
    int freq;
    Node *left, *right;
};
 
// Estructura de datos para almacenar un nodo de árbol
struct HuffmanResult {
    Node* root;
    map<char, int> huffmanCodes;
};

// Función para asignar un nuevo nodo de árbol
Node* getNode(char ch, int freq, Node* left, Node* right)
{
    Node* node = new Node();
 
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
 
    return node;
}
 
// Objeto de comparación que se usará para ordenar el heap
struct comp
{
    bool operator()(const Node* l, const Node* r) const
    {
        // el elemento de mayor prioridad tiene la menor frecuencia
        return l->freq > r->freq;
    }
};
 
// Función de utilidad para verificar si Huffman Tree contiene solo un solo nodo
bool isLeaf(Node* root) {
    return root->left == nullptr && root->right == nullptr;
}
 
// Atraviesa el árbol de Huffman y almacena los códigos de Huffman en un mapa.
void encode(Node* root, string str, unordered_map<char, string> &huffmanCode)
{
    if (root == nullptr) {
        return;
    }
 
    // encontrado un nodo hoja
    if (isLeaf(root)) {
        huffmanCode[root->ch] = (str != EMPTY_STRING) ? str : "1";
    }
 
    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}
 
// Atraviesa el árbol de Huffman y decodifica la string codificada
void decode(Node* root, int &index, string str, ofstream &archivo)
{
    if (root == nullptr) {
        return;
    }
 
    // encontrado un nodo hoja
    if (isLeaf(root))
    {
        //cout << root->ch;
        archivo << root->ch;
        return;
    }
 
    index++;
 
    if (str[index] == '0') {
        decode(root->left, index, str, archivo);
    }
    else {
        decode(root->right, index, str, archivo);
    }
}
 
// Construye Huffman Tree y decodifica el texto de entrada dado
HuffmanResult buildHuffmanTree(string text)
{
    // caso base: string vacía
    if (text == EMPTY_STRING) {
        return HuffmanResult{nullptr, {}};
    }
 
    // cuenta la frecuencia de aparición de cada personaje
    // y almacenarlo en un mapa
    map<char, int> freq;
    for (char ch: text) {
        freq[ch]++;
    }

    /*
    //Muestra el unorder_map
    cout << "Unorder_map: " << endl;
    for (auto pair: freq) {
        cout << pair.first << " " << pair.second << endl;
    }
    */
 
    // Crear una cola de prioridad para almacenar nodos en vivo del árbol de Huffman
    priority_queue<Node*, vector<Node*>, comp> pq;
 
    // Crea un nodo hoja para cada carácter y añádelo
    // a la cola de prioridad.
    for (auto pair: freq) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }
 
    // hacer hasta que haya más de un nodo en la queue
    while (pq.size() != 1)
    {
        // Elimina los dos nodos de mayor prioridad
        // (la frecuencia más baja) de la queue
 
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top();    pq.pop();
 
        // crea un nuevo nodo interno con estos dos nodos como hijos y
        // con una frecuencia igual a la suma de las frecuencias de los dos nodos.
        // Agregar el nuevo nodo a la cola de prioridad.
 
        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }
 
    // `root` almacena el puntero a la raíz de Huffman Tree
    Node* root = pq.top();
 
    return HuffmanResult{root, freq};

}
 
//Códigos Huffman
string Huffman_codes(Node *root, string text)
{
    // Atraviesa el árbol Huffman y almacena códigos Huffman
    // en un mapa. Además imprímelos
    unordered_map<char, string> huffmanCode;
    encode(root, EMPTY_STRING, huffmanCode);
 
    /*
    cout << "Huffman Codes are:\n" << endl;
    for (auto pair: huffmanCode) {
        cout << pair.first << " " << pair.second << endl;
    }
    */
 
    //cout << "\nThe original string is:\n" << text << endl;
 
    // String codificada
    string str;
    for (char ch: text) {
        str += huffmanCode[ch];
    }
 
    //cout << "\nThe encoded string is:\n" << str << endl;

    return str;
}

void decode_Huffman(Node *root, string str)
{
    //Abre un archivo txt llamado "Decodificado.txt"
    ofstream archivo("Decodificado.txt");


    //cout << "\nThe decoded string is:\n";
 
    if (isLeaf(root))
    {
        // Caso especial: Para entradas como a, aa, aaa, etc.
        while (root->freq--) {
            //cout << root->ch;
            archivo << root->ch;
        }
    }
    else {
        // Atraviesa el árbol Huffman de nuevo y esta vez,
        // decodifica la string codificada
        int index = -1;
        while (index < (int)str.size() - 1) {
            decode(root, index, str, archivo);
        }
    }

    archivo.close();
}

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

// Construye Huffman Tree y decodifica el texto de entrada dado
Node* buildHuffmanTree(map<char, int> freq)
{
   
    // Crear una cola de prioridad para almacenar nodos en vivo del árbol de Huffman
    priority_queue<Node*, vector<Node*>, comp> pq;
 
    // Crea un nodo hoja para cada carácter y añádelo
    // a la cola de prioridad.
    for (auto pair: freq) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }
 
    // hacer hasta que haya más de un nodo en la queue
    while (pq.size() != 1)
    {
        // Elimina los dos nodos de mayor prioridad
        // (la frecuencia más baja) de la queue
 
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top();    pq.pop();
 
        // crea un nuevo nodo interno con estos dos nodos como hijos y
        // con una frecuencia igual a la suma de las frecuencias de los dos nodos.
        // Agregar el nuevo nodo a la cola de prioridad.
 
        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }
 
    // `root` almacena el puntero a la raíz de Huffman Tree
    Node* root = pq.top();
 
    return root;
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
                cout << "-------------------------" << endl;
            }
            

        }

        opcion = menu();
    }





    return 0;
}
