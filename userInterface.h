#ifndef UNTITLED3_USERINTERFACE_H
#define UNTITLED3_USERINTERFACE_H
#include "main.h"
//основные меню
void menuList(HeadsTails *pHeadsTails);
void menuAdd(HeadsTails *pHeadsTails);

//побочное меню выбора позиции для вставки элемента
int menuChangePos();

//функции пользовательского выбора
_Bool userChoice(int *choice, int max);
void userArrow(int choice, int prevChoice);
#endif
