#ifndef Arbol_Huffman_H
#define Arbol_Huffman_H

#include "Nodo_Huffman.h"
#include <map>
#include <queue>
#include <unordered_map>
#include <fstream>

#define EMPTY_STRING ""

// Estructura de datos para almacenar un nodo de árbol
struct HuffmanResult {
    Node* root;
    map<char, int> huffmanCodes;
};


// Función para asignar un nuevo nodo de árbol
Node* getNode(char ch, int freq, Node* left, Node* right);
 
// Objeto de comparación que se usará para ordenar el heap
//struct comp

// Función de utilidad para verificar si Huffman Tree contiene solo un solo nodo
bool isLeaf(Node* root);

// Atraviesa el árbol de Huffman y almacena los códigos de Huffman en un mapa.
void encode(Node* root, string str, unordered_map<char, string> &huffmanCode);
 
// Atraviesa el árbol de Huffman y decodifica la string codificada
void decode(Node* root, int &index, string str, ofstream &archivo);
 
// Construye Huffman Tree y decodifica el texto de entrada dado
HuffmanResult buildHuffmanTree(string text);
 
//Códigos Huffman
string Huffman_codes(Node *root, string text);

void decode_Huffman(Node *root, string str);

// Construye Huffman Tree y decodifica el texto de entrada dado
Node* buildHuffmanTree(map<char, int> freq);

#endif
