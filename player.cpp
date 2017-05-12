#include "player.h"

Player::Player()
{
    score = 0;
    bolt = 0;
    res = 0;
}

bool Player::canStep(){
    if ( res != 0 )                     // Если есть свободные кубики, можем ходить и мы накидали хоть что-то
        return true;
    else                                // Ну а если нет, то нет
        return false;
}


int Player::step(){
    res = 0;
    bool check = cubes.generate();
    if (check){
        res = cubes.getResult();
    } else{
        qDebug() << QString("Кажется, последний бросок вышел не особо удачным...");
    }

    qDebug() << QString("Игрок накидал: ");
    qDebug() << int(res);
    int tmp = score + res;              // Просто чтобы в условиях не писать везде эту сумму

    /* Если мы что-то накидали и при этом больше не осталось свободных кубиков,
     * делаем все их снова доступными
     */
    // if ( (res != 0) && (!cubes.haveNonUsedCubes()) )
    //     cubes.setAllAvailable();

    qDebug() << QString("Итого, у игрока в сумме с броском: ");
    qDebug() << int(tmp);

    if ( (tmp < 50) && (res == 0) )
        return 0;
    else if ((res != 0) && (tmp < 50)){
        return 3;
    }

    if ( (tmp >= 400) && (tmp < 450) && (res == 0) ){
        return 0;
    }
    else if ((res != 0) && (tmp < 450) && (tmp > 400)){
        score = 400;
        return 3;
    }

    if ( (tmp >= 880) && (tmp < 1000) && (res == 0) ){
        return 0;
    }
    else if ((res != 0) && (tmp < 1000) && (tmp > 880)){
        score = 880;
        return 3;
    }

    if (tmp == 555)
        return 2;       // Увы

    if (tmp >= 1000)
        return 4;       // Этот запах победы...

    if (!check)         // Раз мы дошли сюда, мы не на бочке. Если ничего не накидали - ловим болт
        return -1;

    return 1;           // Оставшийся случай - мы что-то накидали

}

void Player::setCubesRes(){
    cubes.setResult(0);
}

void Player::setRes(int value){
    res = value;
}

int Player::getRes(){
    return res;
}

int Player::getScore(){
    return score;
}

void Player::setScore(int value){
    score += value;
}

void Player::setName(QString value){
    name = value;
}

QString Player::getName(){
    return name;
}

int Player::getBolt(){
    return bolt;
}

void Player::clearBolt(){
    bolt = 0;
}

void Player::setBolt(){
    bolt++;
    if(bolt == 3){
        score = 0;
        bolt = 0;
    }
}

QString Player::getNonUsedCubes(){
    return cubes.getNonUsedCubes();
}

QString Player::getUsedCubes(){
    return cubes.getUsedCubes();
}

void Player::freeCubes(){
    cubes.setAllAvailable();
}

void Player::samosval(){
    score = 0;
}
