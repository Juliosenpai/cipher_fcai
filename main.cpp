#include <iostream>
#include "Image_Class.h"
using namespace std;
Image save_photo(Image& image) {
    string save, save_type;

    cout << "What is the name you want to save the image with? ";
    cin >> save;

    while (true) {
        cout << "What is the type you want to save the image with? ";
        cin >> save_type;
        if (save_type == "png" || save_type == "jpg" || save_type == "jpeg" || save_type == "bmp") {
            break; // Exit the loop if the type is valid
        } else {
            cout << "Invalid image type. Please enter one of: png, jpg, jpeg, bmp" << endl;
        }
    }

    save = save + "." + save_type;
    image.saveImage(save);
}

Image crop(Image &image) {
    int x,z,a,b;
    cout<<"enter the dimensions of the new photo (W then H)"<<endl;
    cin>>x>>z;
    cout<<"enter the pixel you want to start from (W then H)"<<endl;
    cin>>a>>b;
    Image image2(x,z);

    // Copying lower half of image to image2
    for (int i = 0; i < image2.width; ++i) {
        for (int j = 0; j < image2.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                // Accessing pixels within bounds of image
                unsigned int temp = image.getPixel(i, j, k);
                image2.setPixel(i, j, k, image.getPixel(a+i,  b+j, k));
            }
        }
    }

    // Save the cropped image
    save_photo(image2);
    return image2;
}


Image BW(Image &image) {
    // Convert the loaded image to grayscale
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int intensity = 0.3 * image.getPixel(i, j, 0) +
                                     0.59 * image.getPixel(i, j, 1) +
                                     0.11 * image.getPixel(i, j, 2);

            // Set all channels to the calculated intensity to convert to grayscale
            for (int k = 0; k < image.channels; ++k) {
                image.setPixel(i, j, k, intensity);
            }
        }
    }

    // Define a threshold value for the black and white conversion
    unsigned int threshold = 128;

    // Convert the grayscale image to black and white
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int total = 0;
            for (int k = 0; k < image.channels; ++k) {
                total += image.getPixel(i, j, k);
            }

            // Calculate the average intensity by dividing the total by the number of channels
            unsigned int average = total / image.channels;

            // Determine if the pixel should be white or black based on the threshold
            if (average >= threshold) {
                // Set the pixel to white
                for (int k = 0; k < image.channels; ++k) {
                    image.setPixel(i, j, k, 255); // Set all channels to 255 (white)
                }
            } else {
                // Set the pixel to black
                for (int k = 0; k < image.channels; ++k) {
                    image.setPixel(i, j, k, 0); // Set all channels to 0 (black)
                }
            }
        }
    }
    save_photo(image);
    return image;
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
    switch (filterChoice) {
        case 1:
            // Grayscale Conversion
            // Implement grayscale conversion
            break;
        case 2:
            BW(image);
            break;
        case 3:
            // Invert Image
            Invert_Image(image);
            break;
        case 4:
            // Crop Images
            crop(image);
            // Implement image cropping
            break;
        case 5:
            // Merge Images
            // Implement image merging
            break;
        case 6:
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

            break;
        default:
            cout << "Invalid filter choice. Please try again." << endl;
    }
}

void menu() {
    string name;
    int choice, no_filter;
    Image image;

    cout << "What's your name? ";
    getline(cin, name);
    cout << "Hello Dr, " << name << endl;

    while (true) {
        cout << "What do you want to do?" << endl;
        cout << "1. Load Image" << endl;
        cout << "2. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        while (!(choice > 0 && choice < 3)) {
            cout << "Please enter a valid input: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> choice;
        }

        if (choice == 1) {
            string first_name, type, image_name;
            cout << "Please enter name for image: ";
            cin >> first_name;
            cout << "Please enter type for image: ";
            cin >> type;
            image_name = first_name + "." + type;
            while (true) {
                try {
                    image.loadNewImage(image_name);
                    break;
                } catch (invalid_argument) {
                    cout << "Please enter a valid photo \n" << endl;
                    cout << "Please enter name for image:\n ";
                    cin >> first_name;
                    cout << "Please enter type for image:\n ";
                    cin >> type;
                    image_name = first_name + "." + type;
                }
            }

            while (true) {
                int choice2;
                cout << "1. Apply Filter" << endl;
                cout << "2. Save Image" << endl;
                cout << "3. Return to Main Menu" << endl;
                cout << "Enter your choice: ";
                cin >> choice2;

                while (!(choice2 > 0 && choice2 < 4)) {
                    cout << "Please enter a valid input: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> choice2;
                }

                if (choice2 == 1) {
                    cout << "You want me to filter" << endl;
                    cout << "1-Grayscale Conversion\n2-Black and White \n3-Invert Image\n4-Crop Images\n5-Merge Images\n6-Rotate Image";
                    cin >> no_filter;
                    while (!(no_filter > 0 && no_filter < 7)) {
                        cout << "Please enter a valid input: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin >> no_filter;
                    }
                    applyFilter(image, no_filter);
                } else if (choice2 == 2) {
                    save_photo(image);
                } else {
                    // Return to the main menu
                    break;
                }
            }
        } else {
            // Exit the loop
            break;
        }
    }
}

int main() {
    menu();
    return 0;
}