#include <iostream>
#include "Image_Class.h"
using namespace std;


//filter11 resize 
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


//filter2 black&white
void blackWhite(Image &img) {
    
    for (int i = 0; i < img.width; i++) {
        
        for (int j = 0; j < img.height; j++) {
            unsigned avg = 0;
            
            for (int k = 0; k < img.channels; k++) {
                avg += img(i, j, k);
            }

            avg = avg / img.channels;
            
            unsigned correct = (avg > 128) ? 255 : 0;

            for (int k = 0; k < img.channels; k++) {
                img(i, j, k) = correct;
            }
        }
    }
}

// filter5 flip (H)
void flipHorizontal(Image &img) {
    
    for (int i = 0; i < img.width / 2; i++) {
        
        for (int j = 0; j < img.height; j++) {
            
            for (int k = 0; k < img.channels; k++) {
                
                swap(img(i, j, k), img(img.width - 1 - i, j, k));
            }
        }
    }
}
// filter5 (v)
void flipVertical(Image &img) {
     for (int i = 0; i < img.width; i++) {
         
        for (int j = 0; j < img.height / 2; j++) {
            
            for (int k = 0; k < img.channels; k++) {
                
                swap(img(i, j, k), img(i, img.height - 1 - j, k));
            }
        }
    }
}
//filter8 crop
void crop(Image &img, int x, int y, int width, int height) {
    
    Image cropped(width, height);

    for (int i = 0; i < width; i++) {
        
        for (int j = 0; j < height; j++) {
            
            for (int k = 0; k < img.channels; k++) {
                
                cropped(j, i, k) = img(y + j, x + i, k);
            }
        }
    }

    img = cropped; 
}




int main() {
  

    return 0;
}
