#include <stdio.h>
#include <stdlib.h>

int SIZE = 3;

typedef enum _bool{
    TRUE = 1,
    FALSE = 0
}bool;

typedef struct _Queue{
    int* nums;
    int front;
    int tail;
}Queue;

void InitQue (Queue* q){
    q->nums = (int *)malloc (sizeof(int) * SIZE);
    if (!q->nums) printf("ERROR: DISTRIBUCION OF ESPACIO OF NUMS\n");
    q->front = 0;
    q->tail = 0;
    printf("INICIACION CON EXCITO\n");
}

int LenQue (Queue* q){
    return (q->tail - q->front + SIZE) % SIZE;
}

void ExtenQue (Queue* q){
    if (LenQue(q) == 0) printf("NO NECESSART EXTEND\n");
    int OldSize = SIZE;
    SIZE *= 2;
    if (q->front < q->tail){
        int* temp = (int* )malloc(sizeof(int));
        int i = q->front;
        for(;i <= q->tail;i++){
            temp[i] = q->nums[i];
        }
        free(q->nums);
        q->nums = temp;
    }else{
        int* temp = (int *)malloc(sizeof(int));
        int i = q->front;
        for(;i < OldSize; i++){
            temp[i] = q->nums[i];
        }
        for(;i <= OldSize + q->tail; i++){
            temp[i] = q->nums[q->tail + i - OldSize];
        }
        q->tail = i - 1;
        free(q->nums);
        q->nums = temp;
    }
}

void Push (Queue* q, int val, bool isFront){
    if(LenQue(q) == SIZE - 1) ExtenQue(q);
    if (isFront == TRUE){
        q->nums[q->front] = val;
        q->front = (q->front - 1 + SIZE) % SIZE;
    }else{
        q->tail = (q->tail + 1 + SIZE) % SIZE;
        q->nums[q->tail] = val;
    }
}

void Pop (Queue* q, bool isFront){
    if(LenQue(q) == 0) printf("NONE ELEMENT\n");
    if(isFront == TRUE){
        q->front = (q->front + 1 + SIZE) % SIZE;
        printf("POP IS FRONT: %d\n", q->nums[q->front]);
    }else{
        printf("POP NOT FRONT: %d\n", q->nums[q->tail]);
        q->tail = (q->tail - 1 + SIZE) % SIZE;
    }
}

void DelQue (Queue* q){
    free(q->nums);
}

int main(){
    Queue q;
    InitQue(&q);
    Push(&q, 1, TRUE);
    Push(&q, 2, TRUE);
    Push(&q, 3, TRUE);
    Pop(&q, FALSE);
    Pop(&q, FALSE);
    Pop(&q, FALSE);
    DelQue(&q);
    return 0;
}