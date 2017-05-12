#ifndef CUBE_H
#define CUBE_H

#include "time.h"
#include "stdlib.h"
#include <cstdlib>
#include <time.h>


class Cube
{
public:
    Cube();
    void setAvailability(bool);
    bool getAvailability();
    void setValue(int);
    int getValue();
    void gen();
protected:
    int value;
    bool availability;
};

#endif // CUBE_H
