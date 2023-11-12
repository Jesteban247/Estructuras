#include <iostream>
#include <fstream>
#include "ArbolHuffman.h"

pair< map<int,int>, string > leerBinario(const string& nombreArchivo) 
{
    ifstream archivo(nombreArchivo, ios::binary);

    //Guarda toda la información del archivo en un string
    string str((istreambuf_iterator<char>(archivo)), istreambuf_iterator<char>());

    //n
    string n = str.substr(0, 16);
    bitset<16> twoByteRepresentation(n);
    int value = twoByteRepresentation.to_ulong();
    cout << "n: " << value << endl;
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

    for (auto& par : frecuencias) {
        cout << "ascii: " << par.first << ", freq: " << par.second << endl;
    }

    //w
    string w = str.substr(0, 64);
    bitset<64> wBit(w);
    int wInt = wBit.to_ulong();
    cout << "w: " << wInt << endl;
    str.erase(0, 64);

    //binary_code
    cout << "binary_code: " << str << endl;

    archivo.close();

    return make_pair(frecuencias, str);
}


int main() 
{
    ArbolHuffman arbol;
    int opcion;
    string nombreArchivo;

    do {
        cout << "1. Crear Árbol de Huffman desde archivo de texto\n";
        cout << "2. Cargar Árbol de Huffman desde archivo binario\n";
        cout << "3. Salir\n";
        cout << "Ingrese su opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                cout << "Ingrese el nombre del archivo de texto: ";
                cin >> nombreArchivo;
                ifstream archivo(nombreArchivo);
                string texto((istreambuf_iterator<char>(archivo)), istreambuf_iterator<char>());
                arbol.construirArbol(texto);
                arbol.codificar();
                cout << "----------------------------------------\n";
                cout << "Árbol de Huffman creado con éxito.\n";

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

                cout << "\nLa string codificada es:\n" << strCodificada << endl;

                cout << "\n----------------------------------------\n";

                cout << "Ingrese el nombre del archivo binario para guardar: ";
                cin >> nombreArchivo;

                */
                
                arbol.guardarEnArchivoBinario(strCodificada, nombreArchivo);
                cout << "Árbol de Huffman guardado en archivo binario.\n";

                break;
            }
             
            case 2: {
                cout << "Ingrese el nombre del archivo binario para cargar: ";
                cin >> nombreArchivo;
                cout << "----------------------------------------\n";
                pair < map<int,int>, string > resultado = leerBinario(nombreArchivo);
                cout << "----------------------------------------\n";
                ArbolHuffman arbol2;
                map<int, int> frecuencias = resultado.first;
                string strCodificada = resultado.second;
                arbol2.reconstruirArbol(frecuencias);
                cout << "Árbol de Huffman cargado desde archivo binario.\n";
                cout << "Decodificando...\n";
                arbol2.decodificar(strCodificada);
                
                break;
            }
            case 3:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción no válida, intente de nuevo.\n";
        }
    } while (opcion != 3);

    return 0;
}
