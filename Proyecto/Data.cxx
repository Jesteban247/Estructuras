#include "Data.h"

Data::Data(string continent, int id, string name, list <int> close_countries)
{
    this->continent = continent;
    this->id = id;
    this->name = name;
    this->close_countries = close_countries;
}

string Data::get_continent()
{
    return continent;
}

int Data::get_id()
{
    return id;
}

string Data::get_name()
{
    return name;
}

list <int> Data::get_close_countries()
{
    return close_countries;
}

void Data::set_continent(string continent)
{
    this->continent = continent;
}

void Data::set_id(int id)
{
    this->id = id;
}

void Data::set_name(string name)
{
    this->name = name;
}

void Data::set_close_countries(list <int> close_countries)
{
    this->close_countries = close_countries;
}

void Data::print_without_id(int id)
{
    for (auto i : get_close_countries())
    {
        if (i != id)
        {
            cout << i << ",";
        }
    }
    cout << endl;
}

