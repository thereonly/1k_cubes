#include "cube.h"

Cube::Cube()
{
    availability = true;
}

void Cube::gen(){

    value = rand()%6 + 1;
}

bool Cube::getAvailability(){
    return availability;
}

void Cube::setAvailability(bool val){
    availability = val;
}

void Cube::setValue(int val){
    value = val;
}

int Cube::getValue(){
    return value;
}
