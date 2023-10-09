#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <map>
#include <fstream>
using namespace std;
 
#define EMPTY_STRING ""


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
void decode(Node* root, int &index, string str)
{
    if (root == nullptr) {
        return;
    }
 
    // encontrado un nodo hoja
    if (isLeaf(root))
    {
        cout << root->ch;
        return;
    }
 
    index++;
 
    if (str[index] == '0') {
        decode(root->left, index, str);
    }
    else {
        decode(root->right, index, str);
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
 
    cout << "\nThe original string is:\n" << text << endl;
 
    // Imprimir string codificada
    string str;
    for (char ch: text) {
        str += huffmanCode[ch];
    }
 
    cout << "\nThe encoded string is:\n" << str << endl;

    return str;
}

void decode_Huffman(Node *root, string str)
{
    cout << "\nThe decoded string is:\n";
 
    if (isLeaf(root))
    {
        // Caso especial: Para entradas como a, aa, aaa, etc.
        while (root->freq--) {
            cout << root->ch;
        }
    }
    else {
        // Atraviesa el árbol Huffman de nuevo y esta vez,
        // decodifica la string codificada
        int index = -1;
        while (index < (int)str.size() - 1) {
            decode(root, index, str);
        }
    }

    cout << endl;
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
 

// Implementación del algoritmo de codificación de Huffman en C++
int main()
{
    cout << "Codificación de Huffman" << endl;
    string filename = "input.txt";  // Nombre del archivo de entrada
    string text = readFromFile(filename);  // Leer contenido del archivo

    HuffmanResult result = buildHuffmanTree(text);
    Node* root = result.root;
    map<char, int> huffmanCodes = result.huffmanCodes;

    string str = Huffman_codes(root, text);

    cout << "\nSerialización y deserialización de un mapa" << endl;
    // Serializar el mapa
    SerializeMap(huffmanCodes, "data.bin");
    // Deserializar el mapa
    map<char, int> loaded_freq = DeserializeMap("data.bin");

    Node *root2 = buildHuffmanTree(loaded_freq);
    decode_Huffman(root2, str);


    return 0;
}