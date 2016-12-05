//
// Created by kirill on 05.12.2016.
//

#include "Fireworks2D.h"
#include <gl/gl.h>
#include <math.h>
#include <GL/freeglut.h>
#include <iostream>

Fireworks2D::Fireworks2D() {
    offsetMain = 0.0f;
    offsetAdditional = 0.0f;
    offsetSparks = 0.0f;
    ttlMain = 0.0f;
    ttlSparks = 0.0f;
    ttlAdditional = 0.0f;
    speedMain = 0.0f;
    speedSparks = 0.05f;
    speedAdditional = 0.02f;
    angle = 0;
    addAngle = 0;
    sparksOrAdditional = 0;
    X = 0;
    Y = 0;
}

void Fireworks2D::Fire(int flag) {

    if (flag == 0) glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 10.0f,
              0.0f, 4.1f, 0.0f,
              0.0f, 1.0f, 0.0f);
    glRasterPos2f(-8.8f,9.5f);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)"Fireworks v1.0");
    glRasterPos2f(-8.65f,9.0f);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"Tracing status:");
    if (flag==1)glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)"  ON!");
    glRasterPos2f(-8.56f,8.75f);
    glutBitmapString(GLUT_BITMAP_HELVETICA_10, (const unsigned char*)"Trace switching by mouse keys!");


    //Рисуем пушку (она присутствует в кадре всегда)
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0.0);
    glVertex3f(0, 0.2, 0.0);
    glVertex3f(0.1, 0.2, 0.0);
    glVertex3f(0.1, 0, 0.0);
    glEnd();

    if (offsetMain < ttlMain) {
        mainCharge();
        // Когда закончилось время жизни основного снаряда
    } else {
        // Случайный выбор доп.снарядов или искр ("случайность" можно решулировать)
        (sparksOrAdditional > 5) ? sparks() : additionalCharges();
        if (offsetSparks > ttlSparks) {
            // Когда закончилось время жизни доп.снарядов или искр, готовим новый главный заряд
            initialize();
        }
    }
    glutSwapBuffers();
}

void Fireworks2D::mainCharge(void) {
    glPointSize(10);
    glBegin(GL_POINTS);
    X = offsetMain * angle;
    Y = (-2 * offsetMain * offsetMain + 9.8f * offsetMain);
    glVertex2f(X, Y);
    glEnd();
    offsetMain += speedMain;
}

void Fireworks2D::sparks(void) {
    glPointSize(5);
    glBegin(GL_POINTS);

    for (int i = 0; i < 50; ++i) {
        //Искры движутся случайно в пределах окружности
        float x = X + offsetSparks * (rand() % 20 - 10);
        float y = Y + (rand() % 20 - 10) * sqrtf(10 * offsetSparks * offsetSparks - (x - X) * (x - X));
        glVertex2f(x + (rand() % 20 - 10) * sqrtf(110 * offsetSparks * offsetSparks - (y - Y) * (y - Y)) / 10,
                   y
        );
    }
    glEnd();
    offsetSparks += speedSparks;
}

void Fireworks2D::sparks(float X1, float Y1, float X2, float Y2) {
    glPointSize(4);
    glBegin(GL_POINTS);
    for (int i = 0; i < 50; ++i) {
        float x1 = X1 + offsetSparks * (rand() % 20 - 10);
        float y1 = Y1 + (rand() % 20 - 10) * sqrtf(10 * offsetSparks * offsetSparks - (x1 - X1) * (x1 - X1));
        float x2 = X2 + offsetSparks * (rand() % 20 - 10);
        float y2 = Y2 + (rand() % 20 - 10) * sqrtf(10 * offsetSparks * offsetSparks - (x2 - X2) * (x2 - X2));
        glVertex2f(x1 + (rand() % 20 - 10) * sqrtf(110 * offsetSparks * offsetSparks - (y1 - Y1) * (y1 - Y1)) / 10,
                   y1
        );
        glVertex2f(x2 + (rand() % 20 - 10) * sqrtf(110 * offsetSparks * offsetSparks - (y2 - Y2) * (y2 - Y2)) / 10,
                   y2
        );
    }
    glEnd();
    offsetSparks += speedSparks;
}

void Fireworks2D::additionalCharges(void) {
    if (offsetAdditional > ttlAdditional) { //Если заряды "прогорели" - запускаем искры
        sparks(X + offsetAdditional * (angle + addAngle),
               Y + (-offsetAdditional * offsetAdditional + 9.8f * offsetAdditional),
               X + offsetAdditional * (angle - addAngle),
               Y + (-offsetAdditional * offsetAdditional + 9.8f * offsetAdditional));
    } else {
        glPointSize(8);
        glBegin(GL_POINTS);
        glVertex2f(X + offsetAdditional * (angle + addAngle),
                   Y + (-offsetAdditional * offsetAdditional + 9.8f * offsetAdditional));
        glVertex2f(X + offsetAdditional * (angle - addAngle),
                   Y + (-offsetAdditional * offsetAdditional + 9.8f * offsetAdditional));
        glEnd();
        offsetAdditional += speedAdditional;
    }
}

void Fireworks2D::initialize(void) {
    angle = 0;
    while (angle ==0) angle = (rand() % 20 - 10);
    addAngle = ((rand() % 9 + 1) / 10.0f); //Погрешность несовпадения углов малых снарядов с основным
    ttlMain = ((rand() % 19 + 1) / 20.0f); //Случайное время жизни главного снаряда
    ttlSparks = ttlAdditional = ttlMain / (2 + ((rand() % 9 + 1) /
                                                20.0f)); //Время жизни искр и снарядов примерно в два раза меньше основного
    offsetMain = 0.0f;
    offsetAdditional = 0.0f;
    offsetSparks = 0.0f;
    speedMain = ((rand() % 24 + 6) / 10000.0f); //Случайная скорость главного снаряда
    speedSparks = ttlMain / 500; //Скорость искры пропорциональна времени жизни снаряда
    speedAdditional = speedMain * (2 + ((rand() % 9 + 1) /
                                        20.0f)); //Скорость движения малых зарядов примерно в два раза больше основного
    sparksOrAdditional = rand() % 9 + 1;
    glColor3f(((rand() % 9 + 1) / 10.0f), ((rand() % 9 + 1) / 10.0f), ((rand() % 9 + 1) / 10.0f));

}
