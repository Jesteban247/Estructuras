#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <time.h>

#include "Help.h"
#include "Country.h"
#include "Data.h"
#include "Player.h"

using namespace std;

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

//Load Info.csv
list <Country> load_countries()
{
    list <Country> countries;
    ifstream file("Info.csv");
    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        vector<string> tokens;
        string token;
        while (getline(iss, token, ','))
        {
            tokens.push_back(token);
        }
        Country country(tokens[0], stoi(tokens[1]), tokens[2]);
        countries.push_back(country);
    }
    file.close();
    return countries;
}

//Load Data.csv
list <Data> load_data()
{
    list <Data> data;
    ifstream file("Data.csv");
    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        vector<string> tokens;
        string token;
        while (getline(iss, token, ','))
        {
            tokens.push_back(token);
        }
        list <int> close_countries;
        for (int i = 3; i < tokens.size(); i++)
        {            
            if (tokens[i] != "")
            {
                int close_country = std::stoi(tokens[i]);
                close_countries.push_back(close_country);
            }
        }
        Data info(tokens[0], stoi(tokens[1]), tokens[2], close_countries);
        data.push_back(info);
    }
    file.close();
    return data;
}

int main()
{
    setlocale(LC_ALL, " ");
    string command;
    list <Country> countries;
    list <Data> info_close_countries;
    list <Player> players;

    int NORTH_AMERICA = 9;
    int SOUTH_AMERICA = 4;
    int EUROPE = 7;
    int AFRICA = 6;
    int ASIA = 12;
    int AUSTRALIA = 4;

    info_close_countries = load_data();

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

                    if (players.size()==0)
                    {
                        countries = load_countries();

                        cout << "No hay jugadores registrados." << endl;
                        cout << "Cuantos jugadores van a jugar?" << endl;
                        int num_players;
                        cin >> num_players;

                        while (num_players < 3 || num_players > 6)
                        {
                            cout << "El numero de jugadores debe ser entre 3 y 6." << endl;
                            cout << "Cuantos jugadores van a jugar?" << endl;
                            cin >> num_players;
                        }

                        for (int i = 0; i < num_players; i++)
                        {
                            string name;
                            cout << "Ingrese el nombre del jugador " << i+1 << endl;
                            cin >> name;
                            Player player(name, 0, {}, 0);
                            players.push_back(player);
                        }

                        cout << "----------------------" << endl;
                        cout << "Jugadores registrados:" << endl;
                        for (auto player : players)
                        {
                            cout << player.get_name() << endl;
                        }

                        cout << "----------------------" << endl;
                        cout << "Lanzando dado" << endl;
                        srand(time(NULL));
                        for (auto it = players.begin(); it != players.end(); it++)
                        {
                            int random_number = rand() % 6 + 1;
                            cout << it->get_name() << " rolled a " << random_number << endl;
                            it->set_dado(random_number);
                        }

                        //Ordenar jugadores
                        for (auto it = players.begin(); it != players.end(); it++)
                        {
                            for (auto it2 = players.begin(); it2 != players.end(); it2++)
                            {
                                if (it->get_dado() >= it2->get_dado())
                                {
                                    Player temp = *it;
                                    *it = *it2;
                                    *it2 = temp;
                                }
                            }
                        }

                        cout << "----------------------" << endl;
                        //Asignar turnos y mostrar orden
                        cout << "Orden para jugar:" << endl;
                        int turn = 0;
                        for (auto it = players.begin(); it != players.end(); it++)
                        {
                            it->set_turn(turn + 1);
                            turn ++;
                            cout << "Nombre: " <<it->get_name() << ", Turno: " << it->get_turn() << endl;
                        }

                        //Clean the buffer
                        cin.ignore();

                        cout << "Press Enter to continue...";
                        cin.get();

                        //Añadir tropas a los jugadores
                        int num_armies = 0;

                        if (num_players == 3)
                        {
                            num_armies = 35;
                        }
                        else if (num_players == 4)
                        {
                            num_armies = 30;
                        }
                        else if (num_players == 5)
                        {
                            num_armies = 25;
                        }
                        else if (num_players == 6)
                        {
                            num_armies = 20;
                        }

                        for (auto it = players.begin(); it != players.end(); it++)
                        {
                            it->set_armies(num_armies);
                        }

                        //Asignar paises
                        int num_countries = countries.size();

                        while (num_countries > 0)
                        {
                            for (auto it = players.begin(); it != players.end(); it++)
                            {
                                if (num_countries > 0)
                                {
                                    //Mostrar paises disponibles
                                    cout << "Paises disponibles:" << endl;
                                    for (auto country : countries)
                                    {
                                        if (country.get_status() == 0)
                                        {
                                            cout << country.get_continent() << ": " << country.get_id() << " - " << country.get_name() << endl;
                                        }
                                    }
                                    cout << "-----------------" << endl;

                                    //Pedir pais
                                    int id_country;
                                    cout << "Jugador " << it->get_name() << " ingrese el id del pais que desea:" << endl;
                                    cin >> id_country;
                                    cout << "-----------------" << endl;
                                    //Confirmar que el pais este disponible
                                    int i=0;
                                    while (i==0)
                                    {
                                        for (auto it2 = countries.begin(); it2 != countries.end(); it2++)
                                        {

                                            if (it2->get_id() == id_country)
                                            {
                                                if (it2->get_status() == 0)
                                                {
                                                    it2->set_status(1);
                                                    it2->set_armies(1);
                                                    it->add_country(*it2);
                                                    num_countries--;
                                                    i=1;
                                                    cout << "-----------------" << endl;
                                                    break;
                                                }
                                            }
                                        }

                                        if (i==0)
                                        {
                                            cout << "El pais ya esta ocupado, o no existe" << endl;
                                            cout << "Jugador " << it->get_name() << " ingrese el id del pais que desea:" << endl;
                                            cin >> id_country;
                                            cout << "-----------------" << endl;
                                        }
                                    }
                    
                                }


                            }
                        }

                        //Limpiar buffer
                        cin.ignore();
                    }

                    else
                    {
                        cout << "Ya hay jugadores registrados." << endl;
                        //Mostrar a los jugadores con toda su informacio y sus paises con toda la informacion
                        cout << "-----------------" << endl;
                        cout << "Jugadores registrados:" << endl;
                        for (auto player : players)
                        {
                            cout << "Nombre:" <<player.get_name() << endl;
                            cout << "Tropas: "<<player.get_armies() << endl;
                            cout << "Dado: "<<player.get_dado() << endl;
                            cout << "Turno: "<<player.get_turn() << endl;
                            cout << "Paises:" << endl;
                            for (auto country : player.get_countries())
                            {
                                cout << country.get_txt() << endl;
                            }
                            cout << "-----------------" << endl;
                        }

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
                    if (players.size() == 0)
                    {
                        cout << "No hay jugadores registrados." << endl;
                    }
                    else
                    {
                        string id_jugador = tokens[1];
                        cout << "Comando 'turno' ingresado para el jugador: " << id_jugador << endl;
                        int i=0;
                        for (auto it = players.begin(); it != players.end(); it++)
                        {
                            if (it->get_name() == id_jugador)
                            {
                                if (it->get_turn() == 1)
                                {
                                    cout << "Es turno del jugador: " << it->get_name() << endl;
                                    cout << "-----------------" << endl;
                                    cout << "Cantidad de tropas: " << it->get_armies() << endl;
                                    int cant_paises = it->get_countries().size();
                                    cout << "Cantidad Paises: " << cant_paises << endl;
                                    cout << "-----------------" << endl;
                                    int uni_ad= cant_paises/3;
                                    if (uni_ad < 3)
                                    {
                                        uni_ad = 3;
                                    }
                                    
                                    //Verificar si alguien tiene continentes completos
                                    int north_america=0;
                                    int south_america=0;
                                    int europe=0;
                                    int africa=0;
                                    int asia=0;
                                    int australia=0;

                                    for (auto country : it->get_countries())
                                    {
                                        if (country.get_continent() == "NORTH AMERICA")
                                        {
                                            north_america++;
                                        }
                                        else if (country.get_continent() == "SOUTH AMERICA")
                                        {
                                            south_america++;
                                        }
                                        else if (country.get_continent() == "EUROPE")
                                        {
                                            europe++;
                                        }
                                        else if (country.get_continent() == "AFRICA")
                                        {
                                            africa++;
                                        }
                                        else if (country.get_continent() == "ASIA")
                                        {
                                            asia++;
                                        }
                                        else if (country.get_continent() == "AUSTRALIA")
                                        {
                                            australia++;
                                        }
                                        {
                                            europe++;
                                        }
                                        
                                    }

                                    if (north_america == NORTH_AMERICA)
                                    {
                                        uni_ad += 5;
                                    }

                                    if (south_america == SOUTH_AMERICA)
                                    {
                                        uni_ad += 2;
                                    }

                                    if (europe == EUROPE)
                                    {
                                        uni_ad += 5;
                                    }

                                    if (africa == AFRICA)
                                    {
                                        uni_ad += 3;
                                    }

                                    if (asia == ASIA)
                                    {
                                        uni_ad += 7;
                                    }

                                    if (australia == AUSTRALIA)
                                    {
                                        uni_ad += 2;
                                    }
                                    
                                    
                                    cout << "Unidades Adicionales: " << uni_ad << endl;
                                    it -> set_armies(it->get_armies() + uni_ad);
                                    cout << "-----------------" << endl;
                                    cout << "Tropas actualizadas: " << it->get_armies() << endl;

                                    //Asignar tropas a los paises
                                    cout << "-----------------" << endl;
                                    cout << "Quieres asignar tropas a tus paises? si/no" << endl;
                                    string resp;
                                    cin >> resp;
                                    while (it->get_armies() >0 && resp=="si")
                                    {
                                        cout << "-----------------" << endl;
                                        cout << "Vas a asignar tropas a tus paises" << endl;
                                        cout << "Tus tropas: " << it->get_armies() << endl;
                                        cout << "Paises:" << endl;
                                        for (auto country : it->get_countries())
                                        {
                                            cout << "****" << endl;
                                            country.print();
                                        }

                                        cout << "-----------------" << endl;
                                        cout << "Ingrese el id del pais al que desea asignar tropas:" << endl;
                                        int id_pais;
                                        cin >> id_pais;

                                        int j=0;
                                        list <Country> countries_al = it->get_countries();
                                        for (auto it2 = countries_al.begin(); it2 != countries_al.end(); it2++)
                                        {
                                            if (it2->get_id() == id_pais)
                                            {
                                                cout << "Ingrese la cantidad de tropas que desea asignar:" << endl;
                                                int cant_tropas;
                                                cin >> cant_tropas;
                                                if (cant_tropas > it->get_armies())
                                                {
                                                    cout << "No tienes suficientes tropas." << endl;
                                                    break;
                                                    j=1;
                                                }

                                                j= it->change_country_armies(cant_tropas, id_pais);
                                                it->set_armies(it->get_armies() - cant_tropas);
                                                for (auto it3 = countries.begin(); it3 != countries.end(); it3++)
                                                {
                                                    if (it3->get_id() == id_pais)
                                                    {
                                                        it3->set_armies(it3->get_armies() + cant_tropas);
                                                    }
                                                }


                                                
                                                break;
                                            }
                                        }

                                        if (j==0)
                                        {
                                            cout << "El pais no existe o no es de tu propiedad." << endl;
                            
                                        }

                                        cout << "Quieres continuar? si/no" << endl;
                                        cin >> resp;
                                    }

                                    //Guerra
                                    cout << "-----------------" << endl;
                                    cout << "Quieres atacar a otro jugador? si/no" << endl;
                                    cin >> resp;
                                    if (resp == "si")
                                    {
                                        cout << "-----------------" << endl;
                                        cout << "Paises:" << endl;
                                        for (auto country : it->get_countries())
                                        {
                                            cout << "****" << endl;
                                            country.print();
                                        }

                                        cout << "-----------------" << endl;
                                        cout << "Ingrese el id del pais desde el cual quiere atacar:" << endl;
                                        int id_pais1;
                                        cin >> id_pais1;

                                        //Buscar los paises a loa que puede atacar
                                        cout << "Paises cercanos:" << endl;
                                        list <int> cercanos;
                                        for (auto it2 = info_close_countries.begin(); it2 != info_close_countries.end(); it2++)
                                        {
                                            if (it2->get_id() == id_pais1)
                                            {
                                                list <int> close_countries= it2->get_close_countries();
                                                for (auto it3 = close_countries.begin(); it3 != close_countries.end(); it3++)
                                                {
                                                    cercanos.push_back(*it3);
                                                }
                                            }
                                        }
                                        
                             
                                        cout << "Paises a los que puede atacar:" << endl;

                                        for (auto it2 = cercanos.begin(); it2 != cercanos.end(); it2++)
                                        {
                                            list <Country> countries_al = it->get_countries();
                                            for (auto it3 = countries_al.begin(); it3 != countries_al.end(); it3++)
                                            {
                                                if (it3->get_id() == *it2)
                                                {
                                                    cercanos.erase(it2);
                                                }
                                            }
                                        }

                                        for (auto it2 = cercanos.begin(); it2 != cercanos.end(); it2++)
                                        {
                                            for (auto country : countries)
                                            {
                                                if (country.get_id() == *it2)
                                                {
                                                    cout << "****" << endl;
                                                    country.print();
                                                }
                                            }
                                        }

                                        cout << "-----------------" << endl;
                                        cout << "Ingrese el id del pais al que desea atacar:" << endl;
                                        int id_pais2;
                                        cin >> id_pais2;

                                        //Confirmar que el pais al que se quiere atacar sea valido

                                        int j=0;
                                        for (auto it2 = cercanos.begin(); it2 != cercanos.end(); it2++)
                                        {
                                            if (id_pais2 == *it2)
                                            {
                                                j=1;
                                                break;
                                            }
                                        }

                                        if (j==0)
                                        {
                                            cout << "El pais no existe o no es de tu propiedad." << endl;
                                            break;
                                        }

                                        else
                                        {
                                            //Buscar el jugador al que pertenece el pais
                                            string name;
                                            for (auto it2 = players.begin(); it2 != players.end(); it2++)
                                            {
                                                for (auto country : it2->get_countries())
                                                {
                                                    if (country.get_id() == id_pais2)
                                                    {
                                                        name = it2->get_name();
                                                        break;
                                                    }
                                                }
                                            }

                                            cout << "-----------------" << endl;
                                            cout << "Jugador a atacar: " << name << endl;

                                            //Pedir cantidad de tropas a atacar
                                            cout << "Ingrese la cantidad de tropas con las que desea atacar:" << endl;
                                            int cant_tropas;
                                            cin >> cant_tropas;
                                            

                                            //Confirmar que el pais desde el que se ataca tenga suficientes tropas
                                            int k=0;
                                            for (auto country : it->get_countries())
                                            {
                                                if (country.get_id() == id_pais1)
                                                {
                                                    if (country.get_armies() >= cant_tropas)
                                                    {
                                                        k=1;
                                                        break;
                                                    }
                                                }
                                            }

                                            if (k==0)
                                            {
                                                cout << "No tienes suficientes tropas en el pais." << endl;
                                                break;
                                            }

                                            else
                                            {
                                                string ans = "si";

                                                for (auto country : it->get_countries())
                                                {
                                                    if (country.get_id() == id_pais1)
                                                    {   
                                                        it->change_country_armies(-cant_tropas, id_pais1);
                                                    }
                                                }

                                                //quitar los atacantes de las tropas de la lista de paises
                                            
                                                for (auto it3 = countries.begin(); it3 != countries.end(); it3++)
                                                {
                                                    if (it3->get_id() == id_pais1)
                                                    {
                                                        it3->set_armies(it3->get_armies() - cant_tropas);
                                                    }
                                                }




                                                while (ans == "si")
                                                {
                                                    cout << "Sorteando los 5 dados" <<endl;
                                                    srand(time(NULL));
                                                    int dado1 = rand() % 6 + 1;
                                                    int dado2 = rand() % 6 + 1;
                                                    int dado3 = rand() % 6 + 1;
                                                    int dado4 = rand() % 6 + 1;
                                                    int dado5 = rand() % 6 + 1;
                                                    

                                                    //Ordenar los dados mayor a menor
                                                    vector <int> dados_jugador = {dado1, dado2, dado3};
                                                    vector <int> dados_oponente = {dado4, dado5};

                                                    sort(dados_jugador.begin(), dados_jugador.end());
                                                    sort(dados_oponente.begin(), dados_oponente.end());

                                                    cout << "Tus dados ordenados: " << dados_jugador[2] << ", " << dados_jugador[1] << ", " << dados_jugador[0] << endl;
                                                    cout << "Dados del oponente ordenados: " << dados_oponente[1] << ", " << dados_oponente[0] << endl;
                                            

                                                    for (int i=2; i>0; i--)
                                                    {
                                                        if (dados_jugador[i]>dados_oponente[i-1])
                                                        {
                                                            cout << "Has ganado el dado " << i+1 << endl;
                                                            //Cambiar el numero de tropas del pais atacado
                                                            for (auto it2 = countries.begin(); it2 != countries.end(); it2++)
                                                            {
                                                                if (it2->get_id() == id_pais2)
                                                                {
                                                                    if (it2->get_armies() > 0)
                                                                    {
                                                                        it2->set_armies(it2->get_armies() - 1);
                                                                    }                                                        

                                                                    //cambiar armies en la lista de jugadores
                                                                    for (auto it3 = players.begin(); it3 != players.end(); it3++)
                                                                    {
                                                                        if (it3->get_name() == name)
                                                                        {
                                                                            it3->change_country_armies(-1, id_pais2);
                                                                        }
                                                                    }
                                                                    
                                                                }
                                                            }
                                                        }
                                                        else
                                                        {
                                                            cout << "Has perdido el dado " << i+1 << endl;
                                                            //Cambiar el numero de tropas del pais atacante
                                                            cant_tropas--;
                                                        }
                                                    }

                                                    //Mostrar el numero de tropas de cada pais
                                                    cout << "-----------------" << endl;
                                                    cout << "Tropas del pais atacante: " << cant_tropas << endl;
                                                    if (cant_tropas<=0)
                                                    {
                                                        cout << "Has perdido" << endl;
                                                        break;
                                                    }

                                                    cout << "Tropas del pais atacado: " ;
                                                    for (auto it2 = countries.begin(); it2 != countries.end(); it2++)
                                                    {
                                                        if (it2->get_id() == id_pais2)
                                                        {
                                                            cout << it2->get_armies() << endl;
                                                            if (it2->get_armies()<=0)
                                                            {
                                                                cout << "Has ganado el pais" << endl;
                                                                
                                                                //Cambiar el pais de jugador
                                                                for (auto it3 = players.begin(); it3 != players.end(); it3++)
                                                                {
                                                                    if (it3->get_name() == it->get_name())
                                                                    {
                                                                        it3->add_country(*it2);
                                                                    }
                                                                }

                                                                for (auto it3 = players.begin(); it3 != players.end(); it3++)
                                                                {
                                                                    if (it3->get_name() == name)
                                                                    {
                                                                        it3->delete_country(id_pais2);
                                                                    }
                                                                }

                                                                //dejar tropas restantes en el pais
                                                                for (auto it3 = countries.begin(); it3 != countries.end(); it3++)
                                                                {
                                                                    if (it3->get_id() == id_pais2)
                                                                    {
                                                                        it3->set_armies(cant_tropas);
                                                                    }
                                                                }

                                                                for (auto country : it->get_countries())
                                                                {
                                                                    if (country.get_id() == id_pais2)
                                                                    {   
                                                                        it->change_country_armies(cant_tropas, id_pais2);
                                                                    }
                                                                }

                                                                break;

                                                            }
                                                        }
                                                    }

                                                    cout << "Quieres continuar? si/no" << endl;
                                                    cin >> ans;
                                                }
                                                
                                            }
                                        }
                                        
                                    }
                                    //limpiar buffer
                                    cin.ignore();

                                    //Mover tropas entre paises
                                    cout << "-----------------" << endl;
                                    cout << "Quieres mover tropas entre tus paises? si/no" << endl;
                                    cin >> resp;
                                    while (resp== "si")
                                    {
                                        cout << "-----------------" << endl;
                                        cout << "Paises:" << endl;
                                        for (auto country : it->get_countries())
                                        {
                                            cout << "****" << endl;
                                            country.print();
                                        }

                                        cout << "-----------------" << endl;
                                        cout << "Ingrese el id del pais del que desea mover tropas:" << endl;
                                        int id_pais1;
                                        cin >> id_pais1;

                                        //Arrojar los paises cercanos al id que da el usuario y mostrarlos en pantalla
                                        
                                        cout << "Paises cercanos:" << endl;
                                        list <int> cercanos;
                                        for (auto it2 = info_close_countries.begin(); it2 != info_close_countries.end(); it2++)
                                        {
                                            if (it2->get_id() == id_pais1)
                                            {
                                                list <int> close_countries= it2->get_close_countries();
                                                for (auto it3 = close_countries.begin(); it3 != close_countries.end(); it3++)
                                                {
                                                    for (auto country : it->get_countries())
                                                    {
                                                        if (country.get_id() == *it3)
                                                        {
                                                            cout << "****" << endl;
                                                            country.print();
                                                            cercanos.push_back(country.get_id());
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        
                                        if (cercanos.size()==0)
                                        {
                                            cout << "No tienes cercanos disponible" << endl;
                                        }

                                        else
                                        {
                                            cout << "Digite la cantidad de tropas que desea mover:" << endl;
                                            int cant_tropas;
                                            cin >> cant_tropas;

                                            for (auto country : it->get_countries())
                                            {
                                                if (country.get_id() == id_pais1)
                                                {
                                                    if (country.get_armies() >= cant_tropas)
                                                    {
                                                        cout << "Ingrese el id del pais al que desea mover tropas:" << endl;
                                                        int id_pais2;
                                                        cin >> id_pais2;

                                                        for (auto it3 = cercanos.begin(); it3 != cercanos.end(); it3++)
                                                        {
                                                            if (id_pais2 == *it3)
                                                            {
                                                                it->change_country_armies(-cant_tropas, id_pais1);
                                                                it->change_country_armies(cant_tropas, id_pais2);

                                                                for (auto it3 = countries.begin(); it3 != countries.end(); it3++)
                                                                {
                                                                    if (it3->get_id() == id_pais1)
                                                                    {
                                                                        it3->set_armies(it3->get_armies() - cant_tropas);
                                                                    }
                                                                    else if (it3->get_id() == id_pais2)
                                                                    {
                                                                        it3->set_armies(it3->get_armies() + cant_tropas);
                                                                    }
                                                                }

                                                                break;
                                                            }

                                                        }
                                                    }
                                                    else
                                                    {
                                                        cout << "No tienes suficientes tropas en el pais." << endl;
                                                    }
                                                }
                                            }
                                        }
                                        cout << "-----------------" << endl;
                                        cout << "Quieres continuar? si/no" << endl;
                                        cin >> resp;

                                    }
                                    

                                    //Verificar si alguien ya gano (tiene 42 paises)
                                    for (auto it2 = players.begin(); it2 != players.end(); it2++)
                                    {
                                        if (it2->get_countries().size() == 42)
                                        {
                                            cout << "El jugador " << it2->get_name() << " ha ganado." << endl;
                                            break;
                                        }
                                    }


                                    //Cambiar turno
                                    for (auto it = players.begin(); it != players.end(); it++)
                                    {
                                        if (it->get_turn() == 1)
                                        {
                                            it->set_turn(players.size());
                                        }
                                        else
                                        {
                                            it->set_turn(it->get_turn() - 1);
                                        }
                                    }
                                    i=1;
                                }
                                else
                                {
                                    cout << "No es turno del jugador: " << it->get_name() << endl;
                                    i=1;
                                }

                                //Limpiar buffer
                                cin.ignore();
                                
                                
                            }
                        }
                        if (i==0)
                        {
                            cout << "El jugador no existe." << endl;
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
            
            //Guardar lista_paises
            else if (tokens[0] == "guardar_lista_paises")
            {
                ofstream file("lista_paises.txt");
                for (auto it = countries.begin(); it != countries.end(); it++)
                {
                    file << it->get_txt() << endl;
                }
                file.close();
            }

            //Guardar lista_jugadores
            else if (tokens[0] == "guardar_lista_jugadores")
            {
                ofstream file("lista_jugadores.txt");
                for (auto it = players.begin(); it != players.end(); it++)
                {
                    file << it->get_txt() << endl;
                }
                file.close();
            }

            //Cargar lista_paises
            else if (tokens[0] == "cargar_lista_paises")
            {
                ifstream file("lista_paises.txt");
                string line;
                while (getline(file, line))
                {
                    istringstream iss(line);
                    vector<string> tokens;
                    string token;
                    while (getline(iss, token, ','))
                    {
                        tokens.push_back(token);
                    }
                    Country country(tokens[0], stoi(tokens[1]), tokens[2], stoi(tokens[3]), stoi(tokens[4]));
                    countries.push_back(country);
                }
                file.close();
            }

            //Caragar lista_jugadores
            else if (tokens[0] == "cargar_lista_jugadores")
            {
                ifstream file("lista_jugadores.txt");
                string line;
                while (getline(file, line))
                {
                    istringstream iss(line);
                    vector<string> tokens;
                    string token;
                    while (getline(iss, token, ','))
                    {
                        tokens.push_back(token);
                    }

                    list <Country> countries;
                    for (int i = 4; i < tokens.size(); i+=5)
                    {
                        Country country(tokens[i], stoi(tokens[i+1]), tokens[i+2], stoi(tokens[i+3]), stoi(tokens[i+4]));
                        countries.push_back(country);
                    }

                    Player player(tokens[0], stoi(tokens[1]), stoi(tokens[2]), stoi(tokens[3]), countries);
                    players.push_back(player);
                }
                file.close();
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
