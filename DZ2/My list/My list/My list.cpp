#include <iostream>
#include <string>
using namespace std;

class list
{
public:
    
    ~list()
    {
        list * temp = this;
        while (temp->next != 0)
        {
            temp = temp->next;
            delete temp->previous;
        }
        delete temp;
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
        list* temp = this;
        int i = 0;
        while (i < pos)
        {
            if (temp->next != 0)
            {
                temp = temp->next;
                i++;
            }
            else 
            {
                cout << "Error! There is only " << i + 1 << " elements in this list";
                break;
            }
        }
        incerted->previous = temp->previous;
        incerted->next = temp;
        incerted->content = c;
        temp->previous = incerted;
        temp = incerted->previous;
        temp->next = incerted;
    }
    int get(int n)
    {
        int i = 0;
        list* temp = this;
        while (i != n)
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
        return temp->content;
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
        list* temp = 0;
        for (int i = 0; i < n; i++)
        {

        }
    }
    int content = 0;
    list* next = 0;
    list* previous = 0;
};

int main()
{
    string command;
    int temp1;
    int temp2;
    list* test =  new list;
    while (command != "exit")
    {
        cout << "enter command";
        cout << endl;
        cin >> command;
        cout << endl;
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
    }
    return 0;
}