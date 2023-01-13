
#include <iostream>
#include <string>
#include "main.h"
#include <fstream>
#include <vector>
using namespace std;


point::point() : x{ 0 }, y{ 0 }, z{ 0 }
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
void point::change_z(int n_z)
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
bool point::operator == (const point* other)
{
	if (this->get_coordinate("x") != other->get_coordinate("x") || this->get_coordinate("y") != other->get_coordinate("y")
		|| this->get_coordinate("z") != other->get_coordinate("z"))
	{
		return false;
	}
	else
	{
		return true;
	}
}

int point::get_coordinate(string coordinate) const
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
void Mission::get_int(int& input)
{
	string temp;
	cin >> temp;
	bool is_number = false;
	while (is_number != true)
	{
		is_number = true;
		try 
		{
			input = stoi(temp);
		}
		catch (const std::invalid_argument&)
		{
			is_number = false;
			cout << "You have entered an invalid number!" << endl
				<< "Please enter it again:" << endl;
			cin >> temp;
			cout << endl;
		}
	}
}

void Dive::get_depth(point n_start)
{
	string type_of_depth_def = "";
	cout << "List of avaliable types of depth definition:" << endl
		<< "1. Using depth sensor" << endl
		<< "2. Using echo-sounder" << endl
		<< "Please enter desired type(depth_sensor/echo_sounder)" << endl;
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
	this->get_int(depth);
	cout << endl;
	while (depth > max_y || depth < min_y || depth > n_start.get_coordinate("y"))
	{
		if (depth > max_y || depth < min_y)
		{
			cout << "You have entered depth that lies outside of the working area!" << endl
				<< "Operational depth lies between" << min_y << " and " << max_y << "meters." << endl
				<< "Please enter desired depth again" << endl;
			this->get_int(depth);
			cout << endl;
		}
		if (depth > n_start.get_coordinate("y"))
		{
			cout << "Depth you have entered is higher than the current one!" << endl
				<< "Current depth is: " << n_start.get_coordinate("y") << "meters." << endl
				<< "Please enter depth lower than the one listed above" << endl;
			this->get_int(depth);
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
		this->get_int(radius);
		while (n_start.get_coordinate("x") + sqrt(radius) > max_x
			|| n_start.get_coordinate("x") + sqrt(radius) < min_x
			|| n_start.get_coordinate("z") + sqrt(radius) > max_z
			|| n_start.get_coordinate("z") + sqrt(radius) < min_z)
		{
			cout << "With the radius you have entered AUV will go out of it's operational zone!"
				<< endl << "Please enter a smaller radius:" << endl;
			this->get_int(radius);
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
		<< "Please enter desired type(depth_sensor/echo_sounder)" << endl;
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
	this->get_int(depth);
	cout << endl;
	cout << "Check point 1" << endl;
	while (depth > max_y || depth < min_y || depth < n_start.get_coordinate("y"))
	{
		if (depth > max_y || depth < min_y)
		{
			cout << "You have entered depth that lies outside of the working area!" << endl
				<< "Operational depth lies between" << min_y << " and " << max_y << "meters." << endl
				<< "Please enter desired depth again" << endl;
			this->get_int(depth);
			cout << endl;
		}
		if (depth < n_start.get_coordinate("y"))
		{
			cout << "Depth you have entered is lower than the current one!" << endl
				<< "Current depth is: " << n_start.get_coordinate("y") << "meters." << endl
				<< "Please enter depth higher than the one listed above" << endl;
			this->get_int(depth);
			cout << endl;
		}
	}
	cout << "Check point 2" << endl;
	n_start.change_y(depth);
	cout << "Check point 3" << endl;
	this->end = n_start;
	cout << "Check point 4" << endl;
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
		this->get_int(radius);
		while (n_start.get_coordinate("x") + sqrt(radius) > max_x
			|| n_start.get_coordinate("x") + sqrt(radius) < min_x
			|| n_start.get_coordinate("z") + sqrt(radius) > max_z
			|| n_start.get_coordinate("z") + sqrt(radius) < min_z)
		{
			cout << "With the radius you have entered AUV will go out of it's operational zone!"
				<< endl << "Please enter a smaller radius:" << endl;
			this->get_int(radius);
			cout << endl;
		}
	}
	this->type_of_ascend = type;
	this->start = n_start;
	get_depth(n_start);
	this->name = "Lift";
}
string Lift::who_are_you()
{
	string answer = "";

	if (this->type_of_ascend == "Vertical")
	{
		answer = "Vertical dive to depth ";
		answer += to_string(this->end.get_coordinate("y")) + " meters.";
	}
	else if (this->type_of_ascend == "Spiral")
	{
		answer = "Spiral dive to depth " + to_string(this->end.get_coordinate("y")) + " meters";
		answer += " with radius " + to_string(this->radius) + " meters.";
	}

	return answer;
}


Move::Move(point n_start)
{
	cout << "List of avaliable types of exit:" << endl
		<< "1. To the point" << endl
		<< "2. Along the line" << endl
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
			<< "2. Constant distance to the sea floor (sea_floor)" << endl
			<< "Please enter desired type of exit (point/line):" << endl;
		cin >> type_of_depth_maint;
		cout << endl;
	}
	type_of_depth_maint.shrink_to_fit();
	int x = 0, y = 0, z = 0;
	cout << "Please enter coordinates of a target point. Format of input is x y z." << endl;
	this->get_int(x);
	this->get_int(y);
	this->get_int(z);
	cout << endl;
	while (min_x > x || x > max_x || min_y > y || max_y < y || min_z > z || max_z < z)
	{
		cout << "Point you have entered lies outside of an operating area!" << endl
			<< " Please enter coordinates of a target point again. Format of input is x y z." << endl;
		this->get_int(x);
		this->get_int(y);
		this->get_int(z);
		cout << endl;
	}
	cout << "Please enter a dead zone radius around target point:" << endl;
	this->get_int(tolerance);
	this->end = point(x, y, z);
}
string Move::who_are_you()
{
	string answer = "";

	if (this->type_of_exit == "point")
	{
		answer = "Ordinary move to a point with coordinates: (";
		answer += to_string(this->end.get_coordinate("x")) + ", " + to_string(this->end.get_coordinate("y")) + ", "
			+ to_string(this->end.get_coordinate("z")) + "). ";
	}
	else if (this->type_of_exit == "line")
	{
		answer = "Move along the line to a point with coordinates: (";
		answer += to_string(this->end.get_coordinate("x")) + ", " + to_string(this->end.get_coordinate("y")) + ", "
			+ to_string(this->end.get_coordinate("z")) + "). ";
	}
	if (this->type_of_depth_maint == "depth")
	{
		answer += "During the move AUV maintains constant depth using depth sensor.";
	}
	else if (this->type_of_depth_maint == "sea_floor")
	{
		answer += "During the move AUV maintains constant distance to the sea floor using echo sounder.";
	}
	answer += "AUV is considered to be at the target point when it enters a " + to_string(this->tolerance) + " meters radius.";
	return answer;
}

Return::Return(point n_start)
{
	end = point(0, 0, 0);
	start = n_start;
}
string Return::who_are_you()
{
	return "Return to the starting point.";
}

ofstream fout;
ifstream fin;

int main()
{
	vector <Mission*> test;
	Mission* temp = 0;

	//fout.open("Test Mission.txt");
	string command = "";

	while (command != "Exit")
	{
		cout << "List of avaliable commands:" << endl
			<< "1. New (adds a new step into the sequence)" << endl
			<< "2. Log (Writes the mission to the file without exiting the programm)" << endl
			<< "3. Print (Distlays currently recorded missions without writing to the file)" << endl
			<< "4. Exit (Save the file and close the program)" << endl
			<< "Please enter one of the commands listed above:" << endl;
		cin >> command;
		if (command == "New")
		{
			string type_of_mission = "";
			cout << "List of avaliable missions:" << endl
				<< "1. Dive (Descend to given depth)" << endl
				<< "2. Lift (Ascend to given depth)" << endl
				<< "3. Move (Move to given coordinates)" << endl
				<< "4. Return (Return to the starting point with coordinates [0,0,0])" << endl
				<< "Please enter one of the missions listed above:" << endl;
			cin >> type_of_mission;
			while (type_of_mission != "Dive" && type_of_mission != "Lift" && type_of_mission != "Move" && type_of_mission != "Return")
			{
				cout << "You have entered an incorrect type of mission!" << endl
					<< "List of avaliable inputs:" << endl
					<< "Dive" << endl
					<< "Lift" << endl
					<< "Move" << endl
					<< "Return" << endl
					<< "Please enter one of the missions listed above: " << endl;
				cin >> type_of_mission;
				cout << endl;
			}
			if (type_of_mission == "Dive")
			{
				if (test.size() == 0)
				{
					test.push_back(new Dive(point(0, 0, 0)));
				}
				else
				{
					test.push_back(new Dive(test[test.size() - 1]->get_end_point()));
				}
			}
			else if (type_of_mission == "Lift")
			{
				if (test.size() == 0)
				{
					cout << "Now you are at the starting point with coordinates (0,0,0). You can't lift!" << endl;
					//break;
				}
				else
				{
					test.push_back(new Lift(test[test.size() - 1]->get_end_point()));
				}
			}
			else if (type_of_mission == "Move")
			{
				if (test.size() == 0)
				{
					test.push_back(new Move(point(0, 0, 0)));
				}
				else
				{
					test.push_back(new Move(test[test.size() - 1]->get_end_point()));
				}
			}
		}
		else if (command == "Log")
		{
			fout.open("Test Mission.txt");
			for (int i = 0; i < test.size(); i++)
			{
				fout << to_string(i) + ". " + test[i]->who_are_you() << endl;
			}
			//fout.flush();
			fout.close();
		}
		else if (command == "Print")
		{
			for (int i = 0; i < test.size(); i++)
			{
				cout << to_string(i) + ". " + test[i]->who_are_you() << endl;
			}
		}
		else if (command == "Return")
		{
			if (test.size() == 0)
			{
				cout << "You are at the starting point. You cant return!" << endl;
			}
			else if (test[test.size() - 1]->get_end_point() == &point(0, 0, 0))
			{
				cout << "You are at the starting point. You cant return!" << endl;
			}
			else
			{
				test.push_back(new Return(test[test.size() - 1]->get_end_point()));
			}
		}
		cout << endl << endl;
	}
	if (test.size() != 0)
	{
		if (test[test.size() - 1]->who_are_you() != "Return")
		{
			test.push_back(new Return(test[test.size() - 1]->get_end_point()));
		}
		fout.open("Test Mission.txt");
		for (int i = 0; i < test.size(); i++)
		{
			fout << to_string(i) + ". " + test[i]->who_are_you() << endl;
		}
		fout.close();
	}
	return 0;
}

