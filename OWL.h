#ifndef UNTITLED3_OWL_H
#define UNTITLED3_OWL_H

#include <corecrt.h>
#include "structures.h"
HeadsTails * createDblLinkedList();
void deleteDblLinkedList(HeadsTails *list);

River *createRiver();
River *userInputElement();
void pushFront(HeadsTails *list, River *newRiver);
void pushBack(HeadsTails *list, River *newRiver);
River *getNthing(HeadsTails *list, int index);
void insert(HeadsTails *list, int index, River *insertedRiver);

void deleteNth(HeadsTails *list, int index);

void LenList(HeadsTails *pHeadsTails);

void PrintList(River *head);

void listReverse (HeadsTails *pHeadsTails);
void SortList(River **array_list, int left, int right, int choice);
HeadsTails *fromArray(River **arr, int n);
River **convertToArray(HeadsTails *list);

#endif //UNTITLED3_OWL_H
