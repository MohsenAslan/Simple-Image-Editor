#include <iostream>
#include "Image_Class.h"
using namespace std;

viod resize (Image &img ,int newWidth,int newHeight ){

    Image resized(newWidth, newHeight);
  
    float xr = (float) img.width / newWidth;
    float yr = (float) img.height / newHeight;

    for (int i = 0; i < newWidth; i++) {
        for (int j = 0; j < newHeight; j++) {
            int srcX = (int)(i * xr );
            int srcY = (int)(j * yr );

            for (int k = 0; k < img.channels; k++) {
                resized(j, i, k) = img(srcY, srcX, k);
            }
        }
    }
    img = resized;
}

int main() {
  

    return 0;
}
