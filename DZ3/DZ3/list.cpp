#include <iostream>
#include <string>
#include<vector>
#include "list.h"



    list::~list()
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

    void list::pushback(Mission* p)
    {
        list* temp = this;
        if (temp->next == 0)
        {
            temp->content = p;
            temp->next = new list;
            temp->next->content = 0;
            temp->next->previous = temp;
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
    void list::pushfront(Mission* n)
    {
        //list* new_second = new list;
        if (this->next == 0)
        {
            this->content = n;
            this->next = new list;
            this->next->previous = this;
        }
        else
        {
            list* new_second = new list;
            new_second->content = this->content;
            new_second->next = this->next;
            new_second->previous = this;
            this->next->previous = new_second;
            this->content = n;
            this->next = new_second;
        }
    }
    void list::incert(int pos, Mission* c)
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
    void list::delete_member(int n)
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
    Mission* list::get(int n)
    {
        return this->find(n)->content;
    }
    void list::printlist()
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
    int list::size()
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
   
    
    void list::integrity_check()
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
    void list::swap(int a, int b)
    {
        int i = 0;
        int temp_int = 0;
        Mission* temp = 0;
        if (a == b)
        {
            return;
        }
        else if (a > b)
        {
            temp_int = a;
            a = b;
            b = temp_int;
            temp_int = 0;
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
        temp = temp1->content;
        temp1->content = temp2->content;
        temp2->content = temp;
        return;
    }
   /* string list::user_interface()
    {
        string command;
        Mission* temp_t = 0;
        int temp_int = 0;
        int temp_int_2 = 0;
        list* test = this;
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
                cin >> temp_t;
                cout << endl;
                test->pushfront(temp_t);
            }
            if (command == "back")
            {
                cout << "enter a number" << endl;
                cin >> temp_t;
                cout << endl;
                test->pushback(temp_t);
            }
            if (command == "incert")
            {
                cout << "enter a position" << endl;
                cin >> temp_int;
                cout << endl;
                cout << "enter a number" << endl;
                cin >> temp_t;
                cout << endl;
                test->incert(temp_int - 1, temp_t);
            }
            if (command == "get")
            {
                cout << "enter a position" << endl;
                cin >> temp_int;
                cout << endl;
                test->get(temp_int);
            }
            if (command == "print")
            {
                test->printlist();
            }
            if (command == "delete")
            {
                cout << "enter a position" << endl;
                cin >> temp_int;
                cout << endl;
                test->delete_member(temp_int - 1);
            }
            if (command == "delete_list")
            {
                delete test;
                return "new list";
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
                cin >> temp_int;
                cout << endl << "enter second member of the list" << endl;
                cin >> temp_int_2;
                cout << endl;
                test->swap(temp_int - 1, temp_int_2 - 1);
            }
            if (command == "fill")
            {
                cout << "enter an ammound" << endl;
                cin >> temp_int;
                cout << endl;
                for (T i = 0.0; i < temp_int / 2; i++)
                {
                    test->pushback(i / 2);
                }
                for (T i = (T)temp_int / 2; i < temp_int; i++)
                {
                    test->pushback(-i / 2);
                }

            }
            if (command == "empty")
            {
                delete test;
                test = new list;
            }
        }
        return "exit";
    }*/

    void list::Print_commands()
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
    list* list::find(const int n)
    {
        if (this->next == 0 || n == 0)
        {
            return this;
        }
        int i = 0;
        list* temp = this;
        while (i != n - 1)
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

