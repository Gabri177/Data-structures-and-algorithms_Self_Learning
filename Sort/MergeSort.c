#include <stdio.h>
#include <stdlib.h>
// 归并排序 迭代法(非递归法)
int min(int, int);
void mergeSort (int[], int);

int main (){
    int arr[] = { 22, 34, 3, 32, 82, 55, 89, 50, 37, 5, 64, 35, 9, 70, 1, 200};
    int len = (int) sizeof(arr) / sizeof(*arr);
    mergeSort(arr, len);
    int i;
    for (i = 0; i < len; i++)
        printf("%d ", arr[i]);
    return 0;

}

int min (int num1, int num2){
    return num1 < num2 ? num1 : num2;
}
void mergeSort (int ary[], int len){
    int outer, inner;
    int* apoya = (int *)malloc(len * sizeof(int));
    for (outer = 1; outer < len; outer *= 2){ //外部循环, 指数级别增加切片的长度, 1, 2, 4, ...
        for(inner = 0; inner < len; inner += outer * 2){ //内部循环, 分别对相邻的两个长度为(外部循环切片长度的)两个片段进行对比
            int low = inner, mid = min(len, inner + outer), high = min(len, inner + outer * 2); //外部相邻两个切片距离起始点和终点表示出来
            int start1 = low, end1 = mid; //切片1
            int start2 = mid, end2 = high; //相邻的切片2
            int k = low; // 辅助数组的下标我们用另一个变量存储
            while(start1 < end1 && start2 < end2){
                apoya[k++] = ary[start1] < ary[start2] ? ary[start1++] : ary[start2++];
                // 对两个相邻的切片 从两个切片分别把最左边的量拿出来进行比较,小的放入辅助数组, 然后再依次比较最左边的两个值以此类推
            }
            while(start1 < end1){
                apoya[k++] = ary[start1++];
                //当切片一在比较完还有剩余的时候, 我们把里面的量依次放入辅助数组
            }

            while (start2 < end2){
                apoya[k++] = ary[start2++];
                //对切片二的处理同上
            }
            
        }
        for(int i = 0; i < len; i++){
        ary[i] = apoya[i];
    }
    }
    
    free(apoya);
    //别忘了释放内存
}