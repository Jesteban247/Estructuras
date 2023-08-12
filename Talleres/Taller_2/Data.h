// Data.h

#ifndef Data_H
#define Data_H


#include <list>
#include "Line.h"
#include <sstream>

class Data 
{
    private:
        list<Line> data;
        string word_to_find;
        int number_of_lines;

    public:
        Data();

        void setWord_to_find(string word_to_find);
        string getWord_to_find();

        void setNumber_of_lines(int number_of_lines);
        int getNumber_of_lines();
        
        void addLine(vector<string> line);

        void front_compare_data(string word);
        void find_word_data(string word);
};

#endif // Data_H
