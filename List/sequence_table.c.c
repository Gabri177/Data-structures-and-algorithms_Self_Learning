#include <stdio.h> 
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFERASIBLE -1
#define OVERFLOW -2


#define LIST_INIT_SIZE 100

typedef struct{
    int* elem;
    int length;
}Sqlist;

int InitList (Sqlist* list){
    list->elem = (int *)malloc(LIST_INIT_SIZE * sizeof(int));
    if (!list->elem) return OVERFLOW;
    list->length = 0;
    return OK;
}

void ClearList (Sqlist* list){
    list->length = 0;
}

void DestroyList (Sqlist* list){
    free(list->elem);
    list -> elem = NULL;
}

int InsertElem (Sqlist* list, int elem, int position){
    if (position < 1 || position > LIST_INIT_SIZE) return OVERFLOW;
    int temp = list->length - 1;
    for (;temp >= position - 1; temp--){
        list->elem[temp + 1] = list->elem[temp];
    }
    list->elem[position - 1] = elem;
    list->length++;
    return OK;
}

int DeleElem (Sqlist* list, int posicion){
    if (posicion < 1 || posicion > list->length) return ERROR;
    for (int temp = posicion - 1; temp < list->length - 1; temp ++){
        list->elem[temp] = list->elem[temp + 1];
    }
    list->length--;
    return OK;
}

int AddElem (Sqlist* list, int nums){
    if(list->length + 1 > LIST_INIT_SIZE) return OVERFLOW;
    list->elem[list->length] = nums;
    list->length++;
    return OK;
}

void DisplayList (Sqlist* list){
    printf ("当前的顺序表的长度为  %d\n", list->length);
    for (int i = 0; i < list->length; i ++){
        printf ("这是第%d个元素的值:%d\n", i + 1, list->elem[i]);
    }
}


int main (){
    Sqlist list1;
    InitList(&list1);
    AddElem(&list1, 15);
    AddElem(&list1, 13);
    InsertElem (&list1, 5, 1);
    DeleElem (&list1, 2);

    DisplayList(&list1);

    ClearList(&list1);
    DisplayList(&list1);




    DestroyList (&list1);
    return 0;
}