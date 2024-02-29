#include <stdio.h>
#include <stdlib.h>


// 这是一个基于双向链表 和一个包含头尾指针的变量 而实现的队列结构

//主要想法是 用一个包含两个指针的结构体指针 里面的指针分别指向链表的头部和尾部 

//然后链表用同样的结构体变量构造一个双向链表

//用同一个结构体变量容易造成混淆, 而且如果不借助画图理解, 仅靠大脑思考很容易陷入逻辑漏洞

//最好是可以单独建立一个结构体用来存放头指针和尾部指针, 另外再单独做一个链表的结构体变量用来生成变量, 这样会好很多.

#define ERROR 0
#define OK 0

typedef struct _queue{
    int Value;
    struct _queue* FrontNode;
    struct _queue* TailNode;
}Queue;

int InitQueue (Queue** q){
    *q = (Queue* )malloc(sizeof(Queue));
    if(!(*q)) return ERROR;
    (*q)->FrontNode = NULL;
    (*q)->TailNode = NULL;
    (*q)->Value = 0;
    return OK;
}

int DelQueue (Queue* q){
    if(q->FrontNode == q->TailNode){
        free(q->FrontNode);
        free(q);
        return OK;
    }
    Queue* temp = q->TailNode;
    Queue* temp2;
    while (temp){
        temp2 = temp;
        free(temp2);
        temp = temp->FrontNode;
    }
    free(q);
    return OK;
}

int Push (Queue* q, int num){
    Queue* NewNode = (Queue* )malloc(sizeof(Queue));
    if(!NewNode) return ERROR;
    if(!q->FrontNode && !q->TailNode){
        q->FrontNode = NewNode;
        q->TailNode = NewNode;
        NewNode->Value = num;
        NewNode->FrontNode = NULL;
        NewNode->TailNode = NULL;
    }else{
        q->TailNode->TailNode = NewNode;
        NewNode->FrontNode = q->TailNode;
        NewNode->TailNode = NULL;
        NewNode->Value = num;
        q->TailNode = NewNode;
    }
    return OK;
}

int Pop (Queue* q){
    Queue* temp = q->FrontNode;
    if(!q->FrontNode && !q->TailNode) return ERROR;
    if (q->FrontNode == q->TailNode){
        printf("POP:    %d\n", temp->Value);
        q->FrontNode = NULL;
        q->TailNode = NULL;
        free(temp);
        return OK;
    }
    q->FrontNode = temp->TailNode;
    printf("POP:    %d\n", temp->Value);
    free(temp);
    return OK;
}

int main (){
    Queue* test;
    InitQueue(&test);
    Push(test, 42);
    Push(test, 2);
    Push(test, 1);
    Push(test, 3);
    Pop(test);
    Pop(test);
    Pop(test);
    Pop(test);
    Push(test, 243434);
    Pop(test);
    Pop(test);
    Push(test, 99999);
    Pop(test);
    Pop(test);
    Pop(test);
    Pop(test);
    Pop(test);

    
    DelQueue(test);
    return 0;
}
