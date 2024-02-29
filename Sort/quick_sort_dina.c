#include <stdio.h>
#include <stdlib.h>

typedef struct _range
{
    int front;
    int tail;
}Range;

void swap (int*, int*);
void quickSort(int[], int);
Range* buildRangeDi (int, int);
void OPTarry (int[], int, int);

void swap (int* num1, int* num2){
    int temp;
    temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

Range* buildRangeDi (int left, int right){
    Range* temp = (Range* )malloc(sizeof(Range));
    (*temp).front = left;
    temp->tail = right;
    return temp;
}

void OPTarry (int ary[], int len, int midValue){
    int i = 0;
    len--;
    printf ("数组中间值: %d  数组当前值:   ", midValue);
    for (; i <= len; i++){
        printf("%d  ", ary[i]);
    }
    printf("\n");
}

void quickSort (int ary[], int len){
    if (!len) return;
    Range* Block[len];
    int times = 0;
    Block[times++] = buildRangeDi(0, len - 1);
    int num_free = 1;
    while (times){
        Range* bBlock = Block[--times];
        int left = bBlock->front;
        int right = bBlock->tail;
        int mid = ary[(left + right) / 2];
        OPTarry(ary, len, mid);
        while (left <= right)
        {
            while(ary[left] < mid)left++;
            while(mid < ary[right])right--;
            if (left <= right){
                swap(&ary[left++], &ary[right--]);
            }
        }
        if(bBlock->front < right)Block[times++] = buildRangeDi(bBlock->front, right);
        if(bBlock->tail > left)Block[times++] = buildRangeDi(left, bBlock->tail);
        if (num_free < times) num_free = times;
        OPTarry(ary, len, mid);
    }
    for (int i = 0; i < num_free; i++)free(Block[i]);
    printf("-----%d-----\n", num_free);

}

int main(){
    int arr[] = { 22, 34, 3, 32, 82, 55, 89, 50, 37, 5, 64, 35, 9, 70, 1, 200};
    int len = (int)sizeof(arr)/(int)sizeof(arr[0]);
    quickSort(arr, len);
    int i;
    for (i = 0; i < len; i++)
        printf("%d ", arr[i]);  
    return 0;
}