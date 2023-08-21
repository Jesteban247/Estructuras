#ifndef Data_H
#define Data_H

#include <iostream>
#include <string>
#include <list>

using namespace std;

class Data
{
    private:
        string continent;
        int id;
        string name;
        list <int> close_countries;

    public:
        Data(string continent, int id, string name, list <int> close_countries);
        string get_continent();
        int get_id();
        string get_name();
        list <int> get_close_countries();
        void set_continent(string continent);
        void set_id(int id);
        void set_name(string name);
        void set_close_countries(list <int> close_countries);

        void print_without_id(int id);
};

#endif