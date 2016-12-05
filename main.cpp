#include <gl/gl.h>
#include <GL/freeglut.h>
#include <iostream>
#include "Fireworks2D.h"

float WinWidth = 1500.0;
float WinHeight = 900.0;
float WinPosX = 20.0;
float WinPosY = 20.0;
Fireworks2D firework;
int flag = 0;


// Обработчик изменения размеров окна
void changeSize(int w, int h) {
    // предотвращение деления на ноль
    if (h == 0)
        h = 1;
    float ratio = w * 1.0 / h;
    // используем матрицу проекции
    glMatrixMode(GL_PROJECTION);
    // обнуляем матрицу
    glLoadIdentity();
    // установить параметры вьюпорта
    glViewport(0, 0, w, h);
    // установить корректную перспективу
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    // вернуться к матрице проекции
    glMatrixMode(GL_MODELVIEW);
}

// "Рисующая" функция
void renderScene() {

    firework.Fire(flag);
}

// Добавляем возможность запуска трассировки по щелчкам мыши
void mousePress(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON) {
        flag=0;
    }
    if (button == GLUT_RIGHT_BUTTON) {
        flag=1;
    }

}
int main(int argc, char **argv) {
    FreeConsole();
    // Инициализация GLUT и создание окна
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WinWidth, WinHeight);
    glutInitWindowPosition(WinPosX, WinPosY);
    glutCreateWindow("Fireworks");

    // Регистрация "рисующей" функции
    glEnable(GL_POINT_SMOOTH);
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutMouseFunc(mousePress);

    // Основной цикл
    glutMainLoop();

    return 1;
}

