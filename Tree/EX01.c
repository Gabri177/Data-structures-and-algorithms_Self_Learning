#include <stdio.h>
#include <stdlib.h>

typedef struct _treenode{
    int val;
    struct _treenode *left, *right;

}Node;

typedef enum _position{
    Left = -1,
    Right = 1,
    Middle = 0
}Position;

Node* InitTreeNode (){
    Node* new = (Node* )malloc(sizeof(Node));
    if(!new) return NULL;
    new->left = NULL;
    new->right = NULL;
    new->val = 0; 
    return new;
} 

void CreatComplateBTree (Node** r, int* count){
    if (*count == 0) return;
    if(*r == NULL) (*r) = InitTreeNode();
    (*r)->val = *count;
    (*count)--;
    int leftCount = *count / 2;  // 计算左子树应有的节点数
    int rightCount = *count - leftCount;  // 计算右子树应有的节点数

    // 先创建左子树
    *count = leftCount;
    CreatComplateBTree(&(*r)->left, count);

    // 创建右子树
    *count = rightCount;
    CreatComplateBTree(&(*r)->right, count);
}

void PrintSpace (int len){
    for(int i = 0; i < len; i++){
        printf(" ");
    }
}

void DisplayTree (Node* r, Position p, int nap){
    if (r == NULL) return;
    nap += 3;
    DisplayTree(r->left, Left, nap);
    if (p == Left){
        PrintSpace(nap);
        printf (" /左:%d \n", r->val);
    }else if (p == Middle){
        printf ("--根:%d\n", r->val);
    }else{
        PrintSpace(nap);
        printf (" \\右:%d \n", r->val);
    }
    DisplayTree(r->right, Right, nap);
}

void DestoryTree (Node* r){
    if (!r) return;
    DestoryTree(r->left);
    DestoryTree(r->right);
    free(r);
    r = NULL;
}

int main (){
    Node* Node = NULL;
    int count = 7;
    CreatComplateBTree (&Node, &count);
    DisplayTree (Node, Middle, 0);
    DestoryTree (Node);
    return 0;

}