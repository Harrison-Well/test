//
//  算法.c
//  查找算法
//
//  Created by 金宸极 on 2018/12/27.
//  Copyright © 2018 金宸极. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define MAXNUM 100

typedef int Array[MAXNUM];

typedef struct List{
    Array key;
    int num;
}List;

void Init(List *A){
    (A) = (List *)malloc(sizeof(List));
    for (int i = 0 ; i<MAXNUM; i++) {
        A->key[i] = 0;
    }
    A->num = 0;
}   //初始化数组


//该算法的目的是查找一个乱序数组，按照关键字增序排列的第k个值。
//对于快速排序算法，在一趟排序后可以将原序列的首项元素插入到正确的位置，并保证新序列在前面的都比该元素小，新序列在后面的都比该元素大。
//利用该特点，对第一个元素快速排序，如果发现排序后的下标等于（k-1）则说明恰好就是我们要找的关键字，如果不等于，也可以通过二者的大小关系缩小查询范围。
//当数据体量足够大的时候，应该可以有效的降低时间成本，粗略估计可以达到(n logn /2)的时间复杂度。

int QuickSort(List *A, int min, int max){
    if ((*A).num < max+1) {
        return -1;
    }
    int point = min;
    int low = min + 1;
    int high = max;
    while (low < high) {
        while ((*A).key[high] > (*A).key[point] && low < high) {
            high -= 1;
        }
        while ((*A).key[low] < (*A).key[point] && low < high) {
            low += 1;
        }
        if (low < high) {
            int Tem = (*A).key[low];
            (*A).key[low] = (*A).key[high];
            (*A).key[high] = Tem;
        }
    }
    if ((*A).key[low] < (*A).key[point]) {
        int Tem = (*A).key[low];
        (*A).key[low] = (*A).key[point];
        (*A).key[point] = Tem;
    }
    return high;
}   //对数组A下标 min～max 的范围进行一趟快速排序，并返回最后的插入位置


int Find(List A, int k){    //查找增序排列第k个值
    int SubMark = -1;
    int max = A.num - 1;
    int min = 0;
    while (SubMark != k-1) {
        SubMark = QuickSort(&A, min, max);
        if (SubMark < k-1) {
            min = SubMark + 1;      //向后缩小查询范围
        } else if (SubMark > k-1){
            max = SubMark - 1;      //向前缩小查询范围
        }
    }
    return A.key[SubMark];
}


int main(){
    Array H = {75,34,2567,343,246,783,324,65};
    List Test;
    Init(&Test);
    for (int i = 0; i < 8; i++) {
        Test.key[i] = H[i];
        Test.num += 1;
    }
    
    
    int T = Find(Test, 5);
    
    
    
    return T;
}
