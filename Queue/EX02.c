#include <stdio.h>
#include <stdlib.h>

// 我们写一个用数组实现的单向循环队列
#define SIZE 4 //实际大小其实只有SIZE - 1 因为我们规定, 以Front为下标的元素为守护元素, 不储存实际的值, 这样我们就可以通过---
#define ERROR 0 // ---判断Front和Tail是否指向同一个元素 而确定队列中是否还有元素. 这样有利于判断和逻辑的精简.
#define OK 1

enum _bool{
    TRUE = 1,
    FALSE = 0
};

typedef enum _bool bool;

typedef struct _Queue{
    int* nums;
    int front;
    int tail;
}Queue;

int InitQue (Queue* q){
    q->front = 0;
    q->tail = 0;
    q->nums = (int* )malloc(SIZE * sizeof(int));
    return OK;
}

int LenQue (Queue q){
    if ((q.tail - q.front + SIZE) % SIZE == SIZE - 1) return SIZE;
    else return (q.tail - q.front + SIZE) % SIZE;
}

int Push (Queue* q, int val){
    if(LenQue(*q) == SIZE) return ERROR;
    q->tail = (++q->tail) % SIZE;
    q->nums[q->tail] = val;
    return OK;
}

int Pop (Queue* q){
    if(q->front == q->tail) return ERROR;
    printf("POP:   %d\n", q->nums[(q->front + 1) % SIZE]);
    q->front = (q->front + 1) % SIZE;
    return OK;
}

int DelQue (Queue* q){
    if(!q->nums) return ERROR;
    free(q->nums);
    return OK;
}

int main (){
    Queue q;
    InitQue (&q);
    Push (&q, 1);
    Push (&q, 2);
    Push (&q, 3);
    Push (&q, 4);
    Pop (&q);
    Pop (&q);
    Pop (&q); // 1, 2, 3  --- 此时元素为空
    Push (&q, 4);
    Push (&q, 5);
    Push (&q, 6);
    Pop (&q);
    Pop (&q);//4, 5 --- 此时元素为 6 空两个
    Push (&q, 1);
    Push (&q, 2);
    Push (&q, 3);
    Push (&q, 4);//6 , 1, 2
    Pop (&q);
    Pop (&q);
    Pop (&q);//元素清空
    Push (&q, 4);
    Push (&q, 5);
    Push (&q, 6);
    Pop (&q);
    Pop (&q);
    DelQue (&q);
    return 0;
}