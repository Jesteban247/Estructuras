#include "Data.h"

Data::Data()
{
}

void Data::setNumber_of_lines(int number_of_lines)
{
    this->number_of_lines = number_of_lines;
}

int Data::getNumber_of_lines()
{
    return number_of_lines;
}

void Data::setWord_to_find(string word_to_find)
{
    this->word_to_find = word_to_find;
}

string Data::getWord_to_find()
{
    return word_to_find;
}

void Data::addLine(vector<string> line)
{
    data.push_back(Line(line));
}

void Data::front_compare_data(string word)
{
    int line=1;
    queue<string> total_words;
    for (list<Line>::iterator it = data.begin(); it != data.end(); it++)
    {
        queue<string> words_per_line= it->front_compare_line(word, line);

        while (!words_per_line.empty())
        {
            total_words.push(words_per_line.front());
            words_per_line.pop();
        }

        line++;
        
    }

    cout << "Total words found: " << total_words.size() << endl;
    while (!total_words.empty())
    {
        string input = total_words.front();
        istringstream iss(input);
        vector<std::string> tokens;

        do 
        {
            std::string token;
            iss >> token;
            tokens.push_back(token);
        } while (iss);

        if (tokens.size() >= 2) 
        {
            cout << "Line " << tokens[0] << ": " << tokens[1] << endl;
        }
        total_words.pop();
    }
}

void Data::find_word_data(string word)
{
    int line=1;
    queue<string> words_per_line;
    queue<string> total_words;
    for (list<Line>::iterator it = data.begin(); it != data.end(); it++)
    {
        words_per_line= it->find_word_line(word, line);
        while (!words_per_line.empty())
        {
            total_words.push(words_per_line.front());
            words_per_line.pop();
        }
        line++;
    }
    
    cout << "Total words found: " << total_words.size() << endl;
    while (!total_words.empty())
    {
        string input = total_words.front();
        istringstream iss(input);
        vector<std::string> tokens;

        do 
        {
            std::string token;
            iss >> token;
            tokens.push_back(token);
        } while (iss);

        if (tokens.size() >= 2) 
        {
            cout << "Line " << tokens[0] << ": " << tokens[1] << endl;
        }
        total_words.pop();
    }
}
