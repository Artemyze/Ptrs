#include "main.h"
void FileIn(HeadsTails *pHeadsTails) {
    River *list;
    FILE *filePtr;
    char sFileName[20];
    printf("Введите имя файла: ");
    scanf_s("%s", sFileName);
    if((filePtr = fopen(sFileName, "w+")) != NULL) {
        fprintf(filePtr, "BEGIN");
        if (pHeadsTails->head != NULL) {
            list = pHeadsTails->head;
            printf("Введите имя файла: ");
            while (1) {
                fprintf(filePtr, "\n%s\n%.2f\n%.2f", list->name, list->depth, list->length);
                if (list->pNext != NULL) {
                    list = list->pNext;
                }
                else break;
            };
        } else printf("Внимание! Список пустой!");
        fclose(filePtr);
    }
    else printf("Невозможно записать в файл!");
    system("timeout 1");
}

HeadsTails *FileOut(HeadsTails *pHeadsTails) {
    char buf[40]; //строковый буфер
    int count = 0;
    River *list;
    FILE *filePtr;
    char sFileName[20];
    printf("Введите имя файла: ");
    scanf_s("%s", sFileName);
    if ((filePtr = fopen(sFileName, "r")) != NULL){
        fgets(buf, 50, filePtr);
        while (!feof(filePtr)) {
            if (list != NULL) {
                list->pNext = createRiver();
                list->pNext->pPrev = list;
                list = list->pNext;
            } else {
                list = createRiver();
                if (pHeadsTails->tail != NULL) { //присоединяем список из файла к существующему
                    pHeadsTails->tail->pNext = list;
                    list->pPrev = pHeadsTails->tail;
                } else pHeadsTails->head = list;
            }
            fgets(list->name, 50, filePtr); //в функции вывода сформированного листа в файл
            list->name[strlen(list->name) - 1] = 0; //мы сформировали формат вывода 1строка-name, 2я-depth, 3я-length
            fgets(buf, 50, filePtr);
            list->depth = atof(buf);
            fgets(buf, 50, filePtr);
            list->length = atof(buf);
            count++;
        }
        pHeadsTails->tail = list;
    }
    fclose(filePtr);
    if(count) printf("Всего рек было прочитано из файла: %d.", count);
    else printf("Файл %s был пуст! Либо не существует!", sFileName);
    pHeadsTails->size += count;
    system("timeout 2");
    return pHeadsTails;
}