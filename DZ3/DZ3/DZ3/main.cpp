
#include <iostream>
#include <string>
#include "list.h"
#include "main.h"
#include <fstream>
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
    Dive::Dive(point n_start, int delta_z)
    {
        this->start = n_start;
        point delta(0, 0, delta_z);
        this->end = n_start - &delta;
    }

    ofstream fout;
    ifstream fin;
int main()
{
    fout.open("prog_test.txt");
    fout << "Test of writing to file!" << endl;
    fout << "Test of writing second line to file!";
    cout << "text has been written" << endl;
    fout.flush();
    fout.clear();
    fout << "";
    cout << "fout has been cleared" << endl;
    fout << "";
    fout.flush();
    fout.close();
    cout << "fout is closed" << endl;
    return 0;
}


