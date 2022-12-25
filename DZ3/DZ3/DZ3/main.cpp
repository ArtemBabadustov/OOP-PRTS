
#include <iostream>
#include <string>
#include "main.h"
//#include <fstream>
#include <vector>
using namespace std;


    point::point() : x {0}, y {0}, z {0}
    {};
    point::point(int n_x, int n_y, int n_z)
    {
        x = n_x;
        y = n_y;
        z = n_z;
    };
    void point::change(int n_x, int n_y, int n_z)
    {
        x = n_x;
        y = n_y;
        z = n_z;
    };
    void point::change_x(int n_x)
    {
        x = n_x;
    };
    void point::change_y(int n_y)
    {
        y = n_y;
    }
    void point::change_z (int n_z)
    {
        z = n_z;
    }
    point point::operator + (point* other) const
    {
        point temp{ this->x + other->x, this->y + other->y, this->z + other->z };
        return temp;
    }
    point point::operator - (point* other) const
    {
        point temp{ this->x - other->x, this->y - other->y, this->z - other->z };
        return temp;
    }
    void point::operator = (const point* other)
    {
        this->x = other->x;
        this->y = other->y;
        this->z = other->z;
    }
    int point::get_coordinate(string coordinate) 
    {
        //cout << "get_coordiate is called" << endl;
        if (coordinate == "x")
        {
            //cout << this->x;
            return this->x;

        }
        else if (coordinate == "y")
        {
            //cout << this->x;
            return this->y;
        }
        else if (coordinate == "z")
        {
            //cout << "z coordinate is =" << this->z << endl;
            return this->z;
        }
        else
        {
            cout << "There is no coordinate with such name!";
            return 1;
        }
    }

    Mission::Mission()
    {
        start.change(0, 0, 0);
        end.change(0, 0, 0);
    }
    string Mission::who_are_you()
    {
        //std::string ans = "This_operation_in_mission isn't defined!";
        //ans = "Shit!";
        return "This_operation_in_mission isn't defined!";
    }
    point Mission::get_end_point() const
    {
        return this->end;
    }

    Dive::Dive(point n_start, int delta_z)
    {
        this->start = n_start;
        point delta(0, 0, delta_z);
        this->end = n_start - &delta;
        this->name = "Dive";
    }
    string Dive::who_are_you()
    {
        string answer;
        answer = "Dive to depth ";
        answer += to_string(this->end.get_coordinate("z"));
        return answer;
    }
    

   // ofstream fout;
    //ifstream fin;
int main()
{
    std::vector <Mission*> test;
    Mission* temp = 0;
    //temp = new Dive(point(0, 0, 0), 50);
    test.push_back(new Dive(point(0, 0 ,0), 50));
    test.push_back(new Dive(test[test.size() - 1]->get_end_point(), 20));
   // cout << test[test.size() - 1]->who_are_you();
    for (int i = 0; i < test.size(); i++)
    {
        cout << i << ": " << test[i]->who_are_you() << endl;
    }

}


