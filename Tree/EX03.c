#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// 这是一个创建哈夫曼树 并且将其叶节点的哈夫曼编码放入哈希表 并输出哈希表的过程
typedef enum bool{
    TRUE = 1,
    FALSE = 0
}bool;

typedef enum position{
    LEFT = -1,
    MIDDLE = 0,
    RIGHT = 1
}position;

typedef struct TreeNode {
    struct TreeNode *left, *right, *uproot;
    int value;
    int weight;
}TreeNode;

typedef TreeNode* AryTreeNode;  // 定义存放哈夫曼森林的树根节点指针结构

typedef struct Pair{
    int val;
    int key;
}pair;

typedef struct AryQueue{
    pair** bucket;
    int volumen;
    int len;
}AryQueue;

typedef struct mapset{
    int len;
    void* set;
}mapset;


int HashFunction (int key, int capacidad){
    return key % capacidad; 
}

void InitAryQueue (AryQueue** a, int capacidad){
    *a = (AryQueue* )malloc(sizeof(AryQueue));
    (*a)->volumen = capacidad;
    (*a)->len = 0;
    (*a)->bucket = (pair** )malloc(sizeof(pair*) * capacidad);
}

pair* NewPair (int key, int val){
    pair* tempPair = (pair* )malloc(sizeof(pair));
    tempPair->key = key;
    tempPair->val = val;
    return tempPair;
}

void PushQue (AryQueue* a, int key, int val){
    int index = HashFunction(key, a->volumen);
    if (a->len != a->volumen){
        if(!a->bucket[index]){
            a->bucket[index] = NewPair(key, val);
            a->len++;
        }
    }
}

mapset* GetPairSet (AryQueue* a){
    int index = 0;
    mapset* tempMapset = (mapset* )malloc(sizeof(mapset));
    pair* tempPair = (pair* )malloc(sizeof(pair) * a->len);
    tempMapset->len = a->len;
    for (int i = 0; i < a->volumen; i++){
        if (a->bucket[i]){
            tempPair[index] = *a->bucket[i];
            index++;
        }
    }
    tempMapset->set = tempPair;
    return tempMapset;
}

void PrintHash (AryQueue* a){
    mapset* temp = GetPairSet (a);
    for(int i = 0; i < temp->len; i ++){
        printf("KEY:  %d,  VALUE:  %d\n", ((pair*)(temp->set))[i].key,((pair*)(temp->set))[i].val);
    }
}

void DestoryQue(AryQueue* a){
    int i;
    for (;i < a->volumen; i++)
        if(a->bucket[i])
            free(a->bucket[i]);
    free(a);
}


int sqr (int num, int times){
    if(times == 1) return 1;
    return num * sqr(num ,times - 1);
}

int CharToNum (char sample[]){
    int len = 0, num = 0;
    for (int i = 0; sample[i] != '\0'; i++)
        len++;
    //printf("len : %d\n", sqr(10, 1));
    int j = 0;
    for (int i = len; i >= 1; i--){
        num += (sample[j] - '0') * sqr(10, i);
        j++;
    }
    return num;
}


TreeNode* CreatNewTreeNode (int weight, int val){ 
    TreeNode* newNode = (TreeNode* )malloc(sizeof(TreeNode));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->uproot = NULL;
    newNode->weight = weight;
    newNode->value = val;
    return newNode;
}

TreeNode* BindTreeNode (TreeNode* child1, TreeNode* child2){ //两个森林成树
    if(!child1 || !child2) return NULL;
    TreeNode* up = CreatNewTreeNode (child1->weight + child2->weight, -1);
    child1->uproot = up;
    child2->uproot = up;
    up->left = child1;
    up->right = child2;

    return up;
}

void CreatHaffTree (AryTreeNode* ary, int len){
    int total = 0, i, suf1 = 0, suf2 = 0, index = len;
    bool sign = TRUE;
    while (sign){
        for(i = 1; i <= index; i ++){
            if (!ary[i]->uproot) total++;
        }
        if (total == 1){
            sign = FALSE;
            break;
        }
        total = 0;

        for(i = 1; i <= index; i++){
            if(!ary[i]->uproot){
                if(suf1 == 0) suf1 = i;
                else if (suf2 == 0) suf2 = i;
                else{
                    if (ary[i]->weight <= ary[suf1]->weight && ary[i]->weight <= ary[suf2]->weight){
                        if(ary[suf1]->weight <= ary[suf2]->weight){
                            suf2 = i;
                        }else suf1 = i;
                    }else if(ary[i]->weight <= ary[suf1]->weight){
                        suf1 = i;
                    }else if (ary[i]->weight <= ary[suf2]->weight){
                        suf2 = i;
                    }
                }
            }
        }
        ary[++index] = BindTreeNode(ary[suf1], ary[suf2]);
        //printf("INDEX: %d, suf1: %d suf2: %d----\n", index, suf1, suf2);
        suf1 = 0;
        suf2 = 0;
    }
    
}

void BreakHaffTree (TreeNode* t){
    if(t == NULL) return;
    BreakHaffTree(t->left);
    BreakHaffTree(t->right);
    if(t)free(t);
    t = NULL;
}

void DisplayHaffTree (TreeNode* t, int space, position p){
    if (!t) return; 
    space += 5;
    
    DisplayHaffTree (t->left, space, LEFT);

    //printf("\n");
    for (int i = 0; i < space; i++)
        printf(" ");
    if(p == LEFT){
        printf("/--%d\n", t->weight);
    }else if(p == RIGHT){
        printf("\\--%d\n", t->weight);
    }else{
        printf("--%d\n", t->weight);
    }
    
    DisplayHaffTree (t->right, space, RIGHT);
    
    
}

void AddChar (char** orig, char c){  // 给一个字符串 结尾加上一个字符
    int i = 0, len = 0;
    while ((*orig)[i] != '\0'){
        len++;
        i++;
    }
    char* new = (char* )malloc(sizeof(char) * (len + 2));
    for(i = 0; i < len; i ++){
        new[i] = (*orig)[i];
    }
    new[i] = c;
    new[i + 1] = '\0';
    free(*orig);
    (*orig) = new;
}

bool IsEmpChar (char* c){  // 判断字符串是不是为空
    if (c[0] == '\0') return TRUE;
    else return FALSE;
}

void PopChar (char** orig){ //将字符串结尾一个字符删除
    if(IsEmpChar(*orig)) return;
    int i = 0, len = 0;
    while ((*orig)[i] != '\0'){
        len++;
        i++;
    }
    char* new = (char* )malloc(sizeof(char) * (len + 1));
    for(i = 0; i < len; i ++){
        new[i] = (*orig)[i];
    }
    new[i - 1] = '\0';
    free(*orig);
    (*orig) = new;
}

void DFS_Tree (TreeNode* t, char** c, position p, AryQueue* a){
    if (t == NULL) {
        PopChar(c);
        return;
    }

    if(!t->left && !t->right){
        printf("weight: %d code:%s\n",t->weight, *c);
        PushQue(a, t->weight, CharToNum(*c));
    }
    

    AddChar (c, '0');
    DFS_Tree(t->left, c, LEFT, a);
    AddChar (c, '1');
    DFS_Tree(t->right, c, RIGHT, a);
    PopChar(c);
}




int main (){
    int total = 4; // total 是用于建立哈夫曼树的数据总量
    AryTreeNode HaffAry[2 * total];
    HaffAry[1] = CreatNewTreeNode(3, 1);
    HaffAry[2] = CreatNewTreeNode(4, 2);
    HaffAry[3] = CreatNewTreeNode(7, 3);
    HaffAry[4] = CreatNewTreeNode(5, 4);
    // HaffAry[5] = CreatNewTreeNode(6, 5);
    // HaffAry[6] = CreatNewTreeNode(7, 6);
    // HaffAry[7] = CreatNewTreeNode(8, 7);
    // HaffAry[8] = CreatNewTreeNode(10, 8);
    // HaffAry[9] = CreatNewTreeNode(11, 98);
    CreatHaffTree(HaffAry, total);
    DisplayHaffTree (HaffAry[total * 2 - 1], 0, MIDDLE);
    char* codeHaff = (char* )malloc(strlen("") + 1);
    strcpy(codeHaff, "");

    AryQueue** Que;
    InitAryQueue(Que, 100);




    DFS_Tree(HaffAry[total * 2 - 1], &codeHaff, MIDDLE, *Que);
    
    PrintHash(*Que);

    DestoryQue(*Que);
    BreakHaffTree(HaffAry[total * 2 - 1]);
    free(codeHaff);

    // char *test = (char* )malloc(strlen("1234") + 1);
    // strcpy (test, "");
    // printf("%s\n", test);
    // AddChar(&test, '5');
    // printf("%s\n", test);
    // PopChar(&test);
    // PopChar(&test);
    // printf("%s\n", test);
    // free(test);

    //别忘了释放哈夫曼数组里的树
  
    return 0;

}