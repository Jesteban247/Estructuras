#include <iostream>
#include <vector>

using namespace std;

int menu()
{
    cout << "1. Add a number to the vector" << endl;
    cout << "2. Delete a number from the vector" << endl;
    cout << "3. Print the vector without iterator" << endl;
    cout << "4. Print the vector with iterator" << endl;
    cout << "5. Print the reverse vector with iterator" << endl;
    cout << "6. Size of the vector" << endl;
    cout << "7. Clear the vector" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    return choice;
}

int main ()
{
    vector<int> vector;                             

    int choice = menu();

    while (choice != 8)
    {
        if (choice == 1)
        {
            cout << "Enter a number to add to the vector: ";
            int number;
            cin >> number;
            vector.push_back(number);
        }

        else if (choice == 2)
        {
            cout << "Enter a number to delete from the vector: ";
            int number;
            cin >> number;
            for (int i = 0; i < vector.size(); i++)
            {
                if (vector[i] == number)
                {
                    vector.erase(vector.begin() + i);
                    break;
                }
            }
        }

        else if (choice == 3)
        {
            cout << "The vector contains: ";
            for (int i = 0; i < vector.size(); i++)
            {
                cout << vector[i] << " ";
            }
            cout << endl;
        }

        else if (choice == 4)
        {
            cout << "The vector contains: ";
            for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); ++it)
                cout << ' ' << *it;
            cout << endl;
        }

        else if (choice == 5)
        {
            cout << "The reverse vector contains: ";
            for (std::vector<int>::reverse_iterator rit = vector.rbegin(); rit!= vector.rend(); ++rit)
                cout << ' ' << *rit;
            cout << endl;
        }

        else if (choice == 6)
        {
            cout << "The size of the vector is: " << vector.size() << endl;
        }

        else if (choice == 7)
        {
            vector.clear();
            cout << "The vector is cleared" << endl;
        }

        else
        {
            cout << "Invalid choice" << endl;
        }

        choice = menu();
    }
  return 0;
}