#include <stdio.h>
#include <stdlib.h>
#define SPACE 5

#define MAX_TREE_CAPACIDAD 5000

typedef enum Point{
    LEFT = -1,
    RIGHT = 1,
    MIDDLE = 0
}Point;

typedef struct TreeNode {
    int val;
    int heigh;
    struct TreeNode* toLeft;
    struct TreeNode* toRight;
}TreeNode;

typedef struct Queue{
    TreeNode** TreeNode;
    int capacidad;
    int front;
    int tail;
}Queue;

void InitQueue (Queue* q){
    q->front = 0;
    q->tail = 0;
    q->capacidad = 10;
    q->TreeNode = (TreeNode** )malloc(sizeof(TreeNode* ) * q->capacidad);
}

void PushQueue (Queue* q, TreeNode* t){
    q->TreeNode[(q->tail + q->capacidad + 1) % q->capacidad] = t;
    q->tail = (q->tail + 1 + q->capacidad) % q->capacidad;
}

int IfExistQueue(Queue* q){
    if (q->front == q->tail) return 0;
    else return 1;
}

TreeNode* PopQueue (Queue* q){
    q->front = (q->front + q->capacidad + 1) % q->capacidad;
    return q->TreeNode[q->front];
}

void BreakQueue (Queue* q){
    free(q->TreeNode);
}

TreeNode* newTreeNode (int val){
    TreeNode* node = (TreeNode* )malloc(sizeof(TreeNode));
    node->val = val;
    node->heigh = 0;
    node->toLeft = NULL;
    node->toRight = NULL;
    return node;
}


void InitTreeNode (TreeNode* t){
    t->toLeft = 0;
    t->toRight = 0;
    t->val = 0;
    t->heigh = 0;
}

void printTree(TreeNode* root, int space, Point stat) {
    if (root == NULL) {
        return;
    }

    // Increase distance between levels
    space += SPACE;

    // Process right child first
    printTree(root->toRight, space, RIGHT);

    // Print current node after space
    printf("\n");
    for (int i = SPACE; i < space; i++)
        printf(" ");
    if(stat == LEFT){
        printf("\\--%d\n", root->val);
    }else if(stat == RIGHT){
        printf("/--%d\n", root->val);
    }else{
        printf("--%d\n", root->val);
    }

    // Process left child
    printTree(root->toLeft, space, LEFT);
}

void printTree2 (TreeNode* t){
    TreeNode** temp = (TreeNode** )malloc(sizeof(TreeNode* ) * 10);
    int index = 0;
    temp[0] = NULL;
    TreeNode* p = t;
    
    while(index || p){
        if(p){
            temp[++index] = p;
            p = p->toLeft;
        }else{
            printf("--%d--", temp[index--]->val);
            p = temp[index + 1]->toRight;
        }
    }
    free(temp);

}

void PrintTree3 (TreeNode* root){
    Queue tempQue;
    TreeNode* tempNode;
    InitQueue (&tempQue);
    PushQueue(&tempQue, root);
    while (IfExistQueue(&tempQue)){
        tempNode = PopQueue(&tempQue);
        printf("--%d--", tempNode->val);
        if (tempNode->toLeft) PushQueue(&tempQue, tempNode->toLeft);
        if (tempNode->toRight) PushQueue (&tempQue, tempNode->toRight);
    }
    BreakQueue(&tempQue);
    
}


int main(){
    TreeNode n1;
    TreeNode n2;
    TreeNode n3;
    TreeNode n4;
    TreeNode n5;
    TreeNode n6;
    TreeNode n7;


    n1.toLeft = &n2;
    n1.toRight = &n3;
    n1.val = 1;


    n2.toLeft = &n4;
    n2.toRight = &n5;
    n2.val = 2;

    n3.toLeft = &n6;
    n3.toRight = &n7;
    n3.val = 3;

    InitTreeNode(&n4);
    n4.val = 4;
    InitTreeNode(&n5);
    n5.val = 5;
    InitTreeNode(&n6);
    n6.val = 6;
    InitTreeNode(&n7);
    n7.val = 7;

    printTree(&n1, 0, MIDDLE);
    //printTree2(&n1);
    PrintTree3(&n1);
    return 0;
    
}