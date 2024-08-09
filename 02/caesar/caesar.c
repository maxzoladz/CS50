#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

bool only_digits(char text[]);
char rotate(char letter, int rotationFactor);

int main(int argc, char *argv[]) {

    if(argc != 2 || !only_digits(argv[1])) {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else {
        
        int shiftValue = atoi(argv[1]);
        char text[100];

        printf("Text: ");
        fgets(text, sizeof(text), stdin);

        int textLength = strlen(text);

        for(int textIndex = 0; textIndex < textLength; textIndex++) {
            text[textIndex] = rotate(text[textIndex], shiftValue);
        }

        printf("Ciphertext: %s\n", text);

        return 0;
    }

}

bool only_digits(char text[]) {
    
    int textLength = strlen(text);
    bool answer = false;

    for(int textIndex = 0; textIndex < textLength; textIndex++) {
        if(!isdigit(text[textIndex])) return false; 
    }
    return true;
}

char rotate(char letter, int rotationFactor) {

    while(rotationFactor >= 26){
        rotationFactor -= 26;
    }

    bool isUpperAlphabetical = letter >= 'A' && letter <= 'Z';
    bool isLowerAlphabetical = letter >= 'a' && letter <= 'z';

    if((isUpperAlphabetical && letter + rotationFactor > 'Z') || (isLowerAlphabetical && letter + rotationFactor > 'z')) {
        return letter - rotationFactor;
    }
    else if((isUpperAlphabetical && letter + rotationFactor < 'Z') || (isLowerAlphabetical && letter + rotationFactor < 'z')) {
        return letter = letter + rotationFactor;
    }
    else {
        return letter;
    }
    
}