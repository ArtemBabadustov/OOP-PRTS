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

    int get_coordinate(std::string coordinate);
   
private:
    int x;
    int y;
    int z;
};
class Mission
{
public:
    Mission();
    virtual std::string who_are_you();
    virtual point get_end_point() const;
protected:

    point start;
    point end;
    std::string name = "Not assigned!";
};
class Dive : public Mission
{
    std::string type_of_descend;
    std::string type_of_depth_definition;
    int radius;
    void get_depth(point n_depth);
public:
    Dive(point n_start); 
    virtual std::string who_are_you() override;
    //point get_end_point() const;
};

class Lift : public Mission
{
    std::string type_of_descend;
    std::string type_of_depth_definition;
    int radius;
    void get_depth(point n_depth);
public:
    Lift(point n_start);
    virtual std::string who_are_you() override;
    //point get_end_point() const;
};

class Move : public Mission
{
    std::string type_of_exit;
    std::string type_of_depth_maint;
    int tolerance = 0;
    point start;
    point end;
public: 
    Move(point n_start); 
};
