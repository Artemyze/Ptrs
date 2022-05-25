#include "main.h"
//инициализация нового списка
HeadsTails * createDblLinkedList() {
    HeadsTails *list = (HeadsTails *) malloc(sizeof(HeadsTails));
    list->size = 0;
    list->head = list->tail = NULL;
    return list;
}
//удаление списка
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
//инициализация узла списка
River *createRiver(){
    River *newRiver = (River*) malloc(sizeof (River));
    newRiver->pNext = newRiver->pPrev = NULL;
    return newRiver;
}
//пользовательский ввод элемента
River *userInputElement(){
    River *new_river = createRiver();
    printf("Имя: ");
    scanf("%s", new_river->name);
    printf("Глубина: ");
    fflush(stdin);
    scanf_s("%f", &new_river->depth);
    fflush(stdin);
    printf("Длина: ");
    scanf_s("%f", &new_river->length);
    fflush(stdin);
    return new_river;
}
//вставка элемента в начало списка
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
//в конец списка
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

//выделение из списка элемента стоящего на определенной позиции
River* getNthing(HeadsTails *list, int index) {
    River *tmp = NULL;
    int i;
    //для выделения элемента в двусвязном списке, можно высчитать его позицию и с конца списка
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
    //индекс вне диапазона длины списка - вернется NULL
    return tmp;
}

//связываем все базовые функции вставки элемента в список
void insert(HeadsTails *list, int index, River *insertedRiver) {
    //при введенном индексе = 0, мы вставляем в конец списка, вызываем соответствующую функцию
     if(index == 0) {
        pushBack(list, insertedRiver);
        return;
     }
     // index = 1 то мы вставляем в начало
     else if (index == 1) {
        pushFront(list, insertedRiver);
        return;
     }

    River *element = NULL;
    element = getNthing(list, index);
    if (element == NULL) {
        return; //не найдена позиция в списке, выходим из функции
    }
    insertedRiver->pPrev = element;
    insertedRiver->pNext = element->pNext;
    if (element->pNext) {
        element->pNext->pPrev = insertedRiver;
    }
    element->pNext = insertedRiver;

    if (!element->pNext) {
        list->tail = element;
    }//возможно, нам передадут индекс конца списка, поэтому нужно поменять в списке указатель конца

    list->size++;
}
//удаление N элемента списка
void deleteNth(HeadsTails *list, int index) {
    River *elm = NULL;
    elm = getNthing(list, index);
    if (elm == NULL) {
        return;
    }
    //меняем указатели следующего и предыдущего элементов
    if (elm->pPrev) {
        elm->pPrev->pNext = elm->pNext;
    }
    if (elm->pNext) {
        elm->pNext->pPrev = elm->pPrev;
    }
    //проверяем начало и конец списка
    if (!elm->pPrev) {
        list->head = elm->pNext;
    }
    if (!elm->pNext) {
        list->tail = elm->pPrev;
    }

    free(elm);

    list->size--;
}
//можно проверить длину списка, храня ее в самой структуре списке,
// изменяя ее каждой операцией вставки и удаления элементов,
//а можно каждый раз пересчитывать длину, перебирая все элементы списка
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
                    "Несудоходная",
                    "Для малогабаритных",
                    "Для крупногабаритных"
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
    else printf("Список пуст");
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
    int i = left; // определяем границы массива в i, j
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