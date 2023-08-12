#include "Line.h"

Line::Line(vector<string> line)
{
    this->line = line;
}

queue<string> Line::front_compare_line(string word, int line_number)
{
    queue<string> words;
    for (int i = 0; i < line.size(); i++)
    {  
        string alternative = line[i].substr(0, word.size());
        if (alternative == word)
        {
            words.push(to_string(line_number)+" "+line[i]);
        }
    }

    return words;
}

queue<string> Line::find_word_line(string word, int line_number)
{
    queue<string> words;
    for (int i = 0; i < line.size(); i++)
    {  
        if (line[i].find(word) != std::string::npos) 
        {
            words.push(to_string(line_number)+" "+line[i]);
        } 
    }
    return words;
}