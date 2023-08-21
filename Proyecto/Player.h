#ifndef Player_H
#define Player_H

#include "Country.h"
#include <list>

class Player
{
    private:
        string name;
        int armies;
        list <Country> countries;
        int dado;
        int turn;

    public:
        Player(string name, int armies, list <Country> countries, int turn);

        Player(string name, int armies, int turn, int dado, list <Country> countries);

        string get_name();
        int get_armies();
        list <Country> get_countries();
        int get_dado();
        int get_turn();

        void set_name(string name);
        void set_armies(int armies);
        void set_countries(list <Country> countries);
        void set_dado(int dado);
        void set_turn(int turn);

        void add_country(Country country);
        void delete_country(int id);

        string get_txt();

        int change_country_armies(int armies, int id);

};

#endif