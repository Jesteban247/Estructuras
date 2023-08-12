#include "Data.h"
#include <algorithm>
#include <fstream>


Data read_Data(const std::string& filePath) 
{
    std::ifstream file(filePath);
    Data data;

    if (file.is_open()) 
    {
        string line;
        
        // Read line 0
        if (getline(file, line)) 
        {
            int line0 = std::stoi(line);
            data.setNumber_of_lines(line0);
        }

        // Read line 1
        if (getline(file, line)) 
        {
            string line1 = line;
            data.setWord_to_find(line1);
        }

        while (getline(file, line)) 
        {
            vector<string> tokens;
            std::istringstream tokenizer(line);
            std::string token;

            while (tokenizer >> token) 
            {
                // Remove unwanted characters
                replace(token.begin(), token.end(), ',', ' ');
                replace(token.begin(), token.end(), '.', ' ');
                replace(token.begin(), token.end(), '!', ' ');
                tokens.push_back(token);
            }
            data.addLine(tokens);
        }

        file.close();
    } 

    else
    {
        std::cerr << "Could not open the file." << std::endl;
    }

    return data;
}

int main(int argc, char* argv[]) 
{
    if (argc != 2) 
    {
        std::cerr << "Usage: " << argv[0] << " argument" << std::endl;
        return 1;
    }

    string file = argv[1];
    cout << "Argument: " << file << endl;

    string filePath = "Data/" + file;
    Data data = read_Data(filePath);

    int number = data.getNumber_of_lines();
    string text = data.getWord_to_find();

    cout << "Number of lines:" << number << endl;
    cout << "Words to find:" << text << endl;

    cout << "-----------------" << endl;
    cout << "Comparing with: " << text << endl;
    data.front_compare_data(text);

    cout << "-----------------" << endl;
    cout << "Finding with: " << text << endl;
    data.find_word_data(text);

    cout << "-----------------" << endl;
    reverse(text.begin(), text.end());
    cout << "Reverse word: " << text << std::endl;
    cout << "Finding with: " << text << endl;
    data.find_word_data(text);


    return 0;
}