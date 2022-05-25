#include "main.h"
void FileIn(HeadsTails *pHeadsTails) {
    River *list;
    FILE *filePtr;
    char sFileName[20];
    printf("������� ��� �����: ");
    scanf_s("%s", sFileName);
    if((filePtr = fopen(sFileName, "w+")) != NULL) {
        fprintf(filePtr, "BEGIN");
        if (pHeadsTails->head != NULL) {
            list = pHeadsTails->head;
            printf("������� ��� �����: ");
            while (1) {
                fprintf(filePtr, "\n%s\n%.2f\n%.2f", list->name, list->depth, list->length);
                if (list->pNext != NULL) {
                    list = list->pNext;
                }
                else break;
            };
        } else printf("��������! ������ ������!");
        fclose(filePtr);
    }
    else printf("���������� �������� � ����!");
    system("timeout 1");
}

HeadsTails *FileOut(HeadsTails *pHeadsTails) {
    char buf[40]; //��������� �����
    int count = 0;
    River *list;
    FILE *filePtr;
    char sFileName[20];
    printf("������� ��� �����: ");
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
                if (pHeadsTails->tail != NULL) { //������������ ������ �� ����� � �������������
                    pHeadsTails->tail->pNext = list;
                    list->pPrev = pHeadsTails->tail;
                } else pHeadsTails->head = list;
            }
            fgets(list->name, 50, filePtr); //� ������� ������ ��������������� ����� � ����
            list->name[strlen(list->name) - 1] = 0; //�� ������������ ������ ������ 1������-name, 2�-depth, 3�-length
            fgets(buf, 50, filePtr);
            list->depth = atof(buf);
            fgets(buf, 50, filePtr);
            list->length = atof(buf);
            count++;
        }
        pHeadsTails->tail = list;
    }
    fclose(filePtr);
    if(count) printf("����� ��� ���� ��������� �� �����: %d.", count);
    else printf("���� %s ��� ����! ���� �� ����������!", sFileName);
    pHeadsTails->size += count;
    system("timeout 2");
    return pHeadsTails;
}