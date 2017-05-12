#include "cubes.h"

Cubes::Cubes()
{
    result = 0;
}

bool Cubes::haveNonUsedCubes(){
    int count = 0;
    for (int i = 0; i < 5; i++){
        if(cube[i].getAvailability())
            count++;
        //  qDebug() << QString("Кол-во свободных кубиков: ");
        //  qDebug() << int(count);
    }

  //  if ( count == 0 ){
  //      for (int i = 0; i < 5; i++)
  //          cube[i].setAvailability(true);
  //  }

    if (count == 0){
        return false;
    } else{
        return true;
    }
}

bool Cubes::generate(){                         // Чет не хорошо
    srand(time(NULL));
    if (haveNonUsedCubes()){                    // Если есть неисп кубики - ходим
        for (int i = 0; i < 5; i++){            // Для каждого кубика
            if (cube[i].getAvailability()){     // Проверяем, не использован ли конкретно этот кубик
                cube[i].gen();                  // Генерим значение
                if (cube[i].getValue() == 1)    // Если выпало 1 - присваиваем значение 10 (правила игры)
                    cube[i].setValue(10);
            }
        }

        if (check()){
            return true;                        // все нормально, ходим
        } else{
            return false;                       // увы, болт
        }
    }
}

void Cubes::setAllAvailable(){
    for (int i = 0; i < 5; i++){
        cube[i].setAvailability(true);
        cube[i].setValue(0);
    }
}


bool Cubes::check(){                            // Проверяем, не болт ли это, а заодно подсчитываем очки
    bool flag = false;                          // false - болт, true - не болт
    for(int j = 2; j <= 6; j++){
        int q = 0;                              // Кол-во кубиков одинакового значения
        for (int i = 0; i < 5; i++){
        //    qDebug() << int(cube[i].getValue());
            if ((cube[i].getValue() == j) && cube[i].getAvailability()){
                q++;
            }
        }

        if (q > 2){
            for (int i = 0; i < 5; i++)
                if ( (cube[i].getValue() == j)){
                    cube[i].setAvailability(false);
                }
            flag = true;
        }

        switch (q) {
            case 3:
                result += j * 10;
                break;
            case 4:
                result += j * 40;
                break;
            case 5:
                result += j * 100;
            default:
                break;
        }
    }

    int q = 0;
    for (int j = 0; j < 5; j++){
        if (cube[j].getAvailability() && (cube[j].getValue() == 10))
            q++;
    }
    if (q > 2){
        for (int j = 0; j < 5; j++)
            if(cube[j].getAvailability() && (cube[j].getValue() == 10))
                cube[j].setAvailability(false);
        flag = true;
    }
    switch (q) {
        case 3:
            result += 10 * 10;
            break;
        case 4:
            result += 10 * 40;
            break;
        case 5:
            result += 10 * 100;
            break;
        default:
            break;
    }

    for(int i = 5; i <=10; i+=5)
        for(int j = 0; j < 5; j++)
            if((cube[j].getValue() == i) && cube[j].getAvailability())
            {
                result += i;
                cube[j].setAvailability(false);
                flag = true;
            }
    return flag;
}

void Cubes::setResult(int val){
    result = val;
}

int Cubes::getResult(){
    return result;
}

QString Cubes::getNonUsedCubes(){
    QString answer = "";
    for (int i = 0; i < 5; i++){
        if (cube[i].getAvailability()){
            answer = answer + QString::number(cube[i].getValue()) + " ";
        }
    }
    return answer;
}

QString Cubes::getUsedCubes(){
    QString answer = "";
    for (int i = 0; i < 5; i++){
        if (!cube[i].getAvailability()){
            answer = answer + QString::number(cube[i].getValue()) + " ";
        }
    }
    return answer;
}

