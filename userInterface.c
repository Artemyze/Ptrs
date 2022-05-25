#include "main.h"
/* ��������� �������
 * ������������ �������� ��������� ? ? ������������ ������, ������������ ����� enter'��
 * � ������ ������ ������� �������, � ������� '������' ������������, ��� �� ������
 * ���������� ����� ��� ������ ���������� � ����� ������� ����
 */
void menuList(HeadsTails *pHeadsTails){
    _Bool isWork = 1;//��� ������ ��������� �����
    do{
        int choice = 0,//����� ������
            max = 8;//������������ ���������� ����� ��� ������
        system("cls");
        printf("��������� � ����\n"
               "�� �����..\n"
               "�������� �������\n"
               "�������\n"
               "����������\n"
               "��������������\n"
               "����� ������\n"
               "����� ������\n"
               "�����\n"
               "������� Enter ��� ������\n");
        //���� ���� ������������ �� ������ enter
        while (1){
            if(!userChoice(&choice, max)) break;
        }

        switch (choice) {
            case 0:{
                FileIn(pHeadsTails);
                break;
            };
            case 1:{
                pHeadsTails = FileOut(pHeadsTails);
                break;
            }
            case 2:{
                menuAdd(pHeadsTails);
                break;
            }
            case 3:{
                int index;
                printf("������� ���������� ����� �������� � ��������: ");
                scanf("%d", &index);
                deleteNth(pHeadsTails, index);
                break;
            }
            case 4:{
                //��� ���������� ��� ������ �������� ������� ����������
                //��� �������� ����� ������� ������ �� ����� ������
                River **arr = convertToArray(pHeadsTails);

                //������ ���� ������ ����, �� �������� ���������� �����������
                choice = 0;
                max = 2;
                system("cls");
                printf("�� ���� \"���\"\n"
                       "�� ���� \"�������\"\n"
                       "�� ���� \"�����\"\n"
                       "�������� ���� ����������");
                while (1){
                    if(!userChoice(&choice, max)) break;
                }

                //������� ����������
                SortList(arr, 0, pHeadsTails->size - 1, choice );
                //�������� ������ �� ���������������� �������
                pHeadsTails = fromArray(arr, pHeadsTails->size);
                break;
            }
            case 5:{
                //�������������� ������
                listReverse (pHeadsTails);
                break;
            }
            case 6:{
                //������ �� ����� ����� ������
                LenList(pHeadsTails);
                break;
            }
            case 7:{
                //������� �� ����� ��� �������� ������
                PrintList(pHeadsTails->head);
                break;
            }
            case 8:{
                isWork = 0;
                break;
            }
            default:{
                break;
            }
        }
    } while (isWork);
}
void menuAdd(HeadsTails *pHeadsTails){
    _Bool isWork = 1;

    int pos = 0, choice = 0, max = 2;
    char str[10];

    do{
        system("cls");
        //��� ���������� ������������ � ������� �������� ������� ��� ������� ��������
        switch (pos) {
            case 1:{
                sprintf(str, "������");
                break;
            }
            case 0:{
                sprintf(str, "�����");
                break;
            }
            default:{
                sprintf(str, "%d", pos);
                break;
            }
        }

        printf("��������..\n"
               "���������� �����..\n"
               "�����.\n"
               "���������� ����� ����������� � %s\n"
               "�������� ����� ����.\n", str);
        while (1){
            if(!userChoice(&choice, max)) break;
        }

        switch (choice) {
            case 0:{
                //������� ������� � ������������ ������� ��������, ���������� �������
                insert(pHeadsTails, pos, userInputElement());
                break;
            };
            case 1:{
                //������ ������� ��� ������� ��������
                int buf = 0;
                system("cls");
                buf = menuChangePos();
                if(buf > 0) pos = buf;//����� ����� ���� ������ ����, ���� ���� �� ���� �������� ��������
                break;
            }
            case 2:{
                isWork = 0;
                break;
            }
            default:{
                break;
            }
        }
    } while (isWork);
    system("cls");
}
int menuChangePos(){
    _Bool isWork = 1;
    int choice = 0;
    do{
        printf("� �����\n"
               "� ������\n"
               "���������� �����..\n"
               "�����..\n"
               "�������� ����� ����.\n"
               "������� ��������������� �����: ");

        while (1){
            if(!userChoice(&choice, 3)) break;
        }

        switch (choice) {
            case 0: return 0;
            case 1: return 1;
            case 2:{
                printf("������� ���������� ����� ��������(0 - ����� ������): ");
                scanf_s("%d", &choice);
                system("cls");
                return choice;
            }
            case 3:{
                isWork = 0;
                break;
            }
            default:{
                break;
            }
        }
    } while (isWork);
    system("cls");
    return -1;
}
void userArrow(int choice, int prevChoice){
    COORD coord;

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

    coord.X = 20;
    coord.Y = (short)prevChoice;//���������� ������ ����� ���������� ��������� ���������� �������

    SetConsoleCursorPosition(handle, coord);
    printf("   ");//������� �������
    //�������������� ������� �� ������� �������
    coord.Y = (short)choice;
    SetConsoleCursorPosition(handle, coord);
    printf("<==");
    //������������ ������ �� ������� �������
    coord.X = 0;
    SetConsoleCursorPosition(handle, coord);
}
_Bool userChoice(int *choice, int max){
    char ch = '0';
    int prevChoice = *choice;

    userArrow(*choice, prevChoice);//������ ������� ������
    //���� ���� ���� �� ������ �� ������
    while (!kbhit());
    ch = _getch();

    if (ch == 72) {
        //������� �����
        *choice -= 1;
        if (*choice < 0) *choice = max;
        userArrow(*choice, prevChoice);//�������������� �������
    }
    else if (ch == 80) {
        //������� ����
        *choice += 1;
        if (*choice > max) *choice = 0;
        userArrow(*choice, prevChoice);
    }
    else if (ch == 13) {
        //enter
        system("cls");
        return FALSE;// ������������ ���� '������', ��� ������������ ������ ������������ ������
    }
    return TRUE;
}