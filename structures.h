#ifndef UNTITLED3_STRUCTURES_H
#define UNTITLED3_STRUCTURES_H
typedef struct River{ // объ€вл€ем структуру согласно заданию
    char name[50];
    float depth, length;
    struct River *pNext;
    struct River *pPrev;
}River;

typedef struct HeadsTails{ // храним head's и tail's списков
    River *head,*tail;
    int size;
}HeadsTails;
#endif
