#pragma once
#include <iostream>
#include <string>
#include "main.h"
using namespace std;
class list
{
public:

    ~list();
  
    void pushback(Mission* p);
   
    void pushfront(Mission* n);
    
    void incert(int pos, Mission* c);
    
    void delete_member(int n);
    
    Mission* get(int n);
        
    void printlist();
   
    int size();
   

    void integrity_check();
    
    void swap(int a, int b);
    
   // string user_interface();
   
protected:
    void Print_commands();
    
    list* find(const int n);
   
    Mission* content = 0;
    list* next = 0;
    list* previous = 0;
};
