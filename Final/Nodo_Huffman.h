#ifndef Nodo_Huffman_H
#define Nodo_Huffman_H

#include <iostream>
#include <string>
using namespace std;

// Un nodo de árbol
struct Node
{
    char ch;
    int freq;
    Node *left, *right;
};

#endif
