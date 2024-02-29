#include <stdio.h>
#include <stdlib.h>

//生成一个完全二叉树 利用数组 并且写了可以在树和数组间相互转化的函数

typedef struct TreeNode{
    int val;
    struct TreeNode *left, *right;
}TreeNode;

TreeNode* AryToTree (int ary[], int len){
    TreeNode** ApoyaArt = (TreeNode** )malloc(sizeof(TreeNode*) * (len + 1));
    int front, tail , index;
    TreeNode* root;
    TreeNode* tree = (TreeNode* )malloc(sizeof(TreeNode));
    tree->left = NULL;
    tree->right = NULL;
    tree->val = -1;

    front = 0;
    tail = 0;
    index = 0;

    tree->val = ary[index]; //将输入数组的第一个元素入队
    ApoyaArt[++tail] = tree;
    root = tree; //记录根节点

    while(front != tail){
        tree = ApoyaArt[++front]; //从队列中探出一个元素
        if (!tree->left && index != len - 1){
            tree->left = (TreeNode*) malloc (sizeof(TreeNode));
            tree->left->val = ary[++index];
            ApoyaArt[++tail] = tree->left;
        }
        if (!tree->right && index != len - 1){
            tree->right = (TreeNode*) malloc (sizeof(TreeNode));
            tree->right->val = ary[++index];
            ApoyaArt[++tail] = tree->right;
        }
    }

    free(ApoyaArt);
    return root;
}

void DisplayTree (TreeNode* t, int space, int position){
    if (!t) return;

    space += 5;

    DisplayTree(t->left, space, -1);

    
    for (int i = 0; i < space; i ++){
        printf(" ");
    } 
    if (position == -1)
        printf("--/ %d\n\n", t->val);
    else if (position == 1)
        printf("--\\ %d\n\n", t->val);
    else
        printf("--| %d\n\n", t->val);

    DisplayTree (t->right, space, 1);
}

void DestoryTree (TreeNode* t){
    if(!t) return;

    DestoryTree(t->left);
    DestoryTree(t->right);
    free(t);
}

int* TreeToAry (TreeNode* t, int volumen){
    int* ary = (int*) malloc (sizeof(int) * (volumen + 1));
    TreeNode* point;
    TreeNode** ApoyaAry = (TreeNode** )malloc(sizeof(TreeNode*));

    int front = 0, tail = 0, index = 0; // 我们用index 为 0 的情况来存储数组的长度;
    ApoyaAry[++tail] = t;
    while (front != tail){
        point = ApoyaAry[++front];
        ary[++index] = point->val;
        if(point->left) ApoyaAry[++tail] = point->left;
        if(point->right) ApoyaAry[++tail] = point->right;
    }
    ary[0] = index;
    free (ApoyaAry);
    return ary;
}

int main(){
    int test[] = {1, 2, 3, 4, 5, -1, 7, 8};
    TreeNode* root;
    root = AryToTree (test, 8);
    DisplayTree(root, 2, 0);

    int *ary = TreeToAry (root, 8);
    for (int i = 1; i <= ary[0]; i ++){
        printf("   %d", ary[i]);
    }

    DestoryTree(root);
    return 0;
}