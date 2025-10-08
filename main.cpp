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
void resizeImage (Image &img ,int newWidth,int newHeight ){

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
//filter 10 detect edges
void detectEdges(Image& img) {
    Image edges = img;
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            unsigned avg = 0;
            for (int k = 0; k < 3; k++) {
                avg += img(i, j, k);
            }
            avg /= 3;
            for (int k = 0; k < 3; k++) {
                img(i, j, k) = avg;
            }
        }
    }
    for (int i = 0; i < img.width - 1; i++) {
        for (int j = 0; j < img.height - 1; j++) {
            int current = img(i, j, 0);
            int right = img(i + 1, j, 0);
            int down = img(i, j + 1, 0);

            int diff = abs(current - right) + abs(current - down);
            int t = 50;

            int edge_color = (diff > t) ? 0 : 255;

            for (int k = 0; k < img.channels; k++) {
                edges(i, j, k) = edge_color;
            }
        }
    }
    img = edges;
}
//filter 7

void Darken_and_lighten(Image &image) {
    int choice;
    cout << "1 - Lighten the image\n";
    cout << "2 - Darken the image\n";
    cin >> choice;

    if (choice != 1 && choice != 2) {
        cout << "Wrong choice.\n";
        return;
    }

    float factor = 0.5;
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                unsigned char &p = image(i, j, k);
                int newVal;

                if (choice == 1) {
                    newVal = p + (p * factor);
                    if (newVal > 255) newVal = 255;
                } else {
                    newVal = p - (p * factor);
                    if (newVal < 0) newVal = 0;
                }

                p = static_cast<unsigned char>(newVal);
            }
        }
    }

}
// Filter 15 - Infrared Effect bonus

void toInfrared(Image &image) {

    for (int i = 0; i < image.width; ++i) {

        for (int j = 0; j < image.height; ++j) {

            unsigned char r = image(i, j, 0);

            unsigned char g = image(i, j, 1);

            unsigned char b = image(i, j, 2);

            unsigned char gray = (r + g + b) / 3;

            image(i, j, 0) = 255;

            image(i, j, 1) = 255 - gray;

            image(i, j, 2) = 255 - gray;
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

//Filter 13 sunlight fix
void SunlightFix(Image &img, int brightnessValue) {
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < img.channels; k++) {
                int newValue = img(i, j, k) + brightnessValue;
                if (newValue > 255) newValue = 255;
                if (newValue < 0) newValue = 0;
                img(i, j, k) = newValue;
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






// filter 9--> frame

void complexFrame(Image &image) {
    for (int x = 0; x < image.width; x++) {
        for (int y = 0; y < image.height; y++) {
            if (x<3||y<3||x>image.width-1-3||y>image.height-1-3) {
                image(x,y,0)=255;

                image(x,y,1)=255;

                image(x,y,2)=255;
            }
            else if ((x<15&&x>=3)||(y<15&&y>=3)||(image.width-1-3>=x&&x>image.width-1-15)||(y>image.height-1-15&&y<=image.height-1-3)) {
                image(x,y,0)=0;

                image(x,y,1)=0;

                image(x,y,2)=255;
            }
        }
    }

    int x1=15,y1=15;
    int x2=image.width-1-15,y2=image.height-1-15;
    for (int y=y1; y<=y2; y++) {
        image(x1,y,0)=255;

        image(x1,y,1)=255;

        image(x1,y,2)=255;
    }
    for (int x=x1; x<=x2; x++) {
        image(x,y2,0)=255;

        image(x,y2,1)=255;

        image(x,y2,2)=255;
    }
    for (int x=x1; x<=x2; x++) {
        image(x,y1,0)=255;

        image(x,y1,1)=255;

        image(x,y1,2)=255;
    }
    for (int y=y1; y<=y2; y++) {
        image(x2,y,0)=255;

        image(x2,y,1)=255;

        image(x2,y,2)=255;
    }

    int x7=16,y7=16;
    int x8=image.width-1-16,y8=image.height-1-16;
    for (int y=y7; y<=y8; y++) {
        image(x7,y,0)=255;

        image(x7,y,1)=255;

        image(x7,y,2)=255;
    }
    for (int x=x7; x<=x8; x++) {
        image(x,y8,0)=255;

        image(x,y8,1)=255;

        image(x,y8,2)=255;
    }
    for (int x =x7; x<=x8; x++) {
        image(x,y7,0)=255;

        image(x,y7,1)=255;

        image(x,y7,2)=255;
    }
    for (int y=y7; y<=y8; y++) {
        image(x8,y,0)=255;

        image(x8,y,1)=255;

        image(x8,y,2)=255;
    }

    int x3=24,y3=24;
    int x4=image.width-1-24,y4=image.height-1-24;
    for (int y=y3; y<=y4; y++) {
        image(x3,y,0)=255;

        image(x3,y,1)=255;

        image(x3,y,2)=255;
    }
    for (int y=y3; y<=y4; y++) {
        image(x4,y,0)=255;

        image(x4,y,1)=255;

        image(x4,y,2)=255;
    }
    for (int x=x3; x<=x4; x++) {
        image(x,y3,0)=255;

        image(x,y3,1)=255;

        image(x,y3,2)=255;
    }
    for (int x=x3; x<=x4; x++) {
        image(x,y4,0)=255;

        image(x,y4,1)=255;

        image(x,y4,2)=255;
    }

    int x5=23,y5=23;
    int x6=image.width-1-23,y6=image.height-1-23;
    for (int y=y3; y<=y4; y++) {
        image(x5,y,0)=255;

        image(x5,y,1)=255;

        image(x5,y,2)=255;
    }
    for (int y=y5; y<=y6; y++) {
        image(x6,y,0)=255;

        image(x6,y,1)=255;

        image(x6,y,2)=255;
    }
    for (int x=x5; x<=x6; x++) {
        image(x,y5,0)=255;

        image(x,y5,1)=255;

        image(x,y5,2)=255;
    }
    for (int x=x5; x<=x6; x++) {
        image(x,y6,0)=255;

        image(x,y6,1)=255;

        image(x,y6,2)=255;
    }

}


void simpleFrame(Image &image) {
    for (int x = 0; x < image.width; x++) {
        for (int y = 0; y < image.height; y++) {
            if (x<5 || image.width-1-5<x|| y<5 || y>image.height - 1-5) {
                image(x,y,0)=255;

                image(x,y,1)=255;

                image(x,y,2)=255;
            }
            else if (x<25|| image.width-1-25<x|| y>image.height -1- 25|| y<25) {
                image(x,y,0)=0;

                image(x,y,1)=0;

                image(x,y,2)=255;
            }
        }
    }

}











// filter 12--> blur

void blurImage(Image &image) {
    Image NewImage(image.width, image.height);
    int size = 40;
    float diff = size / 2.0;

    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < 3; k++) {
                float sum = 0;
                for (int x = -diff; x <= diff; x++) {
                    for (int y = -diff; y <= diff; y++) {
                        if (i + x >= 0 && i + x < image.width && j + y >= 0 && j + y < image.height) {
                            sum += image(i + x, j + y, k);
                        }
                    }
                }
                int NewPex = sum / ((2 * diff + 1) * (2 * diff + 1));
                if (NewPex > 255) NewPex = 255;
                if (NewPex < 0) NewPex = 0;
                NewImage(i, j, k) = NewPex;
            }
        }
    }
    image = NewImage;

}





// filter 16 --> Purple

void Purple(Image &image) {
    Image Newimage(image.width, image.height);
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int red = image(i, j, 0);
            int green = image(i, j, 1);
            int blue = image(i, j, 2);

            green = green / 1.5;

            Newimage(i, j, 0) = red;
            Newimage(i, j, 1) = green;
            Newimage(i, j, 2) = blue;
        }
    }
    image = Newimage;

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

    cout << "9. Exit\n";

   cout << "10.Filter // Crop\n";

   cout << "11.Filter // Resize\n";

   cout << "12.Filter // SunlightFix\n";

   cout<<" 13. Filter // detect edges\n";

   cout << "14. Filter // Lighten or Darken\n";

   cout << "15. Filter // Infrared Effect\n";

   cout << "16. Filter // Frame Image\n";

   cout <<"17. Filter // Blur Image \n";

   cout << "18. Filter // Purple\n";

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

                }
                else if (choose == 'v' || choose == 'V'){

                    flipVertical(img);

                }
               break;
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
           case 10: {
              int x,y,w,h;

              cout <<" Enter x, y, width, height : ";
              cin >>x >>y >>w >>h;

              crop(img, x, y, w, h);

              cout<< " Crop is Done \n";
              break;
           }
           case 11:{
              int newW,newH;
              cout << " Enter new width and height: ";
              cin >> newW >> newH;
              resizeImage(img,newW,newH);
              cout<< " Resize is Done. \n";
              break;

           }
           case 12:{
              int brightness_val;
              cout <<"Enter Brightness Value (recommended 30 ---> 80): ";
              cin >> brightness_val;
              SunlightFix(img,brightness_val);
              cout <<"sunlight is fixed \n";
              break;
           }
           case 13:{
              detectEdges(img);
              cout << "Edge detection applied.\n";
             break;
               }
           case 14: {
               Darken_and_lighten(img);
               break;
            }
           case 15: {
                toInfrared(img);
                cout << "Infrared filter applied.\n";
                break;
            }
           case 16 :{
              cout << " What type of frame do you want ?\n 1--> simple\n 2--> complex\n";
              int frameChoice ;
              cin >> frameChoice ;
              if (frameChoice ==1){
                 simpleFrame(img);
                 cout << "Simple Frame filter applied.\n";
              }
              else if (frameChoice == 2) {
                  complexFrame(img);
                  cout << "complex Frame filter applied.\n";
              }
               else{
                   cout << "Invalid frame choice \n";
              }
               break;
           }

           case 17 :{

              blurImage(img);

              cout << "Blur filter applied. \n";

                 break;
           }
           case 18 :{

              Purple(img);

              cout << "Purple filter applied. \n ";

                 break;
           }




          default: cout << "Invalid choice!\n"; break;
        }
    }

    return 0;
}

