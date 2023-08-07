#include <iostream>
#include <deque>

using namespace std;

int menu()
{
    cout << "1. Insert element at beginning" << endl;
    cout << "2. Insert element at the end" << endl;
    cout << "3. Print the deque without iterator" << endl;
    cout << "4. Print the deque with iterator" << endl;
    cout << "5. Print the reverse deque with iterator" << endl;
    cout << "6. Size of the deque" << endl;
    cout << "7. Delete a number from the deque" << endl;
    cout << "8. Delete last element" << endl;
    cout << "9. Delete first element" << endl;
    cout << "10. Exit" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    return choice;
}

int main ()
{
    deque<int> deque;

    int choice = menu();

    while (choice != 10)
    {
        if (choice == 1)
        {
            cout << "Enter a number to add to the deque: ";
            int number;
            cin >> number;
            deque.push_front(number);
        }

        else if (choice == 2)
        {
            cout << "Enter a number to add to the deque: ";
            int number;
            cin >> number;
            deque.push_back(number);
        }

        else if (choice == 3)
        {
            cout << "The deque contains: ";
            for (int i = 0; i < deque.size(); i++)
            {
                cout << deque[i] << " ";
            }
            cout << endl;
        }

        else if (choice == 4)
        {
            cout << "The deque contains: ";
            for (std::deque<int>::iterator it = deque.begin(); it != deque.end(); it++)
            {
                cout << *it << " ";
            }
            cout << endl;
        }

        else if (choice == 5)
        {
            cout << "The reverse deque contains: ";
            for (std::deque<int>::reverse_iterator it = deque.rbegin(); it != deque.rend(); it++)
            {
                cout << *it << " ";
            }
            cout << endl;
        }

        else if (choice == 6)
        {
            cout << "The size of the deque is: " << deque.size() << endl;
        }

        else if (choice == 7)
        {
            cout << "Enter a number to delete from the deque: ";
            int number;
            cin >> number;
            for (int i = 0; i < deque.size(); i++)
            {
                if (deque[i] == number)
                {
                    deque.erase(deque.begin() + i);
                    break;
                }
            }
        }

        else if (choice == 8)
        {
            deque.pop_back();
        }

        else if (choice == 9)
        {
            deque.pop_front();
        }

        else
        {
            cout << "Invalid choice." << endl;
        }

        choice = menu();
    }

    return 0;
}