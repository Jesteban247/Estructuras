#include "Player.h"

Player::Player(string name, int armies, list <Country> countries, int turn)
{
    this->name = name;
    this->armies = armies;
    this->countries = countries;
    this->turn = turn;
}

Player::Player(string name, int armies, int turn, int dado, list <Country> countries)
{
    this->name = name;
    this->armies = armies;
    this->countries = countries;
    this->dado = dado;
    this->turn = turn;
}

string Player::get_name()
{
    return name;
}

int Player::get_armies()
{
    return armies;
}

list <Country> Player::get_countries()
{
    return countries;
}

int Player::get_dado()
{
    return dado;
}

int Player::get_turn()
{
    return turn;
}

void Player::set_name(string name)
{
    this->name = name;
}

void Player::set_armies(int armies)
{
    this->armies = armies;
}

void Player::set_countries(list <Country> countries)
{
    this->countries = countries;
}

void Player::set_dado(int dado)
{
    this->dado = dado;
}

void Player::set_turn(int turn)
{
    this->turn = turn;
}

void Player::add_country(Country country)
{
    this->countries.push_back(country);
}

string Player::get_txt()
{
    string txt = "";
    txt += get_name() + "," + to_string(get_armies()) + "," + to_string(get_turn()) + "," + to_string(get_dado()) + ",";
    for (Country country : get_countries())
    {
        txt += country.get_txt() + ",";
    }
    return txt;
}

int Player::change_country_armies(int armies, int id)
{
    for (Country &country : countries)
    {
        if (country.get_id() == id)
        {
            country.set_armies(armies+country.get_armies());
            return 1;
        }
    }
    return 0;
}

void Player::delete_country(int id)
{
    for (auto it = countries.begin(); it != countries.end(); it++)
    {
        if (it->get_id() == id)
        {
            countries.erase(it);
            break;
        }
    }
    
}
