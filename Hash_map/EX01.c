#include <stdio.h>
#include <stdlib.h>

// 这是一个由链表组成的哈希表 , 当发生哈希冲突的时候(即经过哈希函数计算后的index值相同的时候 我们用链表形式在其中存储.
#define CAPACIDAD 100
typedef enum bool{
    TRUE = 1,
    FALSE = 0
}bool;

typedef struct pair{
    int val;
    struct pair* node;
    int key;
}pair;

typedef struct mapset{
    int len;
    void* entir;
}mapset;

typedef struct hashmap{
    pair* bucket[CAPACIDAD];
}hashmap;

pair*  InitQue (){
    pair* p = (pair* )malloc(sizeof(pair));
    p->node = NULL;
    p->key = 0;
    p->val = 0;
    return p;
}

int HashFunction (int key){
    int index = key % CAPACIDAD;
    return index;

}

void PushItem (pair* p, int key, int value){
    pair* temp = (pair* )malloc(sizeof(pair));
    temp->key = key;
    temp->val = value;
    temp->node = NULL;
    pair* position = p;
    while(position->node){
        position = position->node;
    }
    position->node = temp;
}

void DelItem (pair* p, int key){
    if(p->node == NULL) printf("目前没有任何元素要被删除\n");
    else{
        pair* temp = p;
        pair* te;
        if(!temp->node->node){
            if(temp->node->key == key){
                free(temp->node);
                temp->node = NULL;
            }
        }else{
            te = NULL;
            while(temp->node){
                if(temp->node->key == key){
                    te = temp->node->node;
                    free(temp->node);
                    temp->node = te;
                    break;
                }
                temp = temp->node;
            }
        }
        
    }
}

void PopItem (pair* p){
    if(!p->node) printf("目前没有任何元素要弹出\n");
    else{
        pair* temp;
        temp = p;
        while(temp->node->node){
            temp = temp->node;
        }
        printf("这堆栈弹出得值 : key: %d, value: %d\n", temp->node->key, temp->node->val);
        DelItem(p, temp->node->key);
    }
}

hashmap* InitHashmap(){
    hashmap* temp;
    temp = (hashmap* )malloc(sizeof(hashmap));
    for (int i = 0; i < CAPACIDAD; i ++){
        temp->bucket[i] = NULL;
    }
    return temp;
}

void AddValue (hashmap* h, int key, int value){
    int index = HashFunction (key);
    if(!h->bucket[index]){
        pair* newpair = InitQue();
        PushItem(newpair, key, value);
        h->bucket[index] = newpair;
    }else{
        PushItem(h->bucket[index], key, value);
    }
    
}

mapset* GetMapsetPair (hashmap* h){
    int index = 0, i, total = 0;
    mapset* temp = (mapset* )malloc(sizeof(mapset));
    for (i  = 0; i < CAPACIDAD; i++){
        if(h->bucket[i]){
            pair* check = h->bucket[i]->node;
            while (check){
                total++;
                check = check->node;
            }
        }     
    }
    pair* temPair = (pair* )malloc(sizeof(pair) * total);
    for (i = 0; i < CAPACIDAD; i++){
        if(h->bucket[i]){
            pair* check = h->bucket[i];
            while(check->node){
                temPair[index].key = check->node->key;
                temPair[index].val = check->node->val;
                check = check->node;
                index++;
            }
        }
    }
    temp->entir = temPair;
    temp->len = total;
    return temp;

}

void DelQue (pair* p){
    if(!p) printf("堆栈不存在!\n");
    else{
        pair* temp;
        temp = p;
        while(temp){
            p = p->node;
            free(temp);
            temp = p;
        }
    }
}

void DelHashMap (hashmap* h){
    int i = 0;
    for (;i < CAPACIDAD; i ++){
        if (h->bucket[i])
            DelQue(h->bucket[i]);
            h->bucket[i] = NULL;
    }
}

void DisplayPairSet (hashmap* h){
    mapset* m;
    m = GetMapsetPair (h);
    pair* temp;
    temp = (pair* )m->entir;
    for (int i = 0; i < m->len; i ++){
        printf("KEY:  %d  ->  VALUE: %d\n", temp[i].key, temp[i].val);
    }
}

void QuaryHashmap (hashmap* h, int key){
    mapset* m = GetMapsetPair(h);
    pair* temp;
    int check = 0;
    temp = (pair* )m->entir;
    for (int i = 0; i < m->len; i ++){
        if (temp[i].key == key){
            printf("QUERY:   KEY:  %d  ->  VALUE: %d\n", temp[i].key, temp[i].val);
            check = 1;
        }
            
    }
    if (!check) printf("未找到 key: %d 的元素\n", key);
}

void QuaryHashmap2 (hashmap* h, int key){
    int index = HashFunction(key);
    pair* temp = h->bucket[index];
    pair* position = temp;
    bool check = 0;
    if(temp){
        while(position->node){
            if(position->node->key == key){
                printf("QUERY:   KEY:  %d  ->  VALUE: %d\n", position->node->key, position->node->val);
                check = TRUE;
            }
            position = position->node;
        }
    }
    if (!check)printf("未找到 key: %d 的元素\n", key);
}

int main(){
    hashmap* h = InitHashmap();
    AddValue(h, 1, 10);
    AddValue(h, 101, 100);
    AddValue(h, 2, 234);
    AddValue(h, 202, 456);
    QuaryHashmap2(h, 1);
    DisplayPairSet(h);
    DelHashMap(h);
    h = InitHashmap();
    AddValue(h, 123, 888);
    AddValue(h, 133, 123);
    AddValue(h, 143, 234);
    AddValue(h, 153, 456);
    QuaryHashmap2(h, 143);
    DisplayPairSet(h);
    DelHashMap(h);


    return 0;

}