#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <limits>
#include "ayuda.h"

using namespace std;

int menu_ayuda()
{
    cout << "Ayda" <<endl;
    cout << "1: inicializar" <<endl;
    cout << "2: turno" <<endl;
    cout << "3: guardar" <<endl;
    cout << "4: guardar_comprimido" <<endl;
    cout << "5: inicializar _nombre_archivo" <<endl;
    cout << "6: costo_conquista" <<endl;
    cout << "7: conquista_mas_barata" <<endl;
    cout << "8: salir" <<endl;

    cout << "Que quiere ver:";
    int respuesta;
    cin >> respuesta;

    return respuesta;
}


int main()
{
    string command;

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
                    cout << "Comando 'inicializar' ingresado." << endl;
                }

                //Componente 2: almacenamiento de partidas

                else if (tokens.size() == 2)
                {
                    string archivo = tokens[1];
                    cout << "Comando 'inicializar' ingresado para:" << archivo << endl;
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
                    string id_jugador = tokens[1];
                    cout << "Comando 'turno' ingresado para el jugador: " << id_jugador << endl;
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
                    string archivo = tokens[1];
                    cout << "Comando 'guardar' ingresado para:" << archivo << endl;
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
                    string archivo = tokens[1];
                    cout << "Comando 'guardar_comprimido' ingresado para:" << archivo << endl;
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

            else if (tokens[0] == "ayuda")
            {
                if (tokens.size() > 1)
                {
                    cout << "El comando 'ayuda' no debe tener argumentos adicionales." << endl;
                }
                else
                {
                    int ans;
                    ans= menu_ayuda();
                    if (ans == 1) 
                    {
                        inicializar();
                    } 
                    
                    else if (ans == 2) 
                    {
                        turno();
                    } 

                    else if (ans == 3) 
                    {
                        guardar();
                    } 

                    else if (ans == 4) 
                    {
                        guardar_comprimido();
                    } 

                    else if (ans == 5) 
                    {
                        inicializar_nombre_archivo();
                    } 

                    else if (ans == 6) 
                    {
                        costo_conquista();
                    } 

                    else if (ans == 7) 
                    {
                        conquista_mas_barata();
                    } 

                    else if (ans == 8)
                    {
                        cout << "Bye :)" <<endl;
                    }

                    else 
                    {
                        cout << "ans no es igual a ningún número del 1 al 8" << std::endl;
                    }

                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            
            //Comprobar
            else
            {
                cout << "Comando no reconocido." << endl;
            }
        }
    }

    return 0;
}
