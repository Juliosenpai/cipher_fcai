#include <iostream>
#include "Image_Class.h"

using namespace std;
Image save_photo(Image& image){
    string save,save_type;
    cout << "What is the name you want to save the image with? ";
    cin >> save;
    cout<<"What is the type you want to save the image with? ";
    cin>>save_type;
    while(save_type!="png"||save_type !="bmp"||save_type!="tga"||save_type!="jpg"||save_type!="jpeg"){
        cout << "Please enter a valid type: ";
        cin.clear();
        cin >> save_type;
    }

    save=save+"."+save_type;
    image.saveImage(save);
}
Image Invert_Image(Image& image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                // Calculate negative value for each channel
                int neg_value = 255 - image(i, j, k);
                image(i, j, k) = neg_value;
            }
        }
    }
    save_photo(image);
    return image;
}

Image flip_90(Image &image) {
    Image flippedImage(image.height, image.width);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                flippedImage(j, image.width - i - 1, k) = image(i, j, k);
            }
        }
    }
    save_photo(flippedImage);
    return flippedImage;
}

// Function to flip the image by 180 degrees
Image flip_180(Image &image) {
    Image flippedImage(image.width, image.height); // Create a new image to store the flipped result

    // Flip the image 180 degrees
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                // Assign the pixel value from the transposed position to the flipped image
                flippedImage(image.width - i - 1, image.height - j - 1, k) = image(i, j, k);
            }
        }
    }
    save_photo(flippedImage);
    return flippedImage;
}

// Function to flip the image by 270 degrees
Image flip_270(Image &image) {
    Image flippedImage(image.height, image.width); // Create a new image to store the flipped result

    // Flip the image 270 degrees
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                // Assign the pixel value from the transposed position to the flipped image
                flippedImage(image.height - j - 1, i, k) = image(i, j, k);
            }
        }
    }
    save_photo(flippedImage);
    return flippedImage;
}


void applyFilter(Image& image, int filterChoice) {
    int answer;

    if (filterChoice==1){

    } else if (filterChoice==2){

    }else if(filterChoice==3){
        Invert_Image(image);
    } else if(filterChoice==4){

    } else if (filterChoice==5){

    } else{
        cout<<"How many degrees do you want to rotate the image ?\n1-90\n2-180\n3-270\n";
        cin>>answer;
        while(!(answer>0&&answer<4)){
            cout << "Please enter a valid input: ";
            cin.clear();
            cin >> answer;
        }
        if (answer==1){
            flip_90(image);
        }
        else if(answer==2){
            flip_180(image);
        } else{
            flip_270(image);
        }

    }
}

void menu() {
    string name, save,save_type;
    int choice, count = 0, no_filter;
    bool valid = true;
    Image image;

    cout << "What's your name? ";
    getline(cin, name);
    cout << "Hello Dr, " << name << endl;

    do {
        count = 0;
        if (count == 0) {
            cout << "What do you want to do?" << endl;
            cout << "1. Load Image" << endl;
            cout << "2. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            count++;
        }
        while (!(choice > 0 && choice < 3)) {
            cout << "Please enter a valid input: ";
            cin.clear();
            cin >> choice;
        }

        if (choice == 1) {
            string image_name;
            cout << "Please Enter Name of the Image with type (.png, .jpeg, .jpg, .bmp):";
            cin>>image_name;
            Image image;
            while(true){
                try {
                    image.loadNewImage(image_name);
                    break;
                } catch( invalid_argument) {
                    cout << "Please enter a valid photo \n" << endl;
                    cin>>image_name;
                }
            }
        } else {
            break;
        }
        if (count == 1) {
            cout << "1. Apply Filter" << endl;
            cout << "2. Save Image" << endl;
            cout << "3. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
        }
        while (!(choice > 0 && choice < 4)) {
            cout << "Please enter a valid input: ";
            cin.clear();
            cin >> choice;
        }

        if (choice == 1) {
            cout << "You want me to filter" << endl;
            cout << "1-Grayscale Conversion\n 2-Black and White \n3-Invert Image\n4-Crop Images\n5-Merge Images\n6-Rotate Image\n";
            cin >> no_filter;
            while (!(no_filter > 0 && no_filter < 7)) {
                cout << "Please enter a valid input: ";
                cin.clear();
                cin >> no_filter;
            }
            applyFilter(image, no_filter);
        } else if (choice == 2) {
            save_photo(image);
        } else {
            break;
        }
    } while (true);
}

int main() {
    menu();
    return 0;
}
