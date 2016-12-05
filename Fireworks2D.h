//
// Created by kirill on 05.12.2016.
//

#ifndef GLUT_FIREWORKS2D_H
#define GLUT_FIREWORKS2D_H

class Fireworks2D {
private:
    //Траектории (пути) снарядов и искр
    float offsetMain;
    float offsetAdditional;
    float offsetSparks;
    //Время жизни
    float ttlMain;
    float ttlSparks;
    float ttlAdditional;
    //Скорости
    float speedMain;
    float speedSparks;
    float speedAdditional;
    //Углы
    float angle;
    float addAngle;
    //Что будем запускать (доп.снаряды или сразу искры)
    int sparksOrAdditional;
    //Координаты главного снаряда
    float X;
    float Y;

public:
    Fireworks2D();

    void Fire(int);

private:
    //Метод описывает главный заряд
    void mainCharge(void);

    //Метод описывает сноп искр
    void sparks(void);

    // Перегрузка метода под двойные заряды
    void sparks(float X1, float Y1, float X2, float Y2);

    //Метод описывает два побочных заряда
    void additionalCharges(void);

    //Инициализация (готовим новый снаряд)
    void initialize(void);

};

#endif //GLUT_FIREWORKS2D_H
