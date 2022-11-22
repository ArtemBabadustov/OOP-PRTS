﻿#include <iostream>
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
            //cout << "deleted a whole list" << endl;
        }
           // cout << "deleted a member of a list" << endl;
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
        list* new_second = new list;
        if (this->next != 0)
        {
            this->next->previous = new_second;
        }
        if (this->content != 0)
        {
           // list* new_second = new list;
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
        if (pos == 0)
        {
            this->pushfront(c);
            return;
        }
        list* incerted = new list;
        list* temp = this->find(pos);
        if (temp != 0)
        {
            incerted->previous = temp->previous;
            incerted->next = temp;
            incerted->content = c;
            temp->previous = incerted;
            temp = incerted->previous;
            temp->next = incerted;
        }
        else
            return;
    }
    void delete_member (int n)
    {
        if (n == 0)
        {
            if (this->next != 0)
            {
                this->content = this->next->content;
                delete_member(1);
                return;
            }
            else
            {
                this->content = 0;
                return;
            }
        }
        list* temp = this->find(n);
        //cout << "temp content = " << temp->content << endl;
        if (temp->next != 0 && temp->previous != 0)
        {
            temp->previous->next = temp->next;
            temp->next->previous = temp->previous;
            delete temp;
        }
        else if (temp->next == 0 && temp->previous == 0)
        {
            temp->content = 0;
            return;
        }
        else if (temp->next == 0)
        {
            temp->previous->next = 0;
            delete temp;
        }
        else if (temp->previous == 0)
        {
            temp->content = temp->next->content;
            temp->next = temp->next->next;
            delete temp->next;
        }
        /*cout << "just to confirm that the member of a list is actually deleted from the heap" << endl << "here is what stored in the adress:"
            << "adress of a revious element: " << temp->previous << endl
            << "contents of deleted element: " << temp->content << endl
            << "adress of next element: " << temp->next << endl;*/
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
    list* sort()
    {
        if (this->next != 0)
        {
            //splitting
            list* first_half = 0;
            list* second_half = 0;
            list* slow = this;
            list* fast = this;
            while (fast->next != 0)
            {
                fast = fast->next;
                if (fast->next != 0)
                {
                    slow = slow->next;
                    fast = fast->next;
                }
            }
            /*cout << "this:" << endl;
            this->integrity_check();
            cout << "slow:" << endl;
            slow->integrity_check();*/
            //slow = slow->next;
            if (slow->previous != 0)
            {
                slow->previous->next = 0;
                slow->previous = 0;
            }
            if (slow == this)
            {
                first_half = this;
                first_half->next = 0;
                second_half = fast;
                
            }
            else
            {
                first_half = this->sort();
                second_half = slow->sort();
            }
            //merging
            /*cout << "first_half:" << endl;
            first_half->integrity_check();
            cout << "second_half:" << endl;
            second_half->integrity_check();*/
            if (first_half->content <= second_half->content)
            {
                slow = first_half;
                slow->previous = 0;
                first_half = first_half->next;
                fast = slow;
            }
            else
            {
                slow = second_half;
                slow->previous = 0;
                second_half = second_half->next;
                fast = slow;
            }
            while (first_half != 0 && second_half != 0)
            {
                if (first_half->content <= second_half->content)
                {
                    fast->next = first_half;
                    first_half->previous = fast;
                    fast = fast->next;
                    first_half = first_half->next;
                }
                else
                {
                    fast->next = second_half;
                    second_half->previous = fast;
                    fast = fast->next;
                    second_half = second_half->next;
                }
            }
            if (first_half != 0)
            {
                while (first_half != 0)
                {
                    fast->next = first_half;
                    first_half->previous = fast;
                    fast = fast->next;
                    first_half = first_half->next;
                   
                }
            }
            else if (second_half != 0)
            {
                while (second_half != 0)
                {
                    fast->next = second_half;
                    second_half->previous = fast;
                    fast = fast->next;
                    second_half = second_half->next;
                   
                }
            }
            /*cout << "slow:" << endl;
            slow->printlist();
            cout << endl;*/
            return slow;
        }
        else
        {
            /*cout << "this = " << endl;
            this->printlist();
            cout << endl;*/
            return this;
        }
    }
    void integrity_check()
    {
        list* temp = this;
        while (temp->next != 0)
        {
            cout << temp->content << "->";
            temp = temp->next;
        }
        cout << temp->content;
        cout << endl;
        while (temp->previous != 0)
        {
            cout << temp->content << "<-";
            temp = temp->previous;
        }
        cout << temp->content << endl;
    }
    void swap(int a, int b)
    {        
        int i = 0;
        if (a == b)
        {
            return;
        }
        else if (a > b)
        {
            i = a;
            a = b;
            b = i;
            i = 0;
        }
        list* temp1 = this;
        list* temp2 = 0;
            while (i < a)
            {
                if (temp1->next != 0)
                {
                    temp1 = temp1->next;
                    i++;
                }
                else
                {
                    cout << "Error! There is only " << i + 1 << " elements in this list!";
                    return;
                }
            }
            temp2 = temp1;
            while (i < b)
            {
                if (temp2->next != 0)
                {
                    temp2 = temp2->next;
                    i++;
                }
                else
                {
                    cout << "Error! There is only " << i + 1 << " elements in this list!";
                    return;
                }
            }
            i = temp1->content;
            temp1->content = temp2->content;
            temp2->content = i;
            return;
    }
protected:
    list* find(const int n)
    {
        if (this->next == 0 || n == 0)
        {
            return this;
        }
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
                cout << "Error! There is only " << i + 1 << " elements in this list!" << endl;
                return 0;
            }
        }
        if (temp->next != 0)
        {
            return temp->next;
        }
        else
        {
            return temp;
        }
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
    cout << "swap - swap two elements in the list" << endl;
    cout << "fill - fills the list with alternating positive and negative numbers";
    cout << "integrity_ckeck" << endl;
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
            test->delete_member(temp1 - 1);
        }
        if (command == "delete_list")
        {
            delete test;
        }
        if (command == "sort")
        {
            test = test->sort();
        }
        if (command == "integrity_check")
        {
            test->printlist();
            test->integrity_check();
        }
        if (command == "swap")
        {
            cout << "enter first member of the list" << endl;
            cin >> temp1;
            cout << endl << "enter second member of the list" << endl;
            cin >> temp2;
            cout << endl;
            test->swap(temp1 - 1, temp2 - 1);
        }
        if (command == "fill")
        {
            cout << "enter an ammound" << endl;
            cin >> temp1;
            cout << endl;
            for (int i = 0; i < temp1/2; i++)
            {
                    test->pushback(i);
            }
            for (int i = temp1 / 2; i < temp1; i++)
            {
                test->pushback(-i);
            }
           
        }
        if (command == "empty")
        {
            delete test;
            test = new list;
        }
    }
    return 0;
}