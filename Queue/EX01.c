#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1

typedef enum _bool{
    TRUE = 1,
    FALSE = 0
}bool;

typedef struct _Queue{
    int val;
    struct _Queue *front;
    struct _Queue *tail;
}Queue;

int InitQueue (Queue* q){ //这里有疑问 随后解决 , 如果传入的本身就是一个指针变量 或者 传入的是一个正常的值然后取地址的区别
    // q = (Queue* )malloc (sizeof(Queue));
    // if(!q) return ERROR;
    q->front = NULL;
    q->tail = NULL;
    q->val = 0;
    return OK;
}

int Push (Queue* q, int val, bool isFront){
    Queue* newNode = (Queue* )malloc(sizeof(Queue));
    if(!newNode) return ERROR;

    if(!q->front && !q->tail){ //判断指向头尾的两个指针是不是都是空, 这是都是空的情况

        newNode->front = NULL;
        newNode->tail = NULL;
        newNode->val = val;

        q->front = newNode;
        q->tail = newNode;
        q->val++;
    }else if (isFront == TRUE){ //加在队列的首部, 正常应该是队列尾部入队, 队列首部出队
        
        q->front->front = newNode;

        newNode->tail = q->front;
        newNode->front = NULL;
        newNode->val = val;

        q->front = newNode;
        q->val++;
    }else{ // 一般情况

        q->tail->tail = newNode;
        
        newNode->front = q->tail;
        newNode->tail = NULL;
        newNode->val = val;

        q->tail = newNode;
        q->val++;
    }
    return OK;
    
}

int Pop (Queue* q, bool isFront){
    if(!q->front && !q->tail) return ERROR; //队列为空
    if (q->front == q->tail){ // 这个情况是我最初没有考虑的 , 因为只剩下一个元素的时候 , 队列尾部的指针也要变 ,如果不在下面的判断条件里写明,就必须单独写这个条件
        printf ("POP(FRONT):  %d\n", q->front->val);
        free(q->front);
        q->front = NULL;
        q->tail = NULL;
    }else if (isFront == TRUE){
        Queue* temp = q->front;
        printf ("POP(FRONT):  %d\n", temp->val);

        q->front = temp->tail;
        if(q->front)q->front->front = NULL; //这个情况我也没有考虑 ,应该指针移动后 链表头部的前一个指针挂空

        free(temp);
    }else{
        Queue* temp = q->tail;
        printf ("POP(TAIL):  %d\n", temp->val);

        q->tail = temp->front;
        if(q->tail) q->tail->tail = NULL;//这个情况我也没有考虑 ,应该指针移动后 链表尾部的后一个指针挂空

        free(temp);
    }
    q->val--; //本例子中没用这个值
    return OK;

}

int DelQue (Queue* q){
    if (!q->front && !q->tail) return ERROR;
    Queue* temp;
    while (q->front){
        temp = q->front;
        q->front = temp->tail;
        free(temp);
    }
    return OK;
    
}

void LenQue (Queue q){
    if(q.val) printf("LEN: %d\n", q.val);
    else printf("LEN:   %d\n", q.val);
}

int main (){
    Queue q;
    InitQueue(&q);
    Push(&q, 1, FALSE);
    Push(&q, 2, FALSE);
    Push(&q, 3, FALSE);
    Push(&q, 4, FALSE);
    Push(&q, 5, FALSE);
    Push(&q, 6, FALSE);
    Push(&q, 7, FALSE);
    LenQue(q);
    Pop(&q, FALSE);
    Pop(&q, TRUE);
    Pop(&q, TRUE);
    Push(&q, 21, FALSE);
    Push(&q, 31, FALSE);
    Push(&q, 41, FALSE);
    Pop(&q, FALSE);
    Pop(&q, TRUE);
    Pop(&q, TRUE);
    LenQue(q);
    DelQue(&q);
    return 0;
}

