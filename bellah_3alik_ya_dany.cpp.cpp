// FCAI – Structured Programming – 2024 - Assignment 2
// Program Name: Cipher and Calculator Description
// Program Description: ………

// Author1 and ID and Group and email: جوليانو جوزيف كمال - 20230108 -s19-julianojoseph015@gmail.com
// Author2 and ID and Group and email: s19-داني اشرف عريان -20230133
// Teaching Assistant:
// Vigenere cipher by :Dany Ashraf
// XOR cipher by : Juliano Joseph
#include<iostream>
#include<cctype>
#include<string>
#include <iomanip>
#include <sstream>
#include <vector>
using namespace std;
void encryption33() {
    string A = "";
    string B = "";

    cout << "Enter the text: ";
    cin >> A;

    cout << "Enter the key: ";
    cin >> B;

    string result = "";

    // XOR characters sequentially from strings A and B, wrapping around if necessary
    for (size_t i = 0; i < max(A.length(), B.length()); ++i) {
        char xorResult = A[i % A.length()] ^ B[i % B.length()];
        // Convert the result to hexadecimal representation and add it to the result string
        stringstream ss;
        ss << hex << setw(2) << setfill('0') << static_cast<unsigned>(xorResult);
        result += ss.str() + " ";

        // Print xorResult
        cout << xorResult << " ";
    }

    // Print the result
    cout << endl << result << endl;
}
void decryption33() {
    string encrypted_hex = "";
    string key = "";

    // Input key
    cout << "Enter key: ";
    cin >> key;

    // Input encrypted message in hexadecimal
    cout << "Enter encrypted message in hexadecimal: ";
    cin.ignore(); // Ignore newline character left in the buffer
    getline(cin, encrypted_hex);

    // Convert the input hexadecimal characters to bytes
    stringstream ss(encrypted_hex);
    vector<unsigned char> encrypted_bytes;
    string byte_str;
    while (ss >> setw(2) >> byte_str) {
        unsigned char byte = stoi(byte_str, nullptr, 16);
        encrypted_bytes.push_back(byte);
    }

    // Repeat the key cyclically to match the length of the encrypted message
    string repeated_key;
    size_t key_length = key.length();
    for (size_t i = 0; i < encrypted_bytes.size(); ++i) {
        repeated_key += key[i % key_length];
    }

    // XOR characters sequentially from encrypted message and key
    string decrypted_message;
    for (size_t i = 0; i < encrypted_bytes.size(); ++i) {
        decrypted_message += (encrypted_bytes[i] ^ repeated_key[i]);
    }

    // Print the decrypted message
    cout << "Decrypted message: " << decrypted_message << endl;
}


struct message {
    string message;
    int length, space, maxlenght = 8, number_of_chars = 0;
    bool inWord = false;
};

struct v_encryption {
    string repeat_word, repeat_word2, encodedMessage;;
    int length;
    int repeatIndex = 0;
    int i = 0, digit = 0;
};

string getinput() {
    message input;
    cout << "Please enter the message: \n";
    do {
        cout << "Length of message should be less than 80 \n";
        cin.ignore();
        getline(cin, input.message);
        input.length = input.message.length();

    } while (input.length > 81);
    return input.message;
}

string encryption(const message& input) {
    v_encryption code;
    do {
        cout << "Please enter the repeated keyword (less than 8 characters): ";
        cin.ignore();
        getline(cin, code.repeat_word);
        code.length = code.repeat_word.length();
        for (char& c : code.repeat_word) {
            code.digit = 0;
            if (isalpha(c)) {
                if (islower(c)) {
                    c = toupper(c); // Convert lowercase alphabets to uppercase
                }
                code.repeat_word2 += c;
            }
            if (isdigit(c)) {
                code.digit += 1;
                cout << "Enter valid input(string) " << endl;
                break;

            }
        }
    } while (code.repeat_word2.length() > 8 || code.digit > 0);
    // Repeat the keyword if it's shorter than the message
    while (code.repeat_word2.length() < input.length) {
        code.repeat_word2 += code.repeat_word2;
    }
    // Trim extra characters if the repeated keyword is longer than the message
    code.repeat_word2 = code.repeat_word2.substr(0, input.length);
    return code.repeat_word2;
}
string final_code(const message& input, const v_encryption& repeat_word2) {
    v_encryption solve;

    for (char c : input.message) {
        if (isalpha(c)) {

            char encryptedChar = (c + repeat_word2.repeat_word2[solve.repeatIndex]) % 26 + 'A';
            solve.encodedMessage += encryptedChar;
            solve.repeatIndex++;
        }
        else if (isspace(c))
        {
            solve.encodedMessage += c;
            solve.repeatIndex++;
        }
        else
        {
            solve.encodedMessage += c;
        }
    }
    return solve.encodedMessage;
}


string decryption() {
    string decrypted_message = "";
    string repeat_word2;
    string repeat_word;
    string input;
    cout << "Please enter code: " << endl;
    cin.ignore();
    getline(cin, input);
    for (char c : input) {
        if (isalpha(c)) {
            if (islower(c)) {
                c = toupper(c);
            }
        }
    }

    do {
        cout << "Please enter the repeated keyword (less than 8 characters): ";
        getline(cin, repeat_word);
        repeat_word2 = "";
        for (char c : repeat_word) {
            if (isalpha(c)) {
                repeat_word2 += toupper(c); // Convert to uppercase
            }
            else {
                cout << "Invalid character. Please enter only alphabetic characters." << endl;
                repeat_word2 = ""; // Reset the repeat_word2
                break;
            }
        }
    } while (repeat_word2.length() > 8);

    // Repeat the keyword if it's shorter than the message
    while (repeat_word2.length() < input.length()) {
        repeat_word2 += repeat_word2;
    }
    // Trim extra characters if the repeated keyword is longer than the message
    repeat_word2 = repeat_word2.substr(0, input.length());

    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];
        if (isalpha(c)) {
            char decryptedChar = (c - repeat_word2[i % repeat_word2.length()] + 26) % 26 + 'A';
            if (islower(c)) {
                decryptedChar = toupper(decryptedChar); // Convert uppercase back to lowercase
            }
            decrypted_message += decryptedChar;
        }
        else {
            decrypted_message += c;
        }
    }

    return decrypted_message;
}











bool menu() {
    string user;
    bool valid = true; // Corrected variable name
    int answer;
    int answer2;
    cout << "Welcome\n";
    cout << "Enter your name: ";
    cin >> user;
    cin.ignore();
    cout << "Ahlan ya " << user << " ya habebi"<<endl;
    do {
        cout << "What do you like to do today?\n1- Cipher a message\n2- Decipher a message\n3- End\n";
        cin >> answer;
        cin.ignore();
        while (answer != 1 && answer != 2 && answer != 3) {
            cout << "Please enter valid input: ";
            cin.clear();
            cin.ignore();
            cin >> answer;
        }
        if (answer == 1 || answer == 2) {
            cout << "Which encryption method do you need?\n1- Vigenere\n2- XOR\n ";
            cin >> answer2;
            cin.ignore();
            while (answer2 != 1 && answer2 != 2) {
                cout << "Enter valid input: ";
                cin.clear();
                cin.ignore();
                cin >> answer2;
            }
        }

        if (answer == 1) {
            if (answer2 == 1) {
                message input;
                input.message = getinput();
                input.length = input.message.length();
                v_encryption repeat_word2;
                repeat_word2.repeat_word2 = encryption(input);
                cout << "Encrypted message: " << final_code(input, repeat_word2) << endl;
            }
            else if (answer2 == 2) {
                encryption33();
            }
        }
        else if (answer == 2) {
            if (answer2 == 1) {
                string decrypted_message = decryption();
                cout << "Decrypted message: " << decrypted_message << endl;
            }
            else if (answer2 == 2) {
                decryption33();
            }
        }
        else if (answer == 3) {
            valid = false;
        }
    } while (valid);
    return true;
}

int main() {
    menu();
    return 0;
}
