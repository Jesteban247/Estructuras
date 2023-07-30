#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

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

            
            //Comprobar

            else
            {
                cout << "Comando no reconocido." << endl;
            }

        }
    }

    return 0;
}
