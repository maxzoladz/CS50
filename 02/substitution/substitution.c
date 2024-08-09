#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool keyChecker(char key[]);

int main(int argc, char *argv[]) {

    if(argc != 2) {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if(strlen(argv[1]) != 26){
        printf("Invalid Key: Length of Key must be 26!\n");
        return 1;
    }
    else if(!(keyChecker(argv[1]))) {
        printf("Invalid Key: Key must only contain alphabetic characters, containing each letter once!\n");
        return 1;
    }
    else {
        char text[256];

        printf("Plaintext: ");
        fgets(text, sizeof(text), stdin);

        int textLength = strlen(text);

        for(int textIndex = 0; textIndex < textLength; textIndex++) {

            bool isLowerAlphabetical = text[textIndex] >= 'a' && text[textIndex] <= 'z';
            bool isUpperAlphabetical = text[textIndex] >= 'A' && text[textIndex] <= 'Z';

            if(isLowerAlphabetical) {
                text[textIndex] = (argv[1][text[textIndex] - 'a'] + 32);
            }
            else if(isUpperAlphabetical) {
                text[textIndex] = argv[1][text[textIndex] - 'A'];
            }
        }

        printf("Ciphertext: %s\n", text);

        return  0;
    }
    
}

bool keyChecker(char key[]) {
    
    int keyLength = strlen(key);

    for(int keyIndex = 0; keyIndex < keyLength; keyIndex++) {

        bool isAlphabetical = (key[keyIndex] >= 'a' && key[keyIndex] <= 'z') || (key[keyIndex] >= 'A' && key[keyIndex] <= 'Z');
        if(!(isAlphabetical)) return false;
    }

    for(int keyIndex = 0; keyIndex < keyLength; keyIndex++) {
        for(int nextKeyIndex = keyIndex + 1; nextKeyIndex < keyLength; nextKeyIndex++) {

            bool charIsDuplicate = key[keyIndex] == key[nextKeyIndex];
            if(charIsDuplicate) return false;
        }
    }

    return true;
}