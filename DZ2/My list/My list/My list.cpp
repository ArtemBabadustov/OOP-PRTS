#include <iostream>
#include <string>
using namespace std;

class list
{
public:
    
    ~list()
    {
        if (this->previous == 0 && this->next != 0)
        {
            list* temp = this->next;
            while (temp->next != 0)
            {
                temp = temp->next;
                delete temp->previous;
            }
            delete temp;
            cout << "deleted a whole list" << endl;
        }
            cout << "deleted a member of a list" << endl;
    }
    void pushback(int p)
    {
        list* temp = this;
        if (temp->content == 0)
        {
            temp->content = p;
        }
        else
        {
            while (temp->next != 0)
            {
                temp = temp->next;
            }
            temp->next = new list;
            temp->next->previous = temp;
            temp->next->content = p;
        }
    }
    void pushfront(int n)
    {
        if (this->content != 0)
        {
            list* new_second = new list;
            list* temp = this;
            new_second->previous = this;
            new_second->content = this->content;
            new_second->next = this->next;
            this->next = new_second;
            this->content = n;
        }
        else
        {
            this->content = n;
        }
    }
    void incert(int pos, int c)
    {
        list* incerted = new list;
        list* temp = this->find(pos);
        incerted->previous = temp->previous;
        incerted->next = temp;
        incerted->content = c;
        temp->previous = incerted;
        temp = incerted->previous;
        temp->next = incerted;
    }
    void delete_member (int n)
    {
        list* temp = this->find(n - 1);
        temp->previous->next = temp->next;
        temp->next->previous = temp->previous;
        delete temp;
        cout << "just to confirm that the member of a list is actually deleted from the heap" << endl << "here is what stored in the adress:"
            << "adress of a revious element: " << temp->previous << endl
            << "contents of deleted element: " << temp->content << endl
            << "adress of next element: " << temp->next << endl;
    }
    int get(int n)
    {
        
        return this->find(n)->content;
    }
    void printlist()
    {
        int i = 1;
        list* temp = this;
        while (temp->next != 0)
        {
            cout << i << ": " << temp->content << endl;
            temp = temp->next;
            i++;
        }
        cout << i << ": " << temp->content << endl;
    }
    int size()
    {
        int i = 0;
        list* temp = this;
        while (temp->next != 0)
        {
            temp = temp->next;
            i++;
        }
        return i + 1;
    }
protected:
    list* find(const int n)
    {
        int i = 0;
        list* temp = this;
        while (i != n-1)
        {
            if (temp->next != 0)
            {
                temp = temp->next;
                i++;
            }
            else
            {
                cout << "Error! There is only " << i + 1 << " elements in this list!";
                return 0;
            }
        }
        return temp->next;
    }
    int content = 0;
    list* next = 0;
    list* previous = 0;
};
void Print_commands()
{
    cout << "List of eveliable commands: " << endl;
    cout << "--help - view list of eveliable commands" << endl;
    cout << "exit - close the program" << endl;
    cout << "front - pushfront" << endl;
    cout << "back - pushback" << endl;
    cout << "incert - incert a new member in front of the enterd position" << endl;
    cout << "get - print a number, contained on the position you enter" << endl;
    cout << "print - print the whole list" << endl;
    cout << "delete - delete member of a list on the position you enter" << endl;
    cout << "delete_list - delete the whole list" << endl;
    cout << endl;
}
int main()
{
    string command;
    int temp1;
    int temp2;
    list* test =  new list;
    Print_commands();
    while (command != "exit")
    {
        cout << "enter command";
        cout << endl;
        cin >> command;
        cout << endl;
        if (command == "--help")
        {
            Print_commands();
        }
        if (command == "front")
        {
            cout << "enter a number" << endl;
            cin >> temp1;
            cout << endl;
            test->pushfront(temp1);
        }
        if (command == "back")
        {
            cout << "enter a number" << endl;
            cin >> temp1;
            cout << endl;
            test->pushback(temp1);
        }
        if (command == "incert")
        {
            cout << "enter a position" << endl;
            cin >> temp1;
            cout << endl;
            cout << "enter a number" << endl;
            cin >> temp2;
            cout << endl;
            test->incert(temp1 - 1, temp2); 
        }
        if (command == "get")
        {
            cout << "enter a position" << endl;
            cin >> temp1;
            cout << endl;
            test->get(temp1);
        }
        if (command == "print")
        {
            test->printlist();
        }
        if (command == "delete")
        {
            cout << "enter a position" << endl;
            cin >> temp1;
            cout << endl;
            test->delete_member(temp1);
        }
        if (command == "delete_list")
        {
            delete test;
        }
    }
    return 0;
}