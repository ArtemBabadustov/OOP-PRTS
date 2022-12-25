#pragma once
#include <string>

// Operational area boarders
#define max_x 5000
#define min_x -5000
#define max_z 5000
#define min_z -5000
#define max_y 0
#define min_y -100

struct point
{
    point();
   
    point(int n_x, int n_y, int n_z);
    
    void change(int n_x, int n_y, int n_z);
    
    void change_x(int n_x);
   
    void change_y(int n_y);
   
    void change_z(int n_z);
  

    point operator + (point* other) const;
   
    point operator - (point* other) const;
   
    void operator = (const point* other);
   
private:
    int x;
    int y;
    int z;
};
class Mission
{

protected:

    point start;
    point end;
    std::string name = "Not assigned!";
};
class Dive : Mission
{
    Dive(point n_start, int delta_z);
};