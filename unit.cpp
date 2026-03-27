#include "unit.h"
#include <random>
using namespace std;

Unit::Unit(string nm) : name(nm), target(nullptr){
    random_status();
}


