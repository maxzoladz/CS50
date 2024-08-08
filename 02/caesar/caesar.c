#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

bool only_digits(char text[]);
char rotate(char c, int rotationFactor);

int main(int argc, char *argv[]) {

    if(argc != 2 || !only_digits(argv[1])) {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else {
        
        int value = atoi(argv[1]);
        char text[100];

        printf("Text: ");
        fgets(text, sizeof(text), stdin);

        int textLength = strlen(text);

        for(int textIndex = 0; textIndex < textLength; textIndex++) {
            text[textIndex] = rotate(text[textIndex], value);
        }

        printf("Ciphertext: %s\n", text);

        return 0;
    }

}

bool only_digits(char text[]) {
    
    int textLength = strlen(text);
    bool answer = false;

    for(int textIndex = 0; textIndex < textLength; textIndex++) {
        if(isdigit(text[textIndex])) answer = true; 
        
        else answer = false;

    }
    return answer;
}

char rotate(char c, int rotationFactor) {

    while(rotationFactor >= 26){
        rotationFactor -= 26;
    }

    bool isUpperAlphabetical = c >= 'A' && c <= 'Z';
    bool isLowerAlphabetical = c >= 'a' && c <= 'z';

    if((isUpperAlphabetical && c + rotationFactor > 'Z') || (isLowerAlphabetical && c + rotationFactor > 'z')) {
        return c - rotationFactor;
    }
    else if((isUpperAlphabetical && c + rotationFactor < 'Z') || (isLowerAlphabetical && c + rotationFactor < 'z')) {
        return c = c + rotationFactor;
    }
    else {
        return c;
    }
    
}