#include <iostream>
#include <stack>

using namespace std;

int menu()
{
    cout << "1. Add a number" << endl;
    cout << "2. Remove top element" << endl;
    cout << "3. Access top element" << endl;
    cout << "4. Show all the elements" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    return choice;
}

int main ()
{
    stack<int> stack;

    int choice = menu();

    while (choice != 5)
    {
        if (choice == 1)
        {
            cout << "Enter a number to add to the stack: ";
            int number;
            cin >> number;
            stack.push(number);
        }

        else if (choice == 2)
        {
            cout << "The top element was removed" << endl;
            stack.pop();
        }

        else if (choice == 3)
        {
            cout << "The top element is: " << stack.top() << endl;
        }

        else if (choice == 4)
        {
            std::stack<int> stack2 = stack;
            while (!stack2.empty())
            {
                cout << stack2.top() << " ";
                stack2.pop();
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