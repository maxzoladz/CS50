#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

bool only_digits(char c[]);
char rotate(char c, int n);

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

        int len = strlen(text);

        for(int i = 0; i < len; i++) {
            text[i] = rotate(text[i], value);
        }

        printf("Ciphertext: %s\n", text);

        return 0;
    }

}

bool only_digits(char c[]) {
    
    int length = strlen(c);
    bool answer = false;

    for(int i = 0; i < length; i++) {
        if(isdigit(c[i])) {
            answer = true;
        }
        else {
            answer = false;
        }
    }
    return answer;
}

char rotate(char c, int n) {

    while(n >= 25){
        n -= 25;
    }

    if((c >= 'A' && c <= 'Z' && c + n > 'Z') || (c >= 'a' && c <= 'z' && c + n > 'z')) {
        return c - n;
    }
    else if((c >= 'A' && c <= 'Z' && c + n < 'Z') || (c >= 'a' && c <= 'z' && c + n < 'z')) {
        return c = c + n;
    }
    else {
        return c;
    }
    
}