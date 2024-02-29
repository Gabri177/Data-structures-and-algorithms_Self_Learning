#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFERASIBLE -1
#define OVERFLOW -2

typedef struct Node{
    int nums;
    struct Node* next;
    
}Node;

void InitNode (Node* L){
    L->next = NULL;
    L->nums = 0;
}

int AddElem (Node* L, int elem){
    Node* Newnode = (Node* )malloc(sizeof(Node));
    if(!Newnode) return ERROR;
    Node* p = L;
    while(p->next){
        p = p->next;
    }
    p->next = Newnode;
    Newnode->nums = elem;
    Newnode->next = NULL;
    return OK;
}

void DestChain (Node* L){
    Node* p;
    Node* b;
    p = L;
    b = L->next;
    while(b){
        p = b;
        b = b->next;
        free(p);
    }
    L->next = NULL;
}

Node* QueryValue (Node L, int value){
    if(!L.next){
        printf("链表为空!!\n");
        return NULL;
    }
    Node* p;
    p = L.next;
    while (p)
    {
        if (p->nums == value){
            return p;
        }
        p = p->next;
    }
    return NULL;
    
}

void DispChain (Node* L){
    Node* p;
    int i = 1;
    p = L->next;
    while (p){
        printf("这是链表中的第%d个元素的值:%d\n", i++, p->nums);
        p = p->next;
    }

}

int main (){
    Node test;
    InitNode(&test);
    AddElem(&test, 12);
    AddElem(&test, 22);
    AddElem(&test, 32);
    AddElem(&test, 42);
    Node* test2;
    test2 = QueryValue(test, 22);
    printf("这是我们查找的值:%d\n", test2->nums);
    DispChain(&test);

    DestChain(&test);
    return 0;
}