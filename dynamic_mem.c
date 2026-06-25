#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//creating vector from scratch

//------------create function--------------------
typedef struct{
    int *data;
    int size;
    int capacity;
}DynamicArray;

DynamicArray create(){
    DynamicArray arr;
    arr.data = malloc(2 * sizeof(int));
    arr.size = 0;
    arr.capacity = 2;
    if(arr.data == NULL){
        exit(1);
    }
    return arr;
}

//------------------push--------------------------

//1. check if theres room

void push(DynamicArray *arr, int value){
    if(arr -> size == arr -> capacity){ // block is full
        // calculate new capacity
        int new_capacity = arr -> capacity * 2; // double the previous capacity
        int *new_data = malloc(new_capacity * sizeof(int));
        memcpy(new_data,arr -> data, arr -> size * sizeof(int)); // copy the elements from old data to new
        free(arr -> data); // free 
        arr -> data = new_data;
        arr -> capacity = new_capacity; // update the capacity
    }
    arr -> data[arr -> size] = value;
    arr -> size++;
    
}

int get(DynamicArray *arr, int index){
    return arr -> data[index];
}

void cleanup(DynamicArray *arr){
    free(arr -> data);
    arr -> data = NULL;
}

int main(){
    DynamicArray arr = create();
    push(&arr,1);
    push(&arr,2);
    push(&arr,3);
    push(&arr,4);
    push(&arr,5);
    push(&arr,6);
    printf("%d\n",get(&arr, 2));
    printf("%d\n",get(&arr, 3));
    printf("%d\n",get(&arr, 4));
    cleanup(&arr);
    return 0;
}