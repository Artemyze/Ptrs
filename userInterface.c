#include "main.h"
/* очищается консоль
 * пользователь выбирает клавишами ? ? определенную строку, подтверждает выбор enter'ом
 * в каждой строке описана функция, в которую 'зайдет' пользователь, при ее выборе
 * количество строк для выбора ограничено в самой функции меню
 */
void menuList(HeadsTails *pHeadsTails){
    _Bool isWork = 1;//для работы основного цикла
    do{
        int choice = 0,//выбор строки
            max = 8;//максимальное количество строк для выбора
        system("cls");
        printf("Сохранить в файл\n"
               "Из файла..\n"
               "Добавить элемент\n"
               "Удалить\n"
               "Сортировка\n"
               "Инвертирование\n"
               "Длина списка\n"
               "Вывод списка\n"
               "Выход\n"
               "Нажмите Enter для выбора\n");
        //цикл пока пользователь не нажмет enter
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
                printf("Введите порядковый номер элемента к удалению: ");
                scanf("%d", &index);
                deleteNth(pHeadsTails, index);
                break;
            }
            case 4:{
                //для сортировки был выбран алгоритм быстрой сортировки
                //для которого нужно создать массив из узлов списка
                River **arr = convertToArray(pHeadsTails);

                //делаем меню выбора поля, по которому необходимо сортировать
                choice = 0;
                max = 2;
                system("cls");
                printf("По полю \"Имя\"\n"
                       "По полю \"Глубина\"\n"
                       "По полю \"Длина\"\n"
                       "Выберите поле сортировки");
                while (1){
                    if(!userChoice(&choice, max)) break;
                }

                //быстрая сортировка
                SortList(arr, 0, pHeadsTails->size - 1, choice );
                //собираем список из отсортированного массива
                pHeadsTails = fromArray(arr, pHeadsTails->size);
                break;
            }
            case 5:{
                //переворачиваем список
                listReverse (pHeadsTails);
                break;
            }
            case 6:{
                //печать на экран длины списка
                LenList(pHeadsTails);
                break;
            }
            case 7:{
                //выводим на экран все элементы списка
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
        //для информации пользователя о текущем значении позиции для вставки элемента
        switch (pos) {
            case 1:{
                sprintf(str, "начало");
                break;
            }
            case 0:{
                sprintf(str, "конец");
                break;
            }
            default:{
                sprintf(str, "%d", pos);
                break;
            }
        }

        printf("Добавить..\n"
               "Порядковый номер..\n"
               "Назад.\n"
               "Добавление будет произведено в %s\n"
               "Выберите пункт меню.\n", str);
        while (1){
            if(!userChoice(&choice, max)) break;
        }

        switch (choice) {
            case 0:{
                //функция вставки в определенную позицию элемента, введенного вручную
                insert(pHeadsTails, pos, userInputElement());
                break;
            };
            case 1:{
                //меняем позицию для вставки элемента
                int buf = 0;
                system("cls");
                buf = menuChangePos();
                if(buf > 0) pos = buf;//буфер может быть меньше нуля, если юзер не ввел никакого значения
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
        printf("В конец\n"
               "В начало\n"
               "Порядковый номер..\n"
               "Назад..\n"
               "Выберите пункт меню.\n"
               "Введите соответствующий номер: ");

        while (1){
            if(!userChoice(&choice, 3)) break;
        }

        switch (choice) {
            case 0: return 0;
            case 1: return 1;
            case 2:{
                printf("Введите порядковый номер элемента(0 - конец списка): ");
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
    coord.Y = (short)prevChoice;//координата всегда равна начальному положению предыдущей стрелки

    SetConsoleCursorPosition(handle, coord);
    printf("   ");//стираем стрелку
    //перерисовываем стрелку на текущую позицию
    coord.Y = (short)choice;
    SetConsoleCursorPosition(handle, coord);
    printf("<==");
    //переставляем курсор на базовую позицию
    coord.X = 0;
    SetConsoleCursorPosition(handle, coord);
}
_Bool userChoice(int *choice, int max){
    char ch = '0';
    int prevChoice = *choice;

    userArrow(*choice, prevChoice);//рисуем стрелку выбора
    //ждем пока юзер не нажмет на кнопку
    while (!kbhit());
    ch = _getch();

    if (ch == 72) {
        //стрелка вверх
        *choice -= 1;
        if (*choice < 0) *choice = max;
        userArrow(*choice, prevChoice);//перерисовываем стрелку
    }
    else if (ch == 80) {
        //стрелка вниз
        *choice += 1;
        if (*choice > max) *choice = 0;
        userArrow(*choice, prevChoice);
    }
    else if (ch == 13) {
        //enter
        system("cls");
        return FALSE;// родительское меню 'поймет', что пользователь выбрал определенную строку
    }
    return TRUE;
}