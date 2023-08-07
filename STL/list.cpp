#include <iostream>
#include <list>

using namespace std;

int menu()
{
    cout << "1. Insert element at beginning" << endl;
    cout << "2. Insert element at the end" << endl;
    cout << "3. Print the list with iterator" << endl;
    cout << "4. Print the reverse list with iterator" << endl;
    cout << "5. Size of the list" << endl;
    cout << "6. Delete a number from the list without <remove>" << endl;
    cout << "7. Delete last element" << endl;
    cout << "8. Delete first element" << endl;
    cout << "9. Delete a number with <remove>" << endl;
    cout << "10. Sort elements" << endl;
    cout << "11. Remove duplicates" << endl;
    cout << "12. Exit" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    return choice;
}

int main ()
{
    list<int> dlist;

    int choice = menu();

    while (choice != 12)
    {
        if (choice == 1)
        {
            cout << "Enter a number to add to the list: ";
            int number;
            cin >> number;
            dlist.push_front(number);
        }

        else if (choice == 2)
        {
            cout << "Enter a number to add to the list: ";
            int number;
            cin >> number;
            dlist.push_back(number);
        }

        else if (choice == 3)
        {
            cout << "The list contains: ";
            list<int>::iterator it;
            for (it = dlist.begin(); it != dlist.end(); it++)
            {
                cout << *it << " ";
            }
            cout << endl;
        }

        else if (choice == 4)
        {
            cout << "The reverse list contains: ";
            list<int>::reverse_iterator it;
            for (it = dlist.rbegin(); it != dlist.rend(); it++)
            {
                cout << *it << " ";
            }
            cout << endl;
        }

        else if (choice == 5)
        {
            cout << "The size of the list is: " << dlist.size() << endl;
        }

        else if (choice == 6)
        {
            cout << "Enter a number to delete from the list: ";
            int number;
            cin >> number;
            list<int>::iterator it;
            for (it = dlist.begin(); it != dlist.end(); it++)
            {
                if (*it == number)
                {
                    dlist.erase(it);
                    break;
                }
            }
        }

        else if (choice == 7)
        {
            dlist.pop_back();
        }

        else if (choice == 8)
        {
            dlist.pop_front();
        }

        else if (choice == 9)
        {
            cout << "Enter a number to delete from the list: ";
            int number;
            cin >> number;
            dlist.remove(number);
        }

        else if (choice == 10)
        {
            dlist.sort();
        }

        else if (choice == 11)
        {
            dlist.unique();
        }

        else
        {
            cout << "Invalid choice." << endl;
        }

        choice = menu();
    }

    return 0;
}