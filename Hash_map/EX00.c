
// 数组中的每个空位为 桶bucket, 每个桶可以存储一个键值对
// 查询操作就是找到key 对应的桶, 并在桶中获取value;
// 在哈希表中, 输入空间是所有的 key, 输出空间是所有的桶(数组的索引)
// 输入一个 key , 我们可以通过哈希表函数得到该 key 对应的键值对 在数组中的存储位置


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Hash_Map_Size 100

typedef struct _pair{
    int key; 
    char* name;
}pair;

typedef struct _mapset{
    int len;
    void* set;
}mapset;

typedef struct _Hashmap{
    pair* bucket[Hash_Map_Size]; //数组的索引是index 是经过哈希函数计算的key 
}Hashmap;

int HashFunc (int key){ //根据key 返回索引值;
    int index;
    index = key % Hash_Map_Size;
    return index;
}

Hashmap* InitHashMap (){ //创建定义桶的数量的哈希表
    Hashmap* NewHash = (Hashmap* )malloc(sizeof(Hashmap));
    if(!NewHash) return NULL;
    return NewHash;
}

void Put (Hashmap* h, int key, char* val){
    int index = HashFunc(key);
    pair* newPair = (pair* )malloc(sizeof(pair));
    newPair->key = key;
    newPair->name = (char* )malloc(strlen(val) + 1);
    strcpy(newPair->name, val);

    h->bucket[index] = newPair;
}

char* GetName (Hashmap* h, int key){
    int index = HashFunc(key);
    if (h->bucket[index] == NULL) return NULL;
    return h->bucket[index]->name;
}

void DelItem (Hashmap* h, int key){
    int index = HashFunc(key);
    free(h->bucket[index]->name);
    free(h->bucket[index]);
    h->bucket[index] = NULL;
}

mapset* PairSet (Hashmap* h){
    int index = 0, total = 0, i;
    for (i = 0; i < Hash_Map_Size; i++){
        if (h->bucket[i]){
            total++;
        }
    }
    mapset* tempMapSet = (mapset* )malloc(sizeof(mapset));
    //tempMapSet->set = (pair *)malloc(sizeof(pair) * total);
    pair* tempPair = (pair *)malloc(sizeof(pair) * total);
    for (i = 0; i < Hash_Map_Size; i++){
        if (h->bucket[i]){
            tempPair[index].key= h->bucket[i]->key;
            tempPair[index].name = h->bucket[i]->name;
            index++;
        }
    }
    tempMapSet->set = tempPair;
    tempMapSet->len = total;
    return tempMapSet;
}

mapset* KeySet(Hashmap* h){
    int index = 0, total = 0, i;
    for(i = 0; i < Hash_Map_Size; i++){
        if(h->bucket[i]){
            total++;
        }
    }
    mapset* temp = (mapset* )malloc(sizeof(mapset));
    int* keys = (int* )malloc(sizeof(int) * total);
    for(i = 0; i < Hash_Map_Size; i++){
        if(h->bucket[i]){
            keys[index] = h->bucket[i]->key;
            index++;
        }
    }
    temp->len = total;
    temp->set = keys;
    return temp;
}

mapset* ValSet (Hashmap* h){
    int index = 0, total = 0, i;
    char** temp;
    mapset* tempSet;
    for(i = 0; i < Hash_Map_Size; i++){
        if(h->bucket[i]){
            total++;
        }
    }
    tempSet = (mapset* )malloc(sizeof(mapset));
    temp = (char** )malloc(sizeof(char* ) * total);
    for(i = 0; i < Hash_Map_Size; i++){
        if(h->bucket[i]){
            temp[index] = h->bucket[i]->name;
            index++;
        }
    }
    tempSet->set = temp;
    tempSet->len = total;
    return tempSet;

}

void Print (Hashmap* h){
    int i;
    mapset* set;
    set = PairSet(h);
    for(i = 0; i < set->len; i++){
        printf("key: %d -> value: %s\n", ((pair* )(set->set))[i].key, ((pair* )(set->set))[i].name);
    }
    free(set->set);
    free(set);
}

void DelMap (Hashmap* h){
    int i = 0;
    for(; i < Hash_Map_Size; i++){
        if (h->bucket[i]){
            free(h->bucket[i]);
        }
    }
    free(h);
}

int main (){
    /* 初始化哈希表 */
    Hashmap *map = InitHashMap();

    /* 添加操作 */
    // 在哈希表中添加键值对 (key, value)
    Put(map, 12836, "小哈");
    Put(map, 15937, "小啰");
    Put(map, 16750, "小算");
    Put(map, 13276, "小法");
    Put(map, 10583, "小鸭");
    printf("\n添加完成后，哈希表为\nKey -> Value\n");
    Print(map);

    /* 查询操作 */
    // 向哈希表输入键 key ，得到值 value
    const char *name = GetName(map, 15937);
    printf("\n输入学号 15937 ，查询到姓名 %s\n", name);

    /* 删除操作 */
    // 在哈希表中删除键值对 (key, value)
    DelItem(map, 10583);
    printf("\n删除 10583 后，哈希表为\nKey -> Value\n");
    Print(map);

    /* 遍历哈希表 */
    int i;

    printf("\n遍历键值对 Key->Value\n");
    Print(map);


    mapset* set;
    set = KeySet(map);
    int *keys = (int *)set->set;
    printf("\n单独遍历键 Key\n");
    for (i = 0; i < set->len; i++) {
        printf("%d\n", keys[i]);
    }
    free(set->set);
    free(set);

    set = ValSet(map);
    char **vals = (char **)set->set;
    printf("\n单独遍历值 Value\n");
    for (i = 0; i < set->len; i++) {
        printf("%s\n", vals[i]);
    }
    free(set->set);
    free(set);
    DelMap(map);
    return 0;
}