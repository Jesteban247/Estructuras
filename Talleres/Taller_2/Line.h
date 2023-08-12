// Line.h

#ifndef Line_H
#define Line_H

#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

class Line
{
    private:
        vector<string> line;
    public:
        Line(vector<string> line);
        queue<string> front_compare_line(string word, int line_number);
        queue<string> find_word_line(string word, int line_number);
};

#endif // Line_H