#include <stdio.h>

//pointer arithmetic

//post increment

/*int main(){
    int a[] = {5,10,15,20,25,30,35};
    int *p = &a[0];  // points to the address of 5 lets say 1000
    printf("%d\n", *p++);   //  first value will be assigned which is 1000, then the actual value which is 5
                         // then it will increment so address will be 1004, 
    printf("%d", *p); // p will contain the adddress 1004, *p mean the value is 10
    return 0;

}*/

// pre increment
/*int main(){
    int a[] = {5,10,15,20,25,30,35};
    int *p = &a[0];  // points to the address of 5 lets say 1000
    printf("%d\n", *++p);   //  first the increment will happen *(1004), then value will be assigned 10
    return 0;

}*/

//pre and post decrement
/*int main(){
    int a[] = {5,10,15,20,25,30,35};
    int *p = &a[2];  // points to the address of 15 lets say 1008
    printf("%d\n", *(--p));   //  first the decrement will happen *(1004), then value will be assigned 10
    printf("%d",*(p--)); // value will be assigned *(1008), then it will decrement value will be 10
    return 0;

}*/

//pointer addition
/*int main(){
    int a[]= {1,10,15,20,25,30};
    int *p = &a[0];
    p = p+2;
    printf("%d",p);
    return 0;
}*/

//pointer subtraction
/*int main(){
    int a[] = {2,4,6,8,10};
    int *p = &a[0];
    int *q = &a[3];
    int result = p-q;
    printf("%d",result);
}*/

//pointer to array
/*int main(){
    int a[] = {1,2,3,4,5,6,7};
    int (*p)[7] = &a; // address of entire 1-D array, which is equal to address of 1st element
    printf("%d",**p);  //*p goes in which is address of 1st element, **p goes in which access the element
}*/

//pointer to function

/*int add(int a, int b){
    return a+b;
}
int main(){
    int result;
    int (*ptr)(int,int) = &add;
    result = (*ptr)(10,20);
    printf("%d",result);
    return 0;
}*/
/*#define ops 4
float sum(float a, float b){return (a + b);}
float sub(float a, float b){return (a - b);}
float mul(float a, float b){return (a * b);}
float div(float a, float b){return (a / b);}

int main(){
    float (*ptr[ops])(float,float) = {sum , sub, mul, div};
    int choice;
    float a, b;
    printf("0 for sum, 1 for sub, 2 for mul, 3 for div");
    scanf("%d",&choice);
    printf("Enter 2 numbers : ");
    scanf("%f %f",&a,&b);
    float result = (*ptr[choice])(a,b);
    printf("%f",result);
    return 0;
}*/

/*int my_strlen(const char *str){
    const char *ptr = str;
    while(*ptr != '\0'){
        ptr++;
    }
    int length = ptr - str;
    return length;
}

int main(){
    char text[] = "";
    printf("%d",my_strlen(text));
    return 0;
}*/

/*char *my_strcpy(char *dest, const char *src){
    const char *ptr = src;
    char *ptr2 = dest;
    char c;
    do{
        c = *ptr;
        *ptr2 = c; // copying value
        ptr++;
        ptr2++;
    }while(c != '\0');
    return dest;
}

int main(){
    char dest[20];
    char text[] = "hello world";
    printf("%s",my_strcpy(dest,text));
    return 0;
}*/

/*void *my_memcpy(void *dest, const void *src, size_t n){
    unsigned char *ptr = (unsigned char *)dest;
    unsigned char *ptr2 = (unsigned char *)src;
    for(int i = 0; i < n; i++){
        *ptr = *ptr2;
        ptr++;
        ptr2++;
    }
    return dest;
}

int main(){
    int dest[5];
    int src[5] = {10,20,30,40,50};
    my_memcpy(dest,src,sizeof(src));
    for(int i = 0; i < 5; i++){

        printf("array element : %d\n", dest[i]);
    }
    return 0;
}*/

int main(){
    int arr[5] = {10,20,30,40,50};
    int *ptr = &arr[0];
    for(int i = 0; i < arr[i]; i++){
        printf("%d %p %d\n",i,ptr,*ptr);
        ptr++;
    }
    return 0;
}