#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    unsigned long long bitmap;
    int total_pages;
}Allocator;

// set bit n = bitmap |= (1 << n)
// clear bit n = bitmap &= ~(1 << n)
// check bit n = bitmap & (1 << n)

int is_allocated(Allocator *a, int n){
    if(a -> bitmap & (1ULL << n)){  // returns non zero if page n is allocated
        return 1;
    }
    return 0;
}

void print_map(Allocator *a){
    for(int i = 0; i < a -> total_pages; i++){
        if(is_allocated(a,i)){
            printf("%d",1);
        }else{
            printf("%d",0);
        }
    }
    printf("\n");
}

int allocate(Allocator *a){
    for(int i = 0; i < a -> total_pages; i++){ // loop through all pages
        if(is_allocated(a,i) == 0){ // where page is free
            a -> bitmap |= (1ULL << i); // allocate the page
            return i; // return page number
        }
    }
    return -1; // if no free page found return -1
}

void free_page(Allocator *a, int n){
    a -> bitmap &= ~(1ULL << n);
}

int main(){
    Allocator a = {0,64}; // bitmap starts at 0(all free), 64 pages
    print_map(&a);
    allocate(&a);
    allocate(&a);
    allocate(&a);
    allocate(&a);
    allocate(&a);
    print_map(&a);
    free_page(&a,1);
    print_map(&a);
    printf("is allocated : %d\n", is_allocated(&a,2));
    printf("is not allocated : %d\n", is_allocated(&a,1));
    return 0;
}