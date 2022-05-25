#include "main.h"
//������������� ������ ������
HeadsTails * createDblLinkedList() {
    HeadsTails *list = (HeadsTails *) malloc(sizeof(HeadsTails));
    list->size = 0;
    list->head = list->tail = NULL;
    return list;
}
//�������� ������
void deleteDblLinkedList(HeadsTails *list) {
    River *tmp = list->head;
    River *next = NULL;
    while (tmp) {
        next = tmp->pNext;
        free(tmp);
        tmp = next;
    }
    free(list);
    list = NULL;
}
//������������� ���� ������
River *createRiver(){
    River *newRiver = (River*) malloc(sizeof (River));
    newRiver->pNext = newRiver->pPrev = NULL;
    return newRiver;
}
//���������������� ���� ��������
River *userInputElement(){
    River *new_river = createRiver();
    printf("���: ");
    scanf("%s", new_river->name);
    printf("�������: ");
    fflush(stdin);
    scanf_s("%f", &new_river->depth);
    fflush(stdin);
    printf("�����: ");
    scanf_s("%f", &new_river->length);
    fflush(stdin);
    return new_river;
}
//������� �������� � ������ ������
void pushFront(HeadsTails *list, River *newRiver) {
    newRiver->pNext = list->head;
    newRiver->pPrev = NULL;
    if (list->head) {
        list->head->pPrev = newRiver;
    }
    list->head = newRiver;

    if (list->tail == NULL) {
        list->tail = newRiver;
    }
    list->size++;
}
//� ����� ������
void pushBack(HeadsTails *list, River *newRiver) {
    newRiver->pNext = NULL;
    newRiver->pPrev = list->tail;
    if (list->tail) {
        list->tail->pNext = newRiver;
    }
    list->tail = newRiver;

    if (list->head == NULL) {
        list->head = newRiver;
    }
    list->size++;
}

//��������� �� ������ �������� �������� �� ������������ �������
River* getNthing(HeadsTails *list, int index) {
    River *tmp = NULL;
    int i;
    //��� ��������� �������� � ���������� ������, ����� ��������� ��� ������� � � ����� ������
    if (index < list->size/2) {
        i = 0;
        tmp = list->head;
        while (tmp && i < index) {
            tmp = tmp->pNext;
            i++;
        }
    } else {
        i = list->size - 1;
        tmp = list->tail;
        while (tmp && i > index) {
            tmp = tmp->pPrev;
            i--;
        }
    }
    //������ ��� ��������� ����� ������ - �������� NULL
    return tmp;
}

//��������� ��� ������� ������� ������� �������� � ������
void insert(HeadsTails *list, int index, River *insertedRiver) {
    //��� ��������� ������� = 0, �� ��������� � ����� ������, �������� ��������������� �������
     if(index == 0) {
        pushBack(list, insertedRiver);
        return;
     }
     // index = 1 �� �� ��������� � ������
     else if (index == 1) {
        pushFront(list, insertedRiver);
        return;
     }

    River *element = NULL;
    element = getNthing(list, index);
    if (element == NULL) {
        return; //�� ������� ������� � ������, ������� �� �������
    }
    insertedRiver->pPrev = element;
    insertedRiver->pNext = element->pNext;
    if (element->pNext) {
        element->pNext->pPrev = insertedRiver;
    }
    element->pNext = insertedRiver;

    if (!element->pNext) {
        list->tail = element;
    }//��������, ��� ��������� ������ ����� ������, ������� ����� �������� � ������ ��������� �����

    list->size++;
}
//�������� N �������� ������
void deleteNth(HeadsTails *list, int index) {
    River *elm = NULL;
    elm = getNthing(list, index);
    if (elm == NULL) {
        return;
    }
    //������ ��������� ���������� � ����������� ���������
    if (elm->pPrev) {
        elm->pPrev->pNext = elm->pNext;
    }
    if (elm->pNext) {
        elm->pNext->pPrev = elm->pPrev;
    }
    //��������� ������ � ����� ������
    if (!elm->pPrev) {
        list->head = elm->pNext;
    }
    if (!elm->pNext) {
        list->tail = elm->pPrev;
    }

    free(elm);

    list->size--;
}
//����� ��������� ����� ������, ����� �� � ����� ��������� ������,
// ������� �� ������ ��������� ������� � �������� ���������,
//� ����� ������ ��� ������������� �����, ��������� ��� �������� ������
void LenList(HeadsTails *pHeadsTails){
    int lenList = 0;
    River *head = pHeadsTails->head;
    for (; head != NULL ; head = head->pNext) lenList++;
    printf("%d           %d", lenList, pHeadsTails->size);

    system("timeout 200");
}

void PrintList(River *head){
    int i = 0;
    system("cls");
    if (head != NULL) {
        printf("------------------------------------------------------------------------------------\n");
        do {
            char *str[] = {
                    "������������",
                    "��� ��������������",
                    "��� ����������������"
            };
            enum ships{
                NO_SHIPS,
                SMALL,
                LARGE
            };
            printf("Index: %4d| Name: %10s| Depth: %7.2f| "
                   "Length: %7.2f|", i, head->name, head->depth, head->length);
            printf("%20s|\n", head->depth<2 ? str[NO_SHIPS] : head->depth<4 ? str[SMALL]:str[LARGE] );
            printf("------------------------------------------------------------------------------------\n");
            head = head->pNext;
            i++;
        } while (head != NULL);
    }
    else printf("������ ����");
    system("timeout 200");
}


HeadsTails *fromArray(River **arr, int n) {
    HeadsTails *tmp = NULL;
    int i = 0;
    if (arr == NULL) {
        exit(7);
    }
    tmp = createDblLinkedList();
    while (i < n) {
        pushBack(tmp, arr[i]);
        i++;
    }
    return tmp;
}
River **convertToArray(HeadsTails *list){
    River **array = (River **) malloc(list->size*sizeof (River));
    River *node = list->head;
    for (int i = 0; i < list->size; i++) {
        array[i] = node;
        node = node->pNext;
    }
    return array;
}

void SortList(River **array_list, int left, int right, int choice) {
    River *node, *buf;
    int i = left; // ���������� ������� ������� � i, j
    int j = right;
    node = array_list[(left+right)/2];
    do {
        switch (choice) {
            case 0:{
                while (stricmp(array_list[i]->name, node->name) < 0 ) {
                    printf("%d", i);
                    i++;
                }
                while (stricmp(array_list[j]->name, node->name) > 0 ) {
                    printf("j%d", j);
                    j--;
                }
                break;
            }
            case 1:{
                while (array_list[i]->depth < node->depth)
                    i++;
                while (array_list[j]->depth > node->depth)
                    j--;
                break;
            }
            case 2:{
                while (array_list[i]->length < node->length)
                    i++;
                while (array_list[j]->length > node->length)
                    j--;
                break;
            }
            default:{
                break;
            }
        }

        if(i<=j){
            buf = array_list[i];
            array_list[i] = array_list[j];
            array_list[j] = buf;
            i++;
            j--;
        }
    } while(i<=j);
    if(left < j) SortList(array_list, left, j, choice);
    if(right > i) SortList(array_list, i, right, choice);
}

void listReverse (HeadsTails *pHeadsTails)
{
    River *prev = NULL, *list = pHeadsTails->head;
    pHeadsTails->tail = list;
    while (list)
    {
        River *next = list->pNext;

        list->pNext = prev;
        list->pPrev = next;

        prev = list;
        list = next;
    }

    pHeadsTails->head = prev;
}