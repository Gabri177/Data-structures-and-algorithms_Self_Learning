#include <stdio.h>
#include <stdlib.h>

//我们来实现一个单向可扩充的循环数组队列

#define ERROR 0
#define OK 1
int SIZE = 5;//留空一个元素为守护元素 实际上只能存储 9 个元素

typedef struct _Queue{
    int* nums;
    int front;
    int tail;
}Queue;

int InitQue (Queue* q){
    q->nums = (int *)malloc(SIZE * sizeof(int)); 
    if(!q->nums) return ERROR;
    q->front = 0;
    q->tail = 0;
    q->nums[q->front] = 0;
    return OK;
}

int LenQue (Queue q){ 
    return (q.tail - q.front + SIZE) % SIZE; //返回存储的元素数量 最大为 SIZE - 1
}

int ExtenQue (Queue* q){
    int *temp;
    temp = (int *)malloc(sizeof(int) * SIZE * 2);
    if (!temp) return ERROR;
    SIZE *= 2;
    if(LenQue(*q) == 0){
        printf("NO ELEMENT EN QUEUE, NO NECESSARY EXTEND\n");
        return ERROR;
    }
    else if(q->front < q->tail){
        // printf("不循环的情况: 原来的头下标: %d, 原来的尾下标: %d\n", q->front, q->tail);
        int i;
        for (i = q->front; i <= q->tail; i ++){
            temp[i] = q->nums[i];
        }
        free(q->nums);
        q->tail = i - 1;
        q->nums = temp;
        //printf("不循环的情况: 新的头下标: %d, 新的尾下标: %d\n", q->front, q->tail);

    }else{
        //printf("循环的情况: 原来的头下标: %d, 原来的尾下标: %d\n", q->front, q->tail);
        int i;
        for (i = q->front; i < SIZE / 2; i ++){ //注意这里的SIZE已经不是原来的SIZE了 所以要除2;
            temp[i] = q->nums[i];
        }
        //printf("I: %d\n", i);
        for(i = SIZE / 2;i < SIZE / 2 + q->tail + 1; i++){
            temp[i] = q->nums[i - SIZE / 2 + q->tail];
        }
        q->tail = i - 1;
        free(q->nums);
        q->nums = temp;
        //printf("循环的情况: 原来的头下标: %d, 原来的尾下标: %d\n", q->front, q->tail);
    }
    return OK;
}

void Push (Queue* q, int val){
    if(LenQue(*q) == SIZE - 1){
        ExtenQue(q);
        q->tail = (q->tail + 1) % SIZE;
        q->nums[q->tail] = val;
    }else{
        q->tail = (q->tail + 1) % SIZE;
        q->nums[q->tail] = val;
    }
}

int Pop (Queue* q){
    if (q->front == q->tail) return ERROR;
    printf("POP:   %d\n", q->nums[(q->front + 1) % SIZE]);
    q->front = (q->front + 1) % SIZE;
    return OK;
}

int DelQue (Queue q){
    if (!q.nums) return ERROR;
    free (q.nums);
    return OK;
}

void Display (Queue* q){
    printf ("----SIZE: %d---\n", SIZE);
    if(LenQue(*q) == 0){
        printf("NO ELEMENT EN QUEUE\n");
    }
    else if(q->front < q->tail){
        for (int i = q->front; i <= q->tail; i ++){
            printf("THE VALUE OF THE POSITION %d IS %d\n", i, q->nums[i]);
        }
    }else{
        int i;
        for (i = q->front; i < SIZE; i ++){
            printf("THE VALUE OF THE POSITION %d IS %d\n", i, q->nums[i]);
        }
        for(;i < SIZE + q->tail + 1; i++){
            printf("THE VALUE OF THE POSITION %d IS %d\n", i, q->nums[i - SIZE]);
        }
    }
    printf ("--------\n");
}

int main (){
    Queue q;
    InitQue(&q);
    Push (&q, 1);
    Push (&q, 2);
    Push (&q, 3);
    Push (&q, 4);
    //Display (&q);


    Pop (&q);
    Pop (&q);
    Pop (&q); // 1, 2, 3 --- 4
    //Display (&q);


    Push (&q, 4);
    Push (&q, 5);
    Push (&q, 6);
    //Display (&q);


    Pop (&q);
    Pop (&q);//4, 4 --- 5, 6
    //Display (&q);
    

    Push (&q, 1);
    Push (&q, 2);
    Push (&q, 3);
    Push (&q, 4);
    Push (&q, 5);
    //Display (&q);


    Pop (&q);
    Pop (&q);
    Pop (&q);//5, 6, 1 ---2, 3, 4
    //Display (&q);

    DelQue(q);
    return 0;
}