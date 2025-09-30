//stud1 : 
   // Name: mariem badwey abdelstar
   // Id : 20242326
   // Sec : x
   // Filter : 3 "invert" , 6 "rotate"
//stud2 :
   // Name : mohsen mohamed mohsen
   // Id : 20242260
   // Sec : x
   // Filter : 2 "black & white" , 5 "flip"
//stud3
   // Name : eman saad mostafa
   // Id : 20242064
   // Sec :  x
   // Filter : 1 "grayscale" , 4 "merge"
 


#include <iostream>
#include "Image_Class.h"
#include <fstream>
using namespace std;


//filter11 resize 
//viod resize (Image &img ,int newWidth,int newHeight ){

  //  Image resized(newWidth, newHeight);
  
    //float xr = (float) img.width / newWidth;
    //float yr = (float) img.height / newHeight;

   // for (int i = 0; i < newWidth; i++) {
     //   for (int j = 0; j < newHeight; j++) {
       //     int srcX = (int)(i * xr );
         //   int srcY = (int)(j * yr );

           // for (int k = 0; k < img.channels; k++) {
             //   resized(j, i, k) = img(srcY, srcX, k);
            //}
        //}
    //}
    //img = resized;
//}


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



// filter3 invert 
void invert(Image &image) {
    
    for (int i = 0; i < image.width; i++) {
        
        for (int j = 0; j < image.height; j++) {
            
            for (int k = 0; k < 3; k++) {
                
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }
}


//filter6 rotate
void rotateImage(Image &image, int degree) {
    
    if (degree == 90) {
        
        int H = image.height, W = image.width;
        
        Image rotated(H, W);
        
        for (int i = 0; i < image.width; i++) {
            
            for (int j = 0; j < image.height; j++) {
                
                for (int k = 0; k < 3; k++) {
                    
                    rotated(j, i, k) = image(i, image.height - 1 - j, k);
                }
            }
        }
        image = rotated;
    }
        
    else if (degree == 180) {
        
        Image rotated(image.width, image.height);
        
        for (int i = 0; i < image.width; i++) {
            
            for (int j = 0; j < image.height; j++) {
                
                for (int k = 0; k < 3; k++) {
                    
                    rotated(i, j, k) = image(image.width - 1 - i, image.height - 1 - j, k);
                }
            }
        }
        image = rotated;
    }
    else if (degree == 270) {
        
        Image rotated(image.height, image.width);
        
        for (int i = 0; i < image.width; i++) {
            
            for (int j = 0; j < image.height; j++) {
                
                for (int k = 0; k < 3; k++) {
                    
                    rotated(j, i, k) = image(image.width - 1 - i, j, k);
                }
            }
        }
        image = rotated;
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
//void crop(Image &img, int x, int y, int width, int height) {
    
   // Image cropped(width, height);

   // for (int i = 0; i < width; i++) {
        
      //  for (int j = 0; j < height; j++) {
            
        //    for (int k = 0; k < img.channels; k++) {
                
              //  cropped(j, i, k) = img(y + j, x + i, k);
          //  }
        //}
  //  }

  //  img = cropped; 
//}


//filter 1 grayscal
void toGray(Image &img) {
    
    for (int i = 0; i < img.width; i++) {
        
        for (int j = 0; j < img.height; j++) {
            
            unsigned int avg = 0;
            
            for (int k = 0; k < 3; k++) {
                
                avg += img(i, j, k);
            }
            
            avg /= 3;
            
            for (int k = 0; k < 3; k++) {
                
                img(i, j, k) = avg;
            }
        }
    }
}
//filter 4 merge
Image resize(Image &img, int newWidth, int newHeight) {
   
    Image resized(newWidth, newHeight);
   
    float xr = (float)img.width / newWidth;
   
    float yr = (float)img.height / newHeight;
   
    for (int i = 0; i < newWidth; i++) {
       
        for (int j = 0; j < newHeight; j++) {
           
            int srcX = (int)(i * xr);
           
            int srcY = (int)(j * yr);
           
            for (int k = 0; k < img.channels; k++) {
               
                resized(i, j, k) = img(srcX, srcY, k);
            }
        }
    }
    return resized;
}

Image mergeImages(Image &img1, Image &img2, int option) {
   
    int width, height;
   
    if (option == 1) {
       
        width = max(img1.width, img2.width);
       
        height = max(img1.height, img2.height);
       
        img1 = resize(img1, width, height);
       
        img2 = resize(img2, width, height);
    } else {
        width = min(img1.width, img2.width);
       
        height = min(img1.height, img2.height);
    }

    Image output(width, height);
   
    for (int i = 0; i < width; i++) {
       
        for (int j = 0; j < height; j++) {
           
            for (int k = 0; k < img1.channels; k++) {
               
                int a = img1(i, j, k);
               
                int b = img2(i, j, k);
               
                output(i, j, k) = (a + b) / 2;
            }
        }
    }
    return output;
}

bool FileName(const string &name) {

    return (name.ends_with(".jpg") || name.ends_with(".bmp") || name.ends_with(".png")|| name.ends_with(".jpeg"));
}

void Menu() {

    cout << "1. Load new image\n";

    cout << "2. Filter  // GrayScale\n";

    cout << "3. Filter  // BlackWhite\n";

    cout << "4. Filter  // Invert\n";

    cout << "5. Filter  // Merge\n";

    cout << "6. Filter  // Flip\n";

    cout << "7. Filter  // Rotate\n";

    cout << "8. Save image\n";

    cout << "9. Exit\n\n\n";

}




int main() {

   string fileName;

    cout << "Please enter the file name: ";

    cin >> fileName;

    while (!FileName(fileName) || !ifstream(fileName).good()) {

        cout << "Error: Invalid file. Please enter a valid file name: ";

        cin >> fileName;
    }

    Image img(fileName), img2;

    bool test = true;

    while (test) {

        Menu();

        int num;

        cout << "Please enter the operation number: ";

        cin >> num;

        switch (num) {

            case 1: {
                cout << "Do you want to save the current image before loading new one? (y/n): ";

                char saveChoice;

                cin >> saveChoice;

                if (saveChoice == 'y' || saveChoice == 'Y') {

                    string saveName;

                    cout << "Enter file name to save: ";

                    cin >> saveName;

                    if (!FileName(saveName)) {

                        cout << "Invalid extension!\n";

                    } else {

                        img.saveImage(saveName);

                        cout << "Image saved.\n";
                    }
                }

                cout << "Enter new image file: ";

                cin >> fileName;

                while (!FileName(fileName) || !ifstream(fileName).good()) {

                    cout << "Error: Invalid file. Enter new image file: ";

                    cin >> fileName;
                }

                img.loadNewImage(fileName);

                break;
            }

            case 2:
                 toGray(img);
                break;
            case 3:
                blackWhite(img);
                break;
             case 4:
                invert(img);
                break;
           case 5: {
                cout << "Enter second image file: ";
              
                string fileName2;
              
                cin >> fileName2;
              
                while (!FileName(fileName2) || !ifstream(fileName2).good()) {
                   
                    cout << "Error: Invalid file. Enter second image file: ";
                   
                    cin >> fileName2;
                }
                img2.loadNewImage(fileName2);

                int option;
              
                cout << "Merge Option:\n";
              
                cout << "1 - Resize to max size (larger image)\n";
              
                cout << "2 - Resize to min size (smaller image)\n";
              
                cout << "Enter option (1 or 2): ";
              
                cin >> option;
              
                while (option != 1 && option != 2) {
                   
                    cout << "Invalid option. Please enter 1 or 2: ";
                   
                    cin >> option;
                }

                img = mergeImages(img, img2, option);
              
                cout << "Images merged .\n";
                break;
            }

            case 6: {
                char choose;

                cout << "H for horizontal flip, V for vertical flip: ";

                cin >> choose;

                if (choose == 'h' || choose == 'H') {

                    flipHorizontal(img);
                    break;
                }
                else if (choose == 'v' || choose == 'V'){

                    flipVertical(img);
                    break;
                }
            }

            case 7: {
                int angle;

                cout << "Enter rotation angle (90, 180, 270): ";

                cin >> angle;

                rotateImage(img, angle);

                break;
            }

            case 8: {

                cout << "Save on same file (" << fileName << ")? (y/n): ";

                char saveChoice;

                cin >> saveChoice;

                if (saveChoice == 'y' || saveChoice == 'Y') {

                    img.saveImage(fileName);

                } else {

                    string saveName;

                    cout << "Enter new file name: ";

                    cin >> saveName;

                    if (!FileName(saveName)) {

                        cout << "Invalid extension!\n";

                    } else {

                        img.saveImage(saveName);
                    }
                }
                break;
            }

            case 9: {

                cout << "Do you want to save before exit? (y/n): ";

                char saveChoice;

                cin >> saveChoice;

                if (saveChoice == 'y' || saveChoice == 'Y') {

                    string saveName;

                    cout << "Enter file name to save: ";

                    cin >> saveName;

                    if (FileName(saveName)) {

                        img.saveImage(saveName);

                        cout << "Image saved.\n";

                    } else {
                        cout << "Invalid extension. Exit without saving.\n";
                    }
                }
                test = false;

                break;
            }
          default: cout << "Invalid choice!\n"; break;
        }
    }

    return 0;
}



