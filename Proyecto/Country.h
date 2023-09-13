#ifndef Country_H
#define Country_H

#include <iostream>
#include <string>

using namespace std;

class Country
{
    private:
        string continent;
        int id;
        string name;
        int armies;
        int status;

    public:
        Country(string continent, int id, string name);

        Country(string continent, int id, string name, int armies, int status);

        string get_continent();
        int get_id();
        string get_name();
        int get_armies();
        int get_status();

        void set_armies(int armies);
        void set_status(int status);

        string get_txt();

        void print();
};

#endif