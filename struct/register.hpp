#include <iostream>
#include <variant>
#include <cstring>

using namespace std;

struct Register {    
    int key;
    virtual variant<int, float, string> getKey() = 0;
    virtual void print() = 0;
};