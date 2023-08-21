#include "Country.h"

Country::Country(string continent, int id, string name)
{
    this->continent = continent;
    this->id = id;
    this->name = name;
    this->armies = 0;
    this->status = 0;
}

Country::Country(string continent, int id, string name, int armies, int status)
{
    this->continent = continent;
    this->id = id;
    this->name = name;
    this->armies = armies;
    this->status = status;
}

string Country::get_continent()
{
    return this->continent;
}

int Country::get_id()
{
    return this->id;
}

string Country::get_name()
{
    return this->name;
}

void Country::set_armies(int armies)
{
    this->armies = armies;
}

void Country::set_status(int status)
{
    this->status = status;
}

int Country::get_armies()
{
    return this->armies;
}

int Country::get_status()
{
    return this->status;
}

string Country::get_txt()
{
    return get_continent() + "," + to_string(get_id()) + "," + get_name() + "," + to_string(armies) + "," + to_string(status);
}

void Country::print()
{
    cout << "Continent: " << get_continent() << " - ID: " << get_id() << " - Name: " << get_name()  << " - Armies: " << get_armies() << endl;
}

