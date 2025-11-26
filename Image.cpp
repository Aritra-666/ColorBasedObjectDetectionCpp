#include<iostream>
#include<vector>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

int main(){
    int width, height, channels;
    unsigned char* data = stbi_load("Test.jpeg", &width, &height, &channels, 3);
    if(!data){
        std::cerr<<"Error: Failed to load image";
        return 0;
    }

    std::vector<std::vector<float>> R(height, std::vector<float>(width));
    std::vector<std::vector<float>> G(height, std::vector<float>(width));
    std::vector<std::vector<float>> B(height, std::vector<float>(width));

    int idx = 0;
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            R[r][c] = data[idx++];
            G[r][c] = data[idx++];
            B[r][c] = data[idx++];
        }
    }
    
    std::vector<unsigned char> GenImg( width*height*3);

    // for(int i =0,x=0,y=0; i < width*height*3 && x<width*height ;x++){
    //     if(x > width)x=0,y++;
    //     GenImg[i++]=R[y][x];
    //     GenImg[i++]=G[y][x];
    //     GenImg[i++]=B[y][x];
    // }
    idx=0;
    for(int y=0 ; y<height ; y++){
        for(int x =0 ; x<width ; x++){
             GenImg[idx++]=R[y][x];
             GenImg[idx++]=G[y][x];
             GenImg[idx++]=B[y][x];
        }
    }

    for(int i =0 ; i< width*height*3; i++){
        std::cout<<(float)GenImg[i]<<" ";
    }

    if(stbi_write_png("first.png", width, height, 3,&GenImg[0], width * 3)) {
        std::cout << "Image saved successfully!\n";
    } else {
        std::cout << "Failed to save image.\n";
    }

    stbi_image_free(data);

    return 0;
}