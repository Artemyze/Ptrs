#ifndef UNTITLED3_STRUCTURES_H
#define UNTITLED3_STRUCTURES_H
typedef struct River{ // ��������� ��������� �������� �������
    char name[50];
    float depth, length;
    struct River *pNext;
    struct River *pPrev;
}River;

typedef struct HeadsTails{ // ������ head's � tail's �������
    River *head,*tail;
    int size;
}HeadsTails;
#endif
