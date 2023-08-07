#include <iostream>
#include <queue>

using namespace std;

int menu()
{
    cout << "1. Add a number" << endl;
    cout << "2. Access first element" << endl;
    cout << "3. Access last element" << endl;
    cout << "4. Size" << endl;
    cout << "5. Remove first element" << endl;
    cout << "6. Is empty?" << endl;
    cout << "7. Show all the elements" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    return choice;
}

int main ()
{
    queue<int> queue;

    int choice = menu();

    while (choice != 8)
    {

        if (choice == 1)
        {
            cout << "Enter a number to add to the queue: ";
            int number;
            cin >> number;
            queue.push(number);
        }

        else if (choice == 2)
        {
            cout << "The first element is: " << queue.front() << endl;
        }

        else if (choice == 3)
        {
            cout << "The last element is: " << queue.back() << endl;
        }

        else if (choice == 4)
        {
            cout << "The size of the queue is: " << queue.size() << endl;
        }

        else if (choice == 5)
        {
            cout << "The first element was removed" << endl;
            queue.pop();
        }

        else if (choice == 6)
        {
            if (queue.empty())
            {
                cout << "The queue is empty" << endl;
            }
            else
            {
                cout << "The queue is not empty" << endl;
            }
        }

        else if (choice == 7)
        {
            std::queue<int> queue2 = queue;
            cout << "The queue contains: ";
            while (!queue2.empty())
            {
                cout << queue2.front() << " ";
                queue2.pop();
            }
            cout << endl;
        }


        else
        {
            cout << "Invalid choice" << endl;
        }

        choice = menu();
    }

    return 0;
}