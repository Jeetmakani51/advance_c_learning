#include <stdio.h>


#pragma pack(1)// no padding between bytes, controls padding and alignment

typedef struct{
    char signature[2];
    unsigned int file_size; // file size are never negative so unsigned int which gives full positive range
    short reserved;
    short reserverd;
    unsigned int pixel_data_offset;
}BMPFILEHEADER;

typedef struct{
    unsigned int header_size;
    unsigned int image_width;
    unsigned int image_height;
    short color_planes;
    short bits_per_pixel;
}BMPDIBHEADER;

#pragma pack(0) // restore default padding after

int main(){
    BMPFILEHEADER bfh;
    BMPDIBHEADER bdh;

    FILE *fp;
    //read
    fp = fopen("c-code.bmp","rb");
    if(fp == NULL){
        printf("cannot open file.\n");
        return 1;
    }

    fread(&bfh,sizeof(BMPFILEHEADER), 1, fp);
    fread(&bdh,sizeof(BMPDIBHEADER), 1, fp);
    fclose(fp);

    printf("width : %d\n", bdh.image_width);
    printf("height : %d\n", bdh.image_height);
    printf("file size : %d\n", bfh.file_size);
    printf("bits per pixel : %d\n", bdh.bits_per_pixel);
    return 0;
}

//output
// width : 1728
// height : 1080
// file size : 5598774,                  1728 * 1080 * 3 = 5598720, + 54 bits = 5598774
// bits per pixel : 24,               8 bits each, 8 * 3 = 24      