#include <stdio.h>
#include <stdlib.h>

char* tempchar = NULL;
int charlen = 0;

void PushChar (char val){ //全局字符变量数组的栈 添加一个字符
    if (charlen == 0){
        tempchar = (char* )malloc(sizeof(char));
        tempchar[0] = val;
        charlen++;
    }else{
        charlen++;
        char* temp = (char* )malloc(sizeof(char) * charlen);
        int i;
        for(i = 0; i < charlen - 1; i++){
            temp[i] = tempchar[i];
        }
        temp[i] = val;
        if(tempchar) free(tempchar);
        tempchar = temp;
    }
}

void PopChar (){ //全局字符变量数组的栈 弹出一个字符
    if (charlen == 0);
    else{
        charlen--;
        char* temp = (char* )malloc(sizeof(char) * charlen);
        for(int i = 0; i < charlen; i++)
            temp[i] = tempchar[i];
        if(tempchar) free(tempchar);
        tempchar = temp;
    }
}

void PrintChar(){ //打印当前 全局字符变量数组的栈
    if (charlen != 0){
        PushChar('\0');
        printf("\n目的位置为: %s\n", tempchar);
    }else{
        printf("\nNONE ELEMENTES!\n");
    }
    if(tempchar) free(tempchar);
    tempchar = NULL;
    charlen = 0;
}

typedef struct treenode { //树节点的结构体
    int val;
    int height;
    struct treenode *left, *right;
}treenode;

int HeightTreeNote (treenode* t){ //递归的方式求每个节点的高度 (节点到左子树或右子树最远叶子结点所经过的边的数量)
    if (t == NULL) {
        return -1; 
    }
    
    int leftHeight = HeightTreeNote(t->left);
    int rightHeight = HeightTreeNote(t->right);
    
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;

}

void MarkHeightToTree (treenode* root){ //将树所有的节点高度的值保存在对应的每个节点中
    if (!root) return;
    MarkHeightToTree (root->left);
    MarkHeightToTree (root->right);
    root->height = HeightTreeNote(root);
}

treenode* creatTreenode (int val){  //创建并初始化一个树的节点
    treenode* new = (treenode* )malloc(sizeof(treenode));
    new->left = NULL;
    new->right = NULL;
    new->val = val;
    new->height = -1;
    return new;
}

void inssertTreenode (treenode** root, int val){ //以平衡查找二叉树的方式插入节点 (val 为插入节点的值)
    if (!(*root)) *root = creatTreenode(val);
    else{
        treenode *pre = *root , *temp = *root;
        int position = 0;

        while(temp){
            if(val > temp->val){
                pre = temp;
                temp = temp->right;
                position = 1;
            }else if (val < temp->val){
                pre = temp;
                temp = temp->left;
                position = -1;
            }
        }

        if (position == 1) pre->right = creatTreenode(val);
        if (position == -1) pre->left = creatTreenode(val);
    }
    MarkHeightToTree (*root); // 每次二叉查找树加入新节点后 重新计算每个节点的高度并更改其高度到每个节点对应的高度值中
}

void destoryTree (treenode* t){ // 释放树的所有节点所占用的内存
    if(!t) return;
    destoryTree (t->left);
    destoryTree (t->right);
    free(t);
}

void displayTree (treenode* t, int space, int position){ //将当前的树以可视的方式打印出来, position默认为0即可, space为初始打印间距, 默认为0
    if(!t) return;
    space += 5;

    displayTree(t->left, space, -1);

    for (int i = 0; i < space; i++)
        printf (" ");
    if (position == -1) printf ("--/%d\n", t->val);
    else if (position == 1) printf ("--\\%d\n", t->val);
    else printf("--|%d\n", t->val);

    displayTree(t->right, space, 1);
}

void DatoToTree (treenode** root, int *nums, int len){ // 将一个数组中的每个值分别插入查找二叉树, 并创建树节点
    for (int i = 0; i < len; i++){
        inssertTreenode(root, nums[i]);
    }
}

void QuaryElem (treenode* t, int val){ // 在查找二叉树中查找值为val的节点 并以向左为0, 向右为1 的方式打印出查找元素val的位置
    if(!t){
        PopChar();
        return;
    }
    if(t->val == val) PrintChar();


    PushChar('0');
    QuaryElem(t->left, val);
    PushChar('1');
    QuaryElem(t->right, val);
    PopChar();
    

}

int balanceFactor (treenode* node){ //计算平衡因子 左子树高度与右子树高度的差值
    if(!node) return 0;
    if (node->left && node->right)
        return node->left->height - node->right->height;
    else if (!node->right)
        return node->left->height;
    else return node->right->height;
}

treenode* leftRotate (treenode* node){ // 将某个节点向左旋转 并重新更新其高度
    treenode *child, *grandchild;
    child = node->right;
    grandchild = child->left;

    child->left = node;
    node->right = grandchild;
    HeightTreeNote(node);
    return child;
}

treenode* rightRotate (treenode* node){ //将某个节点向右旋转 并更新其高度
    treenode *child, *grandchild;
    child = node->left;
    grandchild = child->right;

    child->right = node;
    node->left = grandchild;
    HeightTreeNote(child);
    return child;
}

treenode* Rotate (treenode* node){ //自动判断节点是否应该旋转 在什么时候进行什么方式的旋转 一般平衡因子超过1的绝对值 
    int factor = balanceFactor(node); // 我们进行旋转从而使得avl树达到平衡
    if (factor > 1){
        if(balanceFactor(node->left) >= 0)
            return rightRotate(node);
        else{
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }

    if (factor < -1){
        if(balanceFactor(node->right) >= 0)
            return leftRotate(node);
        else{
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    return node;
}

treenode* inssertApaly (treenode* node, int val){ //递归插入 并一次向上进行树节点的旋转 , 以使得avl树平衡
    if(!node) return creatTreenode(val);

    if(val > node->val) node->right = inssertApaly(node->right, val);
    else if (val < node->val) node->left =  inssertApaly(node->left, val);
    else return node;

    MarkHeightToTree (node);
    node = Rotate(node);
    return node;
}

void inssertValue (treenode** t, int val){ //插入函数
    *t = inssertApaly(*t, val);
}

treenode* removeApply (treenode* t, int val){ //递归查找val值的元素并删除
    if (!t) return NULL;

    if(val < t->val){
        t->left = removeApply(t->left, val);
    }else if (val > t->val){
        t->right = removeApply(t->right, val);
    }else{
        treenode *temp;
        int temVal;
        if(t->left && t->right){ //用中序循环元素后继顶替被删除元素位置
            temp = t->right;
            while(temp->left) temp = temp->left;
            temVal = temp->val;
            t->right = removeApply(t->right, temVal);
            t->val = temVal;
        }else if (t->left || t->right){
            treenode* temp2;
            temp2 = t->left;
            if (t->right) temp2 = t->right;
            t = temp2;
        }else return NULL;
    }

    MarkHeightToTree(t);
    t = Rotate(t);
    return t;
}

void removeElem (treenode** t, int val){
    removeApply(*t, val);
}

int main (){
    int vals[] = {8, 6, 15, 1, 7};
    treenode* root = NULL;  // 初始化很重要 , 你想不到能出啥错!!!!!!
    DatoToTree (&root, vals, 5);
    displayTree(root, 0, 0);
    printf("-----------------------------\n");
    inssertValue(&root, 10);
    displayTree(root, 0, 0);
    printf("-----------------------------\n");
    inssertValue(&root, 11);
    displayTree(root, 0, 0);
    printf("-----------------------------\n");
    inssertValue(&root, 9);
    displayTree(root, 0, 0);
    printf("-----------------------------\n");
    removeElem(&root, 10);
    displayTree(root, 0, 0);
    printf("-----------------------------\n");
    QuaryElem(root, 11);
    destoryTree(root);
    return 0;
}
