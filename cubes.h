#ifndef CUBES_H
#define CUBES_H

#include "cube.h"
#include <QHash>
#include <QDebug>
#include <QtCore>
#include <QString>

class Cubes
{
public:
    Cubes();

    bool generate();
    bool check();
    bool haveNonUsedCubes();
    void setAllAvailable();

    void setResult(int);
    int getResult();

    QString getUsedCubes();
    QString getNonUsedCubes();

protected:
    int result;
    Cube cube[5];
};

#endif // CUBES_H
