
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
    void Dive::get_depth( point n_start)
    {
        string type_of_depth_def = "";
        cout << "List of avaliable types of depth definition:" << endl
            << "1. Using depth sensor" << endl
            << "2. Using echo-sounder" << endl
            << "Please enter desired type(depth_sensor\echo_sounder)" << endl;
        cin >> type_of_depth_def;
        cout << endl;
        while (type_of_depth_def != "depth_sensor" && type_of_depth_def != "echo_sounder")
        {
            cout << "Type of depth definition has been entered incorrectly!" << endl
                << "Avaliable inputs:" << endl
                << "1. depth_sensor" << endl
                << "2. echo_sounder" << endl
                << "Please enter one of the types, listed above" << endl;
            cin >> type_of_depth_def;
            cout << endl;
        }
        this->type_of_depth_definition = type_of_depth_def;
        int depth = 10;
        cout << "please enter desired depth" << endl;
        cin >> depth;
        cout << endl;
        while (depth > max_y || depth < min_y || depth > n_start.get_coordinate("y"))
        {
            if (depth > max_y || depth < min_y)
            {
                cout << "You have entered depth that lies outside of the working area!" << endl
                    << "Operational depth lies between" << min_y << " and " << max_y << "meters." << endl
                    << "Please enter desired depth again" << endl;
                cin >> depth;
                cout << endl;
            }
            if (depth > n_start.get_coordinate("y"))
            {
                cout << "Depth you have entered is higher than the current one!" << endl
                    << "Current depth is: " << n_start.get_coordinate("y") << "meters." << endl
                    << "Please enter depth lower than the one listed above" << endl;
                cin >> depth;
                cout << endl;
            }
        }
        n_start.change_y(depth);
        this->end = n_start;
    }
    Dive::Dive(point n_start)
    {
        string type = "";
        cout << "List of avaliable descend types:" << endl
            << "1. Vertical" << endl
            << "2. Spiral" << endl;
        cout << "Please enter desired type of descend" << endl;
        cin >> type;
        cout << endl;
        
        while (type != "Vertical" && type != "Spiral")
        {
            cout << "Type of descend has been entered incorrectly!" << endl
                << "You have this options:" << endl
                << "1. Vertical" << endl
                << "2. Spiral" << endl
                << "Enter the type again" << endl;
            cin >> type;
            cout << endl;
        }
        type.shrink_to_fit();
        if (type == "Vertical")
        {
            radius = 0;
        }
        else
        {
            cout << "Please enter desired spiral radius" << endl;
            cin >> radius;
            while (n_start.get_coordinate("x") + sqrt(radius) > max_x
                || n_start.get_coordinate("x") + sqrt(radius) < min_x
                || n_start.get_coordinate("z") + sqrt(radius) > max_z
                || n_start.get_coordinate("z") + sqrt(radius) < min_z)
            {
                cout << "With the radius you have entered AUV will go out of it's operational zone!"
                    << endl << "Please enter a smaller radius:" << endl;
                cin >> radius;
                cout << endl;
            }
        }
        this->type_of_descend = type;
        this->start = n_start;
        get_depth(n_start);
        this->name = "Dive";
    }
    string Dive::who_are_you()
    {
        string answer = "";
        
        if (this->type_of_descend == "Vertical")
        {
            answer = "Vertical dive to depth ";
            answer += to_string(this->end.get_coordinate("y")) + " meters.";
        }
        else if (this->type_of_descend == "Spiral")
        {
            answer = "Spiral dive to depth " + to_string(this->end.get_coordinate("y")) + " meters";
            answer += " with radius " + to_string(this->radius) + " meters.";
        }
        
        return answer;
    }





    void Lift::get_depth(point n_start)
    {
        string type_of_depth_def = "";
        cout << "List of avaliable types of depth definition:" << endl
            << "1. Using depth sensor" << endl
            << "2. Using echo-sounder" << endl
            << "Please enter desired type(depth_sensor\echo_sounder)" << endl;
        cin >> type_of_depth_def;
        cout << endl;
        while (type_of_depth_def != "depth_sensor" && type_of_depth_def != "echo_sounder")
        {
            cout << "Type of depth definition has been entered incorrectly!" << endl
                << "Avaliable inputs:" << endl
                << "1. depth_sensor" << endl
                << "2. echo_sounder" << endl
                << "Please enter one of the types, listed above" << endl;
            cin >> type_of_depth_def;
            cout << endl;
        }
        type_of_depth_def.shrink_to_fit();
        this->type_of_depth_definition = type_of_depth_def;
        int depth = 10;
        cout << "please enter desired depth" << endl;
        cin >> depth;
        cout << endl;
        while (depth > max_y || depth < min_y || depth > n_start.get_coordinate("y"))
        {
            if (depth > max_y || depth < min_y)
            {
                cout << "You have entered depth that lies outside of the working area!" << endl
                    << "Operational depth lies between" << min_y << " and " << max_y << "meters." << endl
                    << "Please enter desired depth again" << endl;
                cin >> depth;
                cout << endl;
            }
            if (depth > n_start.get_coordinate("y"))
            {
                cout << "Depth you have entered is lower than the current one!" << endl
                    << "Current depth is: " << n_start.get_coordinate("y") << "meters." << endl
                    << "Please enter depth higher than the one listed above" << endl;
                cin >> depth;
                cout << endl;
            }
        }
        n_start.change_y(depth);
        this->end = n_start;
    }
    Lift::Lift(point n_start)
    {
        string type = "";
        cout << "List of avaliable ascend types:" << endl
            << "1. Vertical" << endl
            << "2. Spiral" << endl;
        cout << "Please enter desired type of ascend:" << endl;
        cin >> type;
        cout << endl;

        while (type != "Vertical" && type != "Spiral")
        {
            cout << "Type of descend has been entered incorrectly!" << endl
                << "You have this options:" << endl
                << "1. Vertical" << endl
                << "2. Spiral" << endl
                << "Enter the type again" << endl;
            cin >> type;
            cout << endl;
        }
        if (type == "Vertical")
        {
            radius = 0;
        }
        else
        {
            cout << "Please enter desired spiral radius" << endl;
            cin >> radius;
            while (n_start.get_coordinate("x") + sqrt(radius) > max_x
                || n_start.get_coordinate("x") + sqrt(radius) < min_x
                || n_start.get_coordinate("z") + sqrt(radius) > max_z
                || n_start.get_coordinate("z") + sqrt(radius) < min_z)
            {
                cout << "With the radius you have entered AUV will go out of it's operational zone!"
                    << endl << "Please enter a smaller radius:" << endl;
                cin >> radius;
                cout << endl;
            }
        }
        this->type_of_descend = type;
        this->start = n_start;
        get_depth(n_start);
        this->name = "Dive";
    }
    string Lift::who_are_you()
    {
        string answer = "";

        if (this->type_of_descend == "Vertical")
        {
            answer = "Vertical dive to depth ";
            answer += to_string(this->end.get_coordinate("y")) + " meters.";
        }
        else if (this->type_of_descend == "Spiral")
        {
            answer = "Spiral dive to depth " + to_string(this->end.get_coordinate("y")) + " meters";
            answer += " with radius " + to_string(this->radius) + " meters.";
        }

        return answer;
    }
    


    Move::Move(point n_start)
    {
        {
            cout << "List of avaliable types of exit:" << endl
                << "1. To the point"
                << "2. Along the line"
                << "Please enter desired type of exit (point/line):" << endl;
            cin >> type_of_exit;
            cout << endl;
            while (type_of_exit != "point" && type_of_exit != "line")
            {
                cout << "You have entered an unsupported type of exit!" << endl;
                cout << "List of avaliable types of exit:" << endl
                    << "1. To the point" << endl
                    << "2. Along the line" << endl
                    << "Please enter desired type of exit (point/line):" << endl;
                cin >> type_of_exit;
                cout << endl;
            }
            type_of_exit.shrink_to_fit();
            cout << "List of avaliable types of depth maintenance:" << endl
                << "1. Constant depth" << endl
                << "2. Constant distance to the sea floor" << endl
                << "Please enter desired type of depth maintenance (depth/sea_floor):" << endl;
            cin >> type_of_depth_maint;
            cout << endl;
            while (type_of_depth_maint != "depth" && type_of_depth_maint != "sea_floor")
            {
                cout << "You have entered an unsupported type of depth maintenance!" << endl;
                cout << "List of avaliable types of depth maintenance:" << endl
                    << "1. Constant depth (depth)" << endl
                    << "2. Constant distance to the sea floor (sea_floor)"
                    << "Please enter desired type of exit (point/line):" << endl;
                cin >> type_of_depth_maint;
                cout << endl;
            }
            type_of_depth_maint.shrink_to_fit();
        }
    }

   // ofstream fout;
    //ifstream fin;
int main()
{
    vector <Mission*> test;
    Mission* temp = 0;
    //temp = new Dive(point(0, 0, 0), 50);
    test.push_back(new Dive(point(0, 0 ,0)));
    test.push_back(new Dive(test[test.size() - 1]->get_end_point()));
   // cout << test[test.size() - 1]->who_are_you();
    for (int i = 0; i < test.size(); i++)
    {
        cout << i << ": " << test[i]->who_are_you() << endl;
    }

    /*string command = "";

    while (command != "exit")
    {
        cout << "List of avaliable commands:"
            << "1. New (adds a new step into the sequence)" << endl
            << "2. Log (Writes the mission to the file without exiting the programm)" << endl
            << "3. Exit (Save the file and close the program)" << endl
            << "Please enter one of the commands listed above:" << endl;
        cin >> command;
        if (command == "New")
        {
            string type_of_mission = "";
            cout << "List of avaliable missions:" << endl
                << "1. Dive (Ascend to given depth)" << endl
                << "Please enter one of the missions listed above:" << endl;
            cin >> type_of_mission;


            while ()
            {

            }
        }
           
    }*/

}
