#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool keyChecker(char c[]);

int main(int argc, char *argv[]) {

    if(argc != 2) {
        printf("Usage: ./caesar key\n");
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

        int len = strlen(text);

        for(int i = 0; i < len; i++) {
            if(text[i] >= 'a' && text[i] <= 'z') {
                text[i] = (argv[1][text[i] - 'a'] + 32);
            }
            else if(text[i] >= 'A' && text[i] <= 'Z') {
                text[i] = argv[1][text[i] - 'A'];
            }
        }

        printf("Ciphertext: %s\n", text);

        return  0;
    }
    
}

bool keyChecker(char c[]) {
    
    int len = strlen(c);

    for(int i = 0; i < len; i++) {
        if(!((c[i] >= 'a' && c[i] <= 'z') || (c[i] >= 'A' && c[i] <= 'Z'))) {
            return false;
        }
    }

    for(int j = 0; j < len; j++) {
        for(int k = j + 1; k < len; k++) {
            if(c[j] == c[k]) {
                return false;
            }
        }
    }

    return true;

}