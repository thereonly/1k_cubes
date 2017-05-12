#ifndef PLAYER_H
#define PLAYER_H

#include "cubes.h"
#include <QString>

class Player
{
public:
    Player();

    int step();

    int getRes();
    void setRes(int);

    int getScore();
    void setScore(int);

    QString getName();
    void setName(QString);

    void setBolt();
    int getBolt();

    QString getUsedCubes();
    QString getNonUsedCubes();

    bool canStep();
    void clearBolt();
    void freeCubes();
    void setCubesRes();
    void samosval();    // ?

protected:
    Cubes cubes;
    int score;
    int res;
    int bolt;
    QString name;
};

#endif // PLAYER_H
