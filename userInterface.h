#ifndef UNTITLED3_USERINTERFACE_H
#define UNTITLED3_USERINTERFACE_H
#include "main.h"
//�������� ����
void menuList(HeadsTails *pHeadsTails);
void menuAdd(HeadsTails *pHeadsTails);

//�������� ���� ������ ������� ��� ������� ��������
int menuChangePos();

//������� ����������������� ������
_Bool userChoice(int *choice, int max);
void userArrow(int choice, int prevChoice);
#endif
