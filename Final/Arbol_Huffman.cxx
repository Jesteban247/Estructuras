#include "Arbol_Huffman.h"

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
 
